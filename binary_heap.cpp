//ALGO2 IS1 210B LAB06
//MATEUSZ MUSIAŁ
//mm51061@zut.edu.pl
#include <iostream>
#include <string>
#include <time.h>
#include <math.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

template <typename T>
struct Heap {
	int arraySize = 1;		//rozmiar
	int arrayEl = 0;		//ilosc elementow
	T* array = new T[arraySize];
	
	void add(T element) {		//dodanie elementu wraz z rozrostem
		if (arraySize > arrayEl) {
			array[arrayEl] = element;
			arrayEl++;
		}
		else {
			arraySize = arraySize * 2;
			T* tempArr = new T[arraySize];
			for (int i = 0; i <= arrayEl; i++) {
				tempArr[i] = array[i];			//przepisanie zawartosci starej do tymczasowej
			}
			delete[]array;
			array = tempArr;
			array[arrayEl] = element;				//uzupe�nienie powi�kszonej
			arrayEl++;
		}
		fix_up(arrayEl-1);
	}

	void fix_up(int index) { //funkcja w górę
		if (index <= 0)
			return;
		int p = (index - 1) / 2;
		if (p >= 0) {
			if (array[index] > array[p]) {
				swap(array[index], array[p]);
				fix_up(p);
			}
		}
		else {
			return;
		}
	}

	void fix_down(int index)	//funkcja z dół
	{
		int current = NULL;
		if ((index * 2) + 1 < arrayEl)
		{
			if (array[index] < array[(index * 2) + 1])
			{
				current = (index * 2) + 1;
			}
		}
		if ((index * 2) + 2 < arrayEl)
		{
			if (current == NULL) {
				if (array[index] < array[(index * 2) + 2]) {
					current = (index * 2) + 2;
				}
			}
			else {
				if (array[current] < array[(index * 2) + 2]) {
					current = (index * 2) + 2;
				}
			}
		}
		if (current == NULL) {
			return;
		}
		swap(array[index], array[current]);
		fix_down(current);
	}

	void decrease_arr() { //kurczenie tablicy
		if (arrayEl != 0) {
			if ((arraySize / arrayEl) == 2) {
				arraySize = arraySize / 2;
				T* tempArr2 = new T[arraySize];
				for (int i = 0; i < arrayEl; i++) {
					tempArr2[i] = array[i];
				}
				delete[]array;
				array = tempArr2;
			}
		}
	}

	T deletion() {
		T* tempArr = new T[arraySize];
		T root = array[0];
		swap(tempArr[0], array[arrayEl - 1]);
		arrayEl--;
		for (int i = 1; i <= arrayEl - 1; i++) {
			tempArr[i] = array[i];			//przepisanie zawartosci starej do tymczasowej
		}
		delete[]array;
		array = tempArr;
		fix_down(0);
		decrease_arr();
		return root;
	}

	void clear_array() {		//czyszczenie tablicy
		delete[]array;
		arraySize = 1;
		arrayEl = 0;
	}

	string print() {
		string napis = "korzen: ";
		for (int i = 0; i < arrayEl; i++) {
			 napis = napis + to_string(array[i]) + "\n";
		}
		return napis;
	}
};

int main()
{
	Heap<int>* heap = new Heap<int>{};
	srand(2);
	clock_t a1 = clock();
	const int n = 10;
	for (int i = 0; i < n; i++) {
		int v = rand() % 5;
		cout << "TO ADD: " << v << endl;
		heap->add(v);
		cout << "HEAP NOW: " << heap->print() << endl;
	}
	clock_t a2 = clock();
	double addtime = (a2 - a1) / (double)CLOCKS_PER_SEC;
	cout << "Czas dodawania elementow: " << addtime << "s" << endl;
	cout << "----------------------" << endl;
	clock_t t1 = clock();
	for (int i = 0; i < n; i++) {
		cout << heap->deletion() << endl;
	}
	clock_t t2 = clock();
	double deltime = (t2 - t1) / (double)CLOCKS_PER_SEC;
	cout << "Czas usuwania elementow: " << deltime << "s" << endl;
	heap->clear_array();
	return 0;
}