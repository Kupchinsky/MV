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

    //
    GraphUnitF* guf = new GraphUnitF();
    guf->setStartX(ui->lineEditGaussStart->text().toDouble());
    guf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    guf->setPointsCount((guf->finishX - guf->startX) * 10 + 1);
    guf->setStepY((guf->finishX - guf->startX) / (gfgufpoints_count - 1));
    guf->calcf();
    //

    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot(); /* Рисуем */

    delete gf;
}
