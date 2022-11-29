#include "utils.h"


double GetRandomNumber(double max) {
    return -max + (double) (random() % (long) 1e5) / 1e5 * max * 2;
}