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
    ui->widget->resize(this->width() - 20, this->height() - 260);
    ui->groupBox_Lagra->move(ui->widget->x(), ui->widget->y() + ui->widget->height() + 10);
    ui->groupBox_Gauss->move(ui->widget->x(), ui->groupBox_Lagra->y() + ui->groupBox_Lagra->height() + 10);
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
    if (unit_points - 1 == 3)
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

void Widget::on_pushButton_2_clicked() {}

void Widget::on_pushButton_clicked()
{
    int n, unit;// кол-во точек, узлов
    double start;// начало оси x
    double finish;// конец оси x
    double step,t,G,value;

    start=ui->lineEdit_8->text().toDouble();
    finish=ui->lineEdit_7->text().toDouble();

    value=ui->lineEdit_9->text().toDouble();

    n=(finish-start)*10+1;
    step=(finish-start)/(ui->lineEdit_6->text().toDouble());
    unit=1+ui->lineEdit_6->text().toDouble();

    QVector<double> x(n), y(n),yG(unit+2),xG(unit+2),R(n),P(n),dy(unit+1),d2y(unit+1);


    //заполнение координатами основную функцию
    for (int i=0; i<n; ++i)
    {
        x[i] = start+i*0.1;
        y[i]=log(x[i]) * log(x[i]) + log(x[i]) + 1;
    }

    // Узловые точки
    for (int i=0; i<unit+2; ++i)
    {
        xG[i] = start+i*step;
        yG[i]=log(xG[i]) * log(xG[i]) + log(xG[i]) + 1;
    }

    // Конечные разности 1-го порядка
    for (int i=0;i<unit+1;i++)
            dy[i]=yG[i+1]-yG[i];

    // Конечные разности 2-го порядка
    for (int i=0;i<unit;i++)
        d2y[i]=yG[i+2] - 2*yG[i+1]+yG[i];

    int k=0;

    // Ближайший узел к точке, которую мы выводим
        for(int i=0;i<unit;i++)
            if(qFabs(value-xG[i])>qFabs(value-xG[i+1]))
                k++;
        t=(value-xG[k])/step;
        G=yG[k] + dy[k]*t +d2y[k]*d2y[k]*t*(t-1)*0.5;

     ui->label_5->setText("Значение функции: " + QString::number(G));

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->widget->yAxis2, SLOT(setRange(QCPRange)));
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    ui->widget->clearGraphs();

    // основной график
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x, y);
    ui->widget->graph(0)->setPen(QPen(Qt::red,1));

    //подписи осей
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    //длина осей
    ui->widget->xAxis->setRange(start, finish);
    //ui->widget->yAxis->setRange(0,1.7);
    //ui->widget->yAxis->setRange(ui->lineEdit_5->text().toDouble(), ui->lineEdit_4->text().toDouble()); /* Диапазон значений по оси y */
    ui->widget->replot();
}
