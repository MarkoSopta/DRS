#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>


int generateRandomNumber() {
    return rand() % 100;
}


int calculateArithmeticSum(const std::vector<int>& numbers) {
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
	
    // MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    // MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    srand(time(NULL) + world_rank);

    int random_number = generateRandomNumber();

    std::vector<int> all_numbers(world_size);

    MPI_Gather(&random_number, 1, MPI_INT, &all_numbers[0], 1, MPI_INT, 0, MPI::COMM_WORLD);

    if (world_rank == 0) {
        int arithmetic_sum = calculateArithmeticSum(all_numbers);
        double arithmetic_mean = static_cast<double>(arithmetic_sum) / world_size;

        MPI_Bcast(&arithmetic_mean, 1, MPI_DOUBLE, 0, MPI::COMM_WORLD);

        for (int i = 0; i < world_size; ++i) {
            double deviation_percent = ((double)all_numbers[i] - arithmetic_mean) / arithmetic_mean * 100.0;
            std::cout << "Process " << i << ": Deviation = " << deviation_percent << "%" << std::endl;
        }
    } else {
        double arithmetic_mean;
        MPI_Bcast(&arithmetic_mean, 1, MPI_DOUBLE, 0, MPI::COMM_WORLD);

        double deviation_percent = ((double)random_number - arithmetic_mean) / arithmetic_mean * 100.0;
        std::cout << "Process " << world_rank << ": Deviation = " << deviation_percent << "%" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
