#include <iostream>
#include "Q1.h"

using namespace std;

int main()
{
	Arithmeticprogression a1 = new Arithmeticprogression(2, 2);
	GeometricProgession g1 = new GeometricProgession(1, 2);

	cout << "The second element of (2, 2) is " << a1.getNext(2) << endl;
	cout << "The sum of first 10 elemnts is " << a1.sum(10) << endl;

	cout << "The second element of (1, 2) is " << g1.getNext(1) << endl;
	cout << "The sum of first 10 elements is " << g1.sum(10) << endl;

	return 0;
}