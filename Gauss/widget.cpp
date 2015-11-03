#include "widget.h"
#include "ui_widget.h"

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

void Widget::on_pushButton_clicked()
{
    /*int n, unit;// кол-во точек, узлов
    double start;// начало оси x
    double finish;// конец оси x
    double step,t,G,value;

    start=ui->lineEdit->text().toDouble();
    finish=ui->lineEdit_2->text().toDouble();

    value=ui->lineEdit_4->text().toDouble();

    n=(finish-start)*10+1;
    step=(finish-start)/(ui->lineEdit_3->text().toDouble());
    unit=1+ui->lineEdit_3->text().toDouble();

    QVector<double> x(n), y(n),yG(unit+2),xG(unit+2),R(n),P(n),dy(unit+1),d2y(unit+1);


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
    ui->widget->replot();*/
}
