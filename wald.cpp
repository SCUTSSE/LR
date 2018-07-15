#include<iostream>
#include<math.h>
#include "wald.h"
using namespace std;

float wald::waldtest(double b1, double b2, double b3, double b4, double b5, double b6)
{
	double wb1 = 0;
	double wb2 = 0;

	double seb1 = 0; //seb1为tb1的标准方差
		double seb2 = 0; //seb2为tb2的标准方差
		double sb1 = 0;      //seb1为tb1的标准误差
	double sb2 = 0;      //seb2为tb2的标准误差
	double tb1 = 0;
	double tb2 = 0;
	tb1 = (b2 + b3 + b4 + b5 + b6) / 5;    //tb1为去掉b1所剩的均值
	tb2 = (b1 + b3 + b4 + b5 + b6) / 5;    //tb2为去掉b2所剩的均值

	seb1 = ((b2*b2) + (b3*b3) + (b4*b4) + (b5*b5) + (b6*b6)) / 5;
	seb2 = ((b1*b1) + (b3*b3) + (b4*b4) + (b5*b5) + (b6*b6)) / 5;

	sb1 = sqrt(double(seb1));
	sb2 = sqrt(double(seb2));

	wb1 = (tb1 / sb1)*(tb1 / sb1);
	wb2 = (tb2 / sb2)*(tb2 / sb2);

	return wb1, wb2;
}
