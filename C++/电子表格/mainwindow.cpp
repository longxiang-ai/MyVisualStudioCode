#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tw=new TableWidget(ROW_MAX,COL_MAX,this);
    /*
    tw->setStyleSheet(
        //"color:black;"
        //"gridline-color:black;"
        "background:azure;"
        //"selection-color:yellow;"
        "border:2px solid azure;"
    );
    */
    setCentralWidget(tw);
    initTable();
    //setFocusPolicy(Qt::NoFocus);
    createMenus();
    createToolBars();
    createStatusBar();
    createActions();
    createButtons();

    createFilter();
    paintSelRange();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 21/6/4 Initialize Table
void MainWindow::initTable()
{
    for(int i = 0; i < ROW_MAX; i++) {
        for(int j = 0; j < COL_MAX; j++) {
            tw->setCurrentCell(i,j);
        }
    }
}


void MainWindow::createMenus(){
    mb=new QMenuBar(this);
    setMenuBar(mb);
    fileMenu = mb->addMenu("文件");
    openAction =fileMenu->addAction("打开");
    saveAction =fileMenu->addAction("保存");
    curFile = "未命名.tb";
    QMenu * editMenu = mb->addMenu("编辑");
    findAction = editMenu->addAction("查找/替换");
    formatAction = editMenu->addAction("数据格式");

}

void MainWindow::createToolBars(){
    tb=new QToolBar(this);
    addToolBar( Qt::TopToolBarArea,tb);
    unionbtn=new QPushButton(this);
    unionbtn->setText("合并单元格");
    tb->addWidget(unionbtn);
    splitbtn=new QPushButton(this);
    splitbtn->setText("拆分单元格");
    tb->addWidget(splitbtn);
    leftbtn=new QPushButton(this);
    leftbtn->setText("左对齐");
    tb->addWidget(leftbtn);
    rightbtn=new QPushButton(this);
    rightbtn->setText("右对齐");
    tb->addWidget(rightbtn);
    sethbtn=new QPushButton(this);
    sethbtn->setText("设置行高");
    tb->addWidget(sethbtn);
    setwbtn=new QPushButton(this);
    setwbtn->setText("设置列宽");
    tb->addWidget(setwbtn);
    hideCbtn=new QPushButton(this);
    hideCbtn->setText("隐藏列");
    tb->addWidget(hideCbtn);
    notHideCbtn=new QPushButton(this);
    notHideCbtn->setText("取消隐藏列");
    tb->addWidget(notHideCbtn);
    hideRbtn=new QPushButton(this);
    hideRbtn->setText("隐藏行");
    tb->addWidget(hideRbtn);
    notHideRbtn=new QPushButton(this);
    notHideRbtn->setText("取消隐藏行");
    tb->addWidget(notHideRbtn);
}

void MainWindow::createStatusBar(){
    //设置状态栏
    label=new QLabel("提示信息",this);
    stBar = statusBar();
    setStatusBar(stBar);
    stBar->addWidget(label);
}

