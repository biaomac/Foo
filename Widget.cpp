#include "Widget.hpp"
#include "ui_Widget.h"

#include <QDebug>
#include <QPainter>
#include <QPainterPath>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    dstPixmap.load("/Users/Biao/Desktop/x.png", "png");
    srcPixmap.load("/Users/Biao/Desktop/y.png", "png");
    bgPixmap = QPixmap(400, 400);
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter mainPainter(this);

    bgPixmap.fill(QColor(0, 0, 0, 100));
    QPainter painter(&bgPixmap);
    painter.drawPixmap(0, 0, 400, 400, dstPixmap);
    painter.setCompositionMode(QPainter::CompositionMode_DestinationOut);
    painter.drawPixmap(50, 50, 250, 250, srcPixmap); // 把要绘制的不透明的地方扣掉
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//    painter.drawPixmap(50, 50, 150, 150, srcPixmap);

    mainPainter.setRenderHint(QPainter::Antialiasing);
    mainPainter.fillRect(0, 0, width(), height(), Qt::cyan);
    mainPainter.drawPixmap(0, 0, 400, 400, bgPixmap);
}
