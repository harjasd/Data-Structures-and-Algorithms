#include "AVLTree.h" 

using namespace std;

AVLTree::AVLTree() {
    treeRoot = 0; //set the root to 0
}

void AVLTree::insert(const string &insertStr) {
    Node *newNode = new Node(insertStr); // declare a new node and inserts the new node into the tree. 
    insert(treeRoot,newNode);
} 

void AVLTree::insert(Node *curr, Node *newNode) { //helper for the previous insert function
   if (!treeRoot) { // if the root of the tree causes an error then the newNode is declared and the parent is 0
      treeRoot = newNode;  
      treeRoot->parent = 0;
      return;
   }
   curr = treeRoot;
   
    while (curr) {  //while loop to traverse through the data until the newNode not equal to the current data. (point to the next value)
      if (newNode->data == curr->data) {
          int count;
          curr->count = count++; 
          curr = 0; //reset the current to 0
      } 
      else if ((newNode->data) < (curr->data)) { // if newnodes next val is less than the currents next val enter the loop
         if (curr->left == 0) { 
            curr->left = newNode;  // if the previous value of the current in the tree is equal to 0, it is replaced with a newNode
            
             
            newNode->parent = curr;  // the newnodes parent becomes equal to the current to keep the left side balanced 
            curr = 0; // current is reset to 0
         }
         else
            curr = curr->left; // if it isnt equal to 0, the program continues 
      }
      else {
         if (curr->right == 0) { // same thing as previous but it is for the right subset of the tree.
            curr->right = newNode;
            
             
            newNode->parent = curr;
            curr = 0;
         }
         else
            curr = curr->right;
      }
   }

  newNode = newNode->parent;
  
    
while (newNode) { //rotates the newnode until the newnode is assigned to the parent.(keeps the parent updated)
      rotate(newNode); 
      newNode = newNode->parent; 
      
  }
}
void AVLTree::printBalanceFactors() const { //print function
    printBalanceFactors(treeRoot); 
    cout << endl;
} 

void AVLTree::printBalanceFactors(Node *curr) const {
    if (curr) {
        printBalanceFactors(curr->left); 
        cout << curr->data << "(" << balanceFactor(curr) << "), "; 
        printBalanceFactors(curr->right); 
    }
}

int AVLTree::balanceFactor(Node *curr) const { //returns the balance facor by subtracting the left from the right of the tree
    return height(curr->left) - height(curr->right);
}

int AVLTree::height(Node *curr) const {  //added help to find the height 
    if (curr){
        int finalHeight = 0; 
        height(0,finalHeight,curr); 
        return finalHeight - 1;
    }
    return -1;
} 

void AVLTree::height(int heightCounter, int &finalHeight, Node *curr) const {
    if(curr) {
        heightCounter++; 
        if(heightCounter > finalHeight){
            finalHeight = heightCounter;
        }
        //recursively traverse tree to find the height of each subset
        height(heightCounter,finalHeight,curr->left);
        height(heightCounter,finalHeight,curr->right); 
    }
}

void AVLTree::rotate(Node *curr) { //using 2,-2,1,-1 as four unbalanced cases
    if(balanceFactor(curr) == 2) {
        if(balanceFactor(curr->left) == -1) {
            rotateLeft(curr->left);
        } 
        rotateRight(curr);
    }
    else if(balanceFactor(curr) == -2) {
        if(balanceFactor(curr->right) == 1) { 
            rotateRight(curr->right); 
        } 
        rotateLeft(curr);
    }
}

void AVLTree::rotateRight(Node *curr) { //rotates the node to the right if the curr->parent argument is valid. the child gets replaced with the curr.
    Node *tempVal = curr->left->right;
    if(curr->parent) {
        replaceChild(curr->parent,curr,curr->left);
    } 
    else {
        treeRoot = curr->left; 
        treeRoot->parent = 0;
    }
    setChild(curr->left,"right",curr); //sets the child and balances the tree
    setChild(curr,"left",temp);
}  

void AVLTree::rotateLeft(Node *curr) { //same as above function but rotates the n odes to the left
    Node *tempVal = curr->right->left;
    if(curr->parent) { 
        replaceChild(curr->parent,curr,curr->right);
    } 
    else {
        treeRoot = curr->right; 
        treeRoot->parent = 0;
    }
    setChild(curr->right,"left",curr); 
    setChild(curr,"right",temp);
} 

void AVLTree::setChild(Node *parent, string referenceChild, Node *currChild) { //helper function that sets the child to the correct spot on the tree
    if(referenceChild == "left") {
        parent->left = currChild;
    } 
    else {
        parent->right = currChild;
    } 
    if(currChild) {
        currChild->parent = parent;
    }
}

void AVLTree::replaceChild(Node *parent, Node *curr,Node *newChild) { //helper to replaced the child 
    if(parent->left == curr) {
        setChild(parent,"left",newChild); 
    } 
    else if(parent->right == curr) {
        setChild(parent,"right",newChild);
    }
}

void AVLTree::visualizeTree(const string &outputFilename){
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error"<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,treeRoot);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream & outFS, Node *n){
    if(n){
        if(n->left){
            visualizeTree(outFS,n->left);
            outFS<<n->data <<" -> " <<n->left->data<<";"<<endl;    
        }

        if(n->right){
            visualizeTree(outFS,n->right);
            outFS<<n->data <<" -> " <<n->right->data<<";"<<endl;    
        }
    }
}

