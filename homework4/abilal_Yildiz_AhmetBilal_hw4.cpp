// Ahmet Bilal Yildiz 27925
// soting algotithms in this homework are taken from lecture slides

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "strutils.h"
using namespace std;

//////////////////// insertion sort /////////////
// insertion sort
template <class Comparable>
void insertionSort(vector<Comparable> & a){

	int j;
	for(int p = 1; p < a.size(); p++){
	
		Comparable tmp = a[p];
		for(j = p; j > 0 && tmp < a[j-1]; j--){
			a[j] = a[j-1];
		}
		a[j] = tmp;
	}
}

/////////////////////// quick sort ////////////
// quick sort
template <class Comparable>
 void quickSort( vector<Comparable> & a )
 {
       quickSort( a, 0, a.size( ) - 1 );
 }

//swap operation used in the quick sort !!!!!!!!!!!!!!!!!!!!!! come back here !!!!!!!!!!!!!!!!!!!!
template <class Comparable>
inline void swap1(Comparable & obj1, Comparable & obj2){

	Comparable tmp = obj1;
	obj1 = obj2;
	obj2 = tmp;
}


//void swap(int & i1, int & i2){
//
//	int temp = i1;
//	i1 = i2;
//	i2 = temp;
//
//}

// median3 used in quick sort
template <class Comparable>
const Comparable & median3( vector<Comparable> & a, int left, int right )
{
    int center = ( left + right ) / 2;
    if ( a[ center ] < a[ left ] )
		swap1( a[ left ], a[ center ] );
    if ( a[ right ] < a[ left ] )
		swap1( a[ left ], a[ right ] );
    if ( a[ right ] < a[ center ] )
		swap1( a[ center ], a[ right ] );

    // Place pivot at position right - 1
    swap1( a[ center ], a[ right - 1 ] );
    return a[ right - 1 ];
}

