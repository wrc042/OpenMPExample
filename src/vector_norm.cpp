#include <cstring>
#include <iostream>
#include <omp.h>
#include <random>

#define N (1 << 25)

void random_fill(double *arr, int size) {
    std::random_device rd;
    auto seed(rd());
    std::default_random_engine e(seed);
    std::uniform_real_distribution<double> d(0, 1);
    for (int i = 0; i < size; i++) {
        arr[i] = d(e);
    }
}

int main() {
    double *b = new double[N];
    double ans_seq = 0;
    double ans_omp = 0;
    double ans_omp_sync = 0;
    double seq_time;
    double omp_time;
    double omp_sync_time;
    double tmp_time;
    random_fill(b, N);
    std::cout << "size: " << N << std::endl;

    tmp_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        ans_seq += b[i] * b[i];
    }
    ans_seq = sqrt(ans_seq);
    seq_time = omp_get_wtime() - tmp_time;

    tmp_time = omp_get_wtime();
#pragma omp parallel for reduction(+ : ans_omp)
    for (int i = 0; i < N; i++) {
        ans_omp += b[i] * b[i];
    }
    ans_omp = sqrt(ans_omp);
    omp_time = omp_get_wtime() - tmp_time;

#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        // #pragma omp atomic
#pragma omp critical
        ans_omp_sync += b[i] * b[i];
    }
    ans_omp_sync = sqrt(ans_omp_sync);
    omp_sync_time = omp_get_wtime() - tmp_time;

    std::cout << "sequence result: " << ans_seq << std::endl;
    std::cout << "omp result: " << ans_omp << std::endl;
    std::cout << "omp sync result: " << ans_omp_sync << std::endl;
    std::cout << "sequence time: " << seq_time << std::endl;
    std::cout << "omp time: " << omp_time << std::endl;
    std::cout << "omp sync time: " << omp_sync_time << std::endl;

    delete[] b;
    return 0;
}
