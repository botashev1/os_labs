#ifndef OS_LABS_UTILS_H
#define OS_LABS_UTILS_H

#include <ctime>
#include <random>


const double EPS = 1e-14;

struct Args {
    double r;
    int total, success, limit;
};

double GetRandomNumber(double max);

#endif //OS_LABS_UTILS_H
