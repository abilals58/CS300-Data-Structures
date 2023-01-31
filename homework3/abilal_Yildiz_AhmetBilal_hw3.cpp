// Ahmet Bilal Yildiz

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include <ctype.h>

#include "strutils.h"
#include "Temp_Binary_Search_Tree.h"
#include "Temp_Binary_Search_Tree.cpp"
#include "Temp_Hash_Table.h"
#include "Temp_Hash_Table.cpp"

using namespace std;


struct DocumentItem { // document item is used in the vector which is in the worditem

	string documentName;
	int count;

	DocumentItem(string n = "notfound", int c = 0) // construtor
		:documentName(n), count(c)
	{
	}

};
struct WordItem { // word item is used in the hash table and bst to store the word info

	string word;
	vector<DocumentItem> item_list;

	WordItem( string w = "notfound" ) // constructor
		:  word(w)
	{
	}

	bool operator!=(const WordItem & rhs) const 
	{ 
		
		if(word == rhs.word){
			return false;
		}
		return true;
	}

	bool operator<(const WordItem & rhs) const 
	{

		if(word< rhs.word){
			return true;
		}
		return false;
	}

	int hash(int tableSize ) const // this hash funtion is called in the hash function in hashtable.cpp
	{
		int hashVal = 0;
  
		for (int i = 0; i < word.length();i++) 
		  hashVal = 37 * hashVal + word[ i ];

		hashVal = hashVal % tableSize;

		if (hashVal < 0) 
		  hashVal = hashVal + tableSize;

	   return hashVal;

	}

};

struct word_item{ //word_item is used to store searching datain the vector which is in the info_item
	
	string word;
	int occurence;

	word_item(string s, int i)
		:word(s), occurence(i)
	{
	}
};

struct info_item{ // info_item is used to store searching data

	string doc_name;
	vector<word_item> word_item_list;

	info_item(string s)
		:doc_name(s)
	{
	}
};

void word_seperator(vector<string> &word_list, string &line){ // it takes a vector of strings and and all the words in a line to that vector (seperates the words)

	string word = line;
	string new_word;
	int j = 0;
	for(int i = 0; i < line.length(); i++) {// read the line char by char

		if(i+1 == line.length()){
			if(!isalpha(word[j])){
				new_word = word.substr(0, j);
				word_list.push_back(new_word);
				
			}
			else{
				new_word = word;
				word_list.push_back(new_word);
			}
		}

		else if(!isalpha(word[j])){ // if the char is a seperator

			new_word = word.substr(0, j);
			word = word.substr(j+1);
			word_list.push_back(new_word);
			j = -1; // make j 0 again; 
		}
		j++;
	}


	if(word_list.size() == 0){
	
		word_list.push_back(word);
	}
}


int index(vector<info_item> &info_vector, string doc_name ){

	for(int i = 0; i < info_vector.size(); i++){
		if(doc_name == info_vector[i].doc_name){
			return i;
		}
	}
	return -1; // if it is not in the vector;
}


bool query_in(vector<word_item> &info_vector, string q_name ){

	for(int i = 0; i < info_vector.size(); i++){
		if(q_name == info_vector[i].word){
			return true;
		}
	}
	return false; // if it is not in the vector;
}


