#include "lab3.h"
#include "utils.h"


bool InCircle(ld x, ld y, ld r) {
    if (x * x + y * y <= r * r + EPS) {
        return true;
    }
    return false;
}

void *CalculateArea(void *args) {
    auto *a = (struct Args *) args;
    for (int i = 0; i < a->limit; i++) {
        pthread_mutex_lock(&(a->mutex));
        a->total++;
        a->success += InCircle(GetRandomNumber(-a->r, a->r),
                               GetRandomNumber(-a->r, a->r),
                               a->r);
        pthread_mutex_unlock(&(a->mutex));
    }
    return a;
}