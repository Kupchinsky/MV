#ifndef LAGRA_HPP
#define LAGRA_HPP
#include <QVector>

class Graphf
{
public:
    double startX, finishX, stepY;
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

    void setStepY(double newval)
    {
        this->stepY = newval;
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

class Lagra
{
public:
    QVector<double> lX, lY, result;

    Lagra(int unit_points)
    {
        this->lX.resize(unit_points);
        this->lY.resize(unit_points);
    }

    void calcF(Graphf *gf)
    {
        this->result.resize(gf->points_count);
        this->result.fill(0);

        int unit_points = this->lX.size();
        double step = (gf->finishX - gf->startX) / (unit_points - 1);

        for (int i = 0; i < unit_points; i++)
        {
            this->lX[i] = gf->startX + step * i;
            this->lY[i] = gf->func(this->lX[i]);
        }

        for (int i = 0; i < gf->points_count; i++)
        {
            for (int j = 0; j < unit_points; j++)
            {
                double num = 1, den = 1;

                for (int k = 0; k < unit_points; k++)
                {
                    if (k != j)
                        num *= gf->fX[i] - this->lX[k];

                    if (this->lX[k] != this->lX[j])
                        den *= this->lX[j] - this->lX[k];
                }

                this->result[i] += this->lY[j] * num / den;
            }
        }

    }
};

class LagraRp
{
public:
    QVector<double> fY, result;

    LagraRp()
    {
    }

    double dfunc(double x)
    {
        return (428 - (240 * log(x))) / (x * x * x * x * x * x);
    }

    void calcRp(Graphf *gf, Lagra *l)
    {
        this->fY.resize(gf->points_count);
        this->result.resize(gf->points_count);
        this->result.fill(1);

        for (int i = 0; i < gf->points_count; i++)
            this->fY[i] = dfunc(gf->fX[i]);

        qSort(this->fY.begin(), this->fY.end(), qGreater<double>());
        double max = this->fY[0] * 0.04167;
        int unit_points = l->lX.size();

        for (int i = 0; i < gf->points_count; i++)
        {
            double num = 1;

            for (int j = 0; j < unit_points; j++)
                num *= gf->fX[i] - l->lX[j];

            this->result[i] = qFabs(max * num);
            //qDebug() << "Result[" << i << "]: " << this->result[i];
        }
    }
};
#endif // LAGRA_HPP
