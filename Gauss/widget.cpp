#include "widget.h"
#include "ui_widget.h"
#include "gauss.hpp"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend | QCP::iSelectAxes);
    ui->widget->axisRect()->setupFullAxesBox();

    ui->widget->plotLayout()->insertRow(0);
    ui->widget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget, "Gauss"));

    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    ui->widget->legend->setVisible(true);

    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->widget->legend->setFont(legendFont);
    ui->widget->legend->setSelectedFont(legendFont);
    ui->widget->legend->setSelectableParts(QCPLegend::spNone);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent (QResizeEvent*)
{
    ui->widget->resize(this->width() - 20, this->height() - 140);
    ui->groupBox_Gauss->move(ui->widget->x(), ui->widget->y() + ui->widget->height() + 10);
}

void Widget::on_pushButtonGauss_clicked()
{
    ui->widget->clearGraphs();

    //
    Graphf* gf = new Graphf();
    gf->setStartX(ui->lineEditGaussStart->text().toDouble());
    gf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    gf->setPointsCount((gf->finishX - gf->startX) * 10 + 1);
    gf->calcf();

    QCPGraph *graph = ui->widget->addGraph();
    graph->setData(gf->fX, gf->fY);
    graph->setPen(QPen(Qt::red, 1));
    graph->setName("f(x)");
    //

    //qDebug() << gf->startX << gf->finishX << gf->points_count;
    //qDebug() << gf->fX.length() << gf->fY.length();

    //
    GraphUnitF* guf = new GraphUnitF();
    guf->setStartX(ui->lineEditGaussStart->text().toDouble());
    guf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    guf->setPointsCount(ui->lineEditGaussPointsCount->text().toDouble() + 1);
    guf->setStepY((guf->finishX - guf->startX) / (guf->points_count - 1)); // Это h - шаг
    guf->calcf();
    //

    //qDebug() << guf->fX.length() << guf->fY.length();

    // Конечные разности 1-го порядка
    QVector<double> dY(guf->points_count - 1);
    for (int i = 0; i < dY.length(); i++)
        dY[i] = guf->fY[i + 1] - guf->fY[i];

    // Конечные разности 2-го порядка
    QVector<double> dY2(guf->points_count - 1);
    for (int i = 0; i < dY2.length() - 1; i++)
        dY2[i] = guf->fY[i + 2] - 2 * guf->fY[i + 1] + guf->fY[i];

    //qDebug() << dY.length() << dY2.length();

    // Ближайший узел к точке, которую мы выводим
    double value = ui->lineEditGaussValue->text().toDouble();
    int k = 0;

    // Ищем ближайшую точку (k)
    for (int i = 0; i < guf->points_count - 2; i++)
    {
        if (qFabs(value - guf->fX[i]) > qFabs(value - guf->fX[i+1]))
                k++;
    }

    //qDebug() << guf->points_count - 2 << guf->stepY;

    // Вычисляем t по формуле
    double t = (value - guf->fX[k]) / guf->stepY;

    // Вычисляем L2 по формуле для значения, заданного в текстовом поле в окошке
    double L2 = guf->fY[k] + dY[k] * t + dY2[k] * dY2[k] * t * (t - 1) * 0.5;
/*
    // Остаточный член
    double der3 = 4 / (gf->fX[k] * gf->fX[k] * gf->fX[k]) * (log(gf->fX[k]) - 1);
    double R2 = der3 * guf->stepY * guf->stepY * guf->stepY * ((t * (t * t - 1)) / 6);
*/
    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot();

    delete guf;
    delete gf;

    qDebug() << "L2 = " << L2; // << "; R2 = " << R2;
    QMessageBox::information(this, "Gauss", "L2 = " + QString::number(L2)); // + "; R2 = " + QString::number(R2));
}
