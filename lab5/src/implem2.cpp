#include "signature.h"
#include <stack>

int primeCount(int a, int b) {
    int prime[b + 1];
    for (int i = 0; i <= b; i++) {
        prime[i] = true;
    }
    prime[0] = prime[1] = false;
    int res = 0;
    for (int i = 2; i <= b; ++i)
        if (prime[i]) {
            if (i * 1ll * i <= b)
                for (int j = i * i; j <= b; j += i)
                    prime[j] = false;

            res += (i >= a);
        }
    return res;
}

std::vector <int> sort(std::vector <int>array, int low, int high) {
    int i = low;
    int j = high;
    int pivot = array[(i + j) / 2];

    while (i <= j)
    {
        while (array[i] < pivot)
            i++;
        while (array[j] > pivot)
            j--;
        if (i <= j)
        {
            std::swap(array[i], array[j]);
            i++;
            j--;
        }
    }
    if (j > low)
        array = sort(array, low, j);
    if (i < high)
        array = sort(array, i, high);

    return array;
}