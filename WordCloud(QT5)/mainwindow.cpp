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

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);
    file->addAction(saveAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);
    toolBar->addAction(saveAction);

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
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::white);
    //vl[id]->setPalette(pe);
    if(id%11==0)
    {
        vl[id]->setStyleSheet("color:#568DFB;""font:bold;");
    }
    else if(id%11==1)
    {
        vl[id]->setStyleSheet("color:#EB757B;""font:bold;");
    }
    else if(id%11==2)
    {
        vl[id]->setStyleSheet("color:#A5EA25;""font:bold;");
    }
    else if(id%11==3)
    {
        vl[id]->setStyleSheet("color:#4FC8E3;""font:bold;");
    }
    else if(id%11==4)
    {
        vl[id]->setStyleSheet("color:#FE2FDF;""font:bold;");
    }
    else if(id%11==5)
    {
        vl[id]->setStyleSheet("color:#BECEFF;""font:bold;");
    }
    else if(id%11==6)
    {
        vl[id]->setStyleSheet("color:#FACE1F;""font:bold;");
    }
    else if(id%11==7)
    {
        vl[id]->setStyleSheet("color:#25DFBD;""font:bold;");
    }
    else if(id%11==8)
    {
        vl[id]->setStyleSheet("color:#B3ED8D;""font:bold;");
    }
    else if(id%11==9)
    {
        vl[id]->setStyleSheet("color:#80ED5F;""font:bold;");
    }
    else
    {
        vl[id]->setStyleSheet("color:#C8E4FA;""font:bold;");
    }

    id++;
    if(id==vl.size())
        timer->stop();
}

void MainWindow::openFile()
{
    id=0;
    /*QLabel *label2=new QLabel("  ");
    QFont font1=label2->font();
    font1.setPointSize(10);
    label2->setFont(font1);
    //Label的手工摆放
    g->addWidget(label2,19,19,20,20);
    g->addWidget(label[0],11,6,7,10);//stimulation
    g->addWidget(label[1],8,9,5,6);//cloth
    g->addWidget(label[2],18,5,3,6);//virtual
    g->addWidget(label[3],16,10,4,5);//Garment
    g->addWidget(label[4],8,5,5,4);//Design
    g->addWidget(label[5],7,13,3,3);//sewing
    g->addWidget(label[6],16,14,4,3);//clothing
    g->addWidget(label[7],5,9,3,2);//try
    g->addWidget(label[8],5,10,7,4);//Ellipsoid
    g->addWidget(label[9],10,13,2,3);//scheme
    g->addWidget(label[10],11,8,2,3);//some
    g->addWidget(label[11],5,13,2,3);//human
    g->addWidget(label[12],8,8,2,2);//models
    g->addWidget(label[13],15,8,5,4);//system
    g->addWidget(label[14],17,7,2,2);//have
    g->addWidget(label[15],12,14,1,2);//new
    g->addWidget(label[16],5,11,2,2);//D
    g->addWidget(label[17],5,7,3,2);//proposed
    g->addWidget(label[18],6,14,3,2);//complex
    g->addWidget(label[19],19,12,2,2);//pattern
    g->addWidget(label[20],6,11,2,2);//patterns
    g->addWidget(label[21],14,15,3,3);//been
    //手工摆放结束*/
    memset(fill,0,sizeof(fill));
    vl.clear();
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

/*        Node node;
        for(p=mp.begin();p!=mp.end();p++)
        {
            node.times=p->second;
                node.lb=;
        }*/
        Node node;//将（单词，词频）保存到v中
        for(p=mp.begin();p!=mp.end();p++)
        {
            qDebug()<<p->first<<p->second;
            node.word=p->first;
            node.times=p->second;
            v.push_back(node);
        }
        //按词频降序排序
        //sort(v.begin(),v.end(),cmpNode);
        for(int i=0;i<v.size();i++)//遍历所有的单词
        {
            QLabel *label=new QLabel(v[i].word);//以当前单词新建一个label，并指定其父组件为rightW
            label->setStyleSheet("color:#000000;""font:bold;");
            QFont *font=new QFont("Courier",v[i].times*10);//新建一个与当前单词的频率所对应的font
            label->setFont(*font);//设置字体
            bool flag=true;//当前label待放入gridlayout
            for(int j=0;j+v[i].times<R&&flag;j++)//遍历grid的每一行
                for(int ll=0;ll+v[i].times*v[i].word.size()<C;ll++)//遍历grid的每一列
                {
                    if(ok(j,ll,v[i].times,v[i].times*v[i].word.size()))//当前位置可以放入
                    {qDebug()<<v[i].times<<v[i].word<<j<<ll;
                        vl.push_back(label);
                        set(j,ll,v[i].times,v[i].times*v[i].word.size());//设置标记数组
                        g->addWidget(label,j,ll,v[i].times,v[i].times*v[i].word.size(),Qt::AlignAbsolute);//放置标签
                        //qDebug()<<label->width()<<label->height();,Qt::AlignTop|Qt::AlignRight,Qt::AlignAbsolute,Qt::AlignHCenter
                        flag=false;//已放置
                        break;//跳出内层循环
                    }
                }
            //qDebug()<<label->width()<<label->height();
        }
        //vl(vl.begin(),vl.end(),vl.begin());
        g->setVerticalSpacing(0);//设置垂直间距
        delete(rightW);
        rightW=new QWidget();
        layout->addWidget(rightW);
        rightW->setLayout(g);
        QSizePolicy spr=rightW->sizePolicy();
        spr.setVerticalPolicy(QSizePolicy::Maximum);
        rightW->setSizePolicy(spr);
        qDebug()<<vl.size();
        file.close();
        timer=new QTimer();
        timer->setInterval(5000/vl.size());
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
