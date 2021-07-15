#include "sheet.h"
#include "cell.h"

#include <vector>

// #include "freeTry.h"
Sheet * pointer;

Sheet::Sheet(QWidget *parent)
    : QTableWidget(parent)
{
    autoRecalc = true;

    //��item��ԭ������ΪCell����
    setItemPrototype(new Cell);
    //ѡ��ģʽΪ��ContiguousSelection������������ѡ��򷽷�
    setSelectionMode(ContiguousSelection);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(somethingChanged()));

    //����clear()�����µ������ĳߴ��С���������б���
    clear();
    pointer = this;
}
//�õ���ǰλ��
QString Sheet::currentLocation() const
{
    return QChar('A' + currentColumn())
           + QString::number(currentRow() + 1);
}
//�õ���ǰѡ�е�Ԫ���λ��
QString Sheet::currentSelectedRange() const
{
    QTableWidgetSelectionRange range = selectedRange();
    // ���ֻ��һ����Ԫ��
    if(range.rowCount() == 1 && range.columnCount() == 1)
    return currentLocation();
    // �����Ԫ���ȡ"A999:B999"����ʽ��ʾ
    return QChar('A'+range.leftColumn()) + QString::number(range.topRow()+1)
            +':'
            +QChar('A'+range.rightColumn())+QString::number(range.bottomRow()+1);
}

//���ص�ǰ��Ԫ��Ĺ�ʽ
QString Sheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}

//�Զ���selectedRange(),���ڷ���ѡ�еı��Χ
QTableWidgetSelectionRange Sheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    if (ranges.isEmpty())
        return QTableWidgetSelectionRange();
    return ranges.first();
}

QString Sheet::selectedRangeQstr() const
{
    QTableWidgetSelectionRange range = selectedRange();
    QString rangeQstr = "";
    if (range.rowCount() == 1 && range.columnCount() == 1)
    {
        rangeQstr += QChar('A'+range.leftColumn());
        rangeQstr += QString::number(range.bottomRow() + 1);
    }
    else
    {
        rangeQstr += QChar('A'+range.leftColumn());
        rangeQstr += QString::number(range.topRow() + 1);
        rangeQstr += ":";
        rangeQstr += QChar('A'+range.rightColumn());
        rangeQstr += QString::number(range.bottomRow() + 1);
    }
    return rangeQstr;
}

void Sheet::clear()
{
    //�������Ϊ0��0�У�����������еı������
    setRowCount(0);
    setColumnCount(0);
    //�������ñ��Ĵ�СΪRowCount*ColumnCount
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        //����ˮƽ��������i��item��
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

//�Ӷ������ļ��ж�ȡ���ݲ�д������
bool Sheet::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Sheet"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_3);

    quint32 magic;
    in >> magic;
    if (magic != MagicNumber) {
        QMessageBox::warning(this, tr("Sheet"),
                             tr("The file is not a Sheet file."));
        return false;
    }

    clear();

    quint16 row;
    quint16 column;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);
    while (!in.atEnd()) {
        in >> row >> column >> str;
        setFormula(row, column, str);
    }
    QApplication::restoreOverrideCursor();
    return true;
}

//ͨ�������Ʒ�ʽд���ļ���
bool Sheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Sheet"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        return false;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_3);

    out << quint32(MagicNumber);

    //�������Ϊ�ȴ����(ͨ��Ϊɳ©��)
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            QString str = formula(row, column);
            if (!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }
    //�ӵȴ�����лָ�Ϊ�������
    QApplication::restoreOverrideCursor();
    return true;
}

void Sheet::sort(const SheetCompare &compare)
{
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for (i = 0; i < range.rowCount(); ++i) {
        QStringList row;
        for (int j = 0; j < range.columnCount(); ++j)
            row.append(formula(range.topRow() + i,
                               range.leftColumn() + j));
        rows.append(row);
    }

    qStableSort(rows.begin(), rows.end(), compare);

    for (i = 0; i < range.rowCount(); ++i) {
        for (int j = 0; j < range.columnCount(); ++j)
            setFormula(range.topRow() + i, range.leftColumn() + j,
                       rows[i][j]);
    }

    clearSelection();
    somethingChanged();
}

//cut = copy + del
void Sheet::cut()
{
    copy();
    del();
}

void Sheet::copy()
{
    //�����ڹ��캯����setSelectionMode(ContiguousSelection);��ѡ��Χ�޷�����1�����Զ���selectedRange()
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    //������֮����'\n'���ָ������֮����'\t'���ָ�
    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0)
            str += "\n";
        for (int j = 0; j < range.columnCount(); ++j) {
            if (j > 0)
                str += "\t";
            str += formula(range.topRow() + i, range.leftColumn() + j);
        }
    }
    //�ŵ����а�����
    QApplication::clipboard()->setText(str);
}

void Sheet::paste()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    //���ﲻ�����ܣ�����ѡ��һ����С�ķ�Χ����ճ����ȥ(excel��wpsֻҪѡ��һ����񼴿�)
    if (range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows
                || range.columnCount() != numColumns)) {
        QMessageBox::information(this, tr("Sheet"),
                tr("The information cannot be pasted because the copy "
                   "and paste areas aren't the same size."));
        return;
    }

    for (int i = 0; i < numRows; ++i) {
        QStringList columns = rows[i].split('\t');
        for (int j = 0; j < numColumns; ++j) {
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if (row < RowCount && column < ColumnCount)
                setFormula(row, column, columns[j]);
        }
    }
    somethingChanged();
}

void Sheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if (!items.isEmpty()) {
        foreach (QTableWidgetItem *item, items)
            delete item;	//ֱ���ͷ���Դ����
        somethingChanged();
    }
}
void Sheet::function(int index)
{

}

void Sheet::func()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString rangestr = selectedRangeQstr();
    QString str = "=";
    str += "sum";
    str += "(";
    str += selectedRangeQstr();
    str += ")";
    int numRows = range.rowCount();
    int numColumns = range.columnCount();
    if (numRows == 1)
    {
        setFormula(range.bottomRow(),range.rightColumn()+1,str);
    }
    else if (numColumns == 1)
    {
        setFormula(range.bottomRow()+1,range.rightColumn(),str);
    }
    else
    {
        setFormula(range.bottomRow()+1,range.rightColumn()+1,str);
    }

    somethingChanged();
}

void Sheet::selectCurrentRow()
{
    selectRow(currentRow());
}

void Sheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

void Sheet::recalculate()
{
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            if (cell(row, column))
                cell(row, column)->setDirty();	//���Ϊ���¼���
        }
    }
    //ͨ��update�����»����������ӱ��
    viewport()->update();
}

//�ж��Ƿ��Զ����¼��㲢����
void Sheet::setAutoRecalculate(bool recalc)
{
    autoRecalc = recalc;
    if (autoRecalc)
        recalculate();
}

void Sheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() + 1;

    while (row < RowCount) {
        while (column < ColumnCount) {
            if (text(row, column).contains(str, cs)) {
                //������
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }
    QApplication::beep();
}

void Sheet::findPrevious(const QString &str,
                               Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() - 1;

    while (row >= 0) {
        while (column >= 0) {
            if (text(row, column).contains(str, cs)) {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            --column;
        }
        column = ColumnCount - 1;
        --row;
    }
    QApplication::beep();
}

void Sheet::somethingChanged()
{
    if (autoRecalc)
        recalculate();
    emit modified();
}

Cell *Sheet::cell(int row, int column) const
{
    //����item��һ������
    return static_cast<Cell *>(item(row, column));
}

//�趨��ʽ
void Sheet::setFormula(int row, int column,
                             const QString &formula)
{
    Cell *c = cell(row, column);
    if (!c) {
        c = new Cell;
        setItem(row, column, c);
    }
    c->setFormula(formula);
}

//���ظ�����Ԫ���еĹ�ʽ-->�����ǹ�ʽ�Ľ��
QString Sheet::formula(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c) {
        return c->formula();
    } else {
        return "";
    }
}

//����row�У�column�е�����
QString Sheet::text(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c) {
        return c->text();
    } else {
        return "";
    }
}
// ��A1:B2��������ѹ��һ��QVector<double>����
QVector<double>  Sheet::textInRange(QString Range) const
{
    if(Range.indexOf(":") == -1)  // if there's : in the string, ��Ϊ A1 ����
    {
        int row,colume;
        char temp[5];
        sscanf(Range.toStdString().c_str(),"%[A-Z]%d",temp,&row);
        row --; // ��0��ʼ����
        // ����ֻ֧�ּ򵥵�һλת������AA1�������֧��
        colume = temp[0] -'A';
        QVector<double> ret;
        bool ok;

        double tempd = text(row,colume).toDouble(&ok);
        if(ok)
        ret.append(tempd);
        else
        ret.append(0); // ���ת��ʧ�ܵĻ�����һ��ֵֻ��0��double vector
        return ret;
    }
    // Range �ĸ�ʽ A1:B1
    int leftColume, rightColume, topRow, bottomRow;
    char temp1[5],temp2[5];
    sscanf(Range.toStdString().c_str(),"%[A-Z]%d:%[A-Z]%d",temp1,&topRow,temp2,&bottomRow);
    // ��0��ʼ����
    topRow--;
    bottomRow--;
    leftColume = temp1[0] - 'A';
    rightColume = temp2[0] - 'A';
    int columeCount = rightColume-leftColume+1;
    int rowCount = bottomRow - topRow +1;
    int len = columeCount * rowCount;
    QVector<double> ret;
    for (int i=0; i< len ; i++ ) {
        bool ok;
        double temp = text(topRow + i/columeCount,
                            leftColume+ i%columeCount).toDouble(&ok);
        if(ok)
        ret.append(temp);
        else
        ret.append(0);
    }

    return ret;
}
bool SheetCompare::operator()(const QStringList &row1,
                                    const QStringList &row2) const
{
    for (int i = 0; i < KeyCount; ++i) {
        int column = keys[i];
        if (column != -1) {
            if (row1[column] != row2[column]) {
                if (ascending[i]) {
                    return row1[column] < row2[column];
                } else {
                    return row1[column] > row2[column];
                }
            }
        }
    }
    return false;
}
