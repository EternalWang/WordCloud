#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QHBoxLayout>
#include<map>
#include<vector>
#include<set>
using namespace std;
struct Node
{
    QString word;
    int times;
};

class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();

private:
    QAction *openAction;
    QAction *saveAction;

    QTextEdit *textEdit;

    QString s;
    QWidget *centralW,*rightW;
    QHBoxLayout *layout;
    map<QString,int> mp;
    vector<Node> v;
    set<QString> st;
    const static int R=400,C=100;
    bool fill[R][C];
    bool ok(int r,int c,int h,int l);
    void set(int r,int c,int h,int l);
};

#endif // MAINWINDOW_H
