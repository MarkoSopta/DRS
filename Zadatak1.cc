#include <iostream>
#include <mpi.h>

/*
workaround erorra koji izbacuje

mpirun --oversubscribe -np 5 ./zad 

*/
using namespace std;

int main(int argc, char* argv[] ){


MPI::Init(argc,argv);
int rank,velicina;

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD,&velicina);


string poruka = "Hello from process: " + std::to_string(rank) + "\n";

for(int i = 0; i <=rank;i++){
cout<<poruka;
}

MPI::Finalize();
return 0;

}
