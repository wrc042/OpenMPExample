#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(8)
    {
        int tid = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
        printf("Hello from thread %d of %d\n", tid, num_threads);
    }
    return 0;
}
