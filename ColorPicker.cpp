#include "ColorPicker.hpp"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

ColorPicker::ColorPicker(QWidget *parent) : QWidget(parent) {
    rowCount = 15;
    colCount = 15;
    brightness = 255;
}

void ColorPicker::setBrightness(int brightness) {
    brightness = qMax(brightness, 0);
    brightness = qMin(brightness, 255);
    this->brightness = brightness;

    repaint();
}

QColor ColorPicker::getSelectedColor() const {
    return selectedColor;
}

void ColorPicker::mousePressEvent(QMouseEvent * event) {
    QColor color = getColorAtPicker(event->x(), event->y());

    if (color.isValid()) {
        selectedColor = color;
        emit colorSelected(selectedColor);
    }
}

void ColorPicker::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    QSize pickerSize = getPickerSize();
    int deltaX = pickerSize.width() / colCount;
    int deltaY = pickerSize.height() / rowCount;

    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QColor color = getColorAtPicker(col * deltaX,  row * deltaY);
            painter.fillRect(col * deltaX, row * deltaY, deltaX, deltaY, color);
        }
    }

    // Show the grid lines.
    painter.setPen(Qt::darkGray);
    for (int row = 0; row <= rowCount; ++row) {
        painter.drawLine(0, row * deltaY, deltaX * colCount, row * deltaY);
    }

    for (int col = 0; col <= colCount; ++col) {
        painter.drawLine(col * deltaX, 0, col * deltaX, deltaY * rowCount);
    }
}

QColor ColorPicker::getColorAtPicker(int x, int y) {
    QSize pickerSize = getPickerSize();
    int deltaX = pickerSize.width() / colCount;
    int deltaY = pickerSize.height() / rowCount;

    if (x < 0 || y < 0 || x > deltaX * colCount || y > deltaY * rowCount) { return QColor(); }

    // Calculate the first line block colors: white to black.
    if (y / deltaY == 0) { return QColor::fromHsv(359, 0, 255 - x / deltaX * 255 / colCount); }

    int h = 360 - (x + deltaX) / deltaX * 360 / colCount;
    int s = 256 - y / deltaY * 256 / rowCount;

    h = h > 359 ? 0 : h;
    s = s > 255 ? 255 : s;

    return QColor::fromHsv(h, s, brightness);
}

QSize ColorPicker::getPickerSize() const {
    return QSize(width(), height());
}
