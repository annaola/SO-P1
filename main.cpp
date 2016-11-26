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

using namespace std;

#define NPHIL 5
#define NFORK 7

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

struct Widelec{
int id[1][1]; //pierwsze pole to pierwszy filozof, drugie pole to drugi filozof, pomiędzy którymi jest widelec
int idFilozofa; //id aktualnie trzymającego świdelec filozofa
bool stan; //0-czysty,1-brudny
};







class Philosopher
{
	pthread_t thread;
	//bool forks[NFORK];
/*
	void fillForks(){
		for (int i; i <= NFORK; i++){
			forks[i] = rand() % 2;
		};
	}
*/
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
	int id;
	int pliki[m];


/*	Philosopher() {}

	Philosopher(long i) : id{i}{
		//thread t1(&thread_1);
		pthread_create(&thread, NULL, run, (void*) id); // już nie krzyczy
		fillForks();// tu funkcja generująca losowe boole w tablicy forks
	}
	// a to jest prawdopodobnie destruktor
	~Philosopher(){
		//pthread_join(thread, NULL);
	}
	*/

	Philosopher(int IdOfHim, int LiczbaPlikow): m(LiczbaPlikow),id(IdOfHim){
		for (int i=0;i<m;i++){
			plik[i]=rand()%2;
		}
	}
};

int main(){
	srand(time(NULL));	

	Philosopher philosophers[NPHIL];
	fstream forks[NPHIL];

	for (long i = 1; i <= NPHIL; i++)
	{
		Philosopher p = Philosopher(i);
		philosophers[i] = p;
	}

	return 0;
}