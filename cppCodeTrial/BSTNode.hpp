#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>
class BSTNode {
   public:
    /** Constructor.  Initialize a BSTNode with the given Data item,
     *  no parent, and no children.
     */
    BSTNode(const Data &d) : data(d) { left = right = parent = 0; }

    BSTNode<Data> *left;
    BSTNode<Data> *right;
    BSTNode<Data> *parent;
    Data const data;  // the const Data in this node.

    /** Return the successor of this BSTNode in a BST, or 0 if none.
     ** PRECONDITION: this BSTNode is a node in a BST.
     ** POSTCONDITION:  the BST is unchanged.
     ** RETURNS: the BSTNode that is the successor of this BSTNode,
     ** or 0 if there is none.
     */
    // TODO
    BSTNode<Data> *successor() {

      BSTNode<Data> *currPtr;

      // check if there is a right subtree
      if( right != 0 ) {
        currPtr = right;

        while( currPtr != 0 ) {
          if( currPtr->left == 0 ) {
            return currPtr;
          }
          currPtr = currPtr->left;
        }
      }

      // if there is no right subtree, find smallest parent that is larger
      else {
        
        // tree with only 1 node
        if( parent == 0) {
          return 0;
        }

        currPtr = parent;

        // finds the smallest parent that is larger
        while( currPtr->data < data ) {
          currPtr = currPtr->parent;

          // if it reaches a node with no parent (root), it means that the
          // node itself is the last node (largest) in the tree
          if( currPtr == 0 ) {
            return 0;
          }
        }
        
        // currPtr will be pointing to the parent that is just larger
        return currPtr;
      }

      return 0;

    }
};

/** Overload operator<< to print a BSTNode's fields to an ostream. */
template <typename Data>
ostream &operator<<(ostream &stm, const BSTNode<Data> &n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
