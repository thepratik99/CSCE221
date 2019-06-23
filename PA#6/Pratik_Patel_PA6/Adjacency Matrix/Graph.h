#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <stack>
#include <fstream>

class Graph
{
private:
	std::vector<std::vector<int> > graph;
	std::stack<int> storage;
	int numberOfVertices;
	int numberOfEdges;
public:
	void makeGraph(std::ifstream&);
	void printGraph();
	void printSolution();
	bool searchSolution(int);
	void isThereASolution();
};

#endif