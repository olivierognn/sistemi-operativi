#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include "func.h"
#include <wait.h>

using namespace std;

int main(){
	
	pid_t pid;
	//creo sem e lo inizializzo
	int idSem = semget(IPC_PRIVATE, 2, IPC_CREAT | 0664);
	semctl(idSem, spazioDisp, SETVAL, 1);
	semctl(idSem, messDisp, SETVAL, 0);
	//DEBUG
	cout << "\n [DEBUG] Semaforo creato con ID: " << idSem << endl;
	/*cout << "\n [DEBUG] spazioDisp inizializzato a : " <<
		semctl(idSem,spazioDisp, GETVAL);
	cout << "\n [DEBUG] messDisp inizializzato a : " <<
		semctl(idSem,messDisp, GETVAL);*/

	//creo shm 
	int idShm = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0664);
	int * mess;
	mess = (int*) shmat(idShm, 0, 0);

	//creo i processi
	int nProd = 3;
	int nCons = 3;
	int nProcess = nProd + nCons;
	for (int i = 0 ; i < nProcess ; i++){
		pid = fork();
		if (pid == 0){
			if(i % 2 == 0){
				produttore(idSem,mess);
				sleep(10);
				}else{
				consumatore(idSem,mess);
				sleep(10);
				}
			 _exit(0);
			}
	} 
	

	int status;
	for (int i = 0 ; i < nProcess ; i++){
		pid = wait(&status);	
		if(pid==-1)
			cout<<"\nERRORE\n"<<endl;
		else
		cout<<"\nFiglio n.ro "<<pid<<" è morto con status "<<status<<endl;
	}

	
	cout<<"\n\nELimino sem e shm";
	//elimino sem e shm
	semctl(idSem, 0 , IPC_RMID);
	shmctl(idShm, IPC_RMID, 0);
	
	
cout<<endl<<endl;	
}
