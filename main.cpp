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
	int id;

public:
	//to się chyba nazywa konstruktor :p
	Philosopher(int i) : id{i} {
		pthread_create(&thread, NULL, eating, NULL)
	}

	// a to jest prawdopodobnie destruktor
	~Philosopher(){
		pthread_join(thread, NULL)
	}

	// nie wiem, czy to powinno być tu. W sumie nie wiem nic :D
	void think(){
		srand(time(NULL));
		int x = 0.0;
		while (true){
			x = rand()%1000000;
	 		cout<<x<<str<<endl;
	 		usleep(x);
	 	}
	}
	
	void eating(){
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

	return 0;
}