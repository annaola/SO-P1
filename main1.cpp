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


using namespace std;
string IntToString (int a){
	stringstream ss;
	ss << a;
	string str = ss.str();
	return str;
}




class Philosopher{
public:
	string fork1,fork2,id;

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
};

int main(){
	
	string str="bla";
	string n=IntToString(123098098);
	string nazwa;

	nazwa=str+n+".temp";
	cout<<nazwa<<endl;
	ofstream plik( nazwa );
	plik<<"jsjdjdjdjd";



	Philosopher platon1,platon2,platon3,platon4,platon5;
	platon1.fork1="p1.temp";
	platon1.fork2="p2.temp";
	platon1.id="1\n";

	platon2.fork1="p2.temp";
	platon2.fork2="p3.temp";
	platon2.id=" 2\n";

	platon3.fork1="p3.temp";
	platon3.fork2="p4.temp";
	platon3.id="  3\n";

	platon4.fork1="p4.temp";
	platon4.fork2="p5.temp";
	platon4.id="   4\n";

	platon5.fork1="p5.temp";
	platon5.fork2="p1.temp";
	platon5.id="    5\n"; //każdy wpis ma inną ilość spacji dla ładnego widoku.

	
	

	

	platon1.eating();

	srand(time(NULL));
	int x=0.0;
	cout<<x;
	while (true){


		thread t1(&platon1.eating());
		thread t2(&platon2.eating());
		thread t3(&platon3.eating());
		thread t4(&platon4.eating());
		thread t5(&platon5.eating());



		t1.join();	
		t2.join();
		t3.join();
		t4.join();
		t5.join();

		
		x = rand()%10000;
 		cout<<x<<str<<endl;
 		usleep(x);
 	}
	return 0;
}