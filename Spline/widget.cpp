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
    ui->groupBox_Spline->move(ui->widget->x(), ui->widget->y() + ui->widget->height() + 10);
}

void Widget::on_pushButtonGauss_clicked()
{
    ui->widget->clearGraphs();

    int unitPoints = ui->lineEditGaussPointsCount->text().toInt() + 1; // unit

    //
    Graphf* gf = new Graphf();
    gf->setStartX(ui->lineEditGaussStart->text().toDouble());
    gf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    gf->setPointsCount((gf->finishX - gf->startX) * 5 * (unitPoints - 1) + 1); // n
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
    guf->setPointsCount(unitPoints);
    guf->setStepS((guf->finishX - guf->startX) / (unitPoints - 1));
    guf->calcf();
    //

    //
    int dopRazbienie = (gf->points_count - 1) / (unitPoints - 1);

    QVector<double> S(gf->points_count);
    for (int i = 1; i < unitPoints; i++)
    {
        for (int j = 0; j <= dopRazbienie; j++)
        {
            S[(i - 1) * dopRazbienie + j] =
                    guf->fY[i] + (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j])
                    *
                    (guf->fY[i - 1] - guf->fY[i]) / (guf->fX[i] - guf->fX[i - 1]);
        }
    }

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, S);
    graph->setPen(QPen(Qt::blue, 1));
    graph->setName("Сплайн");

    QVector<double> R(gf->points_count);
    for (int i = 0; i < R.length(); i++)
        R[i] = qFabs(gf->fY[i] - S[i]);

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, R);
    graph->setPen(QPen(Qt::green, 1));
    graph->setName("R(x)");
    //

    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot();

    delete guf;
    delete gf;
}

void Widget::on_pushButtonGauss_Cubic_clicked()
{
    ui->widget->clearGraphs();

    int unitPoints = ui->lineEditGaussPointsCount->text().toInt() + 1; // unit

    //
    Graphf* gf = new Graphf();
    gf->setStartX(ui->lineEditGaussStart->text().toDouble());
    gf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    gf->setPointsCount((gf->finishX - gf->startX) * 5 * (unitPoints - 1) + 1); // n
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
    guf->setPointsCount(unitPoints);
    guf->setStepS((guf->finishX - guf->startX) / (unitPoints - 1));
    guf->calcf();
    //

    //
    int dopRazbienie = (gf->points_count - 1) / (unitPoints - 1);

    QVector<double> S(gf->points_count);
    for (int i = 1; i < unitPoints; i++)
    {
        for (int j = 0; j <= dopRazbienie; j++)
        {
            S[(i - 1) * dopRazbienie + j] =
                    guf->fY[i] + (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j])
                    *
                    (guf->fY[i - 1] - guf->fY[i]) / (guf->fX[i] - guf->fX[i - 1]);
        }
    }

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, S);
    graph->setPen(QPen(Qt::blue, 1));
    graph->setName("Сплайн");

    QVector<double> R(gf->points_count);
    for (int i = 0; i < R.length(); i++)
        R[i] = qFabs(gf->fY[i] - S[i]);

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, R);
    graph->setPen(QPen(Qt::green, 1));
    graph->setName("R(x)");
    //

    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot();

    delete guf;
    delete gf;
}
