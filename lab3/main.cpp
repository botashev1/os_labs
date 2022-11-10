#include <iostream>
#include <pthread.h>
#include <vector>
#include "utils.h"
#include "lab3.h"


int main() {
    int threadCount;
    long double r;
    std::cin >> r >> threadCount;
    unsigned int start_time = clock(); // начальное время
    int total = 0, success = 0, limit = 1e7;
    srandom(time(nullptr));

    std::vector<pthread_t> p(threadCount);
    std::vector<Args> a;

    for (int i = 0; i < threadCount; i++) {
        a.push_back({r, total, success, (limit + threadCount - 1) / threadCount});
        pthread_create(&p[i], nullptr, &CalculateArea, &a[i]);
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(p[i], nullptr);
    }

    unsigned end_time = clock(); // конечное время
    unsigned search_time = end_time - start_time; // искомое время

    int res_success = 0;
    int res_total = 0;
    for (int i = 0; i < threadCount; i++){
        res_success += a[i].success;
        res_total += a[i].total;
    }

    std::cout << res_success * 4 * r * r / (ld) res_total << " " << search_time / (ld) 1000000;
    return 0;
}