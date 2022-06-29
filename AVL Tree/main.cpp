#include <iostream>
#include "AVLTree.h"

using namespace std;

int menu() {
  int choice = 0;
  cout << endl << "Enter Choice (1-3): ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Print" << endl
    << "3. Quit" << endl;
  cin >> choice;

  
  cin.clear();
  cin.ignore(256, '\n');
  return choice;
}

int main( ) {

  AVLTree tree;

  int choice = menu();

  string entry;

  while (choice != 3) {

    if (choice == 1) {
      cout << "Enter string to insert: ";
      getline(cin, entry);
      cout << endl;

      tree.insert(entry);

    } else if (choice == 2) {
      tree.printBalanceFactors();

    } 
 
    choice = menu();
  }

  return 0;
}
