#ifndef COLORPICKER_HPP
#define COLORPICKER_HPP

#include <QWidget>

class ColorPicker : public QWidget {
    Q_OBJECT
public:
    explicit ColorPicker(QWidget *parent = 0);

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
    QColor getColorAtPicker(int x, int y);
    QSize getPickerSize() const;
    
    int rowCount;
    int colCount;
    int brightness;
    QColor selectedColor;
};

#endif // COLORPICKER_HPP
