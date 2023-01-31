// Ahmet Bilal Yildiz

#include<iostream>
#include<string>
#include<fstream>
#include <sstream>
#include<chrono>
#include "Temp_Binary_Search_Tree.h"
#include "Temp_Binary_Search_Tree.cpp"
#include "Temp_AVL_Tree.h"
#include "Temp_AVL_Tree.cpp"
#pragma comment(linker, "/STACK:2000000")

using namespace std;



struct item // item struct stores the title and the info and this struct is used in section
{

	string title; // item title
	string info; // item info

	item(string t = "", string i = "")
		: title(t), info(i)
	{}

	bool item::operator <(const item &rhs) const
	{
		if(title < rhs.title){
			return true;
		}
		return false;
	}
	
	const item& item::operator =(const item &rhs) 
	{
		title = rhs.title;
		info = rhs.info;
		return *this;
	}


	friend std::ostream& operator<<(std::ostream& os, const item& rhs)
	{
		return os << rhs.title; 
	}
};

struct bsection // section that contains binary tree
{
	string title; // secction title
	BinarySearchTree<item> items_tree; // tree of items 

	bsection(string t = " ") // constructor
		:title(t)
	{
	
	}

	bool bsection::operator <(const bsection & rhs) const
	{
		if(title < rhs.title){
			return true;
		}
		return false;
	}

	const bsection& bsection::operator =(const bsection &rhs){
		title = rhs.title;
		items_tree = rhs.items_tree;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const bsection& rhs)
	{
		return os << rhs.title; 
	}

};

struct asection // section that contains avl tree
{
	string title;
	AvlTree<item> items_tree;


	asection( string t = " ") // constructor 
		: title(t) 
	{
	}

	bool asection::operator <(const asection & rhs) const
	{
		if(title < rhs.title){
			return true;
		}
		return false;
	}

	const asection& asection::operator =(const asection  &rhs) 
	{
		title = rhs.title;
		items_tree = rhs.items_tree;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const asection& rhs)
	{
		return os << rhs.title; 
	}

};

void GetSearchSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook); // this function get the title of the section and search for it in the notebooks if it is in notebooks then directs to the section menu
void section_menu(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook,asection *& avlptr, bsection *& bstptr); // it runs the sectin menu including all operations related to the section
void DisplayItemInfo(asection *& avlptr, bsection *& bstptr); // this function gets the item title and displays this item's info
void AddAnItem( asection *& avlptr, bsection *& bstptr);	// this function gets the title and the info values and adds the new item to the tree's of section
void UpdateAnItem( asection *& avlptr, bsection *& bstptr); // this function gets the title seacrh it and update its info
void DeleteAnItem( asection *& avlptr, bsection *& bstptr); // this function gets the title of an item and delete that item from the trees of item in section
void AddNewSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook); // this function gets the title for the new section and add the new section
void DeleteSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook); // this function gets the section title and delete that section from the notebook

