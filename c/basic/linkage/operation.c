#include "operation.h"

double sqrt_r(double num)
{
    if (num < 0) {
        return ERROR;
    }
    double l = 0, r = num;
    while (r > l && (r - l) > EPSILION) {
        double mean = l + (r-l) / 2;
        LOG_DEBUG("mean", mean)
        LOG_DEBUG("l", l)
        LOG_DEBUG("r", r)
        if (num > mean * mean) {
            l = mean;
        } else if (num < mean * mean) {
            r = mean;
        } else {
            return mean;
        }
    }
    return r;
}
