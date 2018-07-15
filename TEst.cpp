#include "LRFirst.h"
#include "wald.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
using namespace std;

int main()
{
	LRFirst lr;
	char filename[30];
	cout << "Input original data file: \n";
	ifstream infile;
	cin >> filename;
	infile.open(filename);
	if (!infile) {
		cout << "Opening the file failed!\n";
		exit(1);
	}
	int row=0;
	int col=0;
	double sst;
	double sse;
	double f;
	double r2;
	string tmp;
	while (getline(infile, tmp, '\n')) {
		row++;
	}
	double tmp1;
	char c;
	for (int i = 0; i < 100; i++) {
		infile >> tmp1;
		++col;
		c = infile.peek();
		if ('\n' == c)
		{
			break;
		}
	}
	double **matrix = new double*[row];
	double **x = new double*[row];
	double **y = new double*[row];
	double **xt = new double*[col];
	double **xtx = new double*[col];
	double **xtxi = new double*[col];
	double **xtxixt = new double*[col];
	double **b = new double*[col];
	double **ym = new double*[row];

	for (int i = 0; i < row; i++) {
		matrix[i] = new double[col];
		x[i] = new double[col];
		y[i] = new double[1];
		ym[i] = new double[1];
	}

	for (int i = 0; i < col; i++) {
		xt[i] = new double[row];
		xtx[i] = new double[2 * col];
		xtxi[i] = new double[col];
		xtxixt[i] = new double[row];
		b[i] = new double[1];
	}
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			infile >> matrix[i][j];
	infile.close();

	for (int i = 0; i < row; i++) {
		x[i][0] = 1;
		y[i][0] = matrix[i][col - 1];
		for (int j = 0; j < col - 1; j++)
			x[i][j + 1] = matrix[i][j];
	}
	lr.transpose(x, xt, row, col);
	lr.multiplication(xt, x, xtx, col, row, col);
	lr.inverse(xtx, xtxi, col);
	lr.multiplication(xtxi, xt, xtxixt, col, col, row);
	lr.multiplication(xtxixt, y, b, col, row, 1);
	sst = lr.SST(y, row);
	sse = lr.SSE(y, x, b, ym, row, col);
	f = ((sst - sse) / (col - 1)) / (sse / (row - col));
	r2 = 1 / (1 + (row - col) / f / (col - 1));

	cout << "输出b矩阵：\n";
	for (int i = 0; i < col; i++) {
		cout << setiosflags(ios::fixed) << setprecision(4) << b[i][0] << ' ';
	}
	double b1 = b[0][0];
	double b2 = b[1][0];
	double b3 = b[2][0];
	double b4 = b[3][0];
	double b5 = b[4][0];
	double b6 = b[5][0];
	cout << endl;
	cout << "sse =" << sse << ";" << "sst =" << sst << ";" << "f =" << f << ";" << "r2 =" << r2 << endl;
	wald W;
	W.waldtest(b1,b2,b3,b4,b5,b6);
	lr.empty1(matrix, row);
	lr.empty1(x, row);
	lr.empty1(y, row);
	lr.empty1(xt, col);
	lr.empty1(xtx, col);
	lr.empty1(xtxi, col);
	lr.empty1(xtxixt, col);
	lr.empty1(b, col);
	lr.empty1(ym, row);
}
