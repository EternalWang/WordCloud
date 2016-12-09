#WordCloud为QT5版本，主要用于EternalWang的开发及分享，词频统计部分已完成。
#wordcould为QT4版本，主要用于kangql和QQQkl的开发及分享，请手动将QT5中的功能同步到该版本。

将QT4转换为QT5版本：
1）.pro文件中添加 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
2）将#include < QtGui > 改为 #include < QtWidgets > 
QWidget是QtGui模块的一部分，是基础界面控件，大部分界面控件都是继承于它，比如QMainWindow、QDialog、QPushButton这些。 
Qt5里面把这些界面控件QtGui里面移出来，作为单独的模块，就是QtWidgets 

将QT5转换为QT4版本：
猜想只是需要去掉第二步中的<QtWidgets>即可，还没试过，别打我~