#ifndef MYSYNTAXHIGHLIGHTER_H
#define MYSYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class MySyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    explicit MySyntaxHighlighter(QString str1,QTextDocument *parent = 0);

signals:

public slots:

protected:
    void highlightBlock(const QString &text); //��������ʵ�ָú���

public:
    QString str;
};

#endif // MYSYNTAXHIGHLIGHTER_H
