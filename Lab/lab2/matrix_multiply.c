#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 600

void matrix_multiply(int a[N][N], int b[N][N], int c[N][N])
{
int i, j, k;
// Use OpenMP to perform parallel matrix multiplication
#pragma omp parallel for shared(a, b, c) private(i, j, k)
for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
		for (k = 0; k < N; k++)
			c[i][j] += a[i][k] * b[k][j];
}

int main(int argc, char *argv[])
{
double begin,end,prl_time,srl_time;
int a[N][N], b[N][N], c[N][N];
int i,j;
// Initialize the matrices
for (i = 0; i < N; i++)
{
    for (j = 0; j < N; j++)
    {
        a[i][j] = i+j;
        b[i][j] = i*j;
    }
}

begin = omp_get_wtime();
matrix_multiply(a, b, c);
end = omp_get_wtime();
prl_time=(end-begin)*1000;
printf("parallel time:%fms,  C[0][1] equals to %d\n",prl_time,c[0][1]);

return 0;
}
