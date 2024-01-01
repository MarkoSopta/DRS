

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

