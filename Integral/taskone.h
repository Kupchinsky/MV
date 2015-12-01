#include <iostream>
#include <QVector>
#include <QDebug>
#include <QtMath>
#include <QtAlgorithms>

//cos(x*x*cos(x))

struct result
{
    double integralValue;
    double R;
};

double function(double x)
{
    return cos(x*x*cos(x));
}

result rectangleFormula(double a, double b, int n)
{
    QVector<double> x(n+1), y(n+1), M(n+1);
    double step;
    double maxM;
    result value;
    value.integralValue = 0;
    value.R = 0;
    step = (b-a)/n;

    for (int i=0; i<n+1;i++)
    {
        x[i]=a+i*step;
        y[i]=function(x[i]);
    }

    for (int i=0; i<n;i++)
    {
        value.integralValue+=step*y[i];
    }

    for (int i=0; i<n+1;i++)
    {
        M[i]=qFabs(x[i]*(x[i]*sin(x[i])-2*cos(x[i]))*sin(x[i]*x[i]*cos(x[i])));
    }

    qSort(M);
    maxM = M[n];
    value.R = (maxM*(b-a)*step)/2;
    return value;
}

result trapezeFormula(double a, double b, int n)
{
    QVector<double> x(n+1), y(n+1), M(n+1);
    double step;
    double maxM;
    result value;
    value.integralValue = 0;
    value.R = 0;
    step = (b-a)/n;

    for (int i=0; i<n+1;i++)
    {
        x[i]=a+i*step;
        y[i]=function(x[i]);
    }

    for (int i=0; i<n+1;i++)
    {
        if(i==0 || i == n)
            value.integralValue+=step*y[i]/2;
        else
           value.integralValue+=step*y[i];
    }

    for (int i=0; i<n+1;i++)
    {
        M[i]=qFabs(-cos(x[i]*x[i]*cos(x[i]))*(2*x[i]*cos(x[i])-x[i]*x[i]*sin(x[i]))*(2*x[i]*cos(x[i])-x[i]*x[i]*sin(x[i])) -
                (x[i]*x[i]*(-cos(x[i])-4*x[i]*sin(x[i])+2*cos(x[i])))*sin(x[i]*x[i]*cos(x[i])));
    }

    qSort(M);
    maxM = M[n];
    value.R = -(maxM*(b-a)*step*step)/12;
    return value;
}

result simpsonFormula(double a, double b, int n)
{
    QVector<double> x(n+1), y(n+1), M(n+1);
    double step;
    double maxM;
    result value;
    value.integralValue = 0;
    value.R = 0;
    step = (b-a)/n;

    for (int i=0; i<n+1;i++)
    {
        x[i]=a+i*step;
        y[i]=function(x[i]);
    }

    for (int i=0; i<n+1;i++)
    {
        if(i==0 || i == n)
        {
            value.integralValue+=y[i];
        }
        else
        {
           if(i%2==0)
           {
              value.integralValue+=y[i]*2;
           }
           else
           {
              value.integralValue+=y[i]*4;
           }
        }
    }
    value.integralValue *= step/3;

    for (int i=0; i<n+1;i++)
    {
        M[i]= cos(x[i]*x[i]*cos(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) *
                                         (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) +
              6*(-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) * sin(x[i]*x[i]*cos(x[i])) *
               (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) -
              4*cos(x[i]*x[i]*cos(x[i])) * (x[i]*x[i]*sin(x[i]) - 6*sin(x[i]) - 6*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) -
              3*cos(x[i]*x[i]*cos(x[i])) * (-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) *
                                           (-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) -
              (x[i]*x[i]*cos(x[i]) + 8*x[i]*sin(x[i]) - 12*cos(x[i]))*sin(x[i]*x[i]*cos(x[i]));
    }

    qSort(M);
    maxM = M[n];
    value.R = -(maxM*(b-a)*step*step*step*step)/180;
    return value;
}

result threeEighth(double a, double b, int n)
{
    QVector<double> x(n+1), y(n+1), M(n+1);
    double step;
    double maxM;
    result value;
    value.integralValue = 0;
    value.R = 0;
    step = (b-a)/n;

    for (int i=0; i<n+1;i++)
    {
        x[i]=a+i*step;
        y[i]=function(x[i]);
    }

    for (int i=0; i<n+1;i++)
    {
        if(i==0 || i == n)
        {
            value.integralValue+=y[i];
        }
        else
        {
           if(i%3==0)
           {
              value.integralValue+=y[i]*2;
           }
           else
           {
              value.integralValue+=y[i]*3;
           }
        }
    }
    value.integralValue *= (3*step/8);

    for (int i=0; i<n+1;i++)
    {
        M[i]= cos(x[i]*x[i]*cos(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) *
                                         (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) +
              6*(-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) * sin(x[i]*x[i]*cos(x[i])) *
               (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) -
              4*cos(x[i]*x[i]*cos(x[i])) * (x[i]*x[i]*sin(x[i]) - 6*sin(x[i]) - 6*x[i]*sin(x[i])) * (2*x[i]*cos(x[i]) - x[i]*x[i]*sin(x[i])) -
              3*cos(x[i]*x[i]*cos(x[i])) * (-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) *
                                           (-x[i]*x[i]*cos(x[i]) - 4*x[i]*sin(x[i]) + 2*cos(x[i])) -
              (x[i]*x[i]*cos(x[i]) + 8*x[i]*sin(x[i]) - 12*cos(x[i]))*sin(x[i]*x[i]*cos(x[i]));
    }

    qSort(M);
    maxM = M[n];
    value.R = -(maxM*(b-a)*step*step*step*step)/80;
    return value;
}

result methodGauss(double a, double b)
{
    int n = 6;
    QVector<double> x(n+1), y(n+1);
    double t[] ={-0.94910791, -0.74153119, -0.40584515, 0, 0.40584515, 0.74153119, 0.94910791};
    double A[] = {0.12948496, 0.27970540, 0.38183006, 0.41795918, 0.38183006, 0.27970540, 0.12948496};
    result value;
    value.integralValue = 0;
    value.R = 0;
    //double R =

    for(int i=0; i<n+1; i++)
    {
        x[i]=(b+a)/2 + (b-a)*t[i]/2;
        y[i]=function(x[i]);
    }

    for (int i = 0; i < n + 1 ; i++)
    {
        value.integralValue += A[i]*y[i];
    }

    value.integralValue *= ((b-a)/2);

    return value;
}

