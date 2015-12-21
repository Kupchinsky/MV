#include <iostream>
#include <QtMath>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <QDebug>
#include <windows.h>
#include <QtAlgorithms>
#include <inout.h>

using namespace std;
//Метод гаусса
double **gauss(double **x,int n) // приведение к треугольному виду
{
    double max,temp,del; int mn;
    for (int k=0; k<n; k++)
    {
        max=qFabs(x[k][k]);
        mn=k;
        for(int i=k; i<n; i++)// поиск мин
        {
            if ((qFabs(x[i][k])> max))
            {
                max=qFabs(x[i][k]);
                mn=i;
            }
        }
        for(int j=k;j<n+1; j++)// перестановка строк
        {
            temp = x[k][j];
            x[k][j]=x[mn][j];
            x[mn][j]=temp;
        }
        for(int i=k+1; i<n;i++)// треугольная матрица
        {
            del=x[i][k]/x[k][k];
            for(int j=0; j<n+1;j++)
            {
                x[i][j]=x[i][j]-x[k][j]*del;
            }
        }
    }

    for (int i=1; i<n;i++)
        for(int j=0;j<i;j++)
            x[i][j]=0;

    return x;
}

double *solution(double **x,int n, double *b) // нахождение решений с помощью метода Гаусса
{
    for (int i = n - 1; i >= 0; i--)
    {
        b[i] = x[i][n];

        for(int j = n - 1; j >= i+1; j--)
        {
            b[i] -= x[i][j]*b[j];
        }
        b[i] /= x[i][i];
    }
    return b;
}

//Метод Зейделя
bool converge(double *xk, double *xkp, int n) // условие остановки метода Зейделя
{
    QList<double> norm;
    double eps = 0.0001;
    for (int i = 0; i < n; i++)
    {
      norm.push_back(qFabs(xk[i] - xkp[i]));
    }

    qSort(norm);

    if(norm.last() <= eps)
      return true;
    return false;
}

double *zeidel(double **a, int n, double *x) // Метод Зейделя
{
    double *p = new double [n];
    do
    {
        for (int i = 0; i < n; i++)
            p[i] = x[i];

        for (int i = 0; i < n; i++)
        {
            double var = a[i][n];

            for (int j = 0; j < i; j++)
                var -= (a[i][j] * x[j]);

            for (int j = i + 1; j < n; j++)
                var -= (a[i][j] * p[j]);

            x[i] = var / a[i][i];
        }
    }
    while (!converge(x, p,n));
    return x;
}

int isRow(double **a,int n,int line) // Нахождение строки
{
    int numberLine = line;

    for (int i = numberLine+1; i < n; i++)
    {        
        double value = 0;
        for(int j = 0; j < n; j++)
        {
            if(j != line)
            value += qFabs(a[i][j]);
        }

        if(qFabs(a[i][line]) > value)
        {
            return i;
        }
    }

    if (numberLine == line)
        return 0;
}

bool checkZeidel(double **a,int n)// проверка на сходимость
{
    int check = 0;   
    int numberLine = 0;
    for(int i = 0; i < n; i++) // перестановка строк, так чтоб значение a[i][i] было больше, чем сумма других на i-той строке
    {
        double value = 0;

        for(int j = 0; j < n; j++)
        {
            if(j != i)
                value += qFabs(a[i][j]);
        }

        if(qFabs(a[i][i]) < value)
        {
          numberLine = isRow(a, n, i);
          if(numberLine == 0)
              return false;
          else
          {
              for(int k = 0;k < n+1; k++) // перестановка строк
              {
                  check = a[i][k];
                  a[i][k]=a[numberLine][k];
                  a[numberLine][k] = check;
              }
          }
        }
    }

    for(int i = 0; i < n; i++)// проверка, та то чтобы a[i][i] был != 0
    {
        if(a[i][i] == 0)
            return false;
    }

    return true;
}

//Медот скорейшего спуска - явная схема
bool stop(double t, double **a, int n, double *x, double *p)
{
    QList<double> norm;
    double epsilon = 0.0001;

    for(int i = 0; i< n; i++)
    {
        double temp = (x[i] - p[i])/t;
        for (int j = 0; j < n; j++)
        {
            temp += a[i][j] * p[i];
        }
        temp -= a[i][n];
        norm.push_back(temp);
    }
    qSort(norm);

    if(norm.last() <= epsilon)
      return true;

    return false;
}

double *discrepancy(double **a, int n, double *x)
{
    double *r = new double [n];

    for(int i = 0; i < n; i++)
    {
        r[i] = 0;
        for(int j = 0; j < n; j++)
        {
            r[i] += a[i][j]*x[i];
        }
        r[i] -= a[i][n];
    }

    return r;
}

double *toVector(double **a, int n, double *r)
{
    double *v = new double [n];

    for(int i = 0; i < n; i++)
    {
        v[i] = 0;

        for(int j = 0; j < n; j++)
        {
           v[i] += a[i][j] * r[i];
        }
    }

    return v;
}

double toScalar(double *first, double *second,int n)
{
    double s = 0;
    for(int i = 0; i < n; i++)
        s += first[i]*second[i];
    return s;
}

double tau(double **a,double *r,int n)
{
    double t;

    t = toScalar(r,r,n)/toScalar(toVector(a, n, r), r, n);

    return t;
}

double *fastestDescent(double **a,int n, double *x)
{
    double *p = new double [n];
    do
    {
        for (int i = 0; i < n; i++)
            p[i] = x[i];

        for (int i = 0; i < n; i++)
        {
            double var = a[i][n];

            for (int j = 0; j < i; j++)
                var -= (a[i][j] * x[j]);

            for (int j = i + 1; j < n; j++)
                var -= (a[i][j] * p[j]);

            x[i] = var / a[i][i];
        }
    }
    while (!stop(tau(a, discrepancy(a,n,x), n), a, n, x, p));
    return x;
}
