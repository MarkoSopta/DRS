/*
Generirati proizvoljnu matricu. Distribuirati pojedni redak
pojedinom računalu(procesu). Formirati donju trokutastu matricu
sa ispisom naziva računala(procesa) koji je ispisao pojedini redak.
Program napisati korištenjem C++ funkcija.
*/

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
        size = MPI::COMM_WORLD.Get_size();
        double matrica[100][100], polje[100];
		
        if( rang == 0 ) {
                for (int i=0;i<size;i++){
                        for (int j=0;j<size;j++){
                                matrica[i][j]=i*2;
                        }

                }
        }
        MPI::COMM_WORLD.Scatter(matrica, 100, MPI::DOUBLE, polje,100,MPI::DOUBLE,0); 
        if(rang!=0){
                MPI::COMM_WORLD.Recv(matrica,1,MPI::DOUBLE,rang-1, 25);
        }
        cout<<"Proces "<<rang<<": ";
        for (int i=0;i<=rang;i++){
                cout<<polje[i]<<" ";
        }
        cout<<endl;

        if(rang<size-1){
                MPI::COMM_WORLD.Send(matrica,1,MPI::DOUBLE,rang+1,25); 
        }
        MPI::Finalize(); 
        return 0;
}


