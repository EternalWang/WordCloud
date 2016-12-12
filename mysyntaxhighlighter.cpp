#include "mysyntaxhighlighter.h"
#include "label.h"
#include "QDebug"
MySyntaxHighlighter::MySyntaxHighlighter(QString str1,QTextDocument *parent) :
    QSyntaxHighlighter(parent)
{
    str = str1;
}

void MySyntaxHighlighter::highlightBlock(const QString &text) //�����ı���
{
    QTextCharFormat myFormat; //�ַ���ʽ
    myFormat.setFontWeight(QFont::Bold);
    myFormat.setForeground(Qt::red);

    QString pattern = "\\b"+str+"\\b"; //Ҫƥ����ַ��������ǡ�char������

    QRegExp expression(pattern); //����������ʽ
    expression.setCaseSensitivity(Qt::CaseInsensitive);
    int index = text.indexOf(expression); //��λ��0��ʼƥ���ַ���
    //���ƥ��ɹ�����ô����ֵΪ�ַ�������ʼλ�ã������ڻ����0
    while (index >= 0)
    {
        int length = expression.matchedLength(); //Ҫƥ���ַ����ĳ���
        setFormat(index, length, myFormat); //��Ҫƥ����ַ������ø�ʽ
        index = text.indexOf(expression, index + length);
        //��ǰ��ƥ�䵽���ַ���֮�����ƥ��
     }
}
