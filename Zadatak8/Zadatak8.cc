#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
	
	rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
   // MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   // MPI_Comm_size(MPI_COMM_WORLD, &size);

   
    std::vector<int> localVector(100, rank + 1);  // Primer: punjenje lokalnog vektora vrednostima rank + 1

   
    std::vector<int> globalVector(size * 100);
    MPI_Gather(localVector.data(), 100, MPI_INT, globalVector.data(), 100, MPI_INT, 0, MPI_COMM_WORLD);

   
    if (rank == 0) {
        int sum = 0;
        for (int i = 0; i < size * 100; ++i) {
            sum += globalVector[i];
        }
        double average = static_cast<double>(sum) / (size * 100);

       
        std::cout << "Srednja vrednost globalnog vektora: " << average << std::endl;
    }

    MPI_Finalize();
    return 0;
}
