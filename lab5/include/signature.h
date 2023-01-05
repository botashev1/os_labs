#ifndef OS_LABS_SIGNATURE_H
#define OS_LABS_SIGNATURE_H

#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <cstddef>
#include <algorithm>
#include <cmath>
#include <vector>

extern "C" {
    int primeCount(int a, int b);
    std::vector <int> sort(std::vector <int> array, int low, int high);
}

#endif /* SIGNATURE */

#endif //OS_LABS_SIGNATURE_H
