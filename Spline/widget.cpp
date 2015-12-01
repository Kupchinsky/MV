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

    //
    Lagra* l = new Lagra(unitPoints);
    l->calcF(gf);

    graph = ui->widget->addGraph();
    graph->setData(gf->fX, l->result);
    graph->setPen(QPen(Qt::yellow, 1));
    graph->setName("L(x)");
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

    QVector<double> S(gf->points_count),
            a(unitPoints), b(unitPoints), c(unitPoints), d(unitPoints), alpha(unitPoints),
            beta(unitPoints), gamma(unitPoints), q(unitPoints), p(unitPoints), fi(unitPoints);

    p[0] = p[1] = 0;
    q[0] = q[1] = 0;
    alpha[0] = alpha[unitPoints - 1] = 0;
    beta[0] = beta[unitPoints - 1] = 0;
    gamma[0] = gamma[unitPoints - 1] = 0;
    fi[0] = fi[unitPoints - 1] = 0;
    c[0] = c[unitPoints - 1] = 0;
    d[0] = b[0] = 0;

    for (int i = 1; i < unitPoints; i++)
        a[i] = guf->fY[i];

    for (int i = 1; i < unitPoints - 1; i++)
    {
        alpha[i] = guf->stepS;
        beta[i] = 4 * guf->stepS;
        gamma[i] = guf->stepS;
        fi[i] = 6 * (guf->fY[i + 1] - 2 * guf->fY[i] + guf->fY[i - 1]) / guf->stepS;
    }

    for (int i = 1; i < unitPoints - 1; i++)
        p[i + 1] = -gamma[i] / (beta[i] + alpha[i] * p[i]);

    for (int i = 1; i < unitPoints - 1; i++)
        q[i + 1] = (fi[i] - alpha[i] * q[i]) / (beta[i] + alpha[i] *  p[i]);

    for (int i = unitPoints - 2; i > 0; i--)
        c[i] = p[i + 1] * c[i + 1] + q[i + 1];

    for (int i = 0; i < unitPoints - 1; i++)
        d[i + 1] = (c[i] - c[i + 1]) / guf->stepS;

    for (int i = 0; i < unitPoints - 1; i++)
        b[i + 1] = (guf->fY[i] - guf->fY[i + 1]) / guf->stepS - c[i + 1] *  guf->stepS / 2 - (c[i] - c[i + 1]) * guf->stepS / 6;

    for (int i = 1; i < unitPoints; i++)
    {
        for (int j = 0; j <= dopRazbienie; j++)
        {
            S[(i - 1) * dopRazbienie + j] =
                    a[i] + b[i] * (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j]) +
                    c[i] * (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j]) *
                    (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j]) / 2 +
                    d[i] * (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j]) *
                    (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j])*
                    (guf->fX[i] - gf->fX[(i - 1) * dopRazbienie + j]) / 6;
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
