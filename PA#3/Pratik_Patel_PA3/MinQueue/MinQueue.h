#include "../TemplateDoublyLinkedList/TemplateDoublyLinkedList.h"

template<typename T>
class MinQueue
{
public:
	int size();
	T min();
	T dequeue();
	void enqueue(T x);
	bool isEmpty();
  TemplateDoublyLinkedList<T> getDLL() const {return dll;}

private:
	TemplateDoublyLinkedList<T> dll;
};

//returns the length of the queue
template<typename T>
int MinQueue<T>::size()
{
	return DoublyLinkedListLength(dll);
}

//finds the least number and removes it
template<typename T>
T MinQueue<T>::dequeue()
{
	DListNode<T> *temp = dll.getFirst();
	DListNode<T> *nodeNextToMinNode = temp->next;
	T min = temp->obj;

    while(temp != dll.getAfterLast())
    {
      if(temp->obj < min)
      {
      	min = temp->obj;
      	nodeNextToMinNode = temp->next;
      }
      temp = temp->next;
    }
	return dll.removeBefore(*nodeNextToMinNode);
}

//inserts a node at the end of the queue
template<typename T>
void MinQueue<T>::enqueue(T x)
{
	dll.insertLast(x);
}

//chekcs if the queue is empty or not
template<typename T>
bool MinQueue<T>::isEmpty()
{
	return dll.isEmpty();
}

//finds and returns the least element in the queue
template<typename T>
T MinQueue<T>::min()
{
	DListNode<T> *temp = dll.getFirst();
	T min = temp->obj;

    while(temp != dll.getAfterLast())
    {
      if(temp->obj < min)
      {
      	min = temp->obj;
      }
      temp = temp->next;
    }

    return min;
}

//prints the queue
template<typename T>
ostream& operator<<(ostream& out, const MinQueue<T>& minq)
{
  TemplateDoublyLinkedList<T> tdll = minq.getDLL();

  DListNode<T> *temp = tdll.getFirst();

  if(!tdll.isEmpty())
  {
    while(temp->next != tdll.getAfterLast())
    {
      cout << temp->obj << ", " ;
      temp = temp->next;
    }

    cout << temp->obj;
  }

  cout << endl;
  
  return out;
}