int main(){

	// getting the filename and number inputs from the user
	int file_num;
	cout << "Enter number of input files: ";
	cin >> file_num;

	// getting filenames in a vector

	vector<string> file_names(file_num, " ");

	for(int i = 1; i < file_num+1; i++){
		
		cout << "Enter " << i << ". file name: ";
		cin >> file_names[i-1]; // getting the file name input

	}

	// preprocessing the files

	//forming document item and word item for not found item
	DocumentItem d_nfound;
	vector<DocumentItem> i_list(1, d_nfound);
	WordItem nfound; 
	nfound.item_list = i_list; // consists of word = "notfound",a vector which has a document item element whose documentname = "notfound" and count = 0;

	HashTable<WordItem> word_item_table(nfound); 
	BinarySearchTree<WordItem> word_item_tree(nfound);

	for(int i = 0 ; i < file_num; i++){ // repeat the process for each file
		
		fstream file;
		file.open(file_names[i]);

		string line;

		while(file >> line){
			
			vector<string> word_list; 
			word_seperator(word_list, line);
			string word;
			for(int j = 0; j < word_list.size(); j++){
				word = word_list[j];
				ToLower(word);
				
				// forming the worditem and searching for word item in the table
				DocumentItem doc_item(file_names[i], 1);
				WordItem w_item(word);
				w_item.item_list.push_back(doc_item);


				if(word_item_table.find(w_item).word == "notfound"){
					//inserting new w_item to the table 
					if(word != ""){ // do not insert new w_item if the word = ""

						word_item_table.insert(w_item);
						word_item_tree.insert(w_item);
					}
				}
				else{
					// updating the existing item
					WordItem * wptr = & word_item_table.find_to_update(w_item);
					WordItem * wtree_ptr = & word_item_tree.find_to_update(w_item);
					if(wptr->item_list.size() < i+1){ // updating item_list with different type of document 
						wptr->item_list.push_back(doc_item);
						wtree_ptr->item_list.push_back(doc_item);
					}
					else{ // updating the count if word in the table and also the document type in the item_list
						wptr->item_list[i].count++;
						wtree_ptr->item_list[i].count++;
					}
				}

			}

		}

		file.close();
	}

	// displaying the loading info 
	cout << endl;
	word_item_table.display_loading_info();
	
	// getting query input as a line
	string querried_words;
	cout << "Enter queried words in one line: ";
	cin.ignore();
	getline(cin, querried_words);
	vector<string> q_words;
	word_seperator(q_words, querried_words);
	string q_word;
	double BSTtime = 0;
	double HTtime = 0;

	vector<info_item> t_info_vector;
	vector<info_item> h_info_vector;

	for(int m = 0; m < q_words.size(); m++){

		q_word = q_words[m];
		ToLower(q_word);
		if(q_word != ""){ // skip the word if it is ""

			// measuring the total search time for BST

			int k = 100;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				word_item_tree.find(q_word);
			}
			auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - start);
			BSTtime += BSTTime.count() / k;

			// storing the searching results for BST
			WordItem wt_item(q_word);
			WordItem * t_ptr = & word_item_tree.find_to_update(wt_item); 
			if( t_ptr->word != "notfound"){
				
				for(int j =0; j < t_ptr->item_list.size(); j++){
					if(index(t_info_vector,t_ptr->item_list[j].documentName) == -1){

						word_item new_word_item(q_word,t_ptr->item_list[j].count);
						info_item new_item(t_ptr->item_list[j].documentName);
						new_item.word_item_list.push_back(new_word_item);
						t_info_vector.push_back(new_item);
					}
					else{
						word_item new_word_item(q_word,t_ptr->item_list[j].count);
						t_info_vector[index(t_info_vector,t_ptr->item_list[j].documentName)].word_item_list.push_back(new_word_item);
					
					}
				}
			}
	
			// measuring the total search time for HT

			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				word_item_table.find(q_word);
			}
			auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
			(std::chrono::high_resolution_clock::now() - start);

			HTtime += HTTime.count() / k;


			// storing searching results
			WordItem wh_item(q_word);
			WordItem * h_ptr = & word_item_table.find_to_update(wh_item);

			if(h_ptr->word != "notfound"){
				
				for(int j =0; j < h_ptr->item_list.size(); j++){

					if(index(h_info_vector,h_ptr->item_list[j].documentName) == -1){

						word_item new_word_item(q_word,h_ptr->item_list[j].count);
						info_item new_item(h_ptr->item_list[j].documentName);
						new_item.word_item_list.push_back(new_word_item);
						h_info_vector.push_back(new_item);
					}
					else{

						word_item new_word_item(q_word,h_ptr->item_list[j].count);
						h_info_vector[index(h_info_vector,h_ptr->item_list[j].documentName)].word_item_list.push_back(new_word_item);
					
					}
				}
			}
		}
	}
	

	// diplaying the searching results for BST
	bool t_contains = false;
	for(int i =0; i < t_info_vector.size(); i ++){

		// checking whether all the querried words in that file or not
		bool t_all_words = true;
		for(int k = 0; k <q_words.size(); k++){
			q_word = q_words[k];
			ToLower(q_word);
			if(! query_in(t_info_vector[i].word_item_list, q_word)){
				t_all_words = false;
				break;
			}
		}
		if(t_all_words){
			t_contains = true;
			cout <<  "in Document " << t_info_vector[i].doc_name;

			for(int j =0; j < t_info_vector[i].word_item_list.size(); j++){
			
				cout << ", " << t_info_vector[i].word_item_list[j].word << " found " << t_info_vector[i].word_item_list[j].occurence << " times";
		
			}
			cout << "."<< endl;
		}
	}

	if(! t_contains){ // display not found message if not found
		cout << "No document contains the given query" << endl;
	}

	// diplaying the searching results for HT
	bool h_contains = false;

	for(int i =0; i < h_info_vector.size(); i ++){

		bool all_words = true;
		for(int k = 0; k <q_words.size(); k++){
			q_word = q_words[k];
			ToLower(q_word);
			if(! query_in(h_info_vector[i].word_item_list, q_word)){
				all_words = false;
			}
		}
		if(all_words){

			h_contains = true;
			cout <<  "in Document " << h_info_vector[i].doc_name;

			for(int j =0; j < h_info_vector[i].word_item_list.size(); j++){
			
				cout <<", " <<  h_info_vector[i].word_item_list[j].word << " found " << h_info_vector[i].word_item_list[j].occurence << " times";
		
			}
		cout << "."<< endl;
		}
	
	}

	if(! h_contains){ // display not found message if not found
		cout << "No document contains the given query" << endl;
	}

	// displaying time
	cout << "\nTime: " << BSTtime << "\n";
	cout << "\nTime: " << HTtime  << "\n";

	cout << "Speed Up: " << BSTtime / HTtime << endl;
	

return 0;
}

