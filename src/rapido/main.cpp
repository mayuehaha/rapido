#include <QtGui>
#include "mainwindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("rapido_zh_CN.qm");
    app.installTranslator(&qtTranslator);

    MainWindow win;

    // 国际化支持（注意.pro文件中的  TRANSLATIONS = rapido_zh_CN.ts）
    // 然后用工具菜单中的 lupdate 生成和更新.ts文件，然后用 QT linguist 工具翻译
    // 最后用工具菜单中的 lrelease 生成.qm文件，就是上面 QTranslator 要加载的那个。
    win.setWindowTitle(QObject::tr("Rapido - MyIM"));

    // 可执行程序的图标，需要关注 .pro 文件中的 RC_FILE = resources/rapido.rc 这一行。

    // 可以在运行时修改窗口的图标（这种方式是将.png图片编译到可执行程序中了）
    //win.setWindowIcon(QIcon(":images/rapido.png"));
    // 还可以动态加载外部图片资源作为图标（一般是透明的.png格式，注意尺寸要合适）：
    //win.setWindowIcon(QIcon("resources/images/rapido.png"));

    // 这里我学习了如何设置窗口的初始大小、最大和最小尺寸的限定
    win.setFixedSize(300, 500);
    win.setMinimumSize(300, 500);
    win.setMaximumSize(600, 800);

    win.show();
    return app.exec();
}


