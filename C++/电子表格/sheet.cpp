#include "sheet.h"
#include "cell.h"

#include <vector>

// #include "freeTry.h"
Sheet * pointer;

Sheet::Sheet(QWidget *parent)
    : QTableWidget(parent)
{
    autoRecalc = true;

    //将item的原型设置为Cell类型
    setItemPrototype(new Cell);
    //选择模式为：ContiguousSelection，则允许单矩形选择框方法
    setSelectionMode(ContiguousSelection);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem *)),
            this, SLOT(somethingChanged()));

    //调用clear()来重新调整表格的尺寸大小并且设置列标题
    clear();
    pointer = this;
}
//得到当前位置
QString Sheet::currentLocation() const
{
    return QChar('A' + currentColumn())
           + QString::number(currentRow() + 1);
}
//得到当前选中单元格的位置
QString Sheet::currentSelectedRange() const
{
    QTableWidgetSelectionRange range = selectedRange();
    // 如果只有一个单元格
    if(range.rowCount() == 1 && range.columnCount() == 1)
    return currentLocation();
    // 多个单元格采取"A999:B999"的形式显示
    return QChar('A'+range.leftColumn()) + QString::number(range.topRow()+1)
            +':'
            +QChar('A'+range.rightColumn())+QString::number(range.bottomRow()+1);
}

//返回当前单元格的公式
QString Sheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}

//自定义selectedRange(),用于返回选中的表格范围
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
    //调整表格为0行0列，做到清空所有的表格内容
    setRowCount(0);
    setColumnCount(0);
    //重新设置表格的大小为RowCount*ColumnCount
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for (int i = 0; i < ColumnCount; ++i) {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A' + i)));
        //设置水平标题栏列i到item中
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

//从二进制文件中读取数据并写入表格中
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

//通过二进制方式写入文件中
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

    //光标设置为等待光标(通常为沙漏型)
    QApplication::setOverrideCursor(Qt::WaitCursor);
    for (int row = 0; row < RowCount; ++row) {
        for (int column = 0; column < ColumnCount; ++column) {
            QString str = formula(row, column);
            if (!str.isEmpty())
                out << quint16(row) << quint16(column) << str;
        }
    }
    //从等待光标中恢复为正常光标
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
    //由于在构造函数中setSelectionMode(ContiguousSelection);则选择范围无法大于1，需自定义selectedRange()
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    //行与行之间用'\n'来分割，列与列之间用'\t'来分割
    for (int i = 0; i < range.rowCount(); ++i) {
        if (i > 0)
            str += "\n";
        for (int j = 0; j < range.columnCount(); ++j) {
            if (j > 0)
                str += "\t";
            str += formula(range.topRow() + i, range.leftColumn() + j);
        }
    }
    //放到剪切板上面
    QApplication::clipboard()->setText(str);
}

void Sheet::paste()
{
    QTableWidgetSelectionRange range = selectedRange();
    QString str = QApplication::clipboard()->text();
    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;

    //这里不够智能，必须选定一样大小的范围才能粘贴上去(excel和wps只要选定一个表格即可)
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
            delete item;	//直接释放资源即可
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
                cell(row, column)->setDirty();	//标记为重新计算
        }
    }
    //通过update来重新绘制整个电子表格
    viewport()->update();
}

//判断是否自动重新计算并更新
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
                //清除光标
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
    //这里item是一个函数
    return static_cast<Cell *>(item(row, column));
}

//设定公式
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

//返回给定单元格中的公式-->返回是公式的结果
QString Sheet::formula(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c) {
        return c->formula();
    } else {
        return "";
    }
}

//返回row行，column列的数据
QString Sheet::text(int row, int column) const
{
    Cell *c = cell(row, column);
    if (c) {
        return c->text();
    } else {
        return "";
    }
}
// 将A1:B2处的数据压成一个QVector<double>返回
QVector<double>  Sheet::textInRange(QString Range) const
{
    if(Range.indexOf(":") == -1)  // if there's : in the string, 则为 A1 类型
    {
        int row,colume;
        char temp[5];
        sscanf(Range.toStdString().c_str(),"%[A-Z]%d",temp,&row);
        row --; // 从0开始计数
        // 现在只支持简单的一位转换，如AA1的情况不支持
        colume = temp[0] -'A';
        QVector<double> ret;
        bool ok;

        double tempd = text(row,colume).toDouble(&ok);
        if(ok)
        ret.append(tempd);
        else
        ret.append(0); // 如果转换失败的话返回一个值只有0的double vector
        return ret;
    }
    // Range 的格式 A1:B1
    int leftColume, rightColume, topRow, bottomRow;
    char temp1[5],temp2[5];
    sscanf(Range.toStdString().c_str(),"%[A-Z]%d:%[A-Z]%d",temp1,&topRow,temp2,&bottomRow);
    // 从0开始计数
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
