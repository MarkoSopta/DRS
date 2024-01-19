<<<<<<< HEAD
/*

Napišite program korištenjem C++ funkcija u kojem će jedan
proces poslati vektor od 100 elemenata svim ostalim procesima,
nakon čega će svaki proces vratiti taj vektor procesu pošiljatelju,
ali uvećan za N+1, gdje je N broj procesa. Pripazite na količinu
vraćenih podataka!

*/
#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI::Init(argc, argv);

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    const int vectorSize = 100;
    std::vector<int> data(vectorSize, 0);

    if (rank == 0) {
        // Proces 0 popunjava vektor i šalje ga ostalim procesima
        for (int i = 0; i < vectorSize; ++i) {
            data[i] = i + 1;
        }

        for (int dest = 1; dest < size; ++dest) {
            MPI::COMM_WORLD.Send(data.data(), vectorSize, MPI::INT, dest, 0);
        }
    } else {
        // Ostali procesi primaju vektor od procesa 0
        MPI::COMM_WORLD.Recv(data.data(), vectorSize, MPI::INT, 0, 0);
        
        for (int i = 0; i < vectorSize; ++i) {
            data[i] += size;
        }

        // Šalju vektor nazad procesu 0
        MPI::COMM_WORLD.Send(data.data(), vectorSize, MPI::INT, 0, 1);
    }

    if (rank == 0) {
        // Proces 0 prikuplja rezultate od ostalih procesa
        for (int source = 1; source < size; ++source) {
            MPI::COMM_WORLD.Recv(data.data(), vectorSize, MPI::INT, source, 1);
            
        }
        
        std::cout << "Konačni vektor: ";
        for (int i = 0; i < vectorSize; ++i) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI::Finalize();
    return 0;
=======
#include <iostream>
#include <mpi.h>
/*
	workaround errora za CPU
	
	mpirun --oversubscribe -np 11 ./Zadatak1

*/
using namespace std;

int main(int argc, char* argv[]){
MPI::Init(argc,argv);

int rank,velicina;

//MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//MPI_Comm_size(MPI_COMM_WORLD, &velicina);

rank = MPI::COMM_WORLD.Get_rank();
velicina = MPI::COMM_WORLD.Get_size();


string poruka = "Hello from process: " + std::to_string(rank) + "\n";

for (int i = 0 ; i<= rank; i++){
cout << poruka;
MPI::Finalize();
return 0;

}

>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a
}
