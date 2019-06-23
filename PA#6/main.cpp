#include <iostream>
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <iterator>
#include <stack>
#include <queue>

bool search(int, std::stack<int>&, std::vector<std::list<int> >&);
void printGraph(std::stack<int>);

using namespace std;

int main(int argc, char const *argv[])
{
	vector<list<int> > graph;

	list<int> temp;
	graph.push_back(temp);

	ifstream inFile;
	inFile.open(argv[1]);

	if(!inFile)
	{
		cout << "The file does not exist." << endl;
		return -1;
	}

	string line;
	int var1;
	int var2;

	string missNowuseLater;
	getline(inFile, missNowuseLater);

	int numberOfVertexes;
	int numberOfEdges;

	for(int i = 0; i < missNowuseLater.length(); ++i)
	{
		if(missNowuseLater.at(i) == 32)
		{
			numberOfVertexes = stoi(missNowuseLater.substr(0, i));
			numberOfEdges = stoi(missNowuseLater.substr((i+1), (missNowuseLater.length()-i-1)));
			break;
		}
	}

	while(getline(inFile, line))
	{
		for(int i = 0; i < line.length(); ++i)
		{
			if(line.at(i) == 32)
			{
				var1 = stoi(line.substr(0, i));
				var2 = stoi(line.substr((i+1), (line.length() - i - 1)));
				break;
			}
		}

		if(var1 >= graph.size() || var2 >= graph.size())
		{
			int max;

			if(var1 >= var2)
				max = var1;
			else 
				max = var2;

			for(int i = graph.size(); i <= max; ++i)
			{
				list<int> temp;
				graph.push_back(temp);
			}
		}

		graph.at(var1).push_back(var2);
		graph.at(var2).push_back(var1);
	}

	for(int i = 1; i < graph.size(); ++i)
	{
		if(graph.at(i).size() == 0)
			continue;

		graph.at(i).sort();

		list<int>::iterator it;
		
		cout << i;
		for(it = graph.at(i).begin(); it != graph.at(i).end(); ++it)
		{
			cout << " -> " << *it ;
		}
		cout << endl;
	}

	cout << endl;

	//graph now has a list implementation

	stack<int> storage;

	bool printed = false;

	for(int i = 1; i < graph.size(); ++i)
	{
		if(search(i, storage, graph))
		{
			if(storage.size() == numberOfEdges + 1)
			{
				printGraph(storage);
				printed = true;
				break;
			}
		}
	}

	if(!printed)
		cout << "There isn't a solution to the given graph." << endl;

	return 0;
}

bool search(int u, stack<int>& storage, vector<list<int> >& graph)
{
	storage.push(u);

	bool testSizeZero = true;

	for(int i = 1; i < graph.size(); ++i)
	{
		if(graph.at(u).size() > 0)
		{
			testSizeZero = false;
			break;
		}
	}

	if(testSizeZero)
		return true;
	else
	{
		for(list<int>::iterator it = graph.at(u).begin(); it != graph.at(u).end(); ++it)
		{
			int temp = *it;
			graph.at(u).remove(temp);
			graph.at(temp).remove(u);

			if(search(temp, storage, graph))
				return true;
			else
			{
				graph.at(u).push_back(temp);
				graph.at(temp).push_back(u);
			}
		}

		storage.pop();
		return false;
	}
}

void printGraph(stack<int> storage)
{
	stack<int> printThis;

	for(int i = 0; i < storage.size(); ++i)
	{
		int temp = storage.top();
		storage.pop();
		printThis.push(temp);
		--i;
	}

	for(int i = 0; i < printThis.size() - 1; ++i)
	{
		int temp = printThis.top();
		printThis.pop();
		cout << temp << " -> ";
		--i;
	}

	int temp = printThis.top();
	printThis.pop();
	cout << temp << endl;
}