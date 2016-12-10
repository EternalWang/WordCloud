#ifndef LABEL_H
#define LABEL_H

#endif // LABEL_H

#include <QLabel>
#include <QString>
#include <QTextEdit>
#include "mysyntaxhighlighter.h"
class Label:public QLabel//����һ��label��
{
    Q_OBJECT
public:
    explicit Label(QString str,QTextEdit *text,QWidget *parent = 0);
    virtual void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    int count;
    void paintEvent(QPaintEvent *event);
    bool over;
    bool press;
    signals:
    //�Զ���clicked()�ź�,��mousePressEvent�¼�����ʱ����
    void clicked();
    public slots:
    void change_color();

public:
    int times;
    QString words;
public:
    MySyntaxHighlighter *highlighter;
    QTextEdit *textEdit;
};
