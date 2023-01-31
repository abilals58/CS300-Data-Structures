// this class is the template version of a hash table and most of the codes is taken from lecture slides
// for the collision handling method, linear probing is used
// after loading the 2/3 of the vector it rehashes
#ifndef Temp_Hash_Table_H
#define Temp_Hash_Table_H

#include <vector>
using namespace std;

template <class HashedObj>
class HashTable
{
    public:

		explicit HashTable( const HashedObj & notFound, int size = 101 ); // constructor
		HashTable( const HashTable & rhs ) // copy constructor
				: ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ), array( rhs.array ), currentSize( rhs.currentSize ) { }

		const HashedObj & find( const HashedObj & x ) const;
		HashedObj & find_to_update( const HashedObj & x ); // this function is used to update a node in the hash table
		void makeEmpty( );
		void insert( const HashedObj & x );
		void remove( const HashedObj & x );
		const HashTable & operator=( const HashTable & rhs );
		void display_loading_info();

		enum EntryType { ACTIVE, EMPTY, DELETED }; // to know status of a node

	private:

		struct HashEntry
		{
			 HashedObj element;
			 EntryType info;

			 HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
					  : element( e ), info( i ) { }
		};
            
		vector<HashEntry> array;
		int currentSize;
		HashedObj ITEM_NOT_FOUND;

		int hash(const HashedObj & x, int tableSize) const;
		int nextPrime(int n);
		bool isPrime(int n);
		bool isActive( int currentPos ) const;
		int findPos( const HashedObj & x ) const;
		void rehash( );
 };

#endif
