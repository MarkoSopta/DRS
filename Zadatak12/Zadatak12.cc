#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

int main() {
    const int N = 4;
    const int M = 100;
    vector<vector<int>> A(N, vector<int>(M, 1));
    int trh_numb;
    double start_time, end_time;

    
    start_time = omp_get_wtime();

    omp_set_num_threads(10);

    #pragma omp parallel
    {
        #pragma omp for
        for(int n = 0; n < N; ++n) {
            for(int i = 2; i < M; ++i) {
                if(i == 2) {
                    A[n][i] += A[n][i-1];
                } else if(i == 1) {
                    A[n][i] = A[n][i];
                } else {
                    A[n][i] = A[n][i-2] + A[n][i-1];
                }
            }
        }
    }

    
    end_time = omp_get_wtime();

    
    int total_sum = 0;
    for(int n = 0; n < N; ++n) {
        for(int i = 0; i < M; ++i) {
            total_sum += A[n][i];
        }
    }

    
    cout << "Ukupni zbroj je: " << total_sum << endl;
    cout << "Vrijeme izvršenja: " << end_time - start_time << " sekundi" << endl;

    return 0;
}
