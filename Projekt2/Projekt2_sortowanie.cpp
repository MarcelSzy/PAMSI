#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

#define ARRAY_SIZE 1000000


using namespace std;

//tworzenie 100 tablic z wylosowanymi liczbami
template <typename T>
T** setRandomArray(T** array,int const & size,int const & size1, int const & max)
{
	array = new T*[size];
	for(int i=0; i<size; ++i) // x tablic o konkretnym wymiarze
	{
		array[i] = new T[size1];
		for(int j=0; j<size; ++j)
			array[i][j]=rand()%max;
	}
	return array;
}

//wyswietlanie tablicy
template <typename T>
void displayArray(T* arr, int const &size)
{
	for(int i=0; i<size; ++i)
		cout<<arr[i]<<" ";
}

// uzupelnianie tablic z danym posortowaniem
template <typename T>
T** percentageRandomArray(T** array, int const &size, int const &size1, int const &max_v, float  &percentage)
{
	array = new T *[size];
	if(percentage>100) 
		percentage = 100;
	if(percentage<0) 
		percentage = 0;
	float real_max = 0.01*percentage*size;
	int max = static_cast<int>(real_max);
	for(int i=0; i<size; ++i){
		array[i] = new T[size1];
		for(int j=0; j<size; ++j){
			if(j<max) 
				array[i][j] = j;
			else
				array[i][j] = rand()%max_v;
		}
	}
	return array;
}

// uzupelnianie tablic z odwrotnym posortowaniem
template <typename T>
T** invertedArray(T** array, int const &size, int const &size1)
{
	array = new T *[size];
	for(int i=0; i<size; ++i)
	{
		array[i] = new T[size1];
		for(int j=0; j<size1; ++j)
			array[i][j] = size1-j;
	}
	return array;
}

// sprawdzenie czy tablica jest posortowana
template <typename T>
bool isSorted(T* arr, int const &size)
{
	for(int i=0; i<size-1; ++i)
	{
		if(arr[i]>arr[i+1])
		{
			return false;
		}
	}
	return true;
}

// #############################################
// SORTOWANIE SZYBKIE
// #############################################

template <typename T>
void quicksort(T *arr, int const & left, int const & right)
{   // zadeklarowanie zmiennych
    int l = left;
    int r = right - 1;
    int size = right - left;
    // warunek wykonania sortowania (wiecej niz jeden element)
    if (size > 1)
    {
        T pivot = arr[rand() % size + l];			// ustawienie pivota jako losowego elementu tablicy
        while (l < r)
	{								// petla wykonujaca sie dopoki index prawy > index lewy
            while (arr[r] > pivot && r > l)		// petla dla prawego elementu
                r--;
            while (arr[l] < pivot && l <= r)		// petla dla lewego elementu
                l++;
            if (l < r) 
	    {							// warunek wykonania zamiany elementow
              //std::swap(arr[l], arr[r]);			no tak nie używać stl'a
		tmp = arr[l];
		arr[l] = arr[r];
		arr[r] = tmp;
                l++;
	    }
        }
        // rekurencyjne wywolywanie quicksort'a dla otrzymanych granic r oraz l
        quicksort(arr, left, l);
        quicksort(arr, r, right);
    }
}

// #############################################
// SORTOWANIE PRZEZ SCALANIE
// #############################################

// funkcja scalajaca - merge
template <typename T>
void merge(T *arr, int const & left, int const & mid, int const & right)
{
	static T *tmp = new T[ARRAY_SIZE]; // tablica tymczasowa/pomocnicza
	int l = left;				// przypisanie wartosci lewego elementu i srodkowego
	int m = mid + 1;			// do zmiennych, dla uproszczenia kodu
 
	for(int k = left; k<=right; ++k) // kopiowanie do tablicy tymczasowej
		tmp[k] = arr[k];  

	for(int k=left; k<=right; ++k){	// scalanie tablic tymczasowych 
		if(l<=mid)
		{
			if(m <= right)
			{
				if(tmp[m]<tmp[l])
				{
					arr[k] = tmp[m++];
				}
				else
					arr[k] = tmp[l++];
			}
			else
				arr[k] = tmp[l++];
		}
		else
			arr[k] = tmp[m++];
	}
}

// sortowanie przez scalanie - funkcja rekurencyjna
template <typename T>
void mergesort(T *arr,int const & left, int const & right)
{
	if(right<=left) return; // warunek konca rekurencji
	int mid = (right+left)/2; // srodek podtablicy
	//dzielenie rekurencyjnie tablicy na dwie czesci
	mergesort(arr, left, mid); 
	mergesort(arr, mid+1, right);
	merge(arr, left, mid, right); // scalenie tablic
}

//########################################################
// SORTOWANIE INTROSPEKTYWNE - scalenie 
//########################################################

template <typename T>
int partition(T *arr, int left, int right)
{
	int x = arr[left];
	int i = left, j = right;
	T tmp;
	while (true){
		while (arr[j] > x)
			j--;
		while (arr[i] < x)
			i++;
		if (i < j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
		else
			return j;
	}
}

template <class T>
void IntroSort (T *Array, int N, int M)
{
  long i;
  if (M<=0)
  {
    mergesort(Array,0,N);
    return;
  }
  i=partition(Array,0,N);
  if (i>9)
    IntroSort(Array,i,M-1);
  if (N-1-i>9)
    IntroSort(Array+i+1,N-1-i,M-1);
}

template <class T>
void Hybrid_Introspective_Sort (T *Array, int N)
{
  IntroSort(Array,N,(int)floor(2*log(N)/M_LN2));
  mergesort(Array,0,N);
}

//########################################################
// CZAS SORTOWANIA
//########################################################

void timeMeasure(clock_t beginning, clock_t ending){
    std::cout << " CZAS WYKONANIA: " << (ending-beginning)/1000000.00<<" s\n";
}


int main()
{
	srand(time(NULL));
//######################################
//KONFIGURACJA PROGRAMU
	int sorted=0;				// ilość prawidłowo posortowanych tablic
	int how_m = 100;			// ilość tablic do posortowania
	int **tab; 				// inicjacja zmiennej na tablice
	float arrcreate = 0;			// procent posortowania tablic poczatkowych
	char sorting = 'm';			// wybor typu sortowania: q-quicksort; m-mergesort(scalenie), s-shellsort, i-introsort(?)
	bool invertedarray = true;		// czy tablica ma byc odwrotnie posortowana na starcie?
//######################################	
	if(invertedarray)
		tab = invertedArray<int>(tab, how_m, ARRAY_SIZE);
	else 
		tab = percentageRandomArray<int>(tab, how_m, ARRAY_SIZE, ARRAY_SIZE, arrcreate);
	switch(sorting)
	{
		case 'q':
		{
			isSorted(tab[0], ARRAY_SIZE);
			clock_t start = clock();
			for(int i=0; i<how_m; ++i)
				quicksort(tab[i], 0, ARRAY_SIZE);
			clock_t stop = clock();
			timeMeasure(start, stop);
			for(int i=0; i<how_m; ++i)
				sorted += isSorted(tab[i], ARRAY_SIZE);
			cout<<"Posortowano "<<sorted<<" tablic.\n";		
		}
			break;
		case 'm':
		{
			isSorted(tab[0], ARRAY_SIZE);
			clock_t start = clock();
			for(int i=0; i<how_m; ++i)
				mergesort(tab[i], 0, ARRAY_SIZE-1);
			clock_t stop = clock();
			timeMeasure(start, stop);
			for(int i=0; i<how_m; ++i)
				sorted += isSorted(tab[i], ARRAY_SIZE);
			cout<<"Posortowano "<<sorted<<" tablic.\n";
			
		}
			break;
		case 'i':
		{
			isSorted(tab[0], ARRAY_SIZE);
			clock_t start = clock();
			for(int i=0; i<how_m; ++i)
				Hybrid_Introspective_Sort(tab[i], ARRAY_SIZE);
			clock_t stop = clock();
			timeMeasure(start, stop);
			for(int i=0; i<how_m; ++i)
				sorted += isSorted(tab[i], ARRAY_SIZE);
			cout<<"Posortowano "<<sorted<<" tablic.\n";
		}
			break;
		default:
			break;
	}
	//displayArray(tab[0], ARRAY_SIZE);

	return 0;
}