int main(){

	// initializing the notebooks

	BinarySearchTree<bsection> bnotebook;
	AvlTree<asection> anotebook;

	// updating item not found objects for both inner trees and notebooks
	item nfound("null", "null");
	AvlTree<item> itemtree(nfound);
	asection anfound;
	anfound.title = "null";
	anfound.items_tree.updatenf(nfound);
	bsection bnfound;
	bnfound.title = "null";
	bnfound.items_tree.updatenf(nfound);

	anotebook.updatenf(anfound);
	bnotebook.updatenf(bnfound);

	cout << "Welcome to the Notebook! " << endl;
	// reading the file
	fstream data;
	string line = "-";
	string i_title, i_info;
	data.open("data.txt");
	// initialization of timer
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now(); 
	long long avltimer = 0, bstimer = 0;
	do{ 

		if(line[0] == '-'){ // getting the title
			getline(data, line);
		}

		bsection b_section(line); // forming b_section
		asection a_section(line);
		getline(data, line);
		while(line[0] == '-'){
			line = line.substr(1, line.length()); // deleting the first dash(-)
			int index = line.find("-");

			i_title = line.substr(0, index);
			i_info = line.substr(index+1, line.length());

			item new_item(i_title, i_info);
			start = std::chrono::high_resolution_clock::now(); // start time
			a_section.items_tree.insert(new_item);
			end = std::chrono::high_resolution_clock::now(); // end time
			avltimer += (end-start).count() / 1000.0;

			start = std::chrono::high_resolution_clock::now(); // start time
			b_section.items_tree.insert(new_item);
			end = std::chrono::high_resolution_clock::now(); // end time
			bstimer += (end-start).count() / 1000.0;
			getline(data, line);
	
		}
		start = std::chrono::high_resolution_clock::now(); // start time
		anotebook.insert(a_section);
		end = std::chrono::high_resolution_clock::now(); // end time
		avltimer += (end-start).count() / 1000.0; // get the elapsed time in microseconds
		cout << "Section "<< a_section.title << " has been inserted into the AVL notebook." << endl;
		std::cout << "[AVL] Elapsed time: " << avltimer <<" microseconds" << endl;

		start = std::chrono::high_resolution_clock::now(); // start time
		bnotebook.insert(b_section); 
		end = std::chrono::high_resolution_clock::now(); // end time
		bstimer += (end-start).count() / 1000.0; // get the elapsed time in microseconds
		cout << "Section "<< b_section.title << " has been inserted into the BST notebook." << endl;
		std::cout << "[BST] Elapsed time: " << bstimer << " microseconds" << endl;
	}while(!data.eof());

	data.close();

	// displaying the main menu
	cout << endl; cout<<"MENU"<<endl
			<<"Please enter an input between [1 - 6]:"<<endl
			<<"1- Display the sections [AVL]"<<endl
			<<"2- Display the sections [BST]"<<endl
			<<"3- Select a section"<<endl
			<<"4- Add new section"<<endl
			<<"5- Delete a section"<<endl
			<<"6- Exit"<<endl;
			cout << endl; 
	while (true){

			int option;
			cout << "Input: ";
			cin>>option;
			switch (option) { 
				case 1: 
					// printing the avl notebook sections in in order traversel way(ascending order)
					cout << "*****" << endl;
					anotebook.printTree();
					cout << "*****" << endl;
					break;
				case 2: 
					// printing the bst notebook sections in in order traversel way(ascending order)
					cout << "*****" << endl;
					bnotebook.printTree(); 
					cout << "*****" << endl;
					break;
				case 3: 

					// getting the section name, searching for it
					GetSearchSection(anotebook, bnotebook);
					break;
				case 4:
					AddNewSection(anotebook, bnotebook);
					break;
				case 5:
					DeleteSection(anotebook, bnotebook);
					break;
				case 6:
					exit(0); 
					break;
				default:
					cout<<"INVALID OPTION!!! Try again"<<endl;
			}//switch 
	}//while (true)

}

void GetSearchSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook){ // this function get the title of the section and search for it in the notebooks if it is in notebooks then directs to the section menu
	item nfound("null","null");
	string section;
	cout << "Enter the title of the section: ";
	cin.ignore();
	getline(cin, section); // getting section as a line
	asection finda(section);
	bsection findb(section);

	asection * avlptr;
	bsection * bstptr;


	avlptr = & anotebook.find_to_update(finda);
	bstptr = & bnotebook.find_to_update(findb);

	avlptr->items_tree.updatenf(nfound);
	bstptr->items_tree.updatenf(nfound);

	if(avlptr->title == "null" && bstptr->title == "null"){
		cout << "Invalid title!" << endl;	
	}
	else{
		cout << "Selected section -> " << section << endl;
		cout << endl; 
		cout<<"Please enter an input between [1 - 7]:"<<endl
			<<"1- Display the items [AVL]"<<endl
			<<"2- Display the items [BST]"<<endl
			<<"3- Display the information of a item"<<endl
			<<"4- Add new item"<<endl
			<<"5- Update the information of a item"<<endl
			<<"6- Delete an item"<<endl
			<<"7- Return to main menu"<<endl;
			cout << endl;
		section_menu(anotebook, bnotebook, avlptr, bstptr);
	}
}


