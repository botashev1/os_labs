#include "lab3.h"
#include "utils.h"


bool InCircle(double x, double y, double r) {
    if (x * x + y * y <= r * r + EPS) {
        return true;
    }
    return false;
}

void *CalculateArea(void *args) {
    auto *a = (struct Args *) args;
    for (int i = 0; i < a->limit; i++) {
        a->total++;
        a->success += InCircle(GetRandomNumber(a->r),
                               GetRandomNumber(a->r),
                               a->r);
    }
    return a;
}