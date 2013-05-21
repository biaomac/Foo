#include "Widget.hpp"
#include "ui_Widget.h"

#include <QDebug>
#include <qmath.h>
#include <QPainter>
#include <QPainterPath>

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    changePreviewBackground(Qt::cyan);

    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), ui->colorWheel, SLOT(setBrightness(int)));
    connect(ui->colorWheel, SIGNAL(colorSelected(QColor)), this, SLOT(changePreviewBackground(QColor)));

    connect(ui->verticalSlider, SIGNAL(valueChanged(int)), ui->colorPicker, SLOT(setBrightness(int)));
    connect(ui->colorPicker, SIGNAL(colorSelected(QColor)), this, SLOT(changePreviewBackground(QColor)));
}

Widget::~Widget() {
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {

}

void Widget::changePreviewBackground(const QColor &color) {
    ui->label->setAutoFillBackground(true);
    QPalette p = ui->label->palette();
    p.setColor(QPalette::Window, color);
    ui->label->setPalette(p);
}
