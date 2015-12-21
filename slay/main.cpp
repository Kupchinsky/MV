#include <matrix.h>

using namespace std;

int main( )
{
    Sleep(100);
    int n;
    double detA;
    double normaA,normaR,M;
    ifstream F;
    F.open("zeidel.txt", ios::in);
    //F.open("gauss.txt", ios::in);
    F >> n;

    double **A=new double *[n];
    for(int i=0;i<n;i++)
        A[i]=new double [n+1];

    double **C=new double *[n];
    for(int i=0;i<n;i++)
        C[i]=new double [n+1];

    double **R=new double *[n];
    for(int i=0;i<n;i++)
        R[i]=new double [n];

    double *B = new double [n];
    double *X = new double [n];
    for(int i=0;i<n;i++)
    {
        B[i]=0;
        X[i]=0;
    }

    input(A,n,&F); // заполнение исходной матрицы из файла
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            R[i][j] = A[i][j];

    for(int i=0; i<n; i++)
        for(int j=0; j<n+1; j++)
            C[i][j] = A[i][j];

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~Matrix A~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    output(A, n,n+1);
    detA = determinant(A,n);
    cout << endl << "Matrix determinant = " << detA << endl << endl;
    normaA = norma(A,n);

    cout << "~~~~~~~~~~~~~~Matrix A after transformation by means of the Gauss method~~~~~~~~~~~~~~" << endl;
    gauss(A,n);
    output(A, n, n+1);
    cout << endl;

    cout << "~~~~~~~~~~~~~~Solution of a matrix by a Gauss method~~~~~~~~~~~~~~" << endl << endl;
    if(A[n-1][n-1] != 0)
    {
        solution(A,n,B);
        for(int i=0;i<n;i++)
            cout << "x[" << i+1 <<"] = " << B[i] << endl;
    }
    else
        cout << "There is no decision" << endl;

    cout << endl << "~~~~~~~~~~~~~~Reverse matrix A~~~~~~~~~~~~~~" << endl << endl;
    if(detA != 0)
    {
        reverse(R, n);
        output(R, n, n);
    }
        normaR = norma(R,n);
        M = normaA * normaR;
        cout << endl << "Condition number = " << M << endl << endl;


    cout << endl << "~~~~~~~~~~~~~~Decision of SLAY by Zeydel's method ~~~~~~~~~~~~~~" << endl << endl;
    if(!checkZeidel(C,n))
    {
        cout << "Impossible to solve by this method" << endl;
    }
    else
    {
        zeidel(C,n,X);
        for(int i=0;i<n;i++)
            cout << "x[" << i+1 <<"] = " << X[i] << endl;

        for(int i=0;i<n;i++)
        {
            X[i]=0;
        }
        cout << endl << "~~~~~~~~~~~~~~Method of the fastest descent - Obvious scheme ~~~~~~~~~~~~~~" << endl << endl;
        fastestDescent(C,n,X);
        for(int i=0;i<n;i++)
            cout << "x[" << i+1 <<"] = " << X[i] << endl;
    }


    F.close();
    return 0;
}

