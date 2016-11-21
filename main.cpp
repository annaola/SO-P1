#include <iostream>
#include <thread>
#include <fstream>
#include <vector>
#include <random>
#include <unistd.h>
#include <cstdlib>
#include <time.h>


using namespace std;
int main(){

	srand(time(NULL));
	int x=0.0;
	cout<<x;
	while (true){
		x = rand()%1000000;
 		cout<<x<<endl;
 		usleep(x);
 	}
	return 0;
}