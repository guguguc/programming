#ifndef __CALC_H
#define  __CALC_H
#define DllExport   __declspec( dllexport )

typedef double (*func)(double);

DllExport double diff(func f, double x, double delta);

#endif