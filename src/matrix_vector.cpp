#include <cstring>
#include <iostream>
#include <omp.h>
#include <random>

#define N (1 << 14)

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
    double *A = new double[N * N];
    double *b = new double[N];
    double *x_seq = new double[N];
    double *x_omp = new double[N];
    double *x_omp_fs = new double[N];
    double seq_time;
    double omp_time;
    double omp_fs_time;
    double tmp_time;
    random_fill(A, N * N);
    random_fill(b, N);
    memset(x_seq, 0, sizeof(double) * N);
    memset(x_omp, 0, sizeof(double) * N);
    memset(x_omp_fs, 0, sizeof(double) * N);
    std::cout << "size: " << N << std::endl;

    tmp_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x_seq[i] += A[i * N + j] * b[j];
        }
    }
    seq_time = omp_get_wtime() - tmp_time;

    tmp_time = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        double tmp = 0;
        for (int j = 0; j < N; j++) {
            tmp += A[i * N + j] * b[j];
        }
        x_omp[i] = tmp;
    }
    omp_time = omp_get_wtime() - tmp_time;

    tmp_time = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            x_omp_fs[i] += A[i * N + j] * b[j];
        }
    }
    omp_fs_time = omp_get_wtime() - tmp_time;

    std::cout << "sequence time: " << seq_time << std::endl;
    std::cout << "simple omp time: " << omp_time << std::endl;
    std::cout << "false sharing time: " << omp_fs_time << std::endl;

    delete[] A;
    delete[] b;
    delete[] x_seq;
    delete[] x_omp;
    delete[] x_omp_fs;
    return 0;
}
