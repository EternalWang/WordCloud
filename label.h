#ifndef LABEL_H
#define LABEL_H

#endif // LABEL_H

#include <QLabel>
#include <QString>
#include <QTextEdit>
#include "mysyntaxhighlighter.h"
class Label:public QLabel//定义一个label类
{
    Q_OBJECT
public:
    explicit Label(QString str,QTextEdit *text,QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    int count;
    void paintEvent(QPaintEvent *event);
    bool over;
    bool press;
public:
    int times;
    QString words;
public:
    MySyntaxHighlighter *highlighter;//高显
    QTextEdit *textEdit;
};
