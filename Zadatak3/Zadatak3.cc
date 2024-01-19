<<<<<<< HEAD
/*

Za slanje ranga procesa 0 upotrijebljen je MPI::Comm.Bcast svim
procesima unutar komunikatora. Nakon primitka procesi vraćaju
procesu 0 naziv računala koje je primilo poruku. Proces 0 prima
poruku od ostalih procesa MPI::Comm.Irecv. Ispisati na zaslon da
su primljene poruke na strani procesa 0. Program napisati
korištenjem C++ funkcija.

*/


#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    const int computerNameMaxLength = MPI_MAX_PROCESSOR_NAME;
    char computerName[computerNameMaxLength];
    int nameLength;

    // Proces 0 šalje svoj rang svim procesima
    MPI::COMM_WORLD.Bcast(&rank, 1, MPI::INT, 0);

    if (rank != 0) {
        // Ostali procesi šalju svoje računalno ime procesu 0
        MPI::Get_processor_name(computerName, nameLength);
        MPI::COMM_WORLD.Send(computerName, nameLength, MPI::CHAR, 0, 0);
    } else {
        // Proces 0 prima poruke od ostalih procesa
        std::vector<MPI::Request> requests;

        for (int source = 1; source < size; ++source) {
            MPI::COMM_WORLD.Irecv(computerName, computerNameMaxLength, MPI::CHAR, source, 0);

            // Dodaj request u vektor
            requests.push_back(MPI::COMM_WORLD.Irecv(computerName, computerNameMaxLength, MPI::CHAR, source, 0));
        }

        // Čekaj završetak svih asinkronih operacija
        MPI::Request::Waitall(requests.size(), requests.data());

        // Ispis primljenih poruka
        for (int source = 1; source < size; ++source) {
            std::cout << "Primljena poruka od procesa " << source << ": " << computerName << std::endl;
        }
    }

    MPI::Finalize();
    return 0;
}


=======


#include <iostream>
#include <mpi.h>
using namespace std;
int main (int argc, char* argv[]) {
        int rang;
        int size;
        MPI::Request zahtjev;
        MPI::Status status;

        MPI::Init(argc, argv); 
        rang = MPI::COMM_WORLD.Get_rank(); 
        size = MPI::COMM_WORLD.Get_size(); 
        int a[size][size], b[size];
        if( rang == 0 ) {
                for (int i=0;i<size;i++){
                        for (int j=0;j<size;j++){
                                a[i][j]=i*j;
                        }

                }
        }
        MPI::COMM_WORLD.Scatter(a, size, MPI::INT, b,size,MPI::INT,0); // slanje svima isti broj poruka
        if(rang!=0){
                MPI::COMM_WORLD.Recv(a,1,MPI::INT,rang-1,10);
        }
        cout<<"Proces "<<rang<<": ";
        for (int i=0;i<=rang;i++){
                cout<<b[i]<<" ";
        }
        cout<<endl;

        if(rang<size-1){
        MPI::COMM_WORLD.Send(a,1,MPI::INT,rang+1,10); // 1 sender 1 recv
        }
        MPI::Finalize(); /* Zavrsi MPI */
        return 0;
}

>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a
