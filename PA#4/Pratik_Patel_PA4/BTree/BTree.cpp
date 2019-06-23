/*
 * Binary Tree - source file (functions implementation)
 */

#include "BTree.h"
#include <queue>


ostream& operator<<(ostream& out, BTree& tree)
{
  tree.print_level_by_level(out);
  return out;
}

ostream& operator<<(ostream& out, Node* node)
{
  out << node->value
      << "["
      << node->search_cost
      << "] ";
  return out;
}

istream& operator>>(istream& in, BTree* tree)
{
  /*
    take input from the in stream, and build your tree

    input will look like
    4 
    2 
    6 
    1 
    3 
    5 
    7
  */

  int temp;

  while(in >> temp)
  {
    tree->insert(temp);
  }

  return in;
}

//copy constructor
BTree::BTree(BTree* other)
{
  /*
    complete this copy constructor
    make sure when copying nodes to copy
    - value
    - left and right children
  */

  if(other->root == NULL)
    root = NULL;
  else
    copyTree(this->root, other->root);
}

//helper function for copy constructor and assignment
void BTree::copyTree(Node *& thisRoot, Node *& sourceRoot)
{
  if(sourceRoot == NULL)
  {
    thisRoot = NULL;
  }
  else
  {
    thisRoot = new Node();
    thisRoot->value = sourceRoot->value;
    thisRoot->search_cost = sourceRoot->search_cost;
    copyTree(thisRoot->left, sourceRoot->left);
    copyTree(thisRoot->right, sourceRoot->right);
  }
}

//move constructor
BTree::BTree(BTree&& other)
{
  /*
    complete this move constructor
  */

  this->root = other.root;

  other.root->value = 0;
  other.root->left = nullptr;
  other.root->right = nullptr;
  other.root->search_cost = 0;
}

//helper function for copy assignment
void BTree::DestroyRecursive(Node* node)
{
  if (node)
  {
    DestroyRecursive(node->left);
    DestroyRecursive(node->right);
    delete node;
  }
}

//copy assignment
BTree& BTree::operator=(BTree* other)
{
  if (this != other)
  {
    DestroyRecursive(this->get_root());

    if(other->root == NULL)
      root = NULL;
    else
      copyTree(this->root, other->root); 
  }
  return *this;
}

//move assignment
BTree& BTree::operator=(BTree&& other)
{
  if (this != &other)
  {
    this->root = other.root;

    other.root->value = 0;
    other.root->left = nullptr;
    other.root->right = nullptr;
    other.root->search_cost = 0;
  }
  return *this;
}

Node* BTree::insert(int obj)
{
  /*
    insert a node into the tree
    - first find where the node should go
    - then modify pointers to connect your new node 
  */

  Node* newNode = new Node(obj);
  Node* temp = get_root();

  int searchCost = 1;

  if(temp == nullptr)
  {
    root = newNode;
    root->search_cost = searchCost;
    ++size;
  }
  else
  {
    while(true)
    {
      searchCost++;
      if(obj < temp->value)
      {
        if(temp->left == nullptr)
        {
          temp->left = newNode;
          temp->left->search_cost = searchCost;
          ++size;
          break;
        }
        else
          temp = temp->left;
      }
      else
      {
        if(temp->right == nullptr)
        {
          temp->right = newNode;
          temp->right->search_cost = searchCost;
          ++size;
          break;
        }
        else
          temp = temp->right;
      }
    }
  }
  return nullptr;
}

Node* BTree::search(int obj)
{
  /*
    recursivly search down the tree to find the node that contains obj
    - if you don't find anything return nullptr
  */

  Node* temp = get_root();

  while(temp!=nullptr)
  {
    if(obj < temp->value)
      temp = temp->left;

    else if(obj > temp->value)
      temp = temp->right;

    else
      return temp;
  }
  return NULL;
}

void BTree::update_search_cost(Node* rootTemp, int depth)
{
  /*
    do a BFS of your tree and update the search cost of all nodes
  */

  rootTemp->search_cost = depth;

  int temp = depth + 1;

  if(rootTemp->left != nullptr)
    update_search_cost(rootTemp->left, temp);

  if(rootTemp->right != nullptr)
    update_search_cost(rootTemp->right, temp);
}

int BTree::calculateTotalCost()
{
  int totalCost = 0;
  inorderCost(root, totalCost);
  return totalCost;
}

void BTree::inorderCost(Node* tempNode, int& totalCost)
{
  if(tempNode == NULL)
    return;

  inorderCost(tempNode->left, totalCost);
  totalCost += tempNode->search_cost;
  inorderCost(tempNode->right, totalCost);
}

void BTree::inorder(ostream& out, Node* tempNode)
{
  /*
    print your nodes in infix order

    if our tree looks like 

    4
    2 6
    1 3 5 7

    we should get

    1 2 3 4 5 6 7 
  */

  if(tempNode == NULL)
  	return;

  inorder(out, tempNode->left);
  out << tempNode;
  inorder(out, tempNode->right);
}

void BTree::print_level_by_level(ostream& out)
{
  /*
    print the tree using a BFS 

    output should look like this if we dont have a full tree

    4
    2 6
    1 X 5 7
    X X X X X X X 9

    it will be helpfull to do this part iterativly, 
    so do the BFS with the std stack data structure.

    it may also be helpfull to put the entire tree into a vector 
    (probably google this if you dont know how to do it)
  */
  
  if(this->root == NULL)
    return ;

  queue<Node*> nodeQueue;

  int current = 1;
  int next = 0;

  nodeQueue.push(this->root);

  Node* printX = new Node(-99);

  bool check = true;

  vector<int> printValue;
  vector<int> printCost;

  while(!nodeQueue.empty())
  {
    Node* temp = nodeQueue.front();
    nodeQueue.pop();
    current--;

    if(temp)
    {
      printValue.push_back(temp->value);
      printCost.push_back(temp->search_cost);

      if(temp->left == NULL)
        nodeQueue.push(printX);
      else
      {
        check = false;
        nodeQueue.push(temp->left);
      }

      if(temp->right == NULL)
        nodeQueue.push(printX);
      else
      {
        check = false;
        nodeQueue.push(temp->right);
      }

      next += 2;
    }

    if(current == 0)
    {

      for(int i = 0; i < printValue.size(); ++i)
      {
        if(printValue.at(i) == -99)
          out << "X " ;
        else
          out << printValue.at(i) << "[" << printCost.at(i) << "] " ;
      }

      out << endl;

      if(check)
        return;

      printValue.clear();
      printCost.clear();
      check = true;

      current = next;
      next = 0;
    }
  }

  delete printX;
}