#include <cstdlib>
#include <iostream>
using namespace std;
template<typename T>
class TemplateDoublyLinkedList; // class declaration

// list node
template<typename T>
struct DListNode {
  T obj;
  DListNode<T> *prev, *next;
  DListNode(T e=0, DListNode *p = NULL, DListNode *n = NULL)
    : obj(e), prev(p), next(n) {}
};

// doubly linked list
template<typename T>
class TemplateDoublyLinkedList {
private:
  DListNode<T> header, trailer;
public:
  TemplateDoublyLinkedList() : header(T()), trailer(T()) // constructor
  { header.next = &trailer; trailer.prev = &header; }
  TemplateDoublyLinkedList(const TemplateDoublyLinkedList<T>& dll); // copy constructor
  TemplateDoublyLinkedList(TemplateDoublyLinkedList<T>&& dll); // move constructor
  ~TemplateDoublyLinkedList(); // destructor
  TemplateDoublyLinkedList<T>& operator=(const TemplateDoublyLinkedList<T>& dll); // assignment operator
  TemplateDoublyLinkedList<T>& operator=(TemplateDoublyLinkedList<T>&& dll); // move assignment operator
  // return the pointer to the first node
  DListNode<T> *getFirst() const { return header.next; } 
  // return the pointer to the trailer
  const DListNode<T> *getAfterLast() const { return &trailer; }
  // return if the list is empty
  bool isEmpty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insertFirst(T newobj); // insert to the first of the list
  T removeFirst(); // remove the first node
  void insertLast(T newobj); // insert to the last of the list
  T removeLast(); // remove the last node
  void insertAfter(DListNode<T> &p, T newobj);
  void insertBefore(DListNode<T> &p, T newobj);
  T removeAfter(DListNode<T> &p);
  T removeBefore(DListNode<T> &p);
};

// output operator
template<typename T>
ostream& operator<<(ostream& out, const TemplateDoublyLinkedList<T>& dll);
// return the list length
template<typename T>
int DoublyLinkedListLength(TemplateDoublyLinkedList<T>& dll);



// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
template<typename T>
TemplateDoublyLinkedList<T>::TemplateDoublyLinkedList(const TemplateDoublyLinkedList<T>& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DListNode<T> *temp = dll.getFirst();

  while(temp != dll.getAfterLast())
  {
    this->insertLast(temp->obj);
    temp = temp->next;
  }
}
// move constructor
template<typename T>
TemplateDoublyLinkedList<T>::TemplateDoublyLinkedList(TemplateDoublyLinkedList<T>&& dll)
{
  header = dll.header;
  trailer = dll.trailer;

  dll.header.obj = T();
  dll.header.next = nullptr;
  dll.header.prev = nullptr;
  
  dll.trailer.obj = T();
  dll.trailer.next = nullptr;
  dll.trailer.prev = nullptr;
}

// assignment operator
template<typename T>
TemplateDoublyLinkedList<T>& TemplateDoublyLinkedList<T>::operator=(const TemplateDoublyLinkedList<T>& dll)
{
  DListNode<T> *previousNode;
  DListNode<T> *temp = header.next;
  while (temp != &trailer) 
  {
    previousNode = temp;
    temp = temp->next;
    delete previousNode;
  }
  
  header.next = &trailer;
  trailer.prev = &header;

  DListNode<T> *tempNode = dll.getFirst();

  while(tempNode != dll.getAfterLast())
  {
    this->insertLast(tempNode->obj);
    tempNode = tempNode->next;
  }

  return *this;
}
// move assignment operator
template<typename T>
TemplateDoublyLinkedList<T>& TemplateDoublyLinkedList<T>::operator=(TemplateDoublyLinkedList<T>&& dll)
{
  if(this != &dll)
  {
    DListNode<T> *previousNode;
    DListNode<T> *temp = header.next;
    while (temp != &trailer) 
    {
      previousNode = temp;
      temp = temp->next;
      delete previousNode;
    }
  
    header.next = &trailer;
    trailer.prev = &header;

    header = dll.header;
    trailer = dll.trailer;

    dll.header.obj = 0;
    dll.header.next = nullptr;
    dll.header.prev = nullptr;
  
    dll.trailer.obj = 0;
    dll.trailer.next = nullptr;
    dll.trailer.prev = nullptr;
  }

  return *this;
}

// insert the new object as the first one
template<typename T>
void TemplateDoublyLinkedList<T>::insertFirst(T newobj)
{ 
    DListNode<T> *toBeInserted = new DListNode<T>(newobj, &header, header.next);
    header.next->prev = toBeInserted;
    header.next = toBeInserted;
}

// insert the new object as the last one
template<typename T>
void TemplateDoublyLinkedList<T>::insertLast(T newobj)
{
    DListNode<T> *toBeInserted = new DListNode<T>(newobj, trailer.prev, &trailer);
    trailer.prev->next = toBeInserted;
    trailer.prev = toBeInserted;
}

// remove the first object from the list
template<typename T>
T TemplateDoublyLinkedList<T>::removeFirst()
{ 
  if (isEmpty())
      throw EmptyDLinkedListException("Empty List");

    DListNode<T> *temp = header.next;
    temp->next->prev = &header;
    header.next = temp->next;
    T elem = temp->obj;
    delete temp;

    return elem;
}

// remove the last object from the list
template<typename T>
T TemplateDoublyLinkedList<T>::removeLast()
{
  if (isEmpty())
      throw EmptyDLinkedListException("Empty List");
    
    DListNode<T> *temp = trailer.prev;
    temp->prev->next = &trailer;
    trailer.prev = temp->prev;
    T elem = temp->obj;
    delete temp;

    return elem;
}

// destructor
template<typename T>
TemplateDoublyLinkedList<T>::~TemplateDoublyLinkedList()
{
    DListNode<T> *previousNode;
    DListNode<T> *temp = header.next;
    while (temp != &trailer) 
    {
      previousNode = temp;
      temp = temp->next;
      delete previousNode;
    }
  
    header.next = &trailer;
    trailer.prev = &header;
}

// return the first object
template<typename T>
T TemplateDoublyLinkedList<T>::first() const
{
  if (isEmpty())
      throw EmptyDLinkedListException("Empty List");

    return header.obj;
}

// return the last object
template<typename T>
T TemplateDoublyLinkedList<T>::last() const
{
  if (isEmpty())
      throw EmptyDLinkedListException("Empty List");

    return trailer.obj;
}

// insert the new object after the node p
template<typename T>
void TemplateDoublyLinkedList<T>::insertAfter(DListNode<T> &p, T newobj)
{
    DListNode<T> *toBeInserted = new DListNode<T>(newobj);

    p.next->prev = toBeInserted;
    toBeInserted->next = p.next;

    p.next = toBeInserted;
    toBeInserted->prev = &p;
}

// insert the new object before the node p
template<typename T>
void TemplateDoublyLinkedList<T>::insertBefore(DListNode<T> &p, T newobj)
{
    DListNode<T> *toBeInserted = new DListNode<T>(newobj);

    p.prev->next = toBeInserted;
    toBeInserted->prev = p.prev;

    p.prev = toBeInserted;
    toBeInserted->next = &p;
}

// remove the node after the node p
template<typename T>
T TemplateDoublyLinkedList<T>::removeAfter(DListNode<T> &p)
{
    DListNode<T> *toBeDeleted = p.next;

    p.next = toBeDeleted->next;
    toBeDeleted->next->prev = &p;

    T elem = toBeDeleted->obj;
    delete toBeDeleted;

    return elem;
}

// remove the node before the node p
template<typename T>
T TemplateDoublyLinkedList<T>::removeBefore(DListNode<T> &p)
{
    DListNode<T> *toBeDeleted = p.prev;

    p.prev = toBeDeleted->prev;
    toBeDeleted->prev->next = &p;

    T elem = toBeDeleted->obj;
    delete toBeDeleted;

    return elem;
}

// return the list length
template<typename T>
int DoublyLinkedListLength(TemplateDoublyLinkedList<T>& dll)
{
    if(dll.isEmpty())
      return 0;

    int length = 0;

    DListNode<T> *temp = dll.getFirst();

    while(temp != dll.getAfterLast())
    {
      length++;
      temp = temp->next;
    }

    return (length);
}

// output operator
template<typename T>
ostream& operator<<(ostream& out, const TemplateDoublyLinkedList<T>& dll)
{
  DListNode<T> *temp = dll.getFirst();

  if(!dll.isEmpty())
  {
    while(temp->next != dll.getAfterLast())
    {
      cout << temp->obj << ", " ;
      temp = temp->next;
    }

    cout << temp->obj;
  }

  cout << endl;
  
  return out;
}
