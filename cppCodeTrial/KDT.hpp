#ifndef KDT_HPP
#define KDT_HPP

#include <math.h>     // pow, abs
#include <algorithm>  // sort, max, min
#include <iostream>   // cout, cin, and cerr
#include <limits>     // numeric_limits<type>::max()
#include <vector>     // vector<typename>
#include "BST.hpp"

using namespace std;

class Point {
   private:
    double delta = 0.00005;

   public:
    /** x and y point coordinates */
    int x, y, z, imgInd;

    /** Default constructor: point at (0, 0) */
    Point() : x(0), y(0), z(0), imgInd(0) {}

    /** constructor that defines point location */
    Point(int x, int y, int z, int i) : x(x), y(y), z(z), imgInd(i) {}

    /** Equals operator */
    bool operator==(const Point &other) const {
        return abs(x - other.x) < delta && abs(y - other.y) < delta
            && abs(z - other.z) < delta;
    }

    /** Not-equals operator */
    bool operator!=(const Point &other) const {
        return abs(x - other.x) > delta || abs(y - other.y) > delta
              || abs(z - other.z) > delta;
    }

    /** Less than operator */
    bool operator<(const Point &other) const {
        cerr << "This operator should not be called, you will need "
             << "check the x and y components each time" << endl;
        return false;
    }

    /** Return the squre of the Euclidean distance between two points p1 and p2
     */
    static int squareDistance(const Point &p1, const Point &p2) {
      return (p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) 
           + (p1.z - p2.z)*(p1.z - p2.z);
    }
};

std::ostream &operator<<(std::ostream &out, const Point &data) {
    out << "(" << data.x << ", " << data.y << ", " <<  data.z << ")";
    return out;
}

bool xLessThan(const Point &p1, const Point &p2) { return p1.x < p2.x; }

bool yLessThan(const Point &p1, const Point &p2) { return p1.y < p2.y; }

bool zLessThan(const Point &p1, const Point &p2) { return p1.z < p2.z; }

class KDT : public BST<Point> {
   public:
    /** Given a vector of Point references, insert a copy into the BST.
     *  Return the number of elements that the fully constructed tree contains
     *  Note. Because of the nature of the KDTree, a simple < operator
     *        will not be sufficient.  You will need to check the x and y
     *        coordinates individually.  Two functions have been provided
     *        for your convenience above, (xLessThan and yLessThan). You may
     *        find them useful for the sort function from #include<algorithm>.
     *  Note. Since KDT inherits from BST, you still have access to the
     *        root, isize, and iheight instance variables and should modify
     *        them accordingly.
     *  Note. We have also provided a private helper method for the build
     *        function called buildSubset defined below.
     */
    virtual unsigned int build(vector<Point> &items) {
      
      if( items.size() == 0 ) {
        return 0;
      }
      // call build subset
      root = buildSubset( items, 0, items.size(), 0, 0 );

      // TODO delete
     // printTree( root );
      // return size of the tree
      return isize;

    }

    /** Find the nearest neighbor to a given point
     *  Returns the point in the kd-tree nearest to the parameter item.
     *  Note. THIS IS DIFFERENT THAN HOW THE PREVIOUS FIND FUNCTION WORKS
     *  Note. Since KDT inherits from BST, you still have access to the
     *        root, isize, and iheight member variables.
     *  Note. The dimension ordering you used to build the tree must be used
     *        to search through it.
     *  Note. We have added a private helper method for your convenience called
     *        findNNHelper defined below.
     */
    // TODO
    virtual iterator findNearestNeighbor(const Point &item) const {
     
      if( root == 0 ) {
        return iterator(0);
      }
      double shortestDistance = Point::squareDistance( item, root->data);
      BSTNode<Point>* closest = root;

      findNNHelper(root, item, &shortestDistance, &closest, 0);

      return iterator(closest);

    }

    /** For the kd-tree, the find method should not be used.  Use the function
     *  findNearestNeighbor instead.
     */
    virtual iterator find(const Point &item) const override {
        cerr << "The KD Tree find method should not be called" << endl;
        cerr << "Use findNearestNeighbor instead" << endl;
        return 0;
    }

    /** For the kd-tree, the insert method should not be used.  The tree is
     *  built all at once.  There should be no scenario where you add individual
     * points.
     */
    virtual bool insert(const Point &item) override {
        cerr << "The KD Tree insert method should not be called" << endl;
        return false;
    }

   private:

    /** 
     * prints the tree
     */
    void printTree( BSTNode<Point> * tree ) {
      if( tree == 0 ) return;
      cout << "Node: " << tree->data ;
      if( tree->left != 0 ) {
        cout << ", left: " << tree->left->data;
      }
      if( tree->right != 0 ) {
        cout << ", right: " << tree->right->data;
      }
      cout << endl;

      //cout << "Node: " << tree->data << ", left: " << tree->left;
      //cout << ", right: " << tree->right << endl;
      printTree( tree->left );
      printTree( tree->right );
    }

    /** Recursively add a subset of the array to the KD tree
     *  Parameters items: the list of points that are used to build the kd tree
     *             start: the starting index for this subsection of the tree
     *             end: the non-inclusive ending index for this subtree
     *             dimension: 0 if sorting along the x-axis, and 
     *                        1 if sorting along the y-axis
     *                        2 if sorting along the z-axis
     *                        
     *  PostConditions: the parent node should have its left and right children
     *                  set if there are any available points and recursive
     *                  calls should be made for the left and right subtree
     *                  (again, if there are any remaining points).
     *  NOTE: We gave you two methods: xLessThan and yLessThan.  We expect you
     *        that you will find these methods very helpful.  For your sake,
     *        please keep this in mind.
     */
    BSTNode<Point> *buildSubset(vector<Point> items, unsigned int start,
                                unsigned int end, unsigned int dimension,
                                unsigned int height) {
      
      // if end < start, return a null ptr
      if( end < start ) {
        return 0;
      }

      /*cout << "\nstart: " << start << ", end: " << end << endl;
      for(int i = 0; i < items.size(); i++ ) {
        cout << items[i];
      }

      cout <<  endl;
      */



      // update height if necessary
      if( iheight < height ){
        iheight = height;
      }

      // if end == start, return a new node with data from that element
      if( end == start ) {
        // update size
        //isize++;
        //return new BSTNode<Point>( items[start] );
        return 0;
      }

      // used to find median index
      unsigned int med;

      // if sorting in terms of x
      if( dimension == 0 ) {

        // sort the vector
        std::sort( items.begin() + start, items.begin() + end, xLessThan );
        
        med = (start + end ) / 2;

        // find the leftmost median
        while( med > start && items[med].x == items[med-1].x ) {
          med--;
        }

      } 

      // if sorting in terms of y
      else if( dimension == 1) {

        // sort the vector
        std::sort( items.begin() + start, items.begin() + end, yLessThan );
        
        med = (start + end ) / 2;

        // find the leftmost median
        while( med > start && items[med].y == items[med-1].y ) {
          med--;
        }

      }

      // if sorting in terms of z
      else {

        // sort the vector
        std::sort( items.begin() + start, items.begin() + end, zLessThan );
        
        med = (start + end ) / 2;

        // find the leftmost median
        while( med > start && items[med].z == items[med-1].z ) {
          med--;
        }

      }


      BSTNode<Point>* pt = new BSTNode<Point>( items[med] );

      //cout << "med: " << med << endl;
      if( end - start == 2 ) {
        if( start == med ) {
          pt->right = 
                 buildSubset( items, med + 1, end, (dimension + 1) % 3, height + 1 );
          pt->left = 0;
        } else {
          pt->left = 
                  buildSubset( items, start, med, (dimension + 1) % 3, height + 1 );
          pt->right = 0;
        }
      } else {

        pt->left = buildSubset( items, start, med, (dimension + 1) % 3, height + 1 );
        pt->right = buildSubset( items, med + 1, end, (dimension + 1) % 3, height + 1 );
      }

      if( pt->left != 0 ) {
        pt->left->parent = pt;
      }

      if( pt->right != 0 ) {
        pt->right->parent = pt;
      }

      // update size
      isize++;
      return pt;
      
    }

    /** Find the node in the subtree with that is closest to the given point p
     *  Parameters: node the root of the subtree being searched
     *              queryPoint the point whose nearest neighbor should be found
     *              smallestSquareDistance the smallest distance value found in
     *                                     the tree so far which can be updated
     *              closestPoint the node corresponding to the current closest
     *                           node in the tree which can be udpated
     *              dimension flags whether the node parameter splits remaining
     *                        nodes in its subtree by the x or y dimension
     *                        (has the value of either 0 or 1)
     *  Return: a BSTNode object that represents the point in the subtree
     *          closest to the given point p (including the root node)
     */
    // TODO

    void findNNHelper(BSTNode<Point> *node, const Point &queryPoint,
                      double *smallestSquareDistance,
                      BSTNode<Point> **closestPoint,
                      unsigned int dimension) const {

      /*
       * STEP 1
       */

      if( node == 0 ) {  // if the node is null, do nothing 
        return;
      }
      
      bool wentLeft = false;
      if( dimension == 0 ) { // in x direction
        if( xLessThan(queryPoint, node->data ) ) {
          wentLeft = true;

          findNNHelper( node->left, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        } else {
          wentLeft = false;
          findNNHelper( node->right, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        }
      } else if( dimension == 1 ) { // in y direction
        if( yLessThan(queryPoint, node->data ) ) {
          wentLeft = true;

          findNNHelper( node->left, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        } else {
          wentLeft = false;
          findNNHelper( node->right, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        }
      } else { // in z direction
        if( zLessThan(queryPoint, node->data ) ) {
          wentLeft = true;

          findNNHelper( node->left, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        } else {
          wentLeft = false;
          findNNHelper( node->right, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        }
      }

      /* 
       * STEP 2
       */

      // update if necessary
      double distance = Point::squareDistance(node->data, queryPoint);
      if( distance < *smallestSquareDistance) {
        *smallestSquareDistance = distance;
        *closestPoint = node;
      }

      /*
       * STEP 3
       */

      // find dimensional distance
      double dimenDist;
      if( dimension == 0 ) { // in x direction
        dimenDist = 
          (node->data.x - queryPoint.x) * (node->data.x - queryPoint.x);
      } else if( dimension == 1 ){ // in y direction
        dimenDist = 
          (node->data.y - queryPoint.y) * (node->data.y - queryPoint.y);
      } else { // in z direction
        dimenDist = 
          (node->data.z - queryPoint.z) * (node->data.z - queryPoint.z);
      }

      if( dimenDist < *smallestSquareDistance ) {
        if( wentLeft ) { // go down right
          findNNHelper( node->right, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        } else { // go down left
          findNNHelper( node->left, queryPoint, smallestSquareDistance, 
                 closestPoint, (dimension + 1) % 3);
        }
        
      }

   }
};

#endif  // KDT_HPP
