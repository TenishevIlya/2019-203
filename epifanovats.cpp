﻿#include "epifanovats.h"

/**
 * Введение в дисциплину
 */
void epifanovats::lab1()
{
cout<<"Hello World!"<<endl;
}


/**
 * Метод Гаусса с выбором главного элемента
 */
void epifanovats::lab2()
{

double* temp = b;//столбец свободжных членов 
//прямой ход
for (int i = 0, j = 0; (i < N - 1) && (j < N - 1); i++, j++)
{
int cur = i;
double max = A[j][j];
for (int num = j; num < N; num++)
if (abs(max) < abs(A[num][j])) max = A[num][j];

while (A[i][j] != max)
i++;

if (cur != i)
{
swap(temp[cur], temp[i]);
swap(A[cur], A[i]);
i = cur;
}
//обратный элемент нашему 
double t = 1/A[i][j];
temp[i] *= t;
for (int cj = j; cj < N; cj++)//строка
A[i][cj] *= t;

for (int ci = i + 1; ci < N; ci++)
{
temp[ci] += temp[i] * (-A[ci][j]);
t = -A[ci][j];
for (int cj = j; cj < N; cj++)
{
A[ci][cj] += A[i][cj] * t;
}
}
}
//обратный ход
for (int i = N - 1, j = N - 1; (i > 0) && (j > 0); i--, j--)
{
int cur = i;
temp[i] *= 1 / A[i][j];
A[i][j] *= 1 / A[i][j];
for (int ci = i - 1; ci >= 0; ci--)
{
temp[ci] += temp[i] * (-A[ci][j]);
A[ci][j] = 0;
}
}

x = temp;
}



/**
 * Метод прогонки
 */
void epifanovats::lab3()
{
int n1=N-1;
double *alfa = new double[N];
double *beta = new double[N];
double y = A[0][0];
alfa[0] = -A[0][1] / y;
beta[0] = b[0] / y;
for (int i = 1; i < n1; i++) {
y = A[i][i] + A[i][i - 1] * alfa[i - 1];
alfa[i] = -A[i][i + 1] / y;
beta[i] = (b[i] - A[i][i - 1] * beta[i - 1]) / y;
}

x[n1] = (b[n1] - A[n1][n1-1] * beta[n1-1]) / (A[n1][n1] + A[n1][n1-1] * alfa[n1-1]);
for (int i = n1-1; i >= 0; i--) {
x[i] = alfa[i] * x[i + 1] + beta[i];
}
}



/**
 * Метод простых итераций
 */
void epifanovats::lab4()
{
	double *new_x = new double[N], 
	tau = 0.001, 
	eps = 1.e-10;
    
	for (int i = 0; i < N; i++)
        x[i] = 0;

    do
    {
        for (int i = 0; i < N; i++)
        {
            double temp = 0;
            for (int j = 0; j < N; j++)
                temp += A[i][j] * x[j];

            new_x[i] = x[i] + tau * (b[i] - temp);
        }

        double maxdif = 0;
        for (int i = 0; i < N; i++)
        {
            if (fabs(x[i] - new_x[i]) > maxdif) maxdif = fabs(x[i] - new_x[i]);
            x[i] = new_x[i];
        }

        if (maxdif < eps) break;
    }while(true);

    delete[] new_x;
}



/**
 * Метод Якоби или Зейделя
 */
void epifanovats::lab5()
{

    double *new_x = new double[N], 
	eps = 1.e-10;
    bool condition;
    
	for (int i = 0; i < N; i++)
        x[i] = 1;

    do
    {
        condition = false;
        for (int i = 0; i < N; i++)
        {
            new_x[i] = b[i];
            for (int j = 0; j < N; j++)
            {
                if (i == j) continue;
                new_x[i] -= A[i][j]*x[j];
            }

            new_x[i] /= A[i][i];
            if (!condition) condition = (fabs(new_x[i] - x[i]) > eps);
            x[i] = new_x[i];
        }

    }while(condition);

    delete[] new_x;
}



/**
 * Метод минимальных невязок
 */
void epifanovats::lab6()
{
double *new_x = new double[N], 
*r = new double[N], 
eps = 1.e-10;

    for (int i = 0; i < N; i++)
        x[i] = 0;

    do
    {
        for (int i = 0; i < N; i++)
        {
            r[i] = b[i];
            for (int j = 0; j < N; j++)
                r[i] -= A[i][j] * x[j];
        }

        double tau, P = 0, Q = 0, t;
        for (int i = 0; i < N; i++)
        {
            t = 0;
            for (int j = 0; j < N; j++)
                t += A[i][j] * r[j];


            P += r[i] * t;
            Q += t * t;
        }

        tau = P / Q;
        for (int i = 0; i < N; i++)
            new_x[i] = x[i] + tau * r[i];

        double maxdif = 0;
        for (int i = 0; i < N; i++)
        {
            if (fabs(x[i] - new_x[i]) > maxdif) 
				maxdif = fabs(x[i] - new_x[i]);
            x[i] = new_x[i];
        }

        if (maxdif < eps) break;
    }while(true);

    delete[] new_x;
    delete[] r;
}



/**
 * Метод сопряженных градиентов
 */
void epifanovats::lab7()
{

}


void epifanovats::lab8()
{

}


void epifanovats::lab9()
{
double * Y = new double[N];//первый вектор приближения
	double * M = new double[N];//второй вектор приближения
	double maxL, L, sum;
	double EPS = 1e-15;
	
	//первичное приближение начального вектора
	for (int i = 0; i < N; i++)
		Y[i] = 0;
	Y[0] = 1;
	
	do{
		sum = 0;
		//нахождение скалярного произведения векторов приближения 
		for (int i = 0; i < N; i++)
			sum += Y[i] * Y[i];
		
		L = sqrt(sum);//норма вектора приближения
		
		//построение последовательности векторов
		for (int i = 0; i < N; i++)
		{
			M[i] = 0;
			for (int j = 0; j < N; j++)
				M[i] += A[i][j] * Y[j] / L;
		}
		sum = 0;
		
		//сравнение нормы полученного вектора с заданной погрешностью
		for (int i = 0; i < N; i++)
			sum += M[i] * M[i];
		maxL = sqrt(sum);
		
		for (int i = 0; i<N; i++)
			Y[i] = M[i];
	} while (abs(maxL - L)>EPS);
	x[0]=maxL;
}


std::string epifanovats::get_name()
{
  return "Epifanova Tatiana Sergeevna";
}
