#include <iostream>
#include <vector>

using namespace std;

bool oddVector(vector<int> a)
{
	for(int i = 0; i < a.size(); ++i)
	{
		if(a.at(i) % 2 == 0)
			return false;
	}
	return true;
}
