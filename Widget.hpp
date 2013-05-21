#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <QWidget>
#include <QPixmap>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    virtual void paintEvent(QPaintEvent *);

private slots:
    void changePreviewBackground(const QColor &color);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_HPP
