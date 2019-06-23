#include "TemplateDoublyLinkedList.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <sstream>

using namespace std;

int main () {
  // Construct a linked list with header & trailer
  cout << "Create a new list" << endl;
  TemplateDoublyLinkedList<string> dll;
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at back with value 10,20,30,..,100
  cout << "Insert 10 nodes at back with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertLast(ss.str());
  }
  cout << "list: " << dll << endl << endl;

  // Insert 10 nodes at front with value 10,20,30,..,100
  cout << "Insert 10 nodes at front with value 10,20,30,..,100" << endl;
  for (int i=10;i<=100;i+=10) {
    stringstream ss;
    ss << i;
    dll.insertFirst(ss.str());
  }
  cout << "list: " << dll << endl << endl;
  
  // Copy to a new list
  cout << "Copy to a new list" << endl;
  TemplateDoublyLinkedList<string> dll2(dll);
  cout << "list2: " << dll2 << endl << endl;
  
  // Assign to another new list
  cout << "Assign to another new list" << endl;
  TemplateDoublyLinkedList<string> dll3;
  dll3=dll;
  cout << "list3: " << dll3 << endl << endl;
  
  // Delete the last 10 nodes
  cout << "Delete the last 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeLast();
  }
  cout << "list: " << dll << endl << endl;
  
  // Delete the first 10 nodes
  cout << "Delete the first 10 nodes" << endl;
  for (int i=0;i<10;i++) {
    dll.removeFirst();
  }
  cout << "list: " << dll << endl << endl;
  
  // Check the other two lists
  cout << "Make sure the other two lists are not affected." << endl;
  //cout << "list2: " << dll2 << endl;
  cout << "list3: " << dll3 << endl;

  //test for insertAfter
  cout << "Insert after the third node(80) in list 2" << endl;
  stringstream ss;
  ss << 55;
  dll3.insertAfter(*(dll3.getFirst()->next->next), ss.str());
  cout << "list : " << dll3 << endl << endl;

  //test for insertBefore
  cout << "Insert before the third node(80) in list 2" << endl;
  stringstream ss1;
  ss1 << 45;
  dll3.insertBefore(*(dll3.getFirst()->next->next), ss1.str());
  cout << "list: " << dll3 << endl << endl;

  //test for removeAfter
  cout << "Remove after the forth node(80) in list 2" << endl;
  dll3.removeAfter(*(dll3.getFirst()->next->next->next));
  cout << "list: " << dll3 << endl << endl;

  //test for removeBefore
  cout << "Remove before the forth node(80) in list 2" << endl;
  dll3.removeBefore(*(dll3.getFirst()->next->next->next));
  cout << "list: " << dll3 << endl << endl;

  //test for length function
  cout << "Length of list2" << endl;
  int length = DoublyLinkedListLength(dll3);
  cout << "Length: " << length << endl;
  
  return 0;
}
