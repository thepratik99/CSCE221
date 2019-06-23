/* 
 *  main function
 */

#include "BTree.h"
#include <iostream>
#include <fstream>

using namespace std;

BTree* read_file(string file_name)
{
  BTree* tree = new BTree();
  /*
    open the file and use the input operator (operator>>)
    to construct a new tree
  */

  ifstream inFile;

  inFile.open(file_name);

  if(!inFile)
  {
  	cerr << "There is no such a file named " << file_name << endl;
  	return NULL;
  }

  inFile >> tree;
    
  return tree;
}

void write_file(string file_name, BTree* bt)
{
	string finalName = file_name + ".txt";
	ofstream outFile;
	outFile.open(finalName);

	outFile << "Total Number of Nodes is " << bt->get_size() << "." << endl << endl;

	outFile << "Inorder traversal of tree is as below." << endl;

	bt->inorder(outFile, bt->get_root());

	outFile << endl << endl;

	outFile << "Level Order traversal of the tree is as below." << endl;

	bt->print_level_by_level(outFile);

	outFile << endl;

	outFile << "Total search cost for this tree is " << bt->calculateTotalCost() << endl;
	outFile << "Average search cost for this tree is " << ((double)bt->calculateTotalCost()/bt->get_size()) << endl;
}


int main()
{
  /*
    write main function
  */
	string fileName;

	//reading the file name from the user
	cout << "\nEnter the name of the file: " ;
	cin >> fileName;
	cout << endl;

	if(read_file(fileName) == NULL)
		return -1;

	//test for read_file and insert function
	//as insert is called inside read_file
	BTree* bt = read_file(fileName);

	cout << "Total search cost for this tree is " << bt->calculateTotalCost() << endl;
	cout << "Average search cost for this tree is " << ((double)bt->calculateTotalCost()/bt->get_size()) << endl;
	/*
	//test for inorder function
	cout << "Printing the tree inorder." << endl;
	bt->inorder(cout, bt->get_root());

	cout << endl << endl;

	//testing for search function
	cout << "Search for integer 14 in the given node." << endl;
	if(bt->search(14) == NULL)
		cout << "Result: Did not find" << endl << endl;

	else
		cout << "Result: Found it" << endl << endl;

	//testing for get_size() function
	cout << "Size of the tree is " << bt->get_size() << "." << endl << endl;

	//testing for level print function
	cout << "Level Order printing of the tree is as below." << endl;
	bt->print_level_by_level(cout);
	cout << endl;

	//writing details in a file.
	write_file(fileName, bt);

	//testing for copy constuctor
	BTree* bt2 = new BTree(bt);

	bt->inorder(cout, bt2->get_root());
	cout << endl;

	//testing for copy assignment
	BTree* bt3 = new BTree();

	bt3 = bt;

	bt->inorder(cout, bt3->get_root());
	cout << endl;*/

	return 0;
}

