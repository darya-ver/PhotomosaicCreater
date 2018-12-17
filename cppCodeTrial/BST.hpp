#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    /** Pointer to the root of this BST, or 0 if the BST is empty */
    BSTNode<Data> *root;

    /** Number of Data items stored in this BST. */
    unsigned int isize;

    /** Height of this BST. */
    unsigned int iheight;

  public:
    /** define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
        Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(0) {}

    /** Default destructor.
        Delete every node in this BST.
     */
    virtual ~BST() {
      deleteAll(root);  
    }

    /** Given a reference to a Data item, insert a copy of it in this BST.
     *  Return  true if the item was added to this BST
     *  as a result of this call to insert,
     *  false if an item equal to this one was already in this BST.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=)  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual bool insert(const Data &item) {
      
      // if there is no root, set the root to the given value
      if( root == 0 ) {
        root = new BSTNode<Data>(item);
        isize = 1;
        iheight = 1;
        return true;
      }
      
      // if there is a root, find out where it should go
      BSTNode<Data> * curr = root;
      int currHeight = 1;

      while ( curr != 0 ) {

        // goes to the right subtree
        if ( curr->data < item ) {

          currHeight ++;

          // if it has no right subtree, set it to data
          if ( curr->right == 0 ) {
            curr->right = new BSTNode<Data>(item);
            curr->right->parent = curr;
            isize ++;

            // update height if necessary
            if ( iheight < currHeight ) {
              iheight = currHeight;
            }
            return true;
          }

          // else, go to the right subtree and look there
          curr = curr->right;
        }

        // goes to the left subtree
        else if ( item < curr->data ) {
          
          currHeight ++;

          // if it has no left subtree, set it to data
          if ( curr->left == 0 ) {
            curr->left = new BSTNode<Data>(item);
            curr->left->parent = curr;
            isize ++;

            // update height if necessary
            if ( iheight < currHeight ) {
              iheight = currHeight;
            }
            return true;
          }

          // else, go to the left subtree and look there
          curr = curr->left;
        }

        // it's equal - return false
        else {
          return false;
        }

      }

      return false; 

    }

    /** Find a Data item in the BST.
     *  Return an iterator pointing to the item, or pointing past
     *  the last node in the BST if not found.
     *  Note: This function should use only the '<' operator when comparing
     *  Data items. (should not use ==, >, <=, >=).  For the reasoning
     *  behind this, see the assignment writeup.
     */
    virtual iterator find(const Data &item) const {
      
      // if root is null, return null iterator
      if( root == 0) {
        return iterator(0);
      }

      BSTNode<Data> *currPtr = root;

      while( currPtr != 0 ) {

        // if item is larger, go to right subtree
        if( currPtr->data < item ) {
          currPtr = currPtr->right;
        }

        // if the item is smaller, go to left subtree
        else if( item < currPtr->data ) {
          currPtr = currPtr->left;
        }

        // else, they are equal - we found it! yay
        else {
          return iterator(currPtr);
        }
      }

      // if it reaches here, it means the node wasn't found
      return iterator(0);
    }

    /** Return the number of items currently in the BST.
     */
    unsigned int size() const {return isize;}

    /** Return the height of the BST.
     */
    unsigned int height() const {return iheight;}

    /** Return true if the BST is empty, else false.
     */
    bool empty() const {return isize == 0;}

    /** Return an iterator pointing to the first item in the BST (not the root).
     */
    iterator begin() const {

      // if BST is empty 
      if( root == 0 ) {
        return 0; 
      }

      // if not empty
      BSTNode<Data> *curr;

      curr = root;

      while(curr != 0 ) {
        if( curr->left == 0 ) {
          break;
        }
        curr = curr->left;
      }

      return iterator(curr);
    }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /** Perform an inorder traversal of this BST.
     */
    void inorder() const { inorder(root); }

  private:
    /** Recursive inorder traversal 'helper' function */

    /** Inorder traverse BST, print out the data of each node in ascending
       order. Implementing inorder and deleteAll base on the pseudo code is an
       easy way to get started.
     */
    void inorder(BSTNode<Data> *n) const {

        // base case - current node is null
        if( n == 0 ) {
          return;
        }

        // otherwise, traverse left subtree, print current, traverse right
        inorder(n->left);
        cout << n->data << endl;
        inorder(n->right);
    }

    /** Find the first element of the BST
     */
    static BSTNode<Data> *first(BSTNode<Data> *curr) {
        if (curr == 0) return 0;
        while (curr->left != 0) curr = curr->left;
        return curr;
    }

    /** do a postorder traversal, deleting nodes
     */
    static void deleteAll(BSTNode<Data> *n) {

        // base case - current node is null
        if( n == 0 ) {
          return;
        }

        deleteAll( n->left );
        deleteAll ( n->right );
        delete n;
    }
};

#endif  // BST_HPP