void section_menu(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook, asection* & avlptr, bsection* & bstptr) // it runs the sectin menu including all operations related to the section
{
	// displaying the section menu
	while (true){

			int option;
			cout <<endl << "Input: ";
			cin>>option;
			switch (option) { 
				case 1:
					//PrintItems(finda);
					cout << "*****" << endl;
					avlptr->items_tree.printTree();
					cout << "*****" << endl;
					break;
				case 2:
					cout << "*****" << endl;
					bstptr->items_tree.printTree();
					cout << "*****" << endl;
					//PrintItems(findb);
					break;
				case 3: 
					DisplayItemInfo(avlptr, bstptr);
					break;
				case 4:
					AddAnItem(avlptr, bstptr);
					break;
				case 5:
					UpdateAnItem(avlptr, bstptr);
					break;
				case 6:
					DeleteAnItem( avlptr ,bstptr);
					break;
				case 7:
					// returning to the main menu
					cout << endl; cout<<"MENU"<<endl
					<<"Please enter an input between [1 - 6]:"<<endl
					<<"1- Display the sections [AVL]"<<endl
					<<"2- Display the sections [BST]"<<endl
					<<"3- Select a section"<<endl
					<<"4- Add new section"<<endl
					<<"5- Delete a section"<<endl
					<<"6- Exit"<<endl;
					cout << endl; 
					return;
				default:
					cout<<"INVALID OPTION!!! Try again"<<endl;
			}//switch 
	}//while (true)

}

void AddNewSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook){ // this function gets the title for the new section and add the new section
	// getting section and forming asection-bsection to search and insert
	item nfound("null","null");
	string section;
	cout << "Enter a title for the section: ";
	cin.ignore();
	getline(cin, section); // getting section as a line
	asection finda(section);
	bsection findb(section);

	if(anotebook.find(finda).title != "null"){ // if the section with this title already exists in the notebooks
		//displaying an error message
	
		cout << "Section \"" << section << "\" already exists." << endl;
	
	}
	else{
		anotebook.insert(finda);
		bnotebook.insert(findb);
		// displaying inform message
		cout << "The new section \"" << section << "\" has been inserted." << endl;
	}

}

void DeleteSection(AvlTree<asection> & anotebook, BinarySearchTree<bsection> &bnotebook){ // this function gets the section title and delete that section from the notebook
	// getting section and forming asection-bsection to search and delete
	item nfound("null","null");
	string section;
	cout << "Enter a title of the section: ";
	cin.ignore();
	getline(cin, section); // getting section as a line
	asection finda(section);
	finda.items_tree.updatenf(nfound);
	bsection findb(section);
	finda.items_tree.updatenf(nfound);

	if(anotebook.find(finda).title == "null"){ // if the section with this title already exists in the notebooks
		//displaying an error message
	
		cout << "Section \"" << section << "\" does not exists." << endl;
	
	}
	else{
		anotebook.remove(finda);
		bnotebook.remove(findb);
		// displaying inform message
		cout << "The section has been deleted." << endl;
	}

}

void DisplayItemInfo( asection *& avlptr, bsection *& bstptr){ // this function gets the item title and displays this item's info

	string ititle;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin,ititle); // getting title as a line
	item  find_item(ititle);
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now(); // end time
	long long avltimer = 0, bstimer = 0;
	// search for item title in both bst and avl sections


	start = std::chrono::high_resolution_clock::now();
	item item_a = avlptr->items_tree.find(find_item);
	end = std::chrono::high_resolution_clock::now();
	avltimer += (end-start).count() / 1000.0;

	start = std::chrono::high_resolution_clock::now();
	item item_b = bstptr->items_tree.find(find_item);
	end = std::chrono::high_resolution_clock::now();
	bstimer += (end-start).count() / 1000.0;

	// displaying the search time
	std::cout << "[AVL] Elapsed time: " << avltimer << " microseconds" <<endl;
	std::cout << "[BST] Elapsed time: " << bstimer << " microseconds" << endl;


	if(item_a.title == "null" && item_b.title == "null"){
		cout << "Invalid title. " << endl;	

	}
	else{
	// displaying the item info // only from avl
		cout << item_a.info << endl;
	
	}

}

void AddAnItem( asection *& avlptr, bsection *& bstptr){ // this function gets the title and the info values and adds the new item to the tree's of section

	string ititle;
	cout << "Enter the title for the item: ";
	cin.ignore();
	getline(cin,ititle); // getting title as a line
	item  find_item(ititle);
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now(); // end time
	long long avltimer = 0, bstimer = 0;

	// search for item title in both bst and avl sections
	item item_a = avlptr->items_tree.find(find_item);
	item item_b = bstptr->items_tree.find(find_item);

	if(item_a.title != "null" && item_b.title != "null"){

		cout << "Item \"" << ititle << "\" already exists in the \"" << avlptr->title << "\"." << endl;	

	}
	else{
	// getting the info and adding the new item
		string info;
		cout << "Enter a description for the item: ";
		getline(cin ,info); // getting title as a line
		find_item.info = info;

		start = std::chrono::high_resolution_clock::now();
		avlptr->items_tree.insert(find_item);
		end = std::chrono::high_resolution_clock::now();
		avltimer += (end-start).count() / 1000.0;

		start = std::chrono::high_resolution_clock::now();
		bstptr->items_tree.insert(find_item);
		end = std::chrono::high_resolution_clock::now();
		bstimer += (end-start).count() / 1000.0;
		
		// displaying the insertion time
		std::cout << "[AVL] Elapsed time: " << avltimer << " microseconds" <<endl;
		std::cout << "[BST] Elapsed time: " << bstimer << " microseconds" << endl;
		cout << "The new item \""  << ititle <<"\" has been inserted." << endl;

	}
}

void UpdateAnItem( asection *& avlptr, bsection *& bstptr){ // this function gets the title search it and update its info

	string ititle;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, ititle); // getting title as a line
	item  find_item(ititle);
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now(); // end time
	long long avltimer = 0, bstimer = 0;

	// search for item title in both bst and avl sections

	start = std::chrono::high_resolution_clock::now();
	item* item_a = &(avlptr->items_tree.find_to_update(find_item));
	end = std::chrono::high_resolution_clock::now();
	avltimer += (end-start).count() / 1000.0;

	start = std::chrono::high_resolution_clock::now();
	item *item_b = &bstptr->items_tree.find_to_update(find_item);
	end = std::chrono::high_resolution_clock::now();
	bstimer += (end-start).count() / 1000.0;

	// displaying the search time
	std::cout << "[AVL] Elapsed time: " << avltimer << " microseconds" <<endl;
	std::cout << "[BST] Elapsed time: " << bstimer << " microseconds" << endl;

	if(item_a->title == "null" && item_b->title == "null"){

		cout << "Item \""<< ititle <<"\" does not exist in the \"" << avlptr->title << "\"." << endl;		

	}
	else{
		// getting new info and updating the item info
		string info;
		cout << "Enter the new information: ";
		//cin.ignore();
		getline(cin, info); // getting info as a line
		
		item_a->info = info;
		item_b->info = info;
		
		cout << "The content " << ititle << " has been updated." << endl;
	}
}

void DeleteAnItem( asection *& avlptr, bsection *& bstptr){ // this function gets the title of an item and delete that item from the trees of item in section

	string ititle;
	cout << "Enter the title of the item: ";
	cin.ignore();
	getline(cin, ititle); // getting title as a line
	item  find_item(ititle);
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now(); // end time
	long long avltimer = 0, bstimer = 0;

	// search for item title in both bst and avl sections

	start = std::chrono::high_resolution_clock::now();
	item item_a = (avlptr->items_tree.find(find_item));
	end = std::chrono::high_resolution_clock::now();
	avltimer += (end-start).count() / 1000.0;

	start = std::chrono::high_resolution_clock::now();
	item item_b = bstptr->items_tree.find(find_item);
	end = std::chrono::high_resolution_clock::now();
	bstimer += (end-start).count() / 1000.0;

	// displaying the search time
	std::cout << "[AVL] Elapsed time: " << avltimer << " microseconds" <<endl;
	std::cout << "[BST] Elapsed time: " << bstimer << " microseconds" << endl;

	if(item_a.title == "null" && item_b.title == "null"){

		cout << "Item \""<< ititle <<"\" does not exist in the \"" << avlptr->title << "\"." << endl;		

	}
	else{
		// deleting the item
		avlptr->items_tree.remove(item_a);
		bstptr->items_tree.remove(item_b);

		cout << "The item \"" << ititle << "\" has been deleted." << endl;
	}
}
