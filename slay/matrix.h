#include <gauss.h>

using namespace std;

double **minor(int z,int x,int n, double **b)// заполнение миноров
{
  double **C = new double*[n-1];
  for(int i=0;i<n-1;i++)
    C[i]=new double[n-1];

  for(int h=0,i=0; i<n-1;i++,h++)
  {
    if(i==z) h++;
    for(int k=0,j=0;j<n-1;j++,k++)
    {
      if(k==x) k++;
      C[i][j]=b[h][k];
    }
  }
   return C;
}

double determinant(double **b, int n) // детерминант матрицы
{
  double sum=0; int umn=1;
  if(n!=2)
    for(int i=0;i<n;i++)//Разложение по первой строке
    {
        if((i%2)== 0) umn = 1; else umn = -1;
      sum+=umn*b[0][i]*determinant(minor(0,i,n,b), n-1);	// суммирование миноров

    }
   else
     sum=b[0][0]*b[n-1][n-1]-b[n-1][0]*b[0][n-1]; // матрица два на два
  return sum;
}

double **reverse(double **A, int n) // обратная матрица
{
    double **C = new double*[n];
    for(int i=0;i<n;i++)
      C[i]=new double[n];

    double detA = determinant(A,n);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            C[i][j] = qPow(-1.0,i+j) * determinant(minor(j,i,n,A),n-1)/detA;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            A[i][j]=C[i][j];
    return A;
}

double norma(double **A, int n) // норма матрицы
{
    double value = 0;

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            value += A[i][j]*A[i][j];
    value = qSqrt(value);
    return value;
}

