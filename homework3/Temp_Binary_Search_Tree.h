// this class is the template version of the binary search tree class which is taken from lecture slides
// changes in this class are:
// default constructor is used in this homework and so default constructor function updatenf (to change ITEM_NOT_FOUND) is added // ITEM_NOT_FOUND become unconst
// function find_to_update is added to return unconst Comparable found object

#ifndef Temp_Binary_Search_Tree_H
#define Temp_Binary_Search_Tree_H

#include <iostream>

using namespace std;

template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode // BinaryNode is the class that is used in BinarySearchTree class as node elements of the class
{
    Comparable element;
    BinaryNode  *left;
    BinaryNode  *right;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt ) // constructor
		: element( theElement ), left( lt ), right( rt )
		{}
            
friend class BinarySearchTree<Comparable>;
};

template <class Comparable>
class BinarySearchTree
{
	public:

		explicit BinarySearchTree( const Comparable & notFound );
		BinarySearchTree(); // default constructor
		BinarySearchTree( const BinarySearchTree & rhs );
		~BinarySearchTree( );

		const Comparable & findMin( ) const;
		const Comparable & findMax( ) const;
		const Comparable & find( const Comparable & x ) const;
		Comparable & find_to_update( const Comparable & x ); // it returns the founded object as an unconst Comparable object // used in update functions
		bool isEmpty( ) const;
		void printTree( ) const;

		void makeEmpty( );
		void insert( const Comparable & x );
		void remove( const Comparable & x );
		void updatenf(const Comparable & x); // it updates the ITEM_NOT_FOUND object
		const BinarySearchTree & operator=( const BinarySearchTree & rhs );
		
	private:

        BinaryNode<Comparable> *root; // it is the initial node of the tree
        Comparable ITEM_NOT_FOUND; // it is the object that find function returns if there is not such an element in the tree which is searched for

        const Comparable & elementAt( BinaryNode<Comparable> *t ) const;

        void insert( const Comparable & x, BinaryNode<Comparable> * & t ) const;
        void remove( const Comparable & x, BinaryNode<Comparable> * & t ) const;
        BinaryNode<Comparable> * findMin( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * findMax( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * find( const Comparable & x,  BinaryNode<Comparable> *t ) const;
        void makeEmpty( BinaryNode<Comparable> * & t ) const;
        void printTree( BinaryNode<Comparable> *t ) const;
        BinaryNode<Comparable> * clone( BinaryNode<Comparable> *t ) const;
};

#endif