/*

Za slanje ranga procesa 0 upotrijebljen je MPI::Comm.Bcast svim
procesima unutar komunikatora. Nakon primitka procesi vraćaju
procesu 0 naziv računala koje je primilo poruku. Proces 0 prima
poruku od ostalih procesa MPI::Comm.Irecv. Ispisati na zaslon da
su primljene poruke na strani procesa 0. Program napisati
korištenjem C++ funkcija.

*/


#include <iostream>
#include <string>
#include <mpi.h>
using namespace std;

int main(int argc, char* argv[]) {
    int rang;
    int size;
    MPI::Request zahtjev;
    MPI::Status status;    
    char a[100], b[100];   // Polja za pohranu stringova
    MPI::Init(argc, argv); 
    rang = MPI::COMM_WORLD.Get_rank(); 
    size = MPI::COMM_WORLD.Get_size(); 

    
    if (rang == 0) {
        
        MPI::COMM_WORLD.Bcast(&a, 100, MPI::CHAR, 0);

        int i = 0;
        
        while (i < size - 1) {
            // Asinkrono primanje poruke
            zahtjev = MPI::COMM_WORLD.Irecv(&b, 100, MPI::CHAR, MPI::ANY_SOURCE, 25);
            zahtjev.Wait(status); // Čekanje na završetak primanja
            i++;
            cout << "Proces 0 primio je poruku od instance " << b << endl;
        }
    }
    
    else if (rang > 0) {
        
        sprintf(a, "%d", rang);
        // Slanje stringa 'a' glavnom procesu (rang 0)
        MPI::COMM_WORLD.Isend(&a, 100, MPI::CHAR, 0, 25);
    }

    MPI::Finalize();
    return 0;
}

 
