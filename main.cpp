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
#define NSTOCK 7

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}



/*truct Widelec{
int id[1][1]; //pierwsze pole to pierwszy filozof, drugie pole to drugi filozof, pomiędzy którymi jest widelec
int idFilozofa; //id aktualnie trzymającego świdelec filozofa
bool stan; //0-czysty,1-brudny
};
*/



// Znalazłam coś takiego w necie, co Ci wysłałam, przerobiłam nieco na to, co sam stworzyłeś
class Fork
{
	bool dirty; //będziemy wiedzieć, że true, gdy brudny ;)
	int philId;
	sem_t* mutex;

public:
	int id;

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
	
};

/*class Philosopher
{
	pthread_t thread;
	bool forks[NFORK];

	void fillForks(){
		for (int i; i <= NFORK; i++){
			forks[i] = rand() % 2;
		};
	}

	void think(){
		int x = 0.0;
		while (true){
			x = rand()%1000000;
	 		usleep(x);
	 	}
	}
	
	// to trzeba dopracować
	void eating(){

	}

	// a to w ogóle napisać
	static void *run(void *arg){

		return NULL;
	}

public:
	int m;//liczba plików
	long id;
	int pliki[m];


	Philosopher() {}

	Philosopher(long i) : id{i}{
		//thread t1(&thread_1);
		pthread_create(&thread, NULL, run, (void*) id); // już nie krzyczy
		fillForks();// tu funkcja generująca losowe boole w tablicy forks
	}
	// a to jest prawdopodobnie destruktor
	~Philosopher(){
		//pthread_join(thread, NULL);
	}


	Philosopher(int IdOfHim, int LiczbaPlikow): m(LiczbaPlikow),id(IdOfHim){
		for (int i=0;i<m;i++){
			plik[i]=rand()%2;
		}
	}
};
*/

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