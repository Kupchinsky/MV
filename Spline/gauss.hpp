#ifndef GAUSS_HPP
#define GAUSS_HPP
#include <QVector>

class GraphUnitF
{
public:
    double startX, finishX, stepS;
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

    void setStepS(double newval)
    {
        this->stepS = newval;
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

        qDebug() << this->points_count << this->startX << this->stepS;

        for (int i = 0; i < this->points_count; i++)
        {
            this->fX[i] = this->startX + i * this->stepS;
            this->fY[i] = this->func(this->fX[i]);

            qDebug() << "uX: " << this->fX[i] << ", uY: " << this->fY[i];
        }
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

        double stepY = (this->finishX - this->startX) / (this->points_count - 1);

        for (int i = 0; i < this->points_count; i++)
        {
            this->fX[i] = this->startX + i * stepY;
            this->fY[i] = this->func(this->fX[i]);
        }
    }

    double func(double x)
    {
        return log(x) * log(x) + log(x) + 1;
    }
};
#endif // GAUSS_HPP
