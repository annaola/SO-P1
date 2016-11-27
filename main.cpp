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
#define N 10

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}



class Fork
{
	bool dirty; //będziemy wiedzieć, że true, gdy brudny ;)
	int philId;
	int stockId;
	sem_t mutex;

public:
	int id;

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

	Fork(int ind, int pId, int sId) : 
		dirty{true},
		philId{pId},
		stockId{sId},
		id{ind}
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
			//cout<<id<<" generowanie zasobów  "<<zasoby[i]<<endl;
		}

	}

	void think(){
		int x = 0;
		
		x = rand()%100;
 		usleep(x);
	 	
	}
	void wyswietl_zasob(){
		for (int j = 0; j < NSTOCK; ++j)
		{
			cout<<id<<" wyswietl_zasob(): "<<zasoby[j]<<endl;
		}

	}
	void eat(){


		for (int i = 0; i < NSTOCK; i++){
			
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				cout<< id << " próbuje sie dostac do zasobu nr "<< i<<endl;
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					cout << id << "chce zablokowac widelec od " << j<< endl;
					forks[i][id][j]->lock();
					cout << "widelec zablokowany " << id<< j<< endl;
				}
				for (int j = id + 1; j < NPHIL; j++){
					cout << id << "chce zablokowac widelec od " << j << endl;;
					forks[i][j][id]->lock();
					cout << "widelec zablokowany " << id<< j << endl;
				}
			}
		}
		//zapis swojego id do pliku
		fstream plik[NSTOCK];
		for (int i=0;i<NSTOCK;i++){
			
			if (zasoby[i]==1){
				string x;
				x=IntToString(i)+".temp";
				cout<<"dostal sie "<<endl;
				plik[i].open( x,  ios::out |ios::app);
				if( plik[i].good() == true )
				{
					plik[i]<<id<<endl;
				    plik[i].close();
				} else cout << "Dostep do pliku zostal zabroniony!" << endl;
			}
		}

		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					cout << id << "chce odblokować widelec od " << j <<endl;
					forks[i][id][j]->unlock();
					cout << "widelec odblokowany " << id<<j<< endl;
				}
				for (int j = id + 1; j < NPHIL; j++){
					cout << id << "chce odblokować widelec od " << j <<endl;
					forks[i][j][id]->unlock();
					cout << "widelec odblokowany " << id<< j << endl;
				}
			}
		}
	}

	void run(){
		think();
		cout << "filozof " << id << " jest głodny" << endl;
		for (int i = 0; i < NSTOCK; i++){

			cout << "bla" <<id << endl;
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				cout << "blah" << id<< endl;
				for (int j = 0; j < id; j++){
					cout << id << "chce zabrać widelec od " << j << endl;
					forks[i][id][j]->getFork(id);
					cout << "widelec zabrany " << id<< j << endl;
				}
				for (int j = id + 1; j < NPHIL; j++){
					cout << id << "chce zabrać widelec od " << j << endl;
					forks[i][j][id]->getFork(id);
					cout << "widelec zabrany " << id<< j << endl;
				}
			}
		}
		eat();
		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ //jeśli filozof chce dostępu do danego zasobu
				// przeglądamy tylko połowę tablicy
				for (int j = 0; j < id; j++){
					forks[i][id][j]->setDirty(true);
					cout << "widelec brudny " << id << j << endl;
				}
				for (int j = id + 1; j < NPHIL; j++){
					forks[i][j][id]->setDirty(true);
					cout << "widelec brudny "  << id<< j<< endl;
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
	/*for (int i = 0; i < NSTOCK; ++i)
	{
		//cout<<"może tu: "<<platon->zasoby[i];
	}*/
}



int main(){
	srand(time(NULL));	

	Fork forks[NSTOCK][NPHIL][NPHIL];
	Philosopher philosophers[NPHIL];

	cout << "widelce i filozofowie stworzeni" << endl;
	//tworzymy filozofów:

	for (int i=0; i < NPHIL; i++)
	{
		Philosopher p = Philosopher(i,forks);
		p.chooseStocks();
		for (int j = 0; j < NSTOCK; j++)
		{
			cout << "filozof " << i << "chce zasobów" << p.zasoby[j] << endl;
		}
		
		philosophers[i] = p;
	}

	cout << "filozofowie wiedzą, których widelców potrzebują" << endl;

	//Tworzymy widelce

	for (int i = 0; i < NSTOCK; i++){
		for (int j = 0; j < NPHIL; j++){
			for (int k = 0; k < NPHIL; k++){
				//cout<<"widelce  "<< philosophers[j].zasoby[i]<<"  "<<philosophers[k].zasoby[i]<<endl;
				//if (philosophers[j].zasoby[i]==philosophers[k].zasoby[i]&&philosophers[j].zasoby[i]==1){

					int lower=(j<k)?j:k;
					
					Fork t = Fork(i*100+j*10+k,lower,i);
					forks[i][j][k] = t;
				
				//cout<<i<<" "<<j<<" "<<k<<endl;
				
			}
		}
	}


	cout << "przypisanie widelców" << endl;

	thread philosophersThreads[NPHIL]; //tablica wątków

	cout << "tablica wątków" << endl;

	for (int i=0; i<NPHIL; i++){
		cout<<"odpalamy jedzenie filozofa nr: "<<i<<endl;
		Philosopher *p1;
		p1= &(philosophers[i]);
		/*
		for (int j = 0; j < NSTOCK; ++j)
		{
			cout<<"przypisywanie: "<<p1->zasoby[j]<<" "<<" "<<philosophers[i].zasoby[j]<<endl;
		}*/
		
		philosophersThreads[i] = thread(&eatForYourLive, p1);	
	}

	cout << "wątki uruchomione" << endl;

    for (int i=0; i<NPHIL; i++){
        philosophersThreads[i].join();
    }



	return 0;
}