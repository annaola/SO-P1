/*
Zespół: Anna Biadasiewicz i Michał Martusewicz

zadanie polega na rozszerzeniu klasycznego problemu ucztujących filozofów na n filozofów i k zasobów.
Stosujemy algorytm Chandy/Misra (za: Wikipedia):


1. Dla każdej pary filozofów ubiegającej się o dostęp do zasobu stwórz widelec 
	i wręcz go filozofowi z niższym identyfikatorem (ID). 
	Każdy widelec może być brudny lub czysty. 
	Na początku wszystkie widelce są brudne.

2. Gdy filozof chce użyć zbioru zasobów (tj. jeść), musi uzyskać widelec 
	od konkurujących z nim sąsiadów. Dla każdego widelca, który nie jest w jego posiadaniu, 
	wysyła żądanie w celu jego uzyskania.

3. Gdy filozof z widelcem otrzymuje żądanie, zatrzymuje widelec, 
	jeśli jest on czysty, jeśli natomiast jest brudny, to go przekazuje, uprzednio myjąc.

4. Gdy filozof kończy jedzenie, wszystkie jego widelce stają się brudne. 
	Jeśli podczas jedzenia przyszło żądanie od innego filozofa, wtedy po skończeniu jedzenia, 
	przekazywany jest czysty widelec.


Dla każdego filozofa losujemy, jakie pliki będzie otwierał.
"Jedzenie" polega na zapisaniu swojego ID do wszystkich plików, które dany filozof otwiera.

*/






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



#define NPHIL 8 //liczba filozofów
#define NSTOCK 5 //liczba używanych plików
#define N 10

//funkcja pomocnicza zamieniająca inta na stringa, służy do tworzenia nazw plików

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}

//klasa Fork będąca naszym "widelcem"

class Fork
{
	bool dirty; //true-brudny, false-czysty
	int philId; //id filozofa, który aktualnie dzierży widelec
	sem_t mutex;

public:

	void lock(){
		sem_wait(&mutex);
	}

	void unlock(){
		sem_post(&mutex);
		
	}

	// Monitor
	void getFork(int holderID){
		while (philId != holderID){
			if (dirty){
				sem_wait(&mutex);
				dirty = false;
				philId = holderID;
				sem_post(&mutex);
			}
			else{
				int x = rand()%1000;
 				usleep(x);	
			}
					
		}
	}
	void setDirty(bool state){
		dirty = state;
	}

	Fork() {}

	Fork(int pId) : 
		dirty{true},
		philId{pId}
		{
			sem_init(&mutex, 0, 1);
		}

	
};


class Philosopher
{
	int id;

public:
	int zasoby[NSTOCK]; //będziemy ją wypełniać przed "jedzeniem", żeby losowo wybierać zasoby, do których chcemy się dobrać
	
	Fork *forks[NSTOCK][NPHIL][NPHIL];//wskaźnik na tablicę forków

	void chooseStocks(){
		for (int i=0; i < NSTOCK; i++){
			zasoby[i] = rand() % 2;
		}

	}

	void think(){
		int x = 0;
		
		x = rand()%100;
 		usleep(x);
	 	
	}

	void eat(){


		for (int i = 0; i < NSTOCK; i++){
			
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					forks[i][id][j]->lock();
				}
				for (int j = id + 1; j < NPHIL; j++){
					forks[i][j][id]->lock();
				}
			}
		}
		//zapis swojego id do pliku
		fstream plik[NSTOCK];
		for (int i=0;i<NSTOCK;i++){
			
			if (zasoby[i]==1){
				string x;
				x=IntToString(i)+".temp";

				plik[i].open( x,  ios::out |ios::app);
				if( plik[i].good() == true )
				{
					plik[i]<<id<<endl;
				    plik[i].close();
				} else cout <<"brak dostępu";
			}
		}

		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					forks[i][id][j]->unlock();
				}
				for (int j = id + 1; j < NPHIL; j++){
					forks[i][j][id]->unlock();
				}
			}
		}
	}

	void run(){
		think();

		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					forks[i][id][j]->getFork(id);
				}
				for (int j = id + 1; j < NPHIL; j++){
					forks[i][j][id]->getFork(id);
				}
			}
		}

		eat();

		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					forks[i][id][j]->setDirty(true);
				}
				for (int j = id + 1; j < NPHIL; j++){
					forks[i][j][id]->setDirty(true);
				}
			}
		}
	}


	Philosopher() {}
	
	Philosopher(int id1, Fork fs[NSTOCK][NPHIL][NPHIL]) : id{id1} {
		for (int l = 0; l < NSTOCK; l++){
			for (int j = 0; j < NPHIL; j++){
				for (int k = 0; k <NPHIL; k++){
					forks[l][j][k] =&( fs[l][j][k]);
				}
			}
		}
	}
};

void eatForYourLive (Philosopher* platon){
	for(int i = 0; i < N; i++){
		platon->run();
	}
}



int main(){
	srand(time(NULL));	

	Fork forks[NSTOCK][NPHIL][NPHIL]; 	// tablica wszystkich widelców
	Philosopher philosophers[NPHIL];	// tablica filozofów

	//tworzymy filozofów:
	for (int i=0; i < NPHIL; i++)
	{
		Philosopher p = Philosopher(i,forks);
		p.chooseStocks();
		philosophers[i] = p;
	}

	//Tworzymy widelce
	for (int i = 0; i < NSTOCK; i++){
		for (int j = 0; j < NPHIL; j++){
			for (int k = 0; k < NPHIL; k++){

					int lower=(j<k)?j:k;
					Fork t = Fork(lower);
					forks[i][j][k] = t;
				

			}
		}
	}

	thread philosophersThreads[NPHIL]; 	//tablica wątków

	for (int i=0; i<NPHIL; i++){
		Philosopher *p1;
		p1= &(philosophers[i]);	
		philosophersThreads[i] = thread(&eatForYourLive, p1);	
	}

    for (int i=0; i<NPHIL; i++){
        philosophersThreads[i].join();
    }
	return 0;
}