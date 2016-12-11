#include"Label.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPalette>


#include "QSyntaxHighlighter"

Label::Label(QString str,QTextEdit *text,QWidget *parent):
QLabel(parent)
{
//QPalette palette;
//palette.setColor(QPalette::WindowText,QColor(50,255,255));
this->setText(str);
//this->setPalette(palette);
setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
//this->setStyleSheet("background-color:blue");
this->setCursor(Qt::PointingHandCursor);
count=0;
press=false;
over=false;
connect(this,SIGNAL(clicked()),this,SLOT(change_color()));
textEdit = text;
//highlighter = new MySyntaxHighlighter(textEdit->document());
}
void Label::mousePressEvent(QMouseEvent*event)
{
//��������˾ʹ���clicked�ź�
if(event->button()==Qt::LeftButton)
{
//����clicked�ź�
count++;
press=true;
emit clicked();
}
//�����¼��������ദ��
QLabel::mousePressEvent(event);
}
void Label::mouseReleaseEvent(QMouseEvent*event)
{
press=false;
update();
}
void Label::enterEvent(QEvent*)
{
over=true;
update();
}
void Label::leaveEvent(QEvent*)
{
over=false;
update();
}
void Label::change_color()
{
if(count%2)
this->setStyleSheet("background-color:red");
else
    this->setStyleSheet("background-color:blue");
//textEdit->setText("hello");
}

void Label::paintEvent(QPaintEvent*event)
{
QPainter paint(this);
paint.setPen(QPen(Qt::red,1));
if(over)
{
QString str = QString::number(times);
this->setToolTip(str);
if(over)
highlighter = new MySyntaxHighlighter(words,textEdit->document());
paint.drawLine(5,this->height()-1,this->width()-5,this->height()-1);//�����»���
}
else
{
    paint.setPen(Qt::NoPen);//������ƿ��»���
}
    QLabel::paintEvent(event);
}


