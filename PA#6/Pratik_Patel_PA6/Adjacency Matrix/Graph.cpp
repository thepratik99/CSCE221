#include <vector>
#include <stack>
#include <fstream>
#include "Graph.h"
#include <string>
#include <iostream>

using namespace std;

//implements a graph usind an adjacency matrix
void Graph::makeGraph(ifstream& inFile)
{
	//getting number of vertices and edges
	string firstLine;
	getline(inFile, firstLine);

	for(int i = 0; i < firstLine.length(); ++i)
	{
		if(firstLine.at(i) == 32)
		{
			numberOfVertices = stoi(firstLine.substr(0, i));
			numberOfEdges = stoi(firstLine.substr((i+1), (firstLine.length()-i-1)));
			break;
		}
	}

	//increase the size of the matrix according to the number of vertices.
	for(int i = 0; i <= numberOfVertices; ++i)
	{
		vector<int> temp(numberOfVertices+1);
		graph.push_back(temp);
	}

	//pre populate the matrix with zeros and row-column indecies.
	for(int i = 0; i < graph.size(); ++i)
	{
		for(int j = 0; j < graph.at(i).size(); ++j)
		{
			if(i == 0)
				graph.at(i).at(j) = j;
			else if(j == 0)
				graph.at(i).at(j) = i;
			else
				graph.at(i).at(j) = 0;
		}
	}

	//get all the other lines in the file and update the matrix accordingly.
	string line;
	int var1;
	int var2;

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

		graph.at(var1).at(var2) = 1;
		graph.at(var2).at(var1) = 1;
	}
}

//prints a graph
void Graph::printGraph()
{
	for(int i = 0; i < graph.size(); ++i)
	{
		for(int j = 0; j < graph.at(i).size(); ++j)
		{
			cout << graph.at(i).at(j) << " " ;
		}
		cout << endl;
	}
	cout << endl;
}

//prints the stack
void Graph::printSolution()
{
	//to get the stack in the first order
	stack<int> printThis;

	//reverse the storage stack and put in the newly created stack
	for(int i = 0; i < storage.size(); ++i)
	{
		int temp = storage.top();
		storage.pop();
		printThis.push(temp);
		--i;
	}

	//print the new stack
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

bool Graph::searchSolution(int u)
{
	//push the current vertex on the stack
	storage.push(u);

	//check if there is no vertices in the matrix
	bool testSizeZero = true;
	for(int j = 1; j < graph.size(); ++j)
	{
		for(int i = 1; i < graph.at(u).size(); ++i)
		{
			if(graph.at(j).at(i) == 1)
			{
				testSizeZero = false;
				break;
			}
		}
	}

	//if there are none return true
	if(testSizeZero)
		return true;
	else
	{
		//check every adjacent vertex of the current vertex
		for(int i = 1; i < graph.at(u).size(); ++i)
		{
			//delete the edge
			int temp = graph.at(u).at(i);
			if(temp == 1)
			{
				graph.at(u).at(i) = 0;
				graph.at(i).at(u) = 0;

				//recursive call with the adjacent vertex
				//if true, then recursion will occur until matrix is empty
				//else, it will restore the deleted edge will try the next adjacent vertex
				if(searchSolution(i))
					return true;
				else
				{
					graph.at(u).at(i) = 1;
					graph.at(i).at(u) = 1;
				}
			}
		}
		
		//if all the adjacent vertices fails, then pop the pushes value from stack and return false
		storage.pop();
		return false;
	}
}

//find if a solution exists or not
void Graph::isThereASolution()
{
	bool printed = false;

	//traverse through all vertices of the graph
	for(int i = 1; i < graph.size(); ++i)
	{
		if(searchSolution(i))
		{
			//if there is a solution check the size of the stack
			if(storage.size() == numberOfEdges + 1)
			{
				printSolution();
				printed = true;
				break;
			}
		}
	}

	//else print the following
	if(!printed)
		cout << "There isn't a solution to the given graph." << endl;
}