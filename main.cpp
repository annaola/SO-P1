#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <random>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <sstream>
#include <semaphore.h>
#include <cstddef>

using namespace std;

#define NPHIL 5
#define NSTOCK 3


class Fork
{
	bool dirty; //będziemy wiedzieć, że true, gdy brudny ;)
	int philId;
	sem_t* mutex;

public:
	int id;

	Fork() {}

	Fork(int ind, int pId) : 
		dirty{true},
		philId{pId},
		id{ind}
		{
			sem_init(mutex, 0, 1);
		}

	void lock(){
		sem_wait(mutex);
	}

	void unlock(){
		sem_post(mutex);
	}

	// Monitor
	void getFork(int holderID){
		while (philId != holderID){
			if (dirty){
				sem_wait(mutex);
				dirty = false;
				philId = holderID;
			}
		}
	}
	void setDirty(bool state){
		dirty = state;
	}
};


class Philosopher
{
	int id;
	thread th;
	int zasoby[NSTOCK]; //będziemy ją wypełniać przed "jedzeniem", żeby losowo wybierać zasoby, do których chcemy się dobrać

	void chooseStocks(){
		for (int i=1; i <= NSTOCK; i++){
			zasoby[i] = rand() % 2;
	};
}

public:
	Fork *forks[NSTOCK][NPHIL][NPHIL];//wskaźnik na tablicę forków
	
	Philosopher(int i, Fork fs[NSTOCK][NPHIL][NPHIL]) : id{i} {
		for (int l = 1; l <= NSTOCK; l++){
			for (int j = 1; j <= NPHIL; j++){
				for (int k = 1; k <= NPHIL; k++){
					forks[i][j][k] =&( fs[i][j][k]);
				}
			}
		}
	}

	void eat(){
		chooseStocks();

		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					(*(forks[i][id][j])).lock();
				}
				for (int j = id + 1; j <= NPHIL; j++){
					(*(forks[i][j][id])).lock();
				}
			}
		}
		//zapis swojego id do pliku
		fstream plik[NSTOCK];
		for (int i=1;i<=NSTOCK;i++){
			if (zasoby[i]==1){
				string x;
				x=IntToString(i)+".temp";
				plik[i].open( x, ios::in | ios::out );
				if( plik[i].good() == true )
				{
					plik[i]<<id<<endl;
				    plik[i].close();
				} else cout << "Dostep do pliku zostal zabroniony!" << endl;
			}
		}
<<<<<<< HEAD
=======
		

>>>>>>> 75008cdd1d5a284d032f2aed5c3eb74288ea410e

		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					(*(forks[i][id][j])).unlock();
				}
				for (int j = id + 1; j <= NPHIL; j++){
					(*(forks[i][j][id])).unlock();
				}
			}
		}
	}

	void run(){
		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					(*(forks[i][id][j])).getFork(id);
				}
				for (int j = id + 1; j <= NPHIL; j++){
					(*(forks[i][j][id])).getFork(id);
				}
			}
		}
		eat();
		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					(*(forks[i][id][j])).setDirty(true);
				}
				for (int j = id + 1; j <= NPHIL; j++){
					(*(forks[i][j][id])).setDirty(true);
				}
			}
		}
	}
};

void eatForYourLive (*Philosopher platon){
	(*platon).run();
}

int main(){
	srand(time(NULL));	


	Fork froks[NPHIL*NPHIL*NSTOCK]
	Philosopher philosophers[NPHIL];
	
	for (int i=1; i <= NPHIL; i++)
	{
		Philosopher p = Philosopher(i);
		philosophers[i] = p;
	}

	return 0;
}