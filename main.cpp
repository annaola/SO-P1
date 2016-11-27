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
	semafor stan; //0-czysty,1-brudny
};


class Philosopher
{
	
	void think(){
		int x = 0;
		while (true){
			x = rand()%1000000;
	 		usleep(x);
	 	}
	}
	
	
public:
	int m;//liczba plików
	int id;
	int pliki[m];
	void eat(Widelec* tab[]) {
		for (int i=0; i<)
	}

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