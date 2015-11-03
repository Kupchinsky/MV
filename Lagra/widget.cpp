#include "widget.h"
#include "ui_widget.h"
#include "lagra.hpp"

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
    ui->widget->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->widget, "Lagra"));

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
    ui->groupBox_Lagra->move(ui->widget->x(), ui->widget->y() + ui->widget->height() + 10);
}

void Widget::on_pushButtonLagra_clicked()
{
    ui->widget->clearGraphs();

    //
    Graphf* gf = new Graphf();
    gf->setStartX(ui->lineEditLagraStart->text().toDouble());
    gf->setFinishX(ui->lineEditLagraFinish->text().toDouble());
    gf->setPointsCount((gf->finishX - gf->startX) * 10 + 1);
    gf->setStepY((gf->finishX - gf->startX) / (gf->points_count - 1));
    gf->calcf();

    QCPGraph *graph = ui->widget->addGraph();
    graph->setData(gf->fX, gf->fY);
    graph->setPen(QPen(Qt::red, 1));
    graph->setName("f(x)");
    //

    //
    Lagra* l = new Lagra(ui->lineEditLagraPointsCount->text().toInt() + 1);
    l->calcF(gf);

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, l->result);
    graph->setPen(QPen(Qt::blue, 1));
    graph->setName("L(x)");
    //

    //
    QVector<double> Rt(gf->points_count);
    for (int i = 0; i < Rt.size(); i++)
        Rt[i] = qFabs(gf->fY[i] - l->result[i]);

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, Rt);
    graph->setPen(QPen(Qt::black, 1));
    graph->setName("R(x)");
    //

    //
    LagraRp* lrp = NULL;

    int unit_points = l->lX.size();
    if (unit_points - 1 == 5)
    {
        lrp = new LagraRp();
        lrp->calcRp(gf, l);

        graph = ui->widget->addGraph();
        graph->setData(gf->fX, lrp->result);
        graph->setPen(QPen(Qt::green, 1));
        graph->setName("Теоретическая погрешность");
    }
    //

    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot(); /* Рисуем */

    if (lrp != NULL)
        delete lrp;

    delete l;
    delete gf;
}
