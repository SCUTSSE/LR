#ifndef LRFIRST_H
#define LRFIRST_H
using namespace std;

class LRFirst
{
public:
	LRFirst();
	void multiplication(double **,double **, double **, int, int , int);
	void transpose(double **, double **, int , int );
	void inverse(double **, double **, int );
	double SST(double** , int) ;
	double SSE(double **, double **, double **, double **, int , int );
	void empty1(double **, int );
};
#endif
