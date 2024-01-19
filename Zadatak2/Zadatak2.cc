<<<<<<< HEAD
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
=======


#include <iostream>
#include <mpi.h>
#include <string>
using namespace std;
int main (int argc, char* argv[]) {
        int rang;
        int size;
        MPI::Request zahtjev;
        MPI::Status status;
        int a;
        int b;
        char string[7];
        MPI::Init(argc, argv); 
        rang = MPI::COMM_WORLD.Get_rank();
        size=MPI::COMM_WORLD.Get_size();
        if( rang == 0 ) {
                a=rang;
                MPI::COMM_WORLD.Bcast(&a, 1, MPI::INT, 0);
                int i=0;
                while(i<size-1){
                        zahtjev = MPI::COMM_WORLD.Irecv(&string,7, MPI_CHAR, MPI::ANY_SOURCE, 20);
                        zahtjev.Wait(status);
                        i++;
                        printf("Procesor %d je primio poruku %s\n",a, string);
                }
}
        else if(rang > 0) {



                int len;
                char name[7];
                 MPI_Get_processor_name(name, &len);


                MPI::COMM_WORLD.Bcast(&b, 1, MPI::INT, 0);

                MPI::COMM_WORLD.Isend(&name,strlen(name), MPI_CHAR, 0, 20);


}

        MPI::Finalize();
        return 0;
}

>>>>>>> 9bb5630629e9b0103bf01869685076081de4328a
