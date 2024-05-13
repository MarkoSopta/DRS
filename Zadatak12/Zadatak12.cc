#include <iostream>
#include <vector>
#include <omp.h>
#include <thread>
using namespace std;

int main() {
    const int N = 4;
    const int M = 100;
    vector<vector<int>> A(N, vector<int>(M, 1));     
    double start_time_p, end_time_p,start_time_s, end_time_s;

    
    start_time_p = omp_get_wtime();

    omp_set_num_threads(1);

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

    
    end_time_p = omp_get_wtime();

    
    int total_sum_p = 0;
    for(int n = 0; n < N; ++n) {
        for(int i = 0; i < M; ++i) {
            total_sum_p += A[n][i];
        }
    }



    start_time_s = omp_get_wtime();  
    
    
    vector<vector<int>> A_sequential(A);

    {
        
        for(int n = 0; n < N; ++n) {
            for(int i = 2; i < M; ++i) {
                if(i == 2) {
                    A_sequential[n][i] += A_sequential[n][i-1];
                } else if(i == 1) {
                    A_sequential[n][i] = A_sequential[n][i];
                } else {
                    A_sequential[n][i] = A_sequential[n][i-2] + A_sequential[n][i-1];
                }
            }
        }
    }

    int total_sum_s = 0;
    for(int n = 0; n < N; ++n) {
        for(int i = 0; i < M; ++i) {
            total_sum_s += A[n][i];
        }
    }
    
    end_time_s = omp_get_wtime();
    
    cout << "Ukupni zbroj je: " << total_sum_p << endl;
    cout << "Paralelno vrijeme izvršenja: " << end_time_p - start_time_p << " sekundi" << endl;
    cout<<  "--------------------------------"<<endl;
    cout << "Ukupni zbroj je: " << total_sum_s << endl;
    cout << "Sekvencijalno vrijeme izvršenja: " << end_time_s - start_time_s << " sekundi" << endl;
    cout<<  "--------------------------------"<<endl;
    if (end_time_p - start_time_p < end_time_s - start_time_s) {
        cout << "Paralelni način izvršavanja je brži." << endl;
        cout<<  "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl;
    } else {
        cout << "Sekvencijalni način izvršavanja je brži." << endl;
        cout<<  "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-"<<endl;
    }
    return 0;
}
