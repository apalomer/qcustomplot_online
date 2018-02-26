#include <QApplication>
#include "qtguiapplication.h"

int main(int argc, char** argv)
{
    QApplication app(argc,argv);
    QtGuiApplication appgui;
    appgui.show();
    return app.exec();
}
