#include "func.h"
#include <iostream>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
using namespace std;

void wait(int idSem, int semNum){
	struct sembuf s;
	s.sem_num = semNum;
	s.sem_flg = 0;
	s.sem_op = -1;
	semop(idSem, &s, 1);
}

void signal(int idSem, int semNum){
	struct sembuf s;
	s.sem_num = semNum;
	s.sem_flg = 0;
	s.sem_op = 1;
	semop(idSem, &s, 1);
}


void produttore(int idSem, int * mess){
	wait(idSem, spazioDisp);
	srand(time(NULL));
	*mess = rand()% 10; //generare il seme con srand(time(NULL));
	cout<<"\nProduttore ha generato : "
		<<*mess<<"  "<<getpid()<<endl;
	sleep(3);
	signal(idSem,messDisp);
	
}

void consumatore(int idSem, int * mess){
	wait(idSem,messDisp);
	cout<<"\nConsumatore ha consumato: "
		<<*mess<<" "<<getpid()<<endl;
	sleep(1);
	signal(idSem,spazioDisp);
}
