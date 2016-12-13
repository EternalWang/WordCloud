#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHBoxLayout>
#include<QRadioButton>
#include <QPushButton>
#include <QtWidgets>
#include <QtGui>
#include<map>
#include<vector>
#include<set>
#include<QLabel>
#include "label.h"
using namespace std;
struct Node
{
    Label* lb;
    int times;
};

class QTextEdit;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void choose();
    void refresh();
private:
    QAction *openAction;
    QAction *saveAction;
    QAction *chooseAction;
    QAction *refreshAction;

    QTextEdit *textEdit;

    QLineEdit *lineEdit;
    QLineEdit *lineEdit2;

    QButtonGroup *groupBox;
    QRadioButton *rb1;
    QRadioButton *rb2;
    QRadioButton *rb3;

    QString s;
    QWidget *centralW,*rightW;
    QHBoxLayout *layout;
    map<QString,int> mp;
    vector<Node> v;
    //vector<QLabel *> vl;
    set<QString> st;
    const static int R=100,C=100;//GridLayout的规模
    bool fill[R][C];//保存每一块是否被占用
    bool ok(int r,int c,int h,int l);//判断左上角放在gird(r,c)且规模为h*l的单词能否放下
    void set(int r,int c,int h,int l);//修改fill
    int id;
    int tmpp;
    QString str;

    QTimer *timer;
    int controll_speed = 5000;
        int controll_colorscheme = 1;
        int controll_fren;
        void reflash();

    private slots:
        void selectWord();
        void changeColor();
        //QGridLayout *g;
        void changespeed();
        void changecolorscheme();
};

#endif // MAINWINDOW_H
