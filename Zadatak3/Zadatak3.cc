

#include <iostream>
#include <mpi.h>
using namespace std;
int main (int argc, char* argv[]) {
        int rang;
        int size;
        MPI::Request zahtjev;
        MPI::Status status;

        MPI::Init(argc, argv); 
        rang = MPI::COMM_WORLD.Get_rank(); 
        size=MPI::COMM_WORLD.Get_size(); 
        int a[size][size], b[size];
        if( rang == 0 ) {
                for (int i=0;i<size;i++){
                        for (int j=0;j<size;j++){
                                a[i][j]=i*j;
                        }

                }
        }
        MPI::COMM_WORLD.Scatter(a, size, MPI::INT, b,size,MPI::INT,0); // slanje svima isti broj poruka
        if(rang!=0){
                MPI::COMM_WORLD.Recv(a,1,MPI::INT,rang-1,10);
        }
        cout<<"Proces "<<rang<<": ";
        for (int i=0;i<=rang;i++){
                cout<<b[i]<<" ";
        }
        cout<<endl;

        if(rang<size-1){
        MPI::COMM_WORLD.Send(a,1,MPI::INT,rang+1,10); // 1 sender 1 recv
        }
        MPI::Finalize(); /* Zavrsi MPI */
        return 0;
}

