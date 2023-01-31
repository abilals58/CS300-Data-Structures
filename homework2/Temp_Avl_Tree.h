// this class is the template version of the  AVL Tree class which is taken from lecture slides
// changes in this class are:
// default constructor is used in this homework and so default constructor function updatenf (to change ITEM_NOT_FOUND) is added // ITEM_NOT_FOUND become unconst
// function find_to_update is added to return unconst Comparable found object
// function getBalance added to return balance factor which is used in the remove
#ifndef Temp_AVL_Tree_H
#define Temp_AVL_Tree_H

#include <iostream>

using namespace std;

template <class Comparable> 
class AvlTree;

template <class Comparable>	// template class AVLNode is the class that is used in the AVL Tree class as nodes of the tree and storing the data
class AvlNode
{
    Comparable 	element;
    AvlNode		*left;
    AvlNode   	*right;
    int        	height;

    AvlNode( const Comparable & theElement, AvlNode *lt, AvlNode *rt, int h = 0 )
        : element( theElement ), left( lt ), right( rt ), height( h ) 
		{}

    friend class AvlTree<Comparable>;
};


template <class Comparable>
class AvlTree
{
    public:
        explicit AvlTree( const Comparable & notFound );
		AvlTree(); // default constructor
        AvlTree( const AvlTree & rhs );
		~AvlTree( );

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
		const AvlTree & operator=( const AvlTree & rhs );

	private:

		AvlNode<Comparable> *root; // it is the initial node of the tree
		Comparable ITEM_NOT_FOUND; // it is the object that find function returns if there is not such an element in the tree which is searched for

		const Comparable & elementAt( AvlNode<Comparable> *t ) const;

		void insert( const Comparable & x, AvlNode<Comparable> * & t ) const;
		void remove(const Comparable & x, AvlNode<Comparable> * & t ) const;

		AvlNode<Comparable> * findMin( AvlNode<Comparable> *t ) const;
		AvlNode<Comparable> * findMax( AvlNode<Comparable> *t ) const;
		AvlNode<Comparable> * find( const Comparable & x, AvlNode<Comparable> *t ) const;
		void makeEmpty( AvlNode<Comparable> * & t ) const;
		void printTree( AvlNode<Comparable> *t ) const;
		AvlNode<Comparable> * clone( AvlNode<Comparable> *t ) const;

		// Avl manipulations
		int height( AvlNode<Comparable> *t ) const;
		int getBalance( AvlNode<Comparable> *t ) const; // this functions returns the differences of the heights of left and right child as the balance factor
		int max( int lhs, int rhs ) const;
		void rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const;
		void rotateWithRightChild( AvlNode<Comparable> * & k1 ) const;
		void doubleWithLeftChild( AvlNode<Comparable> * & k3 ) const;
		void doubleWithRightChild( AvlNode<Comparable> * & k1 ) const;
};

#endif