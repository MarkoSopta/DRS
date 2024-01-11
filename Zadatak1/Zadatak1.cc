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

}
