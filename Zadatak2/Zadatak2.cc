/*
Napišite program koji će ispisati proizvoljnu
poruku na monitor onoliko puta koliki je rang
procesa koji ispisuje poruku. Pokrenite dobiveni
program na 1, 2, 7 i 11 procesora.
*/

#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    for (int i = 0; i < rank + 1; ++i) {
        std::cout << "Proces " << rank << " ispisuje poruku" << std::endl;
    }

    MPI::Finalize();
    return 0;
}