void MainWindow::createActions(){
    //打开文件
    connect(openAction,&QAction::triggered,this,[=](){
        qDebug()<<"OpenFile called.";
        QString fileName = QFileDialog::getOpenFileName(this,tr("打开文件"), ".",tr("表格文件 (*.tb)"));
        if (!fileName.isEmpty())
            if (!readFile(tw,fileName)) {
                qDebug()<<"OpenFile Error.";
            }
        curFile = fileName;
    });
    //保存文件
    connect(saveAction,&QAction::triggered,this,[=](){
        qDebug()<<"SaveFile called.";
        if (curFile.isEmpty()) {
            qDebug()<<"Current File is empty.";
        } else {
            QString filename = QFileDialog::getSaveFileName(this,tr("保存文件"), ".",tr("表格文件 (*.tb)"));
            writeFile(tw,filename);
        }
    });
    //查找与替换
    connect(findAction,&QAction::triggered,this,[=](){
        //创建对话框及其控件
        QDialog * findDlg = new QDialog(this);
        findDlg->setWindowTitle("查找/替换");
        findDlg->setFixedSize(400,250);
        findDlg->show();
        findDlg->raise();
        findDlg->activateWindow();
        //控件
        QLabel *labelFind = new QLabel("查找内容：",findDlg);
        QLabel *labelReplace = new QLabel("替换为：",findDlg);
        QPushButton *btnFind = new QPushButton("查找/替换",findDlg);
        QPushButton *btnCancel = new QPushButton("关闭",findDlg);
        QLineEdit *lineEditFind = new QLineEdit(findDlg);
        QLineEdit *lineEditReplace = new QLineEdit(findDlg);
        labelFind->setGeometry(40,40,120,30);
        labelReplace->setGeometry(40,90,120,30);
        lineEditFind->setGeometry(150,40,200,30);
        lineEditReplace->setGeometry(150,90,200,30);
        btnFind->setGeometry(140,140,120,40);
        btnCancel->setGeometry(140,190,120,40);

        labelFind->show();
        labelReplace->show();
        btnFind->show();
        btnCancel->show();
        lineEditFind->show();
        lineEditReplace->show();

        //获取当前选中位置
//        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
//        int left=ranges.at(0).leftColumn();
//        int right=ranges.at(0).rightColumn();
//        int top=ranges.at(0).topRow();
//        int bottom=ranges.at(0).bottomRow();

        connect(btnCancel,&QPushButton::clicked,findDlg,&QDialog::close);
        connect(btnFind,&QPushButton::clicked,this,[=](){
            qDebug()<<"findNext called.";

            QString strFind = lineEditFind->text();
            QString strRep = lineEditReplace->text();
            qDebug()<<"string="<<strFind;
            if(strRep.size() != 0)qDebug()<<"new string="<<strRep;

            int row = tw->currentRow();
            int column = tw->currentColumn();
            while (row < ROW_MAX) {
                while (column < COL_MAX) {
                    QTableWidgetItem *itemCur = tw->item(row,column);
                    if(itemCur==NULL);
                    else{
                        QString strCur = itemCur->text().trimmed();
                        if(strCur==strFind){
                            if(strRep.size() != 0){
                                itemCur->setText(strRep);
                            }
                            //清除光标
                            tw->clearSelection();
                            tw->setCurrentCell(row, column);

                            activateWindow();
                            return;
                        }
                    }
                    ++column;
                }
                column = 0;
                ++row;
            }//end while loop
        });//end connect btnfind
    });//end connect dialog
}
void MainWindow::createButtons(){
    connect(unionbtn,&QPushButton::clicked,tw,[=](){
        //合并单元格
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        int left=ranges.at(0).leftColumn();
        int right=ranges.at(0).rightColumn();
        int top=ranges.at(0).topRow();
        int bottom=ranges.at(0).bottomRow();
        for(auto range:ranges)
        {
           if(range.topRow()<top)top=range.topRow();
           if(range.bottomRow()>bottom)bottom=range.bottomRow();
           if(range.leftColumn()<left)left=range.leftColumn();
           if(range.rightColumn()>right)right=range.rightColumn();
        }
        qDebug()<<left<<" "<<right<<" "<<top<<" "<<bottom;
        tw->setSpan(top, left, bottom-top+1, right-left+1);

    });
    connect(splitbtn,&QPushButton::clicked,tw,[=](){
        //拆分单元格
        tw->clearSpans();

    });

    connect(leftbtn,&QPushButton::clicked,tw,[=](){
        //左对齐
        QList<QTableWidgetItem*> items = tw->selectedItems();
        int count = items.count();
        for(int i = 0; i < count; i++)
        {
            QTableWidgetItem *item = items.at(i);
            item->setTextAlignment(0x0001|0x0080); //左对齐,垂直方向居中
        }

    });
    connect(rightbtn,&QPushButton::clicked,tw,[=](){
        //右对齐
        QList<QTableWidgetItem*> items = tw->selectedItems();
        int count = items.count();
        for(int i = 0; i < count; i++)
        {
            QTableWidgetItem *item = items.at(i);
            item->setTextAlignment(	0x0002|0x0080); //右对齐,垂直方向居中
        }

    });
    connect(sethbtn,&QPushButton::clicked,tw,[=](){
        // 设置行高，获取整数
        bool ok;
        int value = QInputDialog::getInt(this, tr("行高"), tr("请输入0到1000之间的整数"), 10, 0, 1000, 1, &ok);
        if(ok) qDebug() << "value:" << value;
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.topRow();i<=range.bottomRow();i++){
                tw->setRowHeight(i,value);
            }
        }

    });
    connect(setwbtn,&QPushButton::clicked,tw,[=](){
        // 设置列宽，获取整数
        bool ok;
        int value = QInputDialog::getInt(this, tr("列宽"), tr("请输入0到1000之间的整数"), 10, 0, 1000, 1, &ok);
        if(ok) qDebug() << "value:" << value;
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.leftColumn();i<=range.rightColumn();i++){
                tw->setColumnWidth(i,value);
            }
        }

    });
    connect(hideCbtn,&QPushButton::clicked,tw,[=](){
        //隐藏列
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.leftColumn();i<=range.rightColumn();i++){
                tw->setColumnHidden(i, true);
            }
        }

    });
    connect(notHideCbtn,&QPushButton::clicked,tw,[=](){
        //取消隐藏列
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.leftColumn();i<=range.rightColumn();i++){
                tw->setColumnHidden(i, false);
            }
        }

    });
    connect(hideRbtn,&QPushButton::clicked,tw,[=](){
        //隐藏行
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.topRow();i<=range.bottomRow();i++){
                tw->setRowHidden(i, true);
            }
        }
    });
    connect(notHideRbtn,&QPushButton::clicked,tw,[=](){
        //取消隐藏行
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        for(auto range:ranges)
        {
            int i;
            for(i=range.topRow();i<=range.bottomRow();i++){
                tw->setRowHidden(i, false);
            }
        }
    });
}
//从二进制文件中读取数据并写入表格中
bool MainWindow::readFile(TableWidget *tw,const QString &fileName)
{
    qDebug()<<"readFile called.";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("出错了！"),
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
        QMessageBox::warning(this, tr("出错了！"),
                             tr("The file is not a Table file."));
        return false;
    }

    tw->clear();

    quint16 row;
    quint16 column;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    while (!in.atEnd()) {
        in >> row >> column >> str;
        qDebug()<<"Read in:"<<row<<" "<<column<<" "<<str;
        //读入字符串
        if(tw==NULL){
            qDebug()<<"tw is null.";
        }else{
            QTableWidgetItem *itemCur = tw->item(row,column);
            if(itemCur==NULL){
                qDebug()<<"pos null.";
                itemCur = new QTableWidgetItem(str);
            }else{
                itemCur->setText(str);
            }
            tw->setItem(row,column,itemCur);
        }
    }
    QApplication::restoreOverrideCursor();
    return true;
}

//通过二进制方式写入文件中
bool MainWindow::writeFile(TableWidget *tw,const QString &fileName)
{
    qDebug()<<"writeFile called.";
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("出错了！"),
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
    int row,column;
    for (row = 0; row < ROW_MAX; ++row) {
        for (column = 0; column < COL_MAX; ++column) {
            //向文件中写入字符串
            if(tw==NULL)qDebug()<<"TableWidget is NULL.";
            else{
                QTableWidgetItem *item0 = tw->item(row,column);
//                qDebug()<<"Pos:"<<row<<" "<<column;
                //out<<item0;
                if(item0==NULL)qDebug()<<"item is NULL.";
                else{
                    QString str = item0->text().trimmed();
                    if (!str.isEmpty())
                        out << quint16(row) << quint16(column) << str;
                }
            }
        }
    }
    //从等待光标中恢复为正常光标
    QApplication::restoreOverrideCursor();
    return true;
}



// Below is the part of data filter
// Last Change Time: 21/6/3

// sort row in descend order
// by comparing values
// in operated column
void MainWindow::descendSort()
{
    QWidget* curBtn = QApplication::focusWidget();
    if(!curBtn) return;
    int x = curBtn->frameGeometry().x();
    int y = curBtn->frameGeometry().y();
    int row = tw->indexAt(QPoint(x,y)).row();
    int col = tw->indexAt(QPoint(x,y)).column();
    //tw->sortItems(col, Qt::DescendingOrder);
    int sortCnt = 0;
    for(int i = row+1; tw->item(i, col); i++, sortCnt++);
    for(int i = 0; i < sortCnt; i++) {
      for(int j = 0; j < sortCnt-i-1; j++) {
          int row1 = row+1 + j;
          int row2 = row+1 + j + 1;
          //if(tw->item(row1, col)->text().size()==0 || tw->item(row2, col)->text().size()==0) break;
          if(tw->item(row2, col)->text().toDouble() > tw->item(row1, col)->text().toDouble()) {
              for(int k = menuCol[0]; k <= menuCol[menuCol.size()-1];k++) {
                  QTableWidgetItem* temp = new QTableWidgetItem();
                  temp->setText(tw->item(row1, k)->text());
                  tw->item(row1, k)->setText(tw->item(row2, k)->text());
                  tw->item(row2, k)->setText(temp->text());
              }
          }

      }
    }
}


// sort row in ascend order
// by comparing values
// in operated column
void MainWindow::ascendSort()
{
    QWidget* curBtn = QApplication::focusWidget();
    if(!curBtn) return;
    int x = curBtn->frameGeometry().x();
    int y = curBtn->frameGeometry().y();
    int row = tw->indexAt(QPoint(x,y)).row();
    int col = tw->indexAt(QPoint(x,y)).column();
    //tw->sortItems(col, Qt::DescendingOrder);
    int sortCnt = 0;
    for(int i = row+1; tw->item(i, col); i++, sortCnt++);
    for(int i = 0; i < sortCnt; i++) {
      for(int j = 0; j < sortCnt-i-1; j++) {
          int row1 = row+1 + j;
          int row2 = row+1 + j + 1;
          //if(tw->item(row1, col)->text().size()==0 || tw->item(row2, col)->text().size()==0) break;
          if(tw->item(row2, col)->text().toDouble() < tw->item(row1, col)->text().toDouble()) {
              for(int k = menuCol[0]; k <= menuCol[menuCol.size()-1];k++) {
                  QTableWidgetItem* temp = new QTableWidgetItem();
                  temp->setText(tw->item(row1, k)->text());
                  tw->item(row1, k)->setText(tw->item(row2, k)->text());
                  tw->item(row2, k)->setText(temp->text());
              }
          }

      }
    }
}


void MainWindow::conductFilter()
{
    QString valStr = valueEdit->text();
    if(valStr.size()==0) {
        equalDlg->close();
        return;
    }
    double value = valStr.toDouble();
    QString conditionStr = conditionCom->currentText();
    equalDlg->close();

    if(!curWidget) return;
    int x = curWidget->frameGeometry().x();
    int y = curWidget->frameGeometry().y();
    int row = tw->indexAt(QPoint(x,y)).row();
    int col = tw->indexAt(QPoint(x,y)).column();
    int filterCnt = 0;
    for(int i = row+1; tw->item(i, col); i++, filterCnt++);

    // show all rows before filter
    for(int i = 0; i < filterCnt; i++) {
        int curRow = row+1 + i;
        tw->setRowHidden(curRow, false);
    }

    // start filtering
    for(int i = 0; i < filterCnt; i++) {
        int curRow = row+1 + i;
        if(conditionStr=="等于") {
            if(tw->item(curRow,col)->text().toDouble() != value) {
                tw->setRowHidden(curRow, true);
            }
        }
        else if(conditionStr=="不等于") {
            if(tw->item(curRow,col)->text().toDouble() == value) {
                tw->setRowHidden(curRow, true);
            }
        }
        else if(conditionStr=="大于") {
            if(tw->item(curRow,col)->text().toDouble() <= value) {
                tw->setRowHidden(curRow, true);
            }
        }
        else if(conditionStr=="小于") {
            if(tw->item(curRow,col)->text().toDouble() >= value) {
                tw->setRowHidden(curRow, true);
            }
        }
    }
}


// create a dialog for user to
// input filtered value
void MainWindow::equalFilter()
{
    curWidget = QApplication::focusWidget();
    // create dialog
    equalDlg = new QDialog(this);
    equalDlg->setWindowTitle("条件筛选");
    equalDlg->setFixedSize(400,230);
    equalDlg->show();
    equalDlg->raise();
    equalDlg->activateWindow();
    // widget in dialog
    conditionCom = new QComboBox(equalDlg);
    conditionCom->setGeometry(35,90,70,25);
    conditionCom->addItem("等于");
    conditionCom->addItem("不等于");
    conditionCom->addItem("大于");
    conditionCom->addItem("小于");
    conditionCom->show();
    valueEdit = new QLineEdit(equalDlg);
    valueEdit->setGeometry(120,90,230,25);
    valueEdit->show();
    QPushButton* filterYes = new QPushButton("确定", equalDlg);
    QPushButton* filterCan = new QPushButton("取消", equalDlg);
    filterYes->setGeometry(220,190,80,30);
    filterCan->setGeometry(310,190,80,30);
    filterYes->show();
    filterYes->setShortcut(Qt::Key_Enter);
    filterCan->show();

    connect(filterYes,SIGNAL(clicked()),this,SLOT(conductFilter()));
    connect(filterCan,SIGNAL(clicked()),equalDlg,SLOT(close()));
}

void MainWindow::clearFilter()
{
    QWidget* curBtn = QApplication::focusWidget();
    if(!curBtn) return;
    int x = curBtn->frameGeometry().x();
    int y = curBtn->frameGeometry().y();
    int row = tw->indexAt(QPoint(x,y)).row();
    int col = tw->indexAt(QPoint(x,y)).column();
    int filterCnt = 0;
    for(int i = row+1; tw->item(i, col); i++, filterCnt++);

    // show all rows
    for(int i = 0; i < filterCnt; i++) {
        int curRow = row+1 + i;
        tw->setRowHidden(curRow, false);
    }
}


