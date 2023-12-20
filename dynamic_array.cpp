#include <iostream>
#include <string>
#include <time.h>
using namespace std;

template <typename T>
struct dynamicArray {
	int arraySize;		//rozmiar
	int arrayEl;		//ilosc elementow
	T* array;

	dynamicArray() {	//definicja tablicy
		arraySize = 1;		//rozmiar tablicy
		arrayEl = 0;		//aktualna ilosc elementow
		array = new T [arraySize];
	}

	void add(T element) {		//dodanie elementu wraz z rozrostem
		if (arraySize > arrayEl) {
			array[arrayEl] = element;
			arrayEl++;
		}
		else {
			arraySize = arraySize*2;
			T* tempArr = new T[arraySize];
			for (int i = 0; i < arrayEl; i++) {
				tempArr[i] = array[i];			//przepisanie zawartosci starej do tymczasowej
			}
			delete[]array;
			array = tempArr;
			array[arrayEl] = element;				//uzupełnienie powiększonej
			arrayEl++;
		}
	}

	void clear_array() {		//czyszczenie tablicy
		delete[]array;
		arraySize = 1;		
		arrayEl = 0;		
		array = new T[arraySize];
	}

	T get(int index) {		//podanie wartosci po indeksie
		if (index >= arrayEl) {
			throw out_of_range("");
		}
		return array[index];
	}
	void change(T data, int index) {		//podmiana wartosci po indeksie
		if (index >= arrayEl) {
			throw invalid_argument("zły indeks");
		}
		else {
			array[index] = data;
		}
	}
	void bubbleSort()						//bąbelkowe
	{
		for (int i = 0; i < arrayEl - 1; i++) {
			for (int j = 0; j < arrayEl - i - 1; j++) {
				if (array[j] > array[j + 1]) {
					swap(array[j], array[j + 1]);
				}
			}
		}
	}

	string napis() {
		string info ="rozmiar tablicy "+ to_string(arraySize) + " ilosc elementow " + to_string(arrayEl);
		return info;
	}
};

int main()
{
	dynamicArray<int>* array = new dynamicArray<int>();
	//array->add(30);									//dodawanie 1 elementu
	srand(time(NULL));
	clock_t a1 = clock();
	double max_time_per_element = 0;
	for (int i = 0; i <= 100000000; i++) {
		clock_t t_element = clock();
		
		array->add(rand());
		clock_t t2_element = clock();
		double time_per_element = (t2_element - t_element) / (double) CLOCKS_PER_SEC;
		if (time_per_element > max_time_per_element) {
			cout << "czas:" << time_per_element<<"s at index " <<array->arrayEl<< endl;
			max_time_per_element = time_per_element;
		}
	}
	clock_t a2 = clock();
	clock_t s1 = clock();
	//array->bubbleSort();							//sortowanie
	clock_t s2 = clock();
	//array->clear_array();							//czyszczenie tablicy
	//cout << array->napis();
	try {											
		//cout << array->get(11);					//pokazanie dowolnego indeksu
		//array->change(100,2);						//zamiana elementu
	}
	catch(...)
	{
		cout << "Nie ma takiego indeksu";
	}
	double addtime = a2 - a1;
	double sorttime = s2 - s1;
	
	//for (int i = 0; i < array->arrayEl; i++) {		//wyswietlanie calej tablicy
	//	cout << array->get(i) << "\n";
	//}
	//cout << "Czas dodawania elementow: " << addtime << "ms" << endl;
	//cout << "Czas sortowania elementow: " << sorttime << "ms" << endl;
	return 0;
}
