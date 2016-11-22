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


	Philosopher platon;
	platon.fork1="p1";
	platon.fork2="p2";
	platon.id="Platon";
	platon.eating();

	srand(time(NULL));
	int x=0.0;
	cout<<x;
	/*while (true){
		x = rand()%1000000;
 		cout<<x<<str<<endl;
 		usleep(x);
 	}*/
	return 0;
}