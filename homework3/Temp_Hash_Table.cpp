
#include "Temp_Hash_Table.h"


// hash function
template <class HashedObj>
int HashTable<HashedObj>::hash (const HashedObj & key, int tableSize) const
{ 
   return key.hash(tableSize);
}

template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size ) // constructor
         	: ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) )
{
	currentSize = 0;
    makeEmpty( ); 
}


// find
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x )  const
{
    int currentPos = findPos( x );
    if (isActive( currentPos )) 
        return array[ currentPos ].element; 

    return   ITEM_NOT_FOUND;
}

// find_to_update
template <class HashedObj>
HashedObj & HashTable<HashedObj>::find_to_update( const HashedObj & x ) 
{
    int currentPos = findPos( x );
    if (isActive( currentPos )) 
        return array[ currentPos ].element; 

	return   ITEM_NOT_FOUND;
}


// makeEmpty...
template <class HashedObj> // making hash table logially empty
void HashTable<HashedObj>::makeEmpty(){
	for(int i = 0; i < array.size(); i++){
		array[i].info = EMPTY;
	}
}
// insert
template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
    // Insert x as active
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        return;
    array[ currentPos ] = HashEntry( x, ACTIVE );

     // enlarge the hash table if necessary 
	if ( ++currentSize >= 2 * array.size( ) / 3)
        rehash( );
}

// remove
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
    int currentPos = findPos( x );
    if ( isActive( currentPos ) )
        array[ currentPos ].info = DELETED;
}

// operator=
template <class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>::operator=( const HashTable<HashedObj> & rhs )
{
	if(this != &rhs){
		this->makeEmpty();
	}
	for(int i = 0; i < rhs.array.size(); i ++){
		array[i] = rhs.array[i];
	}
}

template <class HashedObj>
void HashTable<HashedObj>::display_loading_info(){

	double c_size = currentSize;
	cout << "After preprocessing, the unique word count is " << currentSize << ". Current load ratio is " << c_size / array.size() << endl;
}

// privates....


template <class HashedObj>
int HashTable<HashedObj>::nextPrime(int n)
{
	if ( n % 2 == 0 )
        n++;

    for ( ; ! isPrime( n ); n += 2 )
        ;

    return n;

}

template <class HashedObj>
bool HashTable<HashedObj>::isPrime(int n)
{
	if ( n == 2 || n == 3 )
        return true;

    if ( n == 1 || n % 2 == 0 )
        return false;

    for ( int i = 3; i * i <= n; i += 2 )
        if ( n % i == 0 )
            return false;

    return true;

}

template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x ) const // find position using collision handling method: linear probing
{
    int collisionNum = 0;
    int currentPos = hash( x, array.size( ) );

    while ( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
    {
		currentPos += ++collisionNum;  //add the difference // linear probing
        if ( currentPos >= array.size( ) ){  // perform the mod
            currentPos -= array.size(); // if necessary
		}
    }
    return currentPos;
}

template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
     return array[ currentPos ].info == ACTIVE;
}

template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{

    vector<HashEntry> oldArray = array;

    // Create new double-sized, empty table
    array.resize( nextPrime( 2 * oldArray.size( ) ) );
    for ( int j = 0; j < array.size( ); j++ )
            array[ j ].info = EMPTY;

    // Copy table over
    currentSize = 0;
    for ( int i = 0; i < oldArray.size( ); i++ )
        if ( oldArray[ i ].info == ACTIVE )
                insert( oldArray[ i ].element );

	// printing the info related to rehashing
	double c_size = currentSize;
	cout << "rehashed..." << endl;
	cout << "previous table size:" << oldArray.size() << ", new table size: " << array.size() << ", current unique word count " << currentSize << ", current load factor: " << c_size / array.size() << endl; 
}
