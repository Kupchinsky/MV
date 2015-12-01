#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <taskone.h>

using namespace std;
int main()
{
    result integral;
    double a=5;
    double b=7;
    int n;
    double epsilon = qPow(10.0,-14.0);

    cout << "TASK 1" << endl;
    cout << endl << "Enter quantity of pieces = ";
    cin >> n;
    cout << endl;

    integral = rectangleFormula(a,b,n);

    cout << "-------------Method of rectangles----------------" << endl;
    cout << "Value of integral = " << integral.integralValue << endl
         << "Value of the residual member = " << integral.R << endl << endl;

    integral = trapezeFormula(a,b,n);
    cout << "-------------Method of trapeze----------------" << endl;
    cout << "Value of integral = " << integral.integralValue << endl
         << "Value of the residual member = " << integral.R << endl << endl;

    if(n%2==0)
    {
        integral = simpsonFormula(a,b,n);
        cout << "-------------Method of Simpson's----------------" << endl;
        cout << "Value of integral = " << integral.integralValue << endl
             << "Value of the residual member = " << integral.R << endl << endl;
    }

    if(n%3==0)
    {
        integral = threeEighth(a,b,n);
        cout << "-------------Method of three eighth----------------" << endl;
        cout << "Value of integral = " << integral.integralValue << endl
             << "Value of the residual member = " << integral.R << endl << endl;
    }

    integral = methodGauss(a,b);
    cout << "-------------Method of Gauss----------------" << endl;
    cout << "Value of integral = " << integral.integralValue << endl
         << "Value of the residual member = " << integral.R << endl << endl;

    cout << "TASK 2" << endl;
    cout << "Enter quantity of pieces = ";
    cin >> n;

    while (qFabs(simpsonFormula(a,b,n).integralValue - simpsonFormula(a,b,2*n).integralValue) > epsilon)
    {
        n*=2;
    }

    cout << endl << "n = " << n << endl << "Value of integral = " << simpsonFormula(a,b,n).integralValue << endl;

    return 0;
}

