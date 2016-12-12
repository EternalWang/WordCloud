#include"Label.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPalette>


#include "QSyntaxHighlighter"

Label::Label(QString str,QTextEdit *text,QWidget *parent):
QLabel(parent)
{
    this->setText(str);
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    this->setCursor(Qt::PointingHandCursor);
    count=0;
    press=false;
    over=false;
    textEdit = text;
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
        paint.drawLine(5,this->height()-1,this->width()-5,this->height()-1);//绘制下划线
    }
    else
    {
        paint.setPen(Qt::NoPen);//当鼠标移开下划线
    }
        QLabel::paintEvent(event);
}


