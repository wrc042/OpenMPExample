#include <cstring>
#include <iostream>
#include <omp.h>
#include <random>

#define N 1024

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
    double *B = new double[N * N];
    double seq_time;
    double omp_time;
    double tmp_time;
    random_fill(A, N * N);
    std::cout << "size: " << N << std::endl;

    tmp_time = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * A[j * N + k];
            }
            B[i * N + j] = sum;
            B[j * N + i] = sum;
        }
    }
    seq_time = omp_get_wtime() - tmp_time;

    tmp_time = omp_get_wtime();
#pragma omp parallel for schedule(runtime)
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            double sum = 0;
            for (int k = 0; k < N; k++) {
                sum += A[i * N + k] * A[j * N + k];
            }
            B[i * N + j] = sum;
            B[j * N + i] = sum;
        }
    }
    omp_time = omp_get_wtime() - tmp_time;

    std::cout << "sequence time: " << seq_time << std::endl;
    std::cout << "omp time: " << omp_time << std::endl;

    delete[] A;
    delete[] B;
    return 0;
}
