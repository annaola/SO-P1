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

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}


struct Widelec{
	int id[1][1]; //pierwsze pole to pierwszy filozof, drugie pole to drugi filozof, pomiędzy którymi jest widelec
	int idFilozofa; //id aktualnie trzymającego świdelec filozofa
	semafor stan; //0-czysty,1-brudny

class Philosopher
{

// Znalazłam coś takiego w necie, co Ci wysłałam, przerobiłam nieco na to, co sam stworzyłeś
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

	// Monitor?
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
	int zasoby[NSTOCK]; //będziemy ją wypełniać przed "jedzeniem", żeby losowo wybierać zasoby, do których chcemy się dobrać

	void chooseStocks(){
		for (int i=1; i <= NSTOCK; i++){
			zasoby[i] = rand() % 2;
	};
}

public:
	Fork forks[NSTOCK][NPHIL][NPHIL];
	
	Philosopher(int i, Fork fs[NSTOCK][NPHIL][NPHIL]) : id{i} {
		for (int i = 1; i <= NSTOCK; i++){
			for (int j = 1; j <= NPHIL; j++){
				for (int k = 1; k <= NPHIL; k++){
					forks[i][j][k] = fs[i][j][k];
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
					forks[i][id][j].lock();
				}
				for (int j = id + 1; j <= NPHIL; j++){
					forks[i][j][id].lock();
				}
			}
		}

		// operacja na zasobie w wątku

		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					forks[i][id][j].unlock();
				}
				for (int j = id + 1; j <= NPHIL; j++){
					forks[i][j][id].unlock();
				}
			}
		}
	}

	void run(){
		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					forks[i][id][j].getFork(id);
				}
				for (int j = id + 1; j <= NPHIL; j++){
					forks[i][j][id].getFork(id);
				}
			}
		}
		eat();
		for (int i = 1; i <= NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 1; j < id; j++){
					forks[i][id][j].setDirty(true);
				}
				for (int j = id + 1; j <= NPHIL; j++){
					forks[i][j][id].setDirty(true);
				}
			}
		}
	}
};



int main(){
	srand(time(NULL));	

	/*Philosopher philosophers[NPHIL];
	fstream forks[NPHIL];

	for (long i = 1; i <= NPHIL; i++)
	{
		Philosopher p = Philosopher(i);
		philosophers[i] = p;
	}
*/
	return 0;
}