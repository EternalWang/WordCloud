#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"
#include<QLabel>
#include<QDebug>
#include<algorithm>
#include<QGridLayout>
#include<cstring>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QVBoxLayout>


#define k(a,b) int a##b;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //背景颜色
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    //背景颜色
    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    chooseAction = new QAction(tr("choose"), this);
    //chooseAction->setShortcuts(QKeySequence::Save);
    chooseAction->setStatusTip(tr("choose"));
    connect(chooseAction, SIGNAL(triggered()), this, SLOT(choose()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);
    file->addAction(chooseAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);
    toolBar->addAction(chooseAction);

    centralW=new QWidget(this);
    textEdit = new QTextEdit();
    textEdit->setMinimumWidth(300);
    rightW = new QWidget();
    layout=new QHBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(rightW);
    //MainWind中间部件（CentralWidget）设置为centralW，centralW左边为textEdit，右边为rightW。
    centralW->setLayout(layout);
    centralW->setMaximumHeight(1000);
    this->setMaximumHeight(1000);
    setCentralWidget(centralW);

    st.insert("The");
    st.insert("In");
    st.insert("To");
    st.insert("Is");
    st.insert("It");
    st.insert("Of");
    st.insert("Are");
    st.insert("Also");
    st.insert("Which");
    st.insert("A");
    st.insert("On");
    st.insert("Can");
    st.insert("At");
    st.insert("That");
    st.insert("They");
    st.insert("And");
    st.insert("When");
    st.insert("For");
    st.insert("From");
    st.insert("Here");
    st.insert("If");
    st.insert("Into");
    st.insert("Its");
    st.insert("Most");
    st.insert("Not");
    st.insert("You");
    st.insert("Will");
    st.insert("An");
    st.insert("We");

}

MainWindow::~MainWindow()
{
}
bool judge(QChar s)//判断是否为单词的字母
{
    if((s>='a'&&s<='z')||(s>='A'&&s<='Z')||s=='\'')
        return true;
    return false;
}
bool cmpNode(Node a,Node b)//Node的比较函数
{
    return a.times>b.times;
}

bool MainWindow::ok(int r,int c,int h,int l)//左上角放在gird(r,c)且规模为h*l的单词能否放下
{
    for(int i=0;i<h;i++)
        for(int j=0;j<l;j++)
            if(fill[r+i][c+j])
                return false;
    return true;
}
void MainWindow::set(int r, int c, int h, int l)//修改fill
{
    for(int i=0;i<h;i++)
        for(int j=0;j<l;j++)
            fill[r+i][c+j]=true;
}
void MainWindow::changeColor()
{
    if(id%11==0)
    {
        v[id].lb->setStyleSheet("color:#568DFB;""font:bold;");
    }
    else if(id%11==1)
    {
        v[id].lb->setStyleSheet("color:#EB757B;""font:bold;");
    }
    else if(id%11==2)
    {
        v[id].lb->setStyleSheet("color:#A5EA25;""font:bold;");
    }
    else if(id%11==3)
    {
        v[id].lb->setStyleSheet("color:#4FC8E3;""font:bold;");
    }
    else if(id%11==4)
    {
        v[id].lb->setStyleSheet("color:#FE2FDF;""font:bold;");
    }
    else if(id%11==5)
    {
        v[id].lb->setStyleSheet("color:#BECEFF;""font:bold;");
    }
    else if(id%11==6)
    {
        v[id].lb->setStyleSheet("color:#FACE1F;""font:bold;");
    }
    else if(id%11==7)
    {
        v[id].lb->setStyleSheet("color:#25DFBD;""font:bold;");
    }
    else if(id%11==8)
    {
        v[id].lb->setStyleSheet("color:#B3ED8D;""font:bold;");
    }
    else if(id%11==9)
    {
        v[id].lb->setStyleSheet("color:#80ED5F;""font:bold;");
    }
    else
    {
        v[id].lb->setStyleSheet("color:#C8E4FA;""font:bold;");
    }

    id++;
    if(id==v.size())
        timer->stop();
}

