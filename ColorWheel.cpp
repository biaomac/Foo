#include "ColorWheel.hpp"

#include <QDebug>
#include <qmath.h>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>

ColorWheel::ColorWheel(QWidget *parent) : QWidget(parent) {
    brightness = 255;
}

void ColorWheel::setBrightness(int brightness) {
    brightness = qMax(brightness, 0);
    brightness = qMin(brightness, 255);
    this->brightness = brightness;

    repaint();
}

QColor ColorWheel::getSelectedColor() const {
    return selectedColor;
}

void ColorWheel::mousePressEvent(QMouseEvent * event) {
    QPoint p = transformCoordinate(event->x(), event->y());
    QColor color = getColorAtWheel(p.x(), p.y());

    if (color.isValid()) {
        selectedColor = color;
        emit colorSelected(selectedColor);
    }
}

void ColorWheel::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    paintColorWheel(&painter);
}

void ColorWheel::paintColorWheel(QPainter *painter) {
    painter->save();

    const int r = getRadius();
    QPoint cp = getCycleCenter();

    // Move the origin to the center of the widget.
    // Make the axis y active direction up.
    painter->translate(cp.x(), cp.y());
    painter->scale(1, -1);

    for (int y = -r; y <= r; ++y) {
        for (int x = -r; x <= r; ++x) {
            QColor color = getColorAtWheel(x, y);

            if (color.isValid()) {
                painter->fillRect(x, y, 1, 1, color);
            }
        }
    }

    painter->drawEllipse(-r, -r, r * 2, r * 2);

    painter->restore();
}

QColor ColorWheel::getColorAtWheel(int x, int y) const {
    int hue;
    int saturation;
    qreal distance;
    const qreal PI = 3.1415;
    const int r = getRadius();

    // calculate the current distance from center.
    distance = qSqrt(x * x + y * y);

    if (distance > r) { return QColor(); }

    // atan2 returns the angle from -pi to pi
    // radians so we convert to degrees here.
    hue = (int)(qAtan2(y, x) * 180 / PI);
    hue += y < 0 ? 360 : 0;
    hue %= 360;

    // calculate the saturation.
    saturation = (int) (distance / r * 255);
    saturation %= 256;

    // we can now simply convert from HSV to RGB.
   return QColor::fromHsv(hue, saturation, brightness);
}

QPoint ColorWheel::transformCoordinate(int x, int y) const {
    QPoint cp = getCycleCenter();

    return QPoint(x - cp.x(), -y + cp.y());
}

QPoint ColorWheel::getCycleCenter() const {
    return QPoint(width() / 2, height() / 2);
}

int ColorWheel::getRadius() const {
    return (qMin(width(), height())) / 2 - 2;
}
