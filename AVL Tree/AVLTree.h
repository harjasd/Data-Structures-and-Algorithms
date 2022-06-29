    #include "Node.h" 
#include <iostream> 
#include <string> 
#include <fstream> 
#include <sstream> 
#include <cstdlib>

using namespace std; 

class AVLTree { 
    private:
      Node *treeRoot;
      
    public:
      AVLTree();
      void insert(const string &); 
      int balanceFactor(Node*) const;  
      void printBalanceFactors() const;  
      void visualizeTree(const string &);  
      
    private: 
      void rotate(Node *); 
      void rotateLeft(Node *); 
      void rotateRight(Node *);  
      void insert(Node *,Node *); //added
      void printBalanceFactors(Node *) const;
      void visualizeTree(ofstream &, Node *);  
      int height(Node *) const; //added
      void height(int, int &, Node *) const;  //added to help 
      void setChild(Node *, string, Node *); //added to help
      void replaceChild(Node *, Node *,Node *); //added to help 
};
