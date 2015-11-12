#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void resizeEvent (QResizeEvent*);

private slots:

    void on_pushButtonGauss_clicked();

    void on_pushButtonGauss_Cubic_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H