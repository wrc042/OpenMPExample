#include <iostream>
#include <omp.h>

int main() {
    int cnt;
    int results[4];
    cnt = 1;
#pragma omp parallel num_threads(4)
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < 4; i++) {
            cnt += 1;
        }
        results[tid] = cnt;
    }
    std::cout << "no clause:";
    for (int i = 0; i < 4; i++) {
        std::cout << " " << results[i];
    }
    std::cout << std::endl;

    cnt = 1;
#pragma omp parallel num_threads(4) private(cnt)
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < 4; i++) {
            cnt += 1;
        }
        results[tid] = cnt;
    }
    std::cout << "private(not init):";
    for (int i = 0; i < 4; i++) {
        std::cout << " " << results[i];
    }
    std::cout << std::endl;

    cnt = 1;
#pragma omp parallel num_threads(4) firstprivate(cnt)
    {
        int tid = omp_get_thread_num();
        for (int i = 0; i < 4; i++) {
            cnt += 1;
        }
        results[tid] = cnt;
    }
    std::cout << "firstprivate:";
    for (int i = 0; i < 4; i++) {
        std::cout << " " << results[i];
    }
    std::cout << std::endl;
    return 0;
}
