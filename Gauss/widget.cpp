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
    int n, unit;// кол-во точек, узлов
    double start;// начало оси x
    double finish;// конец оси x
    double step,t,G,value;

    start=ui->lineEditGaussStart->text().toDouble();
    finish=ui->lineEditGaussFinish->text().toDouble();

    value=ui->lineEditGaussValue->text().toDouble();

    n=(finish-start)*10+1;

    qDebug() << start << finish << n;

    step=(finish-start)/(ui->lineEditGaussPointsCount->text().toDouble());
    unit=1+ui->lineEditGaussPointsCount->text().toDouble();

    QVector<double> x(n), y(n),yG(unit+2),xG(unit+2),R(n),P(n),dy(unit+1),d2y(unit+1);

    qDebug() << x.length() << y.length();
    qDebug() << yG.length() << xG.length();
    qDebug() << dy.length() << d2y.length();
    //qDebug() << R.length() << P.length();

    //заполнение координатами основную функцию
    for (int i=0; i<n; ++i)
    {
        x[i] = start+i*0.1;
        y[i]=cos(x[i])*cos(x[i])+cos(x[i]+1)+x[i];
    }

    // Узловые точки
    for (int i=0; i<unit+2; ++i)
    {
        xG[i] = start+i*step;
        yG[i]=cos(xG[i])*cos(xG[i])+cos(xG[i]+1)+xG[i];
    }

    // Конечные разности 1-го порядка
    for (int i=0;i<unit+1;i++)
            dy[i]=yG[i+1]-yG[i];

    // Конечные разности 2-го порядка
    for (int i=0;i<unit;i++)
        d2y[i]=yG[i+2] - 2*yG[i+1]+yG[i];

    qDebug() << unit << step;

    int k=0;
    qDebug() << "Значение функции: ";

    // Ближайший узел к точке, которую мы выводим
        for(int i=0;i<unit;i++)
            if(qFabs(value-xG[i])>qFabs(value-xG[i+1]))
                k++;
        t=(value-xG[k])/step;
        G=yG[k] + dy[k]*t +d2y[k]*d2y[k]*t*(t-1)*0.5;

        qDebug() << G;

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
    ui->widget->yAxis->setRange(0,1.7);
    ui->widget->replot();
}

void Widget::on_pushButton_clicked()
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

    qDebug() << gf->startX << gf->finishX << gf->points_count;
    qDebug() << gf->fX.length() << gf->fY.length();

    //
    GraphUnitF* guf = new GraphUnitF();
    guf->setStartX(ui->lineEditGaussStart->text().toDouble());
    guf->setFinishX(ui->lineEditGaussFinish->text().toDouble());
    guf->setPointsCount(ui->lineEditGaussPointsCount->text().toDouble() + 3);
    guf->setStepY((guf->finishX - guf->startX) / (guf->points_count - 3));
    guf->calcf();
    //

    qDebug() << guf->fX.length() << guf->fY.length();

    // Конечные разности 1-го порядка
    QVector<double> dY(guf->points_count - 1);
    for (int i = 0; i < dY.length(); i++)
        dY[i] = guf->fY[i + 1] - guf->fY[i];

    // Конечные разности 2-го порядка
    QVector<double> dY2(guf->points_count - 1);
    for (int i = 0; i < dY2.length() - 1; i++)
        dY2[i] = guf->fY[i + 2] - 2 * guf->fY[i + 1] + guf->fY[i];

    qDebug() << dY.length() << dY2.length();

    // Ближайший узел к точке, которую мы выводим
    double value = ui->lineEditGaussValue->text().toDouble();
    int k = 0;

    for (int i = 0; i < guf->points_count - 2; i++)
    {
        if (qFabs(value - guf->fX[i]) > qFabs(value - guf->fX[i+1]))
                k++;
    }

    qDebug() << guf->points_count - 2 << guf->stepY;

    double t = (value - guf->fX[k]) / guf->stepY;
    double G = guf->fY[k] + dY[k] * t + dY2[k] * dY2[k] * t * (t - 1) * 0.5;

    ui->widget->xAxis->setRange(gf->startX, gf->finishX);
    ui->widget->yAxis->setRange(0, 10);
    ui->widget->replot();

    delete guf;
    delete gf;

    qDebug() << "Result: " << G;
    QMessageBox::information(this, "Gauss", "Result: " + QString::number(G));
}
