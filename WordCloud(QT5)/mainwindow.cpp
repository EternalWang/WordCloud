#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h"
#include<QLabel>
#include<QDebug>
#include<algorithm>
#include<QGridLayout>
#include<cstring>
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
    textEdit->setMinimumSize(400,600);
    rightW = new QWidget();
    rightW->setMinimumSize(1000,600);
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
    memset(fill,0,sizeof(fill));
    /*QLabel *test0=new QLabel("t",rightW);
    QFont *font0=new QFont("Courier",400);
    //fontt->setPixelSize(400);
    //QFont f()
    test0->setFont(*font0);*/
    //test->resize(100,30);
    /*QLabel *test1=new QLabel("test1",rightW);
    QFont *font1=new QFont("Courier",100);
    test1->setFont(*font1);
    //qDebug()<<test->size();*/
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

bool MainWindow::ok(int r,int c,int h,int l)
{
    for(int i=0;i<h;i++)
        for(int j=0;j<l;j++)
            if(fill[r+i][c+j])
                return false;
    return true;
}
void MainWindow::set(int r, int c, int h, int l)
{
    for(int i=0;i<h;i++)
        for(int j=0;j<l;j++)
            fill[r+i][c+j]=true;
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
        qDebug()<<rightW->width()<<rightW->height();
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
        /*QGridLayout *gl=new QGridLayout();
        QLabel *label[10];
        for(int i=0;i<10;i++)
           {
            label[i]=new QLabel("Applicable");
            gl->addWidget(label[i],i,i,1,1);

        }
        rightW->setLayout(gl);*/
        QGridLayout *g=new QGridLayout();
        //g->addWidget();
        Node node;//将（单词，词频）保存
        for(p=mp.begin();p!=mp.end();p++)
        {
            qDebug()<<p->first<<p->second;
            //if(p->second<2)
                //continue;
            node.word=p->first;
            node.times=p->second;
            v.push_back(node);
            /*QLabel *l=new QLabel("%",this->rightW);
            l->setGeometry(20,20,50,10);
            l->show();*/
        }
       /* QLabel *test0=new QLabel("0");
        g->addWidget(test0);
        QLabel *test1=new QLabel("1");
        g->addWidget(test1);
        QLabel *test2=new QLabel("2");
        g->addWidget(test2);
        QLabel *test3=new QLabel("3");
        g->addWidget(test3);
        QLabel *test4=new QLabel("4");
        g->addWidget(test4);*/
        //sort(v.begin(),v.end(),cmpNode);//按词频降序排序并保存到v中
        for(int i=0;i<v.size();i++)
        {
            QPushButton *label=new QPushButton(v[i].word,rightW);
            //<<label->width()<<label->height();
            QFont *font=new QFont("Courier",v[i].times*10);
            label->setFont(*font);
            label->setFixedSize(v[i].times*v[i].word.size()*10,v[i].times*15);
            //label->set
            //l->show();
            bool flag=true;
            for(int j=0;j+v[i].times<R&&flag;j++)
                for(int ll=0;ll+v[i].times*v[i].word.size()<C;ll++)
                {
                    if(ok(j,ll,v[i].times,v[i].times*v[i].word.size()))
                    {qDebug()<<v[i].times<<v[i].word<<j<<ll;
                        set(j,ll,v[i].times,v[i].times*v[i].word.size());
                        //g->addWidget();
                        g->addWidget(label,j,ll,v[i].times,v[i].times*v[i].word.size());
                        //qDebug()<<label->width()<<label->height();,Qt::AlignTop|Qt::AlignRight
                        flag=false;
                        break;
                    }
                }
            qDebug()<<label->width()<<label->height();
            //g->addWidget(label,i,i,1,1);
            //g->addWidget(l,);
//            l->setGeometry(20+i*50,20+i*10,100,100);
//            l->show();
        }
        g->setVerticalSpacing(0);
        rightW->setLayout(g);
        qDebug()<<v.size();
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
