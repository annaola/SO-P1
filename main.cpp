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
#define NSTOCK 15 //liczba używanych plików
#define NREC 10 //liczba zmian plików
#define N 5 //liczba zmian myślenie-jedzenie

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
	bool dirty; 	// true-brudny, false-czysty
	int philId; 	// id filozofa, który aktualnie dzierży widelec
	sem_t mutex; 	// semafor

public:

	void lock(){
		sem_wait(&mutex);
	}

	void unlock(){
		sem_post(&mutex);
	}

	// Monitor
	void getFork(int holderID){
		while (philId != holderID){			// Dopóki filozof wołający nie dostanie widelca, 
											// to sprawdza czy może nie jest on już brudny
			if (dirty){
				sem_wait(&mutex);
				dirty = false;
				philId = holderID;
				sem_post(&mutex);
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
	int id; //id filozofa

public:
	int zasoby[NSTOCK];	// 0 oznacza, że filozof nie korzysta z pliku i, a 1, że korzysta
	
	Fork *forks[NSTOCK][NPHIL][NPHIL];	// wskaźnik na tablicę forków

	//funkcja zapełniająca losowo zasoby
	void chooseStocks(){
		string s;
		for (int i=0; i < NSTOCK; i++){
			zasoby[i] = rand() % 2;
		}
	}
	
	//funkcja odpowiadająca za myślenie
	void think(){
		int x = 0;
		
		x = rand()%100;
 		usleep(x);
	}
	
	//funkcja jedzenie: blokuję wszystkie widelce, wpisuję się do pliku, odblokowuję widelce
	void eat(){
		for (int i = 0; i < NSTOCK; i++){
			if (zasoby[i] == 1){ 		//jeśli filozof chce dostępu do danego zasobu
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
				    cout << "Filozof " << id << " wpisał się do pliku " << i << endl;
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

	//funkcja run: najpierw myśl przez losowy czas, potem zdobądź widelce, zjedz, oddaj widelce
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

//funkcja wywołująca metodę run fiolzofa
void eatForYourLive (Philosopher* platon){
		//na przemian je i myśli i kożysta z tych samych plików
	for (int i = 0; i < N; ++i)

	{
		platon->run();
	}
		
}



int main(){
	srand(time(NULL));	

	Fork forks[NSTOCK][NPHIL][NPHIL]; 	// tablica wszystkich widelców
	Philosopher philosophers[NPHIL];	// tablica wszystkich filozofów

//tworzymy filozofów:
		for (int i=0; i < NPHIL; i++)
		{
			Philosopher p = Philosopher(i,forks);
			p.chooseStocks();
			philosophers[i] = p;
		}


	int iterator =0;
	int war=0;




	//Rozważamy kilka kolejek, w końcu różne programy mogą chcieć się dostać do różnych plików w różnym czasie
	while(iterator<NREC){
		cout<<"kolejka nr: "<<iterator+1<<endl;


		if(war){
			//po pierwszej kolejce nie ma potrzeby tworzenia filozofów, po prostu mieszamy im zasoby:
			for (int i=0; i < NPHIL; i++)
			{
				
				philosophers[i].chooseStocks();
			}
		}
		war=1;

		//Tworzymy widelce
		for (int i = 0; i < NSTOCK; i++){
			for (int j = 0; j < NPHIL; j++){
				for (int k = 0; k < NPHIL; k++){
						int lower=(j<k)?j:k;
						Fork t = Fork(lower); //widelec dzierży filozof o niższym id
						forks[i][j][k] = t;
				}
			}
		}

		thread philosophersThreads[NPHIL]; 	//tablica wątków

		for (int i=0; i<NPHIL; i++){
			Philosopher *p1;
			p1= &(philosophers[i]);	
			philosophersThreads[i] = thread(&eatForYourLive, p1);	//dodajemy do tablicy wątków funkcję odpalającą filozofa
		}

	    for (int i=0; i<NPHIL; i++){
	        philosophersThreads[i].join();//uruchamiamy wątki
	    }
	    iterator++;
	}
	return 0;
}
