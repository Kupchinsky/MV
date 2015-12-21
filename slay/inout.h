using namespace std;

void input(double **x, int n,ifstream *f1) // ввод массива
{
    for(int i=0; i<n; i++)
       for(int j=0; j<n+1; j++)
        *f1 >> x[i][j];
}

void output(double **x, int n ,int m)// вывод массива
{
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
            cout << setw(11) <<  x[i][j];
        cout << endl;
    }
}
