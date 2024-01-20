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


int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    const int computerNameMaxLength = MPI_MAX_PROCESSOR_NAME;
    char computerName[computerNameMaxLength];
    int nameLength;

    if (rank == 0) {
        // Proces 0 šalje svo rang svim procesima
        MPI::COMM_WORLD.Bcast(&rank, 1, MPI::INT, 0);

        // Proces 0 prima poruke od ostalih procesa
        for (int source = 1; source < size; ++source) {
            MPI::COMM_WORLD.Recv(computerName, computerNameMaxLength, MPI::CHAR, source, 0);
            std::cout << "Primljena poruka od procesa " << source << ": " << computerName << std::endl;
        }
    } else {
        
        MPI::COMM_WORLD.Bcast(&rank, 1, MPI::INT, 0);

        // Ostali procesi šalju svoje računalno ime procesu 0
        MPI::Get_processor_name(computerName, nameLength);
        MPI::COMM_WORLD.Send(computerName, nameLength, MPI::CHAR, 0, 0);
    }

    MPI::Finalize();
    return 0;
}
