/*
 * Binary Tree - header file
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
using namespace std;

struct Node
{
  int value;
  Node* left;
  Node* right;
  int search_cost;

  // constructor
  Node(int val = 0, Node* l = NULL, Node* r = NULL)
    : value(val), left(l), right(r), search_cost(0) {}

  // query
  bool is_leaf() { return (left == nullptr && right == nullptr); }
};

class BTree
{
private:
  int size;
  Node* root;

public:
  // constructors
  BTree() : root(nullptr), size(0) {} // default constructor
  BTree(BTree* other); // copy constructor
  BTree(BTree&& other); // move constructor
  // assignment and move assignment operator
  BTree& operator=(BTree* other);
  BTree& operator=(BTree&& other);

  int get_size() { return size; }
  Node* get_root() { return root; }
  // should not be used unless it is really necessary
  void set_root(Node* node) { root = node; }
  Node* insert(int obj);
  Node* search(int obj);
  void update_search_cost(Node*, int);
  void inorder(ostream&, Node*);
  void inorderCost(Node*, int&);
  int calculateTotalCost();
  void print_level_by_level(ostream& out);

  void copyTree(Node *& thisRoot, Node *& sourceRoot);
  void DestroyRecursive(Node* node);

};

ostream& operator<<(ostream& out, BTree& tree);
ostream& operator<<(ostream& out, Node* node);

istream& operator>>(istream& in, BTree* tree);

#endif
