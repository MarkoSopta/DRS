/*
*Uporabom MPI-a izraditi simulaciju raspodijeljenog problema n
filozofa. Pri svakoj promjeni program mora vizualno prikazati za
sve filozofe što oni rade. Npr. kada filozof 4 ide jesti, tada treba
ispis izgledati otprilike ovako: "Stanje filozofa: X o O X o" (X-jede,
o-razmišlja, O-čeka na vilice).
* Problem pet filozofa. Filozofi obavljaju samo dvije različite
aktivnosti: misle ili jedu. To rade na poseban način. Na jednom
okruglom stolu nalazi se pet tanjura te pet štapića (između
svaka dva tanjura po jedan). Filozof prilazi stolu, uzima lijevi
štapić, pa desni te jede. Zatim vraća štapiće na stol i odlazi
misliti.
* Program napisati korištenjem C++ funkcija
*/

#include <iostream>
#include <mpi.h>
#include <unistd.h>

#define N 5

using namespace std;

char state[N] = { 'o', 'o', 'o', 'o', 'o' };

void prikaziStanjaFilozofa(int rank) {
    cout << "Stanja filozofa " << rank << ": ";
    for (int i = 0; i < N; i++) {
        cout << state[i] << "  ";
    }
    cout << endl;
}

void test(int rank) {
    // 'O' == HUNGRY, 'X' == EATING, 'o' == THINKING
    if (state[rank] == 'O' && state[(rank + 4) % N] != 'X' && state[(rank + 1) % N] != 'X') {
        state[rank] = 'X';
        MPI::COMM_WORLD.Bcast(&state[0], N, MPI::CHAR, rank);
    }

    prikaziStanjaFilozofa(rank);
    
}

void takeForks(int rank) {
    if (state[(rank + 4) % N] != 'X' && state[(rank + 1) % N] != 'X') {
        state[rank] = 'O';
        test(rank);
        MPI::COMM_WORLD.Bcast(&state[0], N, MPI::CHAR, rank);
    }
}

void returnForks(int rank) {
    sleep(1);
    state[rank] = 'o';
    MPI::COMM_WORLD.Bcast(&state[0], N, MPI::CHAR, rank);
}

void filozof(int rank) {
    while (true) {
        sleep(2);
        takeForks(rank);
        sleep(0);
        returnForks(rank);
    }
}

int main(int argc, char **argv) {
    MPI::Init(argc, argv);
    int size, rank;
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();

    if (size != N) {
        if (rank == 0) {
            cout << "Ovaj program zahtijeva točno 5 procesa." << endl;
        }
        MPI::Finalize();
        return 1;
    }

    filozof(rank);

    MPI::Finalize();
    return 0;
}


