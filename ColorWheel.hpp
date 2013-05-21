#ifndef COLORWHEEL_HPP
#define COLORWHEEL_HPP

#include <QWidget>

class ColorWheel : public QWidget {
    Q_OBJECT
public:
    explicit ColorWheel(QWidget *parent = 0);

    // Return the selected color.
    QColor getSelectedColor() const;

public slots:
    // Set the brightness that will cause repainting the color wheel.
    void setBrightness(int brightness);
    
signals:
    void colorSelected(const QColor &color);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    
private:
    void paintColorWheel(QPainter *painter);
    QColor getColorAtWheel(int x, int y) const;

    // Transform the point's coordinate from the widget to color wheel's widget.
    QPoint transformCoordinate(int x, int y) const;
    QPoint getCycleCenter() const;
    int getRadius() const;

    int brightness;
    QColor selectedColor;
};

#endif // COLORWHEEL_HPP
