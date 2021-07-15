#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include<QPushButton>
#include <QClipboard>
#include <QFileDialog>
#include<QString>
#include<QMenuBar>
#include<QTextEdit>
#include<QToolBar>
#include<QAbstractItemView>
#include<QDebug>
#include<QStatusBar>
#include<QLabel>
#include<QLayout>
#include <QInputDialog>
#include <QAction>
// 21/6/3
#include<QDialog>
#include<QComboBox>
#include<QItemDelegate>
#include<QPainter>
#include<QTableView>
#include<QRect>
#include<QWidget>
#include<QStyledItemDelegate>
#include<QItemDelegate>
#define ROW_MAX 100
#define COL_MAX 100
#define MagicNumber 0x7F51C883

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(int x,int y,QWidget* parent) : QTableWidget(x,y,parent) {}
    void paintEvent(QPaintEvent* event) Q_DECL_OVERRIDE;
private slots:
    void paintRange(QItemSelection selected, QItemSelection deselected);
private:
    // 21/6/3 paint range
    QRect SelRange;
    QList<QModelIndex> topBorder;
    QList<QModelIndex> bottomBorder;
    QList<QModelIndex> leftBorder;
    QList<QModelIndex> rightBorder;
};


class selectedRange : public QStyledItemDelegate
{
public:
    void paint(QPainter* painter, const QStyleOptionViewItem& option,
               const QModelIndex& index) const Q_DECL_OVERRIDE;
    void paintSelRange(QPainter* painter, const QRect& rect, const QModelIndex& index) const;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private:
    // 21/6/4 initialize table
    void initTable();

    void createButtons();
    void createToolBars();
    void createMenus();
    void createActions();
    void createStatusBar();
    // 21/6/2 create data filter
    void createFilter();
    // 21/6/3 paint Selection Range
    void paintSelRange();


    bool readFile(TableWidget *tw,const QString &fileName);
    bool writeFile(TableWidget *tw,const QString &fileName);
    TableWidget *tw;
    QString curFile;
    QMenuBar *mb;
    QMenu * fileMenu;
    QMenu * editMenu;
    // 21/6/2 data filter menu
    QList<QMenu*> dataFilterMenuList;

    QToolBar *tb;
    QAction * findAction;
    QAction * formatAction;
    QAction * openAction;
    QAction * saveAction;

    // 21/6/2 data filter
    QAction* dataFilterAction;
    QList<QAction*> dataFilterSelActionList;
    QList<QAction*> descendOrderActionList;
    QList<QAction*> ascendOrderActionList;
    QList<QAction*> condiFilterActionList;
    QList<QAction*> clearActionList;

    QLabel *label;
    QStatusBar * stBar;
    QPushButton *unionbtn;
    QPushButton *splitbtn;
    QPushButton *leftbtn;
    QPushButton *rightbtn;
    QPushButton *sethbtn;
    QPushButton *setwbtn;
    QPushButton *hideCbtn;
    QPushButton *notHideCbtn;
    QPushButton *hideRbtn;
    QPushButton *notHideRbtn;

    // 21/6/2 data filter
    QList<QPushButton*> openMenuBtnList;
    QList<int> menuRow;
    QList<int> menuCol;

    // 21/6/3 equal filter
    QDialog* equalDlg;
    QComboBox* conditionCom;
    QLineEdit* valueEdit;
    QWidget* curWidget;



private slots:
    void on_dataFilterAction_triggered(bool checked);
    void descendSort();
    void ascendSort();
    void equalFilter();
    void conductFilter();
    void clearFilter();

};



#endif // MAINWINDOW_H
