#include "Temp_Binary_Search_Tree.h"

using namespace std;

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
	if(root == NULL ){
		return true;
	}
	return false;
}
template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::find( const Comparable & x ) const
{
	return elementAt(find(x,root));
}

template <class Comparable>
Comparable & BinarySearchTree<Comparable>::find_to_update( const Comparable & x ) // it returns the founded object as an unconst Comparable object // used in update functions
{
	BinaryNode<Comparable> *t= find(x, root);
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::find( const Comparable & x, BinaryNode<Comparable> * t ) const
{
	if ( t == NULL )
		return NULL;
	else if( x < t->element )
		return find( x, t->left );
	else if( t->element < x )
		return find( x, t->right );
	else
		return t;    // Match
}

template <class Comparable> 
const Comparable & BinarySearchTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMin( BinaryNode<Comparable> *t ) const  // private
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::findMax( BinaryNode<Comparable> *t ) const // private 
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template <class Comparable>
const Comparable & BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable> * t) const
{
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}
template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert( const Comparable & x, BinaryNode<Comparable> * & t ) const // private
{
    if( t == NULL ) //  create a new node at the right place
        t = new BinaryNode<Comparable>( x, NULL, NULL );
    else if( x < t->element )
        insert( x, t->left );  // insert at the left or 
    else if( t->element < x )
        insert( x, t->right );  // right subtree
    else
        ;  // Duplicate; do nothing
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x )
{
     remove( x, root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove( const Comparable & x, BinaryNode<Comparable> * & t ) const // private
{
    if( t == NULL )
        return;   // Item not found; do nothing
    if( x < t->element )
        remove( x, t->left );
    else if( t->element < x )
        remove( x, t->right );
	else if( t->left != NULL && t->right != NULL ) // Two children
	{
		t->element = findMin( t->right )->element;
		remove( t->element, t->right );
	}
	else // one or no children
	{
		BinaryNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}
}   

template <class Comparable>
void BinarySearchTree<Comparable>::updatenf(const Comparable & x){ // it updates the ITEM_NOT_FOUND object

	ITEM_NOT_FOUND = x;
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

template <class Comparable> 
void BinarySearchTree<Comparable>::makeEmpty( BinaryNode<Comparable> * & t ) const // private
{
    if( t != NULL )
    {
        makeEmpty( t->left );
        makeEmpty( t->right );
        delete t;
    }
    t = NULL;
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        cout << endl;
    else
        printTree( root );
}

template <class Comparable>
void BinarySearchTree<Comparable>::printTree( BinaryNode<Comparable> * t ) const // private
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}
//default constructor
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( ) 
	: root( NULL )
	{}
// constructor
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable & notFound ) 
	:ITEM_NOT_FOUND( notFound ), root( NULL )
	{}

// destructor
template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree( )
{
    makeEmpty( );
}

// copy constructor
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree( const BinarySearchTree<Comparable> & rhs ) 
	:root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
    *this = rhs;
}

template <class Comparable>
BinaryNode<Comparable> * BinarySearchTree<Comparable>::clone( BinaryNode<Comparable> * t ) const // private
{
    if ( t == NULL )
        return NULL;
    else
        return new BinaryNode<Comparable>( t->element, clone( t->left ),clone( t->right ) );
}

template <class Comparable>
const BinarySearchTree<Comparable> & BinarySearchTree<Comparable>::operator=( const BinarySearchTree<Comparable> & rhs )
{

	if(this != &rhs){
		this->makeEmpty();

		root = clone(rhs.root);
	}

	return *this;

}
