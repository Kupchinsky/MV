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
            this->fY[i] = func(this->fX[i]);

            qDebug() << "uX: " << this->fX[i] << ", uY: " << this->fY[i];
        }
    }

#define SAMPLE_1

    static double func(double x)
    {
#ifdef SAMPLE_1
        return sin(x);
#else
        return log(x) * log(x) + log(x) + 1;
#endif
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
            this->fY[i] = GraphUnitF::func(this->fX[i]);
        }
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
            this->lY[i] = GraphUnitF::func(this->lX[i]);
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
#endif // GAUSS_HPP