void MainWindow::on_dataFilterAction_triggered(bool checked)
{
    // Addition: 21/6/2
    // create a filter menu
    // filter menu over table unit
    // unchecked -> checked: create menu
    if(checked) {
        QList<QTableWidgetSelectionRange>ranges=tw->selectedRanges();
        int leftCol = ranges.at(0).leftColumn();
        int rightCol = ranges.at(ranges.size()-1).rightColumn();
        int top = ranges.at(0).topRow();
        for(int i = leftCol; i <= rightCol; i++) {
            int menuCnt = i - leftCol;
            // open button & menu
            openMenuBtnList.push_back(new QPushButton());
            dataFilterMenuList.push_back(new QMenu());
            openMenuBtnList[menuCnt]->setMenu(dataFilterMenuList[menuCnt]);
            dataFilterSelActionList.push_back(new QAction(dataFilterMenuList[menuCnt]));
            /* sort */
            // descend: trigger means sort and no state is recorded
            descendOrderActionList.push_back(new QAction("降序"));
            descendOrderActionList[menuCnt]->setCheckable(0);
            descendOrderActionList[menuCnt]->setToolTip("降序");
            dataFilterMenuList[menuCnt]->addAction(descendOrderActionList[menuCnt]);
            connect(descendOrderActionList[menuCnt],SIGNAL(triggered()),this,SLOT(descendSort()));
            // ascend: trigger means sort and no state is recorded
            ascendOrderActionList.push_back(new QAction("升序"));
            dataFilterMenuList[menuCnt]->addAction(ascendOrderActionList[menuCnt]);
            ascendOrderActionList[menuCnt]->setCheckable(0);
            ascendOrderActionList[menuCnt]->setToolTip("升序");
            dataFilterMenuList[menuCnt]->addAction(ascendOrderActionList[menuCnt]);
            connect(ascendOrderActionList[menuCnt],SIGNAL(triggered()),this,SLOT(ascendSort()));
            /* filter */
            // conditional filter: trigger means opening a dialog
            condiFilterActionList.push_back(new QAction("筛选"));
            condiFilterActionList[menuCnt]->setCheckable(0);
            condiFilterActionList[menuCnt]->setToolTip("筛选");
            dataFilterMenuList[menuCnt]->addAction(condiFilterActionList[menuCnt]);
            connect(condiFilterActionList[menuCnt],SIGNAL(triggered()),this,SLOT(equalFilter()));
            // clear: trigger means clear filter done before
            clearActionList.push_back(new QAction("清除筛选"));
            clearActionList[menuCnt]->setCheckable(0);
            clearActionList[menuCnt]->setToolTip("清除筛选");
            dataFilterMenuList[menuCnt]->addAction(clearActionList[menuCnt]);
            connect(clearActionList[menuCnt],SIGNAL(triggered()),this,SLOT(clearFilter()));

            menuRow.push_back(top);
            menuCol.push_back(i);
            tw->setCellWidget(top, i, openMenuBtnList[menuCnt]);
        }

    }
    // checked -> unchecked: destroy menu
    else {
        int size = openMenuBtnList.size();
        for(int i = 0; i < size; i++) {
            removeAction(descendOrderActionList[i]);
            removeAction(ascendOrderActionList[i]);
            removeAction(condiFilterActionList[i]);
            removeAction(dataFilterSelActionList[i]);
            openMenuBtnList[i]->setMenu(nullptr);
            tw->removeCellWidget(menuRow[i], menuCol[i]);
        }
        // reset
        descendOrderActionList.clear();
        ascendOrderActionList.clear();
        condiFilterActionList.clear();
        clearActionList.clear();
        dataFilterSelActionList.clear();
        dataFilterMenuList.clear();
        openMenuBtnList.clear();

        menuRow.clear();
        menuCol.clear();
    }
}

void MainWindow::createFilter()
{
    // Addition: 21/6/2
    // extra independent menu in selected row for data filter
    // NOTE: only one row of data filter is allowed to exist
    // data filter is regard as action
    // SET ATTRIBUTES OF DATA FILTER ACTION
    dataFilterAction=new QAction(this);
    dataFilterAction->setText("数据过滤");
    dataFilterAction->setCheckable(1);
    QIcon filterIcon("filter.bmp");
    dataFilterAction->setIcon(filterIcon);
    dataFilterAction->setToolTip("数据过滤");
    tb->addAction(dataFilterAction);

    connect(dataFilterAction,SIGNAL(triggered(bool)),this, SLOT(on_dataFilterAction_triggered(bool)));
}



