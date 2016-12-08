#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"
#include<QLabel>
#include<QDebug>
#include<algorithm>
#define k(a,b) int a##b;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    openAction = new QAction(QIcon(":/images/file-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    saveAction = new QAction(QIcon(":/images/file-save"), tr("&Save..."), this);
    saveAction->setShortcuts(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a new file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

    centralW=new QWidget(this);
    textEdit = new QTextEdit();
    textEdit->setMinimumSize(400,400);
    rightW = new QWidget();
    rightW->setMinimumSize(400,400);
    layout=new QHBoxLayout;
    layout->addWidget(textEdit);
    layout->addWidget(rightW);
    //MainWind中间部件（CentralWidget）设置为centralW，centralW左边为textEdit，右边为rightW。
    centralW->setLayout(layout);
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


void MainWindow::openFile()
{
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

        Node node;//将（单词，词频）保存
        for(p=mp.begin();p!=mp.end();p++)
        {
            qDebug()<<p->first<<p->second;
            node.word=p->first;
            node.times=p->second;
            v.push_back(node);
            /*QLabel *l=new QLabel("%",this->rightW);
            l->setGeometry(20,20,50,10);
            l->show();*/
        }
        sort(v.begin(),v.end(),cmpNode);//按词频降序排序并保存到v中
        for(int i=0;i<v.size();i++)
        {
            qDebug()<<v[i].times<<v[i].word;
            QLabel *l=new QLabel(v[i].word,this->rightW);
            l->setGeometry(20+i*50,20+i*10,100,100);
            l->show();
        }

        file.close();
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
