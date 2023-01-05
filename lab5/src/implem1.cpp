#include "signature.h"

int primeCount(int a, int b) {
    int res = 0;
    for (int i = a; i <= b; i++){
        if (i > 1) {
            bool is_prime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    is_prime = false;
                    break;
                }
            }
            if (is_prime) {
                res++;
            }
        }
    }
    return res;
}

std::vector <int>sort(std::vector <int>array, int low, int high) {
    for (int i = 0; i < high; i++) {
        for (int j = 0; j < high - 1; j++) {
            if (array[j] > array[j + 1]) {
                std::swap(array[j], array[j + 1]);
            }
        }
    }
    return array;
}