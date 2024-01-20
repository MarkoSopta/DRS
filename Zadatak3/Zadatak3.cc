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
            
            MPI::COMM_WORLD.Probe(MPI::ANY_SOURCE, 25, status);
            // Asinkrono primanje poruke
            zahtjev = MPI::COMM_WORLD.Irecv(&b, 100, MPI::CHAR, status.Get_source(), 25);
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