// quick sort internal
template <class Comparable>
void quickSort( vector<Comparable> & a,  int left, int right )
{
    if ( left + 10 <= right )
    {
        Comparable pivot = median3( a, left, right );
		// Begin partitioning
		int i = left, j = right - 1;
		for ( ; ; )
		{
			while ( a[ ++i ] < pivot ) { }

			while ( pivot < a[ --j ] ) { }

			if ( i < j )
				swap1( a[ i ], a[ j ] );
			else
					break;
		}
		swap1( a[ i ], a[ right - 1 ] );   // Restore pivot

        quickSort( a, left, i - 1 );       // Sort small elements
        quickSort( a, i + 1, right );    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertion_sort( a, left, right );
}

// insertion_sort internal used in quick sort    !!!!!!!!!!!!!!!! do I really need it? !!!!!!!!!!!!!!!
template <class Comparable>
void insertion_sort( vector<Comparable> & a, int left, int right )
{
    for ( int p = left + 1; p <= right; p++ )
    {
        Comparable tmp = a[ p ];
        int j;

        for ( j = p; j > left && tmp < a[ j - 1 ]; j--)
            a[ j ] = a[ j - 1 ];
        a[ j ] = tmp;
	}
}

///////////////////////// merge sort ///////////////////
 // mergeSort
template <class Comparable>
void mergeSort( vector<Comparable> & a )
{
    vector<Comparable> tmpArray( a.size( ) );

    mergeSort( a, tmpArray, 0, a.size( ) - 1 );
}

// mergeSort internal
template <class Comparable>
void mergeSort( vector<Comparable> & a, vector<Comparable> & tmpArray, int left, int right )
{
    if ( left < right )
    {
        int center = ( left + right ) / 2;
        mergeSort( a, tmpArray, left, center );
        mergeSort( a, tmpArray, center + 1, right );
        merge( a, tmpArray, left, center + 1, right );
    }
}

// merge function / used in mergeSort
template <class Comparable>
void merge(  vector<Comparable> & a, vector<Comparable> & tmpArray, int leftPos, int rightPos, int rightEnd )
{
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;
	// Main loop
	while ( leftPos <= leftEnd && rightPos <= rightEnd )
			if ( a[ leftPos ] <= a[ rightPos ] )
				tmpArray[ tmpPos++ ] = a[ leftPos++ ];
			else
				tmpArray[ tmpPos++ ] = a[ rightPos++ ];

	while ( leftPos <= leftEnd )    // Copy rest of first half
		tmpArray[ tmpPos++ ] = a[ leftPos++ ];

	while ( rightPos <= rightEnd )  // Copy rest of right half
		tmpArray[ tmpPos++ ] = a[ rightPos++ ];

	// Copy tmpArray back
	for ( int i = 0; i < numElements; i++, rightEnd-- )
		a[ rightEnd ] = tmpArray[ rightEnd ];
}

////////////////////// heap sort //////////////////

inline int leftChild( int i )
{
	return 2*i+1;
}

template <class Comparable>
void heapSort(vector<Comparable> & a)
{
	// buildHeap
	for (int i = a.size()/2; i >=0; i--)
		percDown(a, i, a.size());

	// sort
	for (int j = a.size()-1; j >0; j--)
	{
  	     swap1(a[0], a[j]);    // swap max to the last pos.
         percDown(a, 0, j); // re-form the heap
	}
}

template <class Comparable>  // for deleteMax
// a is the array, i is the position to percolate down from
// n is the logical size of the array
void percDown( vector<Comparable> & a, int i, int n )
{
    int child;
    Comparable tmp;

    for (tmp=a[i] ; leftChild(i) < n; i = child )
    {
            child = leftChild(i);
            if ( child != n-1 && a[ child  ] < a[ child+1 ] )
                child++;
            if ( a[child ] > tmp )
                a[i] = a[ child ];
            else
                break;
    } 
    a[ i ] = tmp;
}


// sequential search (linear search)

template <class Comparable>
int sequential_search(vector<Comparable> & a, Comparable obj){

	for(int i = 0; i < a.size(); i++){
		if(obj == a[i]){
			return i; // return index of the founded object
		}
	}
	return -1; // if notfound object return -1
}


// Binary search
template <class Comparable>
Comparable fullContactBinarySearch(vector<Comparable> & a, Comparable obj, int min, int max){

	if(max >= min){

		int mid = (min+ max) /2;
	
		if( obj < a[mid]){

			return fullContactBinarySearch(a, obj, min, mid-1);
		}
		else if(obj > a[mid]){
	
			return fullContactBinarySearch(a, obj, mid+1 , max);
	
		}

		else{ // if a[mid].name == objects name
			// adding all the words that are matching the partial word to the vector
			int i = mid;
			while(obj == a[i]){ // searching through the left
				if(obj *= a[i]){
					return a[i];
				}
				i--;
			}
			i = mid; // 
			while(obj == a[i]){ // searching through the right
				if(obj *= a[i]){

					return a[i];
				}
				i++;
			}
		}

		
	}
	Comparable nfound;
	return nfound; // if object is notfound

}

template <class Comparable>
vector<Comparable> partialContactBinarySearch(vector<Comparable>& a, string &name, int min, int max){

	vector<Comparable> founded_vector;
	if(max >= min){

		int mid = (min+ max) /2;
	
		if( a[mid].p_left(name)){

			return partialContactBinarySearch(a, name, min, mid-1);
		}
		else if(a[mid].p_right(name)){
	
			return partialContactBinarySearch(a, name, mid+1 , max);
	
		}
		else{ // if a[mid].name matches the searched partial name
			// adding all the words that are matching the partial word to the vector
			int i = mid;
			while(i != 0 && a[i].p_find(name)){ // going to the left most matching index

				i--;
			}
			i++; // now i is the first index that corresponds to left most matching index
			while(i != a.size() && a[i].p_find(name)){ // adding all matching words to the vector

				founded_vector.push_back(a[i]);
				i++;
			}
		}
	}
	return founded_vector; // if object is notfound

}


template <class Comparable>
Comparable fullContactSequentialSearch(vector<Comparable> & a, Comparable & obj){
		
	for(int i = 0; i < a.size(); i++){
		if(obj *= a[i]){
			return a[i]; // return index of the founded object
		}
	}
	contact nfound; // forming nfound with default constructor
	return nfound; // if notfound object return -1

}

template <class Comparable>
vector<Comparable> partialContactSequentialSearch(vector<Comparable> & a, string & name){
		
	vector<Comparable> founded_contacts;
	for(int i = 0; i < a.size(); i++){
		if(a[i].p_find(name)){ // if the name starting with partial name
			founded_contacts.push_back(a[i]); // return index of the founded object
		}
	}
	
	return founded_contacts; // it is an empty vector if there is not matching contact in contacts
}




// Binary search
//template <class Comparable>
//int binary_search(vector<Comparable> & a, Comparable obj, int min, int max){
//
//	if(max >= min){
//
//		int mid = (min+ max) /2;
//	
//		if( obj *< a[mid]){
//
//			binary_search(a, obj, min, mid-1);
//		}
//		else if(obj *> a[mid]){
//	
//			binary_search(a, obj, mid+1 , max);
//	
//		}
//		else{ // if obj == a[mid]
//
//			return mid; // return founded index
//
//		}
//	}
//
//	return -1; // if object is notfound
//
//}



struct contact{

	string name, surname, telephone, city;

	contact(string n = "nfound", string s = "nfound", string t = "nfound", string c = "nfound")
		:name(n), surname(s), telephone(t), city(c)
	{
	}

	bool operator<(contact &rhs){ // comparisan with respect to names
		if(name < rhs.name){
			return true;
		}
		return false;
	}
	//bool small_ns(contact &rhs){ // comparisan with respect to names and surnames
	//	string c1 = name + surname;
	//	string c2 = rhs.name + rhs.surname;
	//	if(c1 < c2){
	//		return true;
	//	}
	//	return false;
	//}
	bool operator<=(contact &rhs){
		if(name <= rhs.name){
			return true;
		}
		return false;
	}
	bool operator>(contact &rhs){
		if(name > rhs.name){
			return true;
		}
		return false;
	}
	/*bool great_ns(contact &rhs){
		string c1 = name + surname;
		string c2 = rhs.name + rhs.surname;
		if(c1 > c2){
			return true;
		}
		return false;
	}*/

	bool operator==(contact &rhs){
		if(name == rhs.name){
			return true;
		}
		return false;
	}
	bool operator*=(contact &rhs){ // full assignment operator that chechks whether both name and surnames of contacts equals to each other
		if(name == rhs.name && surname == rhs.surname){
			return true;
		}
		return false;
	}

	bool p_find(string &n ){ // partial find

		if(name.find(n) == 0){
			return true;
		}
		return false;
	}
	bool p_left(string &n ){ // partial left

		if(name.find(n) != 0 && n < name ){
			return true;
		}
		return false;
	}
	bool p_right(string &n ){ // partial right

		if(name.find(n) != 0 && n > name){
			return true;
		}
		return false;
	}


};

//template <class Comparable>
//Comparable fullContactBinarySearch(vector<Comparable> & a, Comparable &obj, int min , int max){
//
//	contact nfound;
//	if(max >= min){
//
//		int mid = (min+ max) /2;
//	
//		if( obj < a[mid]){
//
//			return fullContactBinarySearch(a, obj,  min, mid-1);
//		}
//		else if(obj > a[mid]){
//	
//			return fullContactBinarySearch(a, obj, mid+1 , max);
//	
//		}
//		else{ // if names are the same 
//
//			if(obj *= a[mid]){ // comparison for the surnames
//				return a[mid]; // return founded index
//			}
//			else{
//				return nfound;
//			}
//		}
//	}
//	return nfound; // if object is notfound
//
//}


//vector<contact> partialContactBinarySearch(vector<contact>& a, string name, int min, int max){
//
//	vector<contact> founded_vector;
//	if(max >= min){
//
//		int mid = (min+ max) /2;
//	
//		if( a[mid].name.find(name) != 0 && name < a[mid].name){
//
//			return partialContactBinarySearch(a, name, min, mid-1);
//		}
//		else if(a[mid].name.find(name) != 0 && name > a[mid].name){
//	
//			return partialContactBinarySearch(a, name, mid+1 , max);
//	
//		}
//		else{ // if a[mid].name matches the searched partial name
//			// adding all the words that are matching the partial word to the vector
//			int i = mid;
//			while(a[i].name.find(name) == 0){ // going to the left most matching index
//
//				i--;
//			}
//			i++; // now i is the first index that corresponds to left most matching index
//			while(a[i].name.find(name) == 0){ // adding all matching words to the vector
//
//				founded_vector.push_back(a[i]);
//				i++;
//			}
//		}
//	}
//	return founded_vector; // if object is notfound
//
//}



//contact fullContactSequentialSearch(vector<contact> & a, string name, string surname){
//		
//	for(int i = 0; i < a.size(); i++){
//		if(name == a[i].name && surname == a[i].surname){
//			return a[i]; // return index of the founded object
//		}
//	}
//	contact nfound; // forming nfound with default constructor
//	return nfound; // if notfound object return -1
//
//}
//
//vector<contact> partialContactSequentialSearch(vector<contact> & a, string name){
//		
//	vector<contact> founded_contacts;
//	for(int i = 0; i < a.size(); i++){
//		if(a[i].name.find(name) == 0 ){ // if the name starting with partial name
//			founded_contacts.push_back(a[i]); // return index of the founded object
//		}
//	}
//	
//	return founded_contacts; // it is an empty vector if there is not matching contact in contacts
//}



int main(){

	// getting the filename from the user
	string fileName, words;
	cout << "Please enter the contact file name: " << endl;
	cin >> fileName;

	fstream file;
	file.open(fileName);
	
	// reading the file line by line, forming contacts from these lines and stroring data to the vector
	
	vector<contact> contacts;
	string line, name, surname, telephone, city;
	while(getline(file, line)){
		
		istringstream words(line);
		words >> name >> surname >> telephone >> city;
		// stroing name and surname as upper case letters to make search case incentisive
		ToUpper(name);
		ToUpper(surname);

		contact new_contact(name, surname, telephone, city);

		contacts.push_back(new_contact);
	
	}

	file.close();


	// forming copies of the vector

	vector<contact> contacts_2; 

	contacts_2 = contacts; // contacts_2 is to keep the info of the contacts (unsorted)

	// getting the querried words from the user as a line
	cout << "Please enter the word to be queried : " << endl;
	cin.ignore();
	getline(cin, words);

	// adding the querried words to a vector
	vector<string> q_words;
	string word;
	istringstream iss(words);
	while(iss >> word){
		ToUpper(word);
		q_words.push_back(word);
	}


	// sorting for all copies and gettig times
	int t_insertionSort = 0, t_quickSort = 0, t_mergeSort = 0, t_heapSort = 0;
	int N = 1; // if cannot be measured, try N = 1000

	// insertion sort
	for (int i = 0; i < N; i++){
		contacts = contacts_2; 
		auto start = std::chrono::high_resolution_clock::now(); // start measuring
		insertionSort(contacts);
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		//auto end = std::chrono::high_resolution_clock::now(); // start measuring
		t_insertionSort += duration.count();
	}
	t_insertionSort /= N;

	//quick sort
	for (int i = 0; i < N; i++){
		contacts = contacts_2; 
		auto start = std::chrono::high_resolution_clock::now(); // start measuring
		quickSort(contacts);
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		t_quickSort += duration.count();
	}
	t_quickSort /= N;


	// merge sort
	for (int i = 0; i < N; i++){
		contacts = contacts_2; 
		auto start = std::chrono::high_resolution_clock::now(); // start measuring
		mergeSort(contacts);
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		t_mergeSort += duration.count();
	}
	t_mergeSort /= N;


	// heap sort
	for (int i = 0; i < N; i++){
		contacts = contacts_2; 
		auto start = std::chrono::high_resolution_clock::now(); // start measuring
		heapSort(contacts);
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
		t_heapSort += duration.count();
	}
	t_heapSort /= N;


	// displaying the soting times
	cout << "Sorting the vector copies " << endl;
	cout <<"======================================" << endl;

	cout << "Quick Sort Time: " << t_quickSort << " Nanoseconds" << endl;
	cout << "Insertion Sort Time: " << t_insertionSort << " Nanoseconds" << endl;
	cout << "Merge Sort Time: " << t_mergeSort << " Nanoseconds" << endl;
	cout << "Heap Sort Time: " << t_heapSort << " Nanoseconds" << endl;


	// searching for querried words
	contact founded;
	vector<contact> foundeds;
	cout << "Searching for " << words << endl;
	if(q_words.size() == 1){ // do partial contact name search 


	// partial contact name binary search

		// measuring the time
		for (int i = 0; i < N; i++){
			auto start = std::chrono::high_resolution_clock::now(); // start measuring
			partialContactBinarySearch(contacts, q_words[0], 0, contacts.size());
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
			t_heapSort += duration.count();
		}
		t_heapSort /= N;

		// searching and displaying the search results

		foundeds = partialContactBinarySearch(contacts, q_words[0], 0, contacts.size());

		if(foundeds.size() == 0){ // if there is not a matching name in the phonebook // diplaying searching result
		
			cout << q_words[0] << " does NOT exist in the dataset" << endl;
		
		}
		else{ // if there are matching contacts displaying all of them

			for(int i = 0; i < foundeds.size(); i++){
				founded = foundeds[i];
				cout << founded.name << " " << founded.surname << " " << founded.telephone << " " << founded.city << endl;
			}
		}


		// displaying time

	// partial contact name sequential search
		// measuring time 

		cout << endl <<  "Search results for Sequential Search: " << endl << endl;
		// searching and displaying the searching info
		foundeds = partialContactSequentialSearch(contacts, q_words[0]);

		if(foundeds.size() == 0){ // if there is not a matching name in the phonebook // diplaying searching result
		
			cout << q_words[0] << " does NOT exist in the dataset" << endl;
		
		}
		else{ // if there are matching contacts displaying all of them

			for(int i = 0; i < foundeds.size(); i++){
				founded = foundeds[i];
				cout << founded.name << " " << founded.surname << " " << founded.telephone << " " << founded.city << endl;
			}
		}

		//printing time
	
	
	
	
	
	}
	else{ // if q_words.size() == 2 // do full contact name search
	

	// full contact binary search

		// storing the search time

		contact find_obj(q_words[0], q_words[1]);
		founded = fullContactBinarySearch(contacts, find_obj, 0, contacts.size());
		// printing the relative information
		if(founded.name == "nfound"){ // if item is not found

			cout << q_words[0] << " " << q_words[1] << " does NOT exist in the dataset" << endl;

		}
		else{

			cout << founded.name << " " << founded.surname << " " << founded.telephone << " " << founded.city << endl;
		
		}

		// printing the search time





	// full contact sequential search
		
		// storing the search time
		cout << "Search results for Sequential Search: " << endl;
		founded = fullContactSequentialSearch(contacts, find_obj);
		// printing the relative information
		if(founded.name == "nfound"){ // if item is not found

			cout << q_words[0] << " " << q_words[1] << " does NOT exist in the dataset" << endl;

		}
		else{

			cout << founded.name << " " << founded.surname << " " << founded.telephone << " " << founded.city << endl;
		
		}

		// printing the search time
	
	}




return 0;
}