void MainWindow::openFile()
{
    delete(rightW);
    rightW=new QWidget();
    id=0;
    memset(fill,0,sizeof(fill));
    QGridLayout *g=new QGridLayout();
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        v.clear();//清空vector v
        mp.clear();//清空map mp
        map<QString,int>::iterator p;//迭代器
        QTextStream in(&file);
        textEdit->setText(s=in.readAll());
        QString tmp;
        int l,r;//指示单词范围的左右指针
        //配色
        //qDebug()<<rightW->width()<<rightW->height();
        for(l=r=0;r<s.size()&&l<s.size();)//切词并统计词频
        {
            while(l<s.size()&&!judge(s[l]))
                l++;
            if(l==s.size())
                break;
            r=l;
            while(r<s.size()&&judge(s[r]))
                r++;
            tmp=s.mid(l,r-l);
            tmp[0]=tmp[0].toUpper();//首字符大写，其余小写。
            for(int i=1;i<tmp.size();i++)
                tmp[i]=tmp[i].toLower();
            if(st.find(tmp)!=st.end())
            {
                l=r;
                continue;
            }
            p=mp.find(tmp);
            if(p==mp.end())
                mp[tmp]=1;
            else
                p->second++;
            l=r;
        }

        Node node;
        for(p=mp.begin();p!=mp.end();p++)
        {
            node.times=p->second;
            Label *label=new Label(p->first,textEdit,rightW);
            label->words = p->first;
            label->times = p->second;
            node.lb=label;
            label->setStyleSheet("color:#000000;""font:bold;");
            QFont *font=new QFont("Courier",node.times*10);//新建一个与当前单词的频率所对应的font
            label->setFont(*font);//设置字体
            bool flag=true;//当前label待放入gridlayout
            for(int j=0;j+node.times<R&&flag;j++)//遍历grid的每一行
                for(int ll=0;ll+node.times*p->first.size()<C;ll++)//遍历grid的每一列
                {
                    if(ok(j,ll,node.times,node.times*p->first.size()))//当前位置可以放入
                    {//qDebug()<<v[i].times<<v[i].word<<j<<ll;
                        v.push_back(node);
                        set(j,ll,node.times,node.times*p->first.size());//设置标记数组
                        g->addWidget(label,j,ll,node.times,node.times*p->first.size(),Qt::AlignAbsolute);//放置标签
                        //qDebug()<<label->width()<<label->height();,Qt::AlignTop|Qt::AlignRight,Qt::AlignAbsolute,Qt::AlignHCenter
                        flag=false;//已放置
                        break;//跳出内层循环
                    }
                }
            //qDebug()<<label->width()<<label->height();
        }
        sort(v.begin(),v.end(),cmpNode);
        g->setVerticalSpacing(0);//设置垂直间距
        layout->addWidget(rightW);
        rightW->setLayout(g);
        QSizePolicy spr=rightW->sizePolicy();
        spr.setVerticalPolicy(QSizePolicy::Maximum);
        rightW->setSizePolicy(spr);
        //qDebug()<<vl.size();
        file.close();
        timer=new QTimer();
        timer->setInterval(5000/v.size());
        timer->start();
        connect(timer,SIGNAL(timeout()),this,SLOT(changeColor()));
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"), ".", tr("Text Files(*.txt)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Write File"), tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    } else {
        QMessageBox::warning(this, tr("Path"), tr("You did not select any file."));
    }
}

void MainWindow::choose()
{
    QDialog *dlg = new QDialog(this);
    lineEdit = new QLineEdit(dlg);
    QPushButton *btn = new QPushButton(dlg);
    btn->setText(tr("commit"));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(lineEdit);
    layout->addWidget(btn);
    dlg->setLayout(layout);
    dlg->show();
}
