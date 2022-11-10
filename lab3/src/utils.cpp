#include "utils.h"


ld GetRandomNumber(ld min, ld max) {
    return min + (ld) (random() % (long) 1e5) / 1e5 * (max - min);
}