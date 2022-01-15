#ifndef __operation
#define __operation

#define EPSILION 1e-6
#define ERROR -1

#ifdef DEBUG
#include <stdio.h>
#define LOG_DEBUG(msg, x) printf("[debug] %s: %lf\n", msg, x);
#else
#define LOG_DEBUG(msg, x) (void)(x);
#endif

double sqrt_r(double num);

#endif
