#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <random>
#include <unistd.h>
#include <cstdlib>
#include <time.h>
#include <string>

using namespace std;
class Philospher{
	string file1,file2,id;

	void eating ( string file1, string file2,string id){
		fstream plik1;
		fstream plik2;
		plik1.open( file1, ios::in | ios::out );
		if( plik1.good() == true )
		{
   			plik2.open( file2, ios::in | ios::out );
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
	string n=0;
	string nazwa="";
	nazwa=str+".temp";
	cout<<nazwa<<endl;
	//ofstream plik( nazwa );
	//plik<<"jsjdjdjdjd";


	srand(time(NULL));
	int x=0.0;
	cout<<x;
	while (true){
		x = rand()%1000000;
 		cout<<x<<str<<endl;
 		usleep(x);
 	}
	return 0;
}