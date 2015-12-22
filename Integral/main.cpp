#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <taskone.h>

// 13 вариант
// 13. f(x) = (x+1)sin(x);
// a = 1,6; b = 2.4.

using namespace std;
int main()
{
    result integral;
    double a = 1.6;
    double b = 2.4;
    int n;

    cout << "TASK 1" << endl;
    cout << endl << "Split parts (razbienya) = ";
    cin >> n;
    cout << endl;

    integral = rectangleFormula(a,b,n);

    cout << "-------------Method of rectangles----------------" << endl;
    cout << "I = " << integral.integralValue << endl
         << "R = " << integral.R << endl << endl;

    integral = trapezeFormula(a,b,n);
    cout << "-------------Method of trapeze----------------" << endl;
    cout << "I = " << integral.integralValue << endl
         << "R = " << integral.R << endl << endl;

    if(n%2==0)
    {
        integral = simpsonFormula(a,b,n);
        cout << "-------------Method of Simpson's----------------" << endl;
        cout << "I = " << integral.integralValue << endl
             << "R = " << integral.R << endl << endl;
    } else
        cout << "n % 2 != 0 -> Method of Simpson's not found" << endl;

    if(n%3==0)
    {
        integral = threeEighth(a,b,n);
        cout << "-------------Method of three eighth----------------" << endl;
        cout << "I = " << integral.integralValue << endl
             << "R = " << integral.R << endl << endl;
    } else
        cout << "n % 3 != 0 -> Method of three eighth not found" << endl;

    integral = methodGauss(a,b);
    cout << "-------------Method of Gauss (N = 7) ----------------" << endl;
    cout << "I = " << integral.integralValue << endl
         << "R = " << integral.R << endl << endl;

    double epsilon = qPow(10.0, -14.0); // 10^-14

    cout << "TASK 2 (epsilon = " << epsilon << ")" << endl;
    cout << "Enter quantity of pieces = ";
    cin >> n;

    while (qFabs(simpsonFormula(a,b,n).integralValue - simpsonFormula(a,b,2*n).integralValue) > epsilon)
    {
        n*=2;
    }

    cout << endl << "n = " << n << endl << "I = " << simpsonFormula(a,b,n).integralValue << endl;

    return 0;
}

