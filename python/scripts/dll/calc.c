#include "calc.h"

double diff(func f, double x, double delta)
{
	double ret = (f(x + delta) - f(x - delta)) / ( 2 * delta);
	return ret;
}