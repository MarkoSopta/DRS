#include <iostream>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]){
MPI::Init(argc,argv);

int rank,velicina;

//MPI_Comm_rank(MPI_COMM_WORLD, &rank);
//MPI_Comm_size(MPI_COMM_WORLD, &velicina);

rank = MPI::COMM_WORLD.Get_rank();
velicina = MPI::COMM_WORLD.Get_size();

if(rank%2==0){
cout << "Procesor " << rank << ": Hello World" << endl;
}
for (int i = 0 ; i<= rank; i++){

MPI::Finalize();
return 0;

}

}
