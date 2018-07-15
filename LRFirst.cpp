#include <iostream>
#include <fstream>
#include "LRFirst.h"

using namespace std;

LRFirst::LRFirst()
{
}

void LRFirst::transpose(double **m1, double **m2, int x, int y) {
	for (int i = 0; i < y; i++)
		for (int j = 0; j < x; j++)
			m2[i][j] = m1[j][i];
}

void LRFirst::multiplication(double **m1, double **m2, double **m3, int x, int y, int z) {
	double sum;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < z; j++) {
			sum = 0;
			for (int k = 0; k < y; k++)
				sum += m1[i][k] * m2[k][j];
			m3[i][j] = sum;
		}
	}
}

void LRFirst::inverse(double **m1, double **m2, int x)
{
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			m1[i][j + x] = 0;
			m1[i][i+ x] = 1;
		}
	}

	for (int i = 0; i < x; i++)
	{
		while (m1[i][i] == 0)
		{
			for (int y = i + 1; y < x; y++)
			{
				if (m1[y][i] != 0)
				{
					double temp = 0;
					for (int z = i; z < 2 * i; y++)
					{
						temp = m1[y][z];
						m1[y][z] = m1[i][z];
						m1[i][z] = temp;
					}
				}
				break;
			}
		}
	}

	double m = 0;
	for (int i = 0; i < x; i++) {
		for (int j = i - 1; j >= 0; j--) {
			m = (-1)*m1[j][i] / m1[i][i];
			for (int r = 0; r < 2 * x; r++)
				m1[j][r] += m * m1[i][r];
		}
	}

	for (int i = x - 1; i >= 0; i--) {
		for (int j = i - 1; j >= 0; j--) {
			m = (-1)*m1[j][i] / m1[i][i];
			for (int r = 0; r < 2 * x; r++)
				m1[j][r] += m * m1[i][r];
		}
	}

	for (int i = x - 1; i >= 0; i--)
	{
		m = m1[i][i];
		for (int j = 0; j < 2 * x; j++)
			m1[i][j] /= m;
	}

	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < x; j++)
			m2[i][j] = m1[i][x + j];
	}
}

double LRFirst::SST(double **m1, int x)
{
	double SUM1 = 0, SUM2 = 0, average = 0;
	for (int i = 0; i < x; i++)
		SUM1 += m1[i][0];
	average = SUM1 / x;
	for (int i = 0; i < x; i++)
		SUM2 += (m1[i][0] - average)*(m1[i][0] - average);
	return SUM2;
}

double LRFirst::SSE(double **m1, double **m2, double **m3, double **m4, int x, int y)
{
	double SUM1 = 0, SUM2 = 0;
	for (int i = 0; i < x; i++)
	{
		SUM1 = 0;
		for (int j = 0; j < y; j++)
			SUM1 += m2[i][j] * m3[j][0];
		m4[i][0] = SUM1;
	}
	for (int i = 0; i < x; i++)
		SUM2 += (m1[i][0] - m4[i][0])*(m1[i][0] - m4[i][0]);
	return SUM2;
}

void LRFirst::empty1(double **m, int x)
{
	for (int i = 0; i < x; i++)
		delete[]m[i];
	delete[]m;
}
