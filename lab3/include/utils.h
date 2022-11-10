#ifndef OS_LABS_UTILS_H
#define OS_LABS_UTILS_H

#include <ctime>
#include <random>

#define ld long double

const ld EPS = 1e-14;

struct Args {
    ld r;
    int total, success, limit;
    pthread_mutex_t mutex;
};

ld GetRandomNumber(ld min, ld max);

#endif //OS_LABS_UTILS_H
