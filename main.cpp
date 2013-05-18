#include <QApplication>
#include "Widget.hpp"
#include <QString>
#include <QDebug>
#include <QSettings>
#include <QTextStream>
#include <QFile>
#include <memory>
#include <iostream>

void foo(int* &a) {
    a = new int[3];
    a[0] = 1;
    a[1] = 2;
    a[2] = 3;
}

int main(int argc, char *argv[]) {
    int* a = NULL;
    foo(a);

    std::cout << a[2] << std::endl;

    return 0; // Comment test
}

