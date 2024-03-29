/*
Napravite program koji izračunava zbroj prilagođenih prefiksa dan
u nastavku za 4 različita niza i nakon toga ih sve zbrojiti.
Upotrijebite OpenMP directive za paralelno izvršavanje.
 A(1) = A(1)
 A(2) = A(2) + A(1)
 A(i) = A(i-2) + A(i-1)
*/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10
int main(void) {
  int x[N], y[N], z[N], c[N], zb[N];
  int i, sum =0; 

  for (i = 0; i < N; i++) {
    x[i] = i+1;
    y[i] = i*2;
    z[i] = i+2;
    c[i] = i*3;
  }
  
  omp_set_num_threads(4);
  #pragma omp parallel shared(x, y, z, c, zb) private(i)
  {
    #pragma omp for
    for (int i = 0; i < N; i++) {
        
	if(i==1) {
	   x[i]+=x[0];
	   y[i]+=y[0];
	   z[i]+=z[0];
	   c[i]+=c[0];
	}
		
	if(i>1) {
	   x[i]=x[i-2]+x[i-1];  // Prethodna vrijednost + sljedeća
           y[i]=y[i-2]+y[i-1];
           z[i]=z[i-2]+z[i-1];
           c[i]=c[i-2]+c[i-1];
	}
		
        zb[i]=x[i]+y[i]+z[i]+c[i];
        sum+=zb[i];

    }
  }
    printf("Ukupna suma 4 niza je: %d  \n\n",sum);

}