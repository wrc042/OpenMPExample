#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel num_threads(8)
    {
        int tid = omp_get_thread_num();
        int num_threads = omp_get_num_threads();
#pragma omp for ordered
        for (int i = 0; i < num_threads; i++) {
            // do something
            // #pragma omp ordered
            // #pragma omp critical
            std::cout << "Hello from thread " << tid << std::endl;
        }
    }
    return 0;
}
