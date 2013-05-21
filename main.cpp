#include <QApplication>
#include "Widget.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Widget *widget = new Widget();
    widget->show();

    app.exec();
}

