#include <vector>

using namespace std;

vector<int> multiplyVectors(vector<int> a, vector<int> b)
{
	vector<int> c;

	if(a.size() == b.size())
	{
		for(int i = 0, i < a.size(); ++i)
			c.push_back(a.at(i) * b.at(i));
	}
	else
		cout << "The vectors passed in this function are not of same size." << endl;

	return c;
}