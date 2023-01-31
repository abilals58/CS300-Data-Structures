#include "Temp_AVL_Tree.h"

template <class Comparable>
bool AvlTree<Comparable>::isEmpty() const
{
	if(root == NULL ){
		return true;
	}
	return false;
}
template <class Comparable>
const Comparable & AvlTree<Comparable>::find( const Comparable & x ) const
{
	return elementAt(find(x,root));
}

template <class Comparable>
Comparable & AvlTree<Comparable>::find_to_update( const Comparable & x ) // it returns the founded object as an unconst Comparable object // used in update functions
{
	AvlNode<Comparable> *t = find(x, root);
	return t == NULL ? ITEM_NOT_FOUND : t->element;
}


template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::find( const Comparable & x, AvlNode<Comparable> * t ) const
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
const Comparable & AvlTree<Comparable>::findMin( ) const
{
    return elementAt( findMin( root ) );
}

template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMin( AvlNode<Comparable> *t ) const  // private
{
    if( t == NULL )
        return NULL;
    if( t->left == NULL )
        return t;
    return findMin( t->left );
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::findMax( ) const
{
    return elementAt( findMax( root ) );
}

template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::findMax( AvlNode<Comparable> *t ) const // private 
{
    if( t != NULL )
        while( t->right != NULL )
            t = t->right;
    return t;
}

template <class Comparable>
const Comparable & AvlTree<Comparable>::elementAt(AvlNode<Comparable> * t) const
{

	return t == NULL ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
void AvlTree<Comparable>::makeEmpty( )
{
    makeEmpty( root );
}

template <class Comparable> 
void AvlTree<Comparable>::makeEmpty( AvlNode<Comparable> * & t ) const // private
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
void AvlTree<Comparable>::printTree( ) const
{
    if( isEmpty( ) )
        cout << endl;
    else
        printTree( root );
}

template <class Comparable>
void AvlTree<Comparable>::printTree( AvlNode<Comparable> * t ) const // private
{
    if ( t != NULL )
    {
        printTree( t->left );
        cout << t->element << endl;
        printTree( t->right );
    }
}
// default constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree() 
	: root( NULL )
	{}

// constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree(const Comparable & notFound ) 
	:ITEM_NOT_FOUND( notFound ), root( NULL )
	{}

// destructor
template <class Comparable>
AvlTree<Comparable>::~AvlTree( )
{
    makeEmpty( );
}

// copy constructor
template <class Comparable>
AvlTree<Comparable>::AvlTree( const AvlTree<Comparable> & rhs ) 
	:root( NULL ), ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND )
{ 
    *this = rhs;
}

template <class Comparable>
AvlNode<Comparable> * AvlTree<Comparable>::clone( AvlNode<Comparable> * t ) const // private
{
    if ( t == NULL )
        return NULL;
    else
        return new AvlNode<Comparable>( t->element, clone( t->left ),clone( t->right ) );
}

template <class Comparable>
const AvlTree<Comparable> & AvlTree<Comparable>::operator=( const AvlTree<Comparable> & rhs )
{
	if(this != &rhs){
		this->makeEmpty();

		root = clone(rhs.root);
		ITEM_NOT_FOUND = rhs.ITEM_NOT_FOUND;
	}

	return *this;
}

template <class Comparable>
int AvlTree<Comparable>::height( AvlNode<Comparable> *t ) const // private
 {
    if (t == NULL)
	    return -1;
	
    return t->height;
}

template <class Comparable>
int AvlTree<Comparable>::getBalance( AvlNode<Comparable> *t ) const // private // this functions returns the differences of the heights of left and right child as the balance factor
 {
    if (t == NULL)
	    return 0;
	
	return height(t->left) - height(t->right);
}


template <class Comparable>
int AvlTree<Comparable>::max( int lhs, int rhs ) const // private
{
    if (lhs > rhs)
	    return lhs;

    return rhs;            
}

template <class Comparable>
void AvlTree<Comparable>::insert( const Comparable & x )
{
    insert( x, root );
}

template <class Comparable>
 void AvlTree<Comparable>::insert ( const Comparable & x, AvlNode<Comparable> * & t ) const // private
 {
    if ( t == NULL )
        t = new AvlNode<Comparable>( x, NULL, NULL );

    else if ( x < t->element ) {
        // X should be inserted to the left tree!
        insert( x, t->left );
           
		// Check if the left tree is out of balance (left subtree grew in height!)
        if ( height( t->left ) - height( t->right ) == 2 )
            if ( x < t->left->element )  // X was inserted to the left-left subtree!
                    rotateWithLeftChild( t );
            else			     // X was inserted to the left-right subtree!
                    doubleWithLeftChild( t );
    }
	else if( t->element < x )
    {    // Otherwise X is inserted to the right subtree
            insert( x, t->right );
            if ( height( t->right ) - height( t->left ) == 2 )
			// height of the right subtree increased
                if ( t->right->element < x )
		     	// X was inserted to right-right subtree
                    rotateWithRightChild( t );
            else // X was inserted to right-left subtree
                    doubleWithRightChild( t );
    }
    else
        ;  // Duplicate; do nothing
            
	// update the height the node
    t->height = max( height( t->left ), height( t->right ) ) + 1;

}

template <class Comparable>
void AvlTree<Comparable>::rotateWithLeftChild( AvlNode<Comparable> * & k2 ) const // private
{
    AvlNode<Comparable> *k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
    k1->height = max( height( k1->left ), k2->height ) + 1;
    k2 = k1;
}

template <class Comparable> 
void AvlTree<Comparable>::rotateWithRightChild ( AvlNode<Comparable> * & k1 ) const // private
{
    AvlNode<Comparable> *k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
    k2->height = max( height( k2->right ), k1->height ) + 1;
    k1 = k2;
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithLeftChild ( AvlNode<Comparable> * & k3 ) const // private
{
    rotateWithRightChild( k3->left );
    rotateWithLeftChild( k3 );
}

template <class Comparable>
void AvlTree<Comparable>::doubleWithRightChild ( AvlNode<Comparable> * & k1 ) const // private
{
    rotateWithLeftChild( k1->right );
    rotateWithRightChild( k1 );
}


template <class Comparable>
void AvlTree<Comparable>::remove( const Comparable & x )
{
     remove( x, root );
}



template <class Comparable>
 void AvlTree<Comparable>::remove( const Comparable & x, AvlNode<Comparable> * & t ) const // private 
{
	// deleting as a avl tree
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
		AvlNode<Comparable> *oldNode = t;
		t = ( t->left != NULL ) ? t->left : t->right;
		delete oldNode;
	}

	// updating the height of the current node
	if(t == NULL){
		return;
	}

	t->height = max(height(t->left), height(t->right)) + 1; 

	 //rebalance the tree

	// getting the balance factor
	int balance = getBalance(t);

	// Check if the left tree is out of balance (left subtree grew in height!)
    if (  balance > 1 ){
		if ( getBalance(t->left) >= 0 ){  // X was removed to the left-right subtree!
            rotateWithLeftChild( t );
			return;
		}
        else{ // X was removed to the left-left subtree!

            doubleWithLeftChild( t );
			return;
		}
	}
	if ( balance < -1 ) // height of the right subtree increased
		if ( getBalance(t->right) <= 0){ // X was removed to right-left subtree

            rotateWithRightChild( t );
			return;
		}
        else{ // X was removed to right-right subtree

            doubleWithRightChild( t );
			return;
		}
 }

template <class Comparable>
void AvlTree<Comparable>::updatenf(const Comparable & x){ // it updates the ITEM_NOT_FOUND object
	ITEM_NOT_FOUND = x;
}