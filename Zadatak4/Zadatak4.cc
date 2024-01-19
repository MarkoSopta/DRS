#include <mpi.h>
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>

const int NUM_PHILOSOPHERS = 5;

enum PhilosopherState {
<<<<<<< HEAD
 THINKING,
 EATING
};

void printState(const std::vector<PhilosopherState>& states, int rank) {
 std::string output = "Stanje filozofa: ";
 for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
 if (states[i] == EATING) {
 output += "X ";
 } else if (i == rank) {
 output += "o ";
}else {
output += "O ";
}
 }
 std::cout << output << std::endl;
}

int main(int argc, char** argv) {
 MPI_Init(&argc, &argv);

 int world_size, rank;
 
 

 world_size = MPI::COMM_WORLD.Get_size();
 rank = MPI::COMM_WORLD.Get_rank();

 if (world_size != NUM_PHILOSOPHERS) {
 std::cerr << "Očekivano je " << NUM_PHILOSOPHERS << " procesa." << std::endl;
 MPI_Finalize();
 return 1;
 }

 std::vector<PhilosopherState> philosopherStates(NUM_PHILOSOPHERS, THINKING);

 MPI_Request sendRequest, recvRequest;

 while (true) {
 // Filozof razmišlja
 philosopherStates[rank] = THINKING;
 printState(philosopherStates, rank);
 usleep(1000000); // Simulacija razmišljanja

 // Filozof želi jesti
 philosopherStates[rank] = EATING;
 printState(philosopherStates, rank);

 // Slanje zahtjeva za lijevim štapićem
 MPI_Isend(&rank, 1, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &sendRequest);

//Slanje zahtjeva za desnim štapićem
MPI_Isend(&rank, 1, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &sendRequest);
=======
 THINKING,
 EATING
};

void printState(const std::vector<PhilosopherState>& states, int rank) {
 std::string output = "Stanje filozofa: ";
 for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
 if (states[i] == EATING) {
 output += "X ";
 } else if (i == rank) {
 output += "o ";
}else {
output += "O ";
}
 }
 std::cout << output << std::endl;
}

int main(int argc, char** argv) {
 MPI_Init(&argc, &argv);

 int world_size, rank;

 rank = MPI::COMM_WORLD.Get_rank(); 
 world_size = MPI::COMM_WORLD.Get_size();

 //MPI_Comm_size(MPI_COMM_WORLD, &world_size);
 //MPI_Comm_rank(MPI_COMM_WORLD, &rank);

 if (world_size != NUM_PHILOSOPHERS) {
 std::cerr << "Očekivano je " << NUM_PHILOSOPHERS << " procesa." << std::endl;
 MPI_Finalize();
 return 1;
 }

 std::vector<PhilosopherState> philosopherStates(NUM_PHILOSOPHERS, THINKING);

 MPI_Request sendRequest, recvRequest;

 while (true) {
 // Filozof razmišlja
 philosopherStates[rank] = THINKING;
 printState(philosopherStates, rank);
 usleep(1000000); // 

 // Filozof želi jesti
 philosopherStates[rank] = EATING;
 printState(philosopherStates, rank);

 
 MPI_Isend(&rank, 1, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &sendRequest);


MPI_Isend(&rank, 1, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &sendRequest);
>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a

MPI_Status status;

//Cekanje potvrde za lijevi štapić
<<<<<<< HEAD
MPI_Probe((rank+1)%NUM_PHILOSOPHERS,0,MPI_COMM_WORLD,&status);
int count;
MPI_Get_count(&status,MPI_INT,&count);
MPI_Irecv(NULL, 0, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);

//Cekanje potvrde za desni štapić
MPI_Probe((rank+1)%NUM_PHILOSOPHERS,0,MPI_COMM_WORLD,&status);
MPI_Get_count(&status,MPI_INT,&count);
MPI_Irecv(NULL, 0, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &recvRequest);
=======
MPI_Probe((rank+1)%NUM_PHILOSOPHERS,0,MPI::COMM_WORLD,&status);
int count;
MPI_Get_count(&status,MPI_INT,&count);
MPI_Irecv(NULL, 0, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);

//Cekanje potvrde za desni štapić
MPI_Probe((rank+1)%NUM_PHILOSOPHERS,0,MPI::COMM_WORLD,&status);
MPI_Get_count(&status,MPI_INT,&count);
MPI_Irecv(NULL, 0, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &recvRequest);
>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);

//Filozof jede
printState(philosopherStates, rank);
usleep(1000000); // Simulacija jedenja

//Vraćanje štapića na stol
<<<<<<< HEAD
MPI_Isend(&rank, 1, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &sendRequest);
MPI_Isend(&rank, 1, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &sendRequest);

//Cekanje potvrde za vraćanje lijevog štapića
MPI_Irecv(NULL, 0, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);

//Cekanje potvrde za vraćanje desnog štapića
MPI_Irecv(NULL, 0, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI_COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);
 }
=======
MPI_Isend(&rank, 1, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &sendRequest);
MPI_Isend(&rank, 1, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &sendRequest);

//Cekanje potvrde za vraćanje lijevog štapića
MPI_Irecv(NULL, 0, MPI_INT, (rank + 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);

//Cekanje potvrde za vraćanje desnog štapića
MPI_Irecv(NULL, 0, MPI_INT, (rank + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS, 0, MPI::COMM_WORLD, &recvRequest);
MPI_Wait(&recvRequest, MPI_STATUS_IGNORE);
 }
>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a

MPI_Finalize();

return 0;
}
