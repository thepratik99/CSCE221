#include "DoublyLinkedList.h"
#include <stdexcept>

// extend range_error from <stdexcept>
struct EmptyDLinkedListException : std::range_error {
  explicit EmptyDLinkedListException(char const* msg=NULL): range_error(msg) {}
};

// copy constructor
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& dll)
{
  // Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DListNode *temp = dll.getFirst();

  while(temp != dll.getAfterLast())
  {
  	this->insertLast(temp->obj);
  	temp = temp->next;
  }
}
// move constructor
DoublyLinkedList::DoublyLinkedList(DoublyLinkedList&& dll)
{
  header = dll.header;
  trailer = dll.trailer;

  dll.header.obj = 0;
  dll.header.next = nullptr;
  dll.header.prev = nullptr;
  
  dll.trailer.obj = 0;
  dll.trailer.next = nullptr;
  dll.trailer.prev = nullptr;
}

// assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& dll)
{
  DListNode *previousNode;
  DListNode *temp = header.next;
  while (temp != &trailer) 
  {
   	previousNode = temp;
   	temp = temp->next;
   	delete previousNode;
  }
  
  header.next = &trailer;
  trailer.prev = &header;

  DListNode *tempNode = dll.getFirst();

  while(tempNode != dll.getAfterLast())
  {
  	this->insertLast(tempNode->obj);
  	tempNode = tempNode->next;
  }

  return *this;
}
// move assignment operator
DoublyLinkedList& DoublyLinkedList::operator=(DoublyLinkedList&& dll)
{
  if(this != &dll)
  {
  	DListNode *previousNode;
  	DListNode *temp = header.next;
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
void DoublyLinkedList::insertFirst(int newobj)
{ 
    DListNode *toBeInserted = new DListNode(newobj, &header, header.next);
    header.next->prev = toBeInserted;
    header.next = toBeInserted;
}

// insert the new object as the last one
void DoublyLinkedList::insertLast(int newobj)
{
    DListNode *toBeInserted = new DListNode(newobj, trailer.prev, &trailer);
    trailer.prev->next = toBeInserted;
    trailer.prev = toBeInserted;
}

// remove the first object from the list
int DoublyLinkedList::removeFirst()
{ 
	if (isEmpty())
	    throw EmptyDLinkedListException("Empty List");

    DListNode *temp = header.next;
    temp->next->prev = &header;
    header.next = temp->next;
    int elem = temp->obj;
    delete temp;

    return elem;
}

// remove the last object from the list
int DoublyLinkedList::removeLast()
{
	if (isEmpty())
	    throw EmptyDLinkedListException("Empty List");
    
    DListNode *temp = trailer.prev;
    temp->prev->next = &trailer;
    trailer.prev = temp->prev;
    int elem = temp->obj;
    delete temp;

    return elem;
}

// destructor
DoublyLinkedList::~DoublyLinkedList()
{
    DListNode *previousNode;
    DListNode *temp = header.next;
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
int DoublyLinkedList::first() const
{
	if (isEmpty())
	    throw EmptyDLinkedListException("Empty List");

    return header.obj;
}

// return the last object
int DoublyLinkedList::last() const
{
	if (isEmpty())
	    throw EmptyDLinkedListException("Empty List");

    return trailer.obj;
}

// insert the new object after the node p
void DoublyLinkedList::insertAfter(DListNode &p, int newobj)
{
    DListNode *toBeInserted = new DListNode(newobj);

    p.next->prev = toBeInserted;
    toBeInserted->next = p.next;

    p.next = toBeInserted;
    toBeInserted->prev = &p;
}

// insert the new object before the node p
void DoublyLinkedList::insertBefore(DListNode &p, int newobj)
{
    DListNode *toBeInserted = new DListNode(newobj);

    p.prev->next = toBeInserted;
    toBeInserted->prev = p.prev;

    p.prev = toBeInserted;
    toBeInserted->next = &p;
}

// remove the node after the node p
int DoublyLinkedList::removeAfter(DListNode &p)
{
    DListNode *toBeDeleted = p.next;

    p.next = toBeDeleted->next;
    toBeDeleted->next->prev = &p;

    int elem = toBeDeleted->obj;
    delete toBeDeleted;

  	return elem;
}

// remove the node before the node p
int DoublyLinkedList::removeBefore(DListNode &p)
{
    DListNode *toBeDeleted = p.prev;

    p.prev = toBeDeleted->prev;
    toBeDeleted->prev->next = &p;

    int elem = toBeDeleted->obj;
    delete toBeDeleted;

  	return elem;
}

// return the list length
int DoublyLinkedListLength(DoublyLinkedList& dll)
{
    if(dll.isEmpty())
    	return 0;

    int length = 0;

    DListNode *temp = dll.getFirst();

    while(temp != dll.getAfterLast())
    {
    	length++;
    	temp = temp->next;
    }

    return (length);
}

int DoublyLinkedList::countNodes(DListNode& n)
{
	if(n.next == nullptr)
		return 0;
	else if(n.next != nullptr)
		return 1 + countNodes(*(n.next));
}

// output operator
ostream& operator<<(ostream& out, const DoublyLinkedList& dll)
{
  DListNode *temp = dll.getFirst();

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
