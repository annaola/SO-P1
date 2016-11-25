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

string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}



/*class Philosopher{
public:
	string fork1, fork2, id;

	void eating ( ){
		fstream plik1;
		fstream plik2;
		plik1.open( fork1, ios::in | ios::out );
		if( plik1.good() == true )
		{
   			plik2.open( fork2, ios::in | ios::out );
   			if( plik2.good() == true ){
   				plik1<<id;
   				plik2<<id;
   				plik1.close();
   				plik2.close();
   			}
   			else{
   				cout << "Dostep do pliku zostal zabroniony!" << endl;
   			}
    //tu operacje na pliku
		}
		else {			
			cout << "Dostep do pliku zostal zabroniony!" << endl;
		}
	}
};*/

class Philosopher
{
	pthread_t thread;

	// nie wiem, czy to powinno być tu. W sumie nie wiem nic :D
	void think(){
		srand(time(NULL));
		int x = 0.0;
		while (true){
			x = rand()%1000000;
	 		usleep(x);
	 	}
	}
	
	// to trzeba dopracować
	void eating(){
		/*fstream plik1;
		fstream plik2;
		plik1.open( fork1, ios::in | ios::out );
		if( plik1.good() == true )
		{
   			plik2.open( fork2, ios::in | ios::out );
   			if( plik2.good() == true ){
   				plik1<<id;
   				plik2<<id;
   				plik1.close();
   				plik2.close();
   			}
   			else{
   				cout << "Dostep do pliku zostal zabroniony!" << endl;
   			}
    //tu operacje na pliku
		}
		else {			
			cout << "Dostep do pliku zostal zabroniony!" << endl;
		}*/
	}

	// a to w ogóle napisać
	static void *run(void *arg){
		// tu bym umieściła coś podonego do Rysunku 6.13. ze Stallingsa
		// połączenie eating i think
		return NULL;
	}

public:
	long id;

	//to się chyba nazywa konstruktor :p
	Philosopher() {}

	Philosopher(long i) : id{i}{
		pthread_create(&thread, NULL, run, (void*) id); // coś krzyczy i nie wiem, co z tym zrobić
	}

	// a to jest prawdopodobnie destruktor
	~Philosopher(){
		pthread_join(thread, NULL);
	}
};

int main(){
	
	/*string str="bla";
	string n=IntToString(123098098);
	string nazwa;

	nazwa=str+n+".temp";
	cout<<nazwa<<endl;
	ofstream plik( nazwa );
	plik<<"jsjdjdjdjd";



	Philosopher platon;
	platon.fork1="p1.temp";
	platon.fork2="p2.temp";
	platon.id="Platon";
	platon.eating();

	srand(time(NULL));
	int x=0.0;
	cout<<x;
	while (true){
		x = rand()%1000000;
 		cout<<x<<str<<endl;
 		usleep(x);
 	}*/

	Philosopher philosophers[NPHIL];
	fstream forks[NPHIL];

	for (long i = 1; i <= NPHIL; i++)
	{
		Philosopher p = Philosopher(i);
		philosophers[i] = p;
	}

	return 0;
}