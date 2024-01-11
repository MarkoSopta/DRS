#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <mpi.h>

using namespace std;

int main(int argc, char* argv[]) {
    int rang;
    int size;
    MPI::Init(argc, argv);
    rang = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();
    MPI::Request zahtjev;
    MPI::Status status;

    vector<string> v;
    string linija;
    ifstream fsm;

    int c = 0;
    ifstream fs;
    string line;

    if (rang == 0) {
        fs.open("input.txt");
        while (getline(fs, line)) {
            c += line.length();
        }
        fs.close();
    }

    MPI::COMM_WORLD.Bcast(&c, 1, MPI::INT, 0);

    float lm = static_cast<float>(c) / static_cast<float>(size);
    int lm1 = static_cast<int>(round(lm));

    fsm.open("input.txt");
    fsm.seekg(rang * lm1, ios::beg);

    if (rang != 0) {
        // Preskoči prvi red ako proces nije rang 0
        fsm.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (fsm && v.size() < lm1) {
        getline(fsm, linija);
        v.push_back(linija);
    }

    fsm.close();

    MPI_Barrier(MPI::COMM_WORLD);

    if (rang < v.size()) {
        cout << "Proces ranga " << rang << " , je ucitao: " << v[rang] << endl;
    }

    MPI::Finalize();
    return 0;
}
