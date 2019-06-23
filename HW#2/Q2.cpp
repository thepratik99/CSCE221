#include <iostream>

using namespace std;

int countNodes(Node n);

int main()
{
	return 0;
}

int countNodes(Node n)
{
	if(n == nullptr)
		return 0;
	else if(n != nullptr)
		return 1 + countNodes(n.next);
}