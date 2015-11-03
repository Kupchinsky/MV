#ifndef GAUSS_HPP
#define GAUSS_HPP
#include <QVector>

class GraphUnitF
{
public:
    double startX, finishX, stepY;
    QVector<double> fX, fY;
    int points_count;

    GraphUnitF()
    {
    }

    void setStartX(double newval)
    {
        this->startX = newval;
    }

    void setFinishX(double newval)
    {
        this->finishX = newval;
    }

    void setStepY(double newval)
    {
        this->stepY = newval;
    }

    void setPointsCount(int newval)
    {
        qDebug() << "Unit points count: " << newval;
        this->points_count = newval;
    }

    void calcf()
    {
        this->fX.resize(this->points_count);
        this->fY.resize(this->points_count);

        for (int i = 0; i < this->points_count; i++)
        {
            this->fX[i] = this->startX + i * this->stepY;
            this->fY[i] = this->func(this->fX[i]);
        }

        //qDebug() << this->fX << this->stepY;
    }

    double func(double x)
    {
        return log(x) * log(x) + log(x) + 1;
    }
};

class Graphf
{
public:
    double startX, finishX;
    QVector<double> fX, fY;
    int points_count;

    Graphf()
    {
    }

    void setStartX(double newval)
    {
        this->startX = newval;
    }

    void setFinishX(double newval)
    {
        this->finishX = newval;
    }

    void setPointsCount(int newval)
    {
        qDebug() << "Points count: " << newval;
        this->points_count = newval;
    }

    void calcf()
    {
        this->fX.resize(this->points_count);
        this->fY.resize(this->points_count);

        for (int i = 0; i < this->points_count; i++)
        {
            this->fX[i] = this->startX + i * 0.1;
            this->fY[i] = this->func(this->fX[i]);
        }
    }

    double func(double x)
    {
        return log(x) * log(x) + log(x) + 1;
    }
};
#endif // GAUSS_HPP
