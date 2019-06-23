#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stack>
#include "Graph.h"

using namespace std;

int main(int argc, char const *argv[])
{
	//open a file
	ifstream inFile;
	inFile.open(argv[1]);

	//check if the file exists or not
	if(!inFile)
	{
		cout << "The file does not exist." << endl;
		return -1;
	}

	//An instace of class Graph
	Graph g1;

	g1.makeGraph(inFile);
	g1.printGraph();
	g1.isThereASolution();

	return 0;
}