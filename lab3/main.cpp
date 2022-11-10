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
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, nullptr);
    Args *a = new Args{r, total, success, (limit + threadCount - 1) / threadCount, mutex};
    for (int i = 0; i < threadCount; i++) {
        pthread_create(&p[i], nullptr, &CalculateArea, a);
    }

    for (int i = 0; i < threadCount; i++) {
        pthread_join(p[i], nullptr);
    }

    unsigned end_time = clock(); // конечное время
    unsigned search_time = end_time - start_time; // искомое время
    std::cout << a->success * 4 * r * r / (ld) a->total << " " << search_time / (ld) 1000000;
    pthread_mutex_destroy(&mutex);
    return 0;
}