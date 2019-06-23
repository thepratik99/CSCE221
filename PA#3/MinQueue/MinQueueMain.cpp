#include "MinQueue.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	//initialize a MinQueue of integer type
	MinQueue<int> minq1;

	//test case for isEmpty() function
	cout << "\nThe queue is right now empty." << endl;
	cout << "Result of the isEmpty() function: " << boolalpha << minq1.isEmpty() << endl;

	//Add some elements to the queue
	minq1.enqueue(2);
	minq1.enqueue(5);
	minq1.enqueue(3);
	minq1.enqueue(-9);
	minq1.enqueue(4);
	minq1.enqueue(1);

	//test case for size() function
	cout << "\nThe queue after inserting 6 elements looks like following" << endl;
	cout << minq1 << endl;
	cout << "The Length of the queue is: " ;
	cout << minq1.size() << endl;

	//test case for min() function
	cout << "The least number in the queue is: " ;
	cout << minq1.min() << endl;

	//test case for dequeue() function
	cout << "Dequeue the least element " ;
	cout << minq1.dequeue() << "." << endl;

	cout << "\nThe queue now looks like following" << endl;
	cout << minq1 << endl;
}