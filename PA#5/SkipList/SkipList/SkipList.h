//
//  SkipList.h
//  SkipList
//
//  Created by Pratik Patel on 4/13/19.
//  Copyright © 2019 TAMU. All rights reserved.
//

#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <list>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;

struct Node
{
    int value;
    list<Node>::iterator down;
    
    Node(int value, list<Node>::iterator down)
    {
        this->value = value;
        this->down = down;
    }
};

class SkipList
{
    
private:
    vector<list<Node> > skipLists;
public:
    int totalNodes = 0;
    int removeComparisions = 0;
    int searchComparisions =0;
    int insertComparisions = 0;
    SkipList();
    void printSkipList(ofstream&);
    void insert(int);
    list<Node>::iterator search(int, ofstream&);
    void remove(int, ofstream&);
};

#endif
