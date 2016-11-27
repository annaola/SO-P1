#include <iostream>

#include <vector>
#include <fstream>
using namespace std;
class test{
public:
	int tab[10];
	void functionw(){
		for (int i = 0; i < 10; ++i)
		{
			tab[i]=i;
		}
	}
	void function2 (){
		for (int i = 0; i < 10; ++i)
		{
			tab[i]=i*2;
		}
	}
};
int main(){
	int x[2][2][2];
	x[1][1][1]=10;
	int *y;
	y=x;
	cout<<y[1][1][1];

}