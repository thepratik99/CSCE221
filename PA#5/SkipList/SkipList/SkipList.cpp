//
//  SkipList.cpp
//  SkipList
//
//  Created by Pratik Patel on 4/13/19.
//  Copyright © 2019 TAMU. All rights reserved.
//

#include "SkipList.h"
#include <list>
#include <iterator>
#include <vector>
#include <limits>
#include <ctime>
#include <iostream>

using namespace std;

SkipList::SkipList()
{
    list<Node> temp;
    skipLists.push_back(temp);
    skipLists.at(0).push_back(Node(INT_MIN, skipLists.at(0).end()));
    skipLists.at(0).push_back(Node(INT_MAX, skipLists.at(0).end()));
}

void SkipList::printSkipList(ofstream& outFile)
{
    //cout<<"outside first loop"<<endl;
    for(int i = (skipLists.size() - 1); i >= 0; --i)
    {
        //cout<<"first four loop"<<endl;
        for(list<Node>::iterator it = skipLists.at(i).begin(); it != skipLists.at(i).end(); ++it)
        {
            if(it->value == INT_MIN)
                outFile << "-infinity " ;
            else if(it->value == INT_MAX)
                outFile << "infinity" << endl;
            else
                outFile << it->value << " ";
        }
    }
}

void SkipList::insert(int insertValue)
{
    int numberOfTails = 0;
    
    while(rand() % 2 == 1)
    {
        numberOfTails++;
    }
    
    int insertLevel = numberOfTails + 1;
    
    int tempIndex = skipLists.size();
    
    if(insertLevel >= tempIndex)
    {
        for(tempIndex = skipLists.size(); tempIndex < insertLevel + 1; ++tempIndex)
        {
            list<Node> temp;
            skipLists.push_back(temp);
            skipLists.at(tempIndex).push_back(Node(INT_MIN, skipLists.at(tempIndex-1).begin()));
            skipLists.at(tempIndex).push_back(Node(INT_MAX, --skipLists.at(tempIndex-1).end()));
        }
    }
    
    int currLevel = skipLists.size() - 1;
    
    list<Node>::iterator it = skipLists.at(skipLists.size() - 1).begin();
    list<Node>::iterator temp = skipLists.at(skipLists.size() - 1).end();
    
    while(currLevel >= 0)
    {
        if(currLevel <= (insertLevel - 1))
        {
            if(insertValue > it->value)
            {
                ++it;
                ++insertComparisions;
            }
            else if(insertValue < it->value)
            {
                skipLists.at(currLevel).insert(it, Node(insertValue, skipLists.at(0).end()));
                --it;
                temp->down = it;
                temp = it;
                --it;
                it = it->down;
                --currLevel;
                ++insertComparisions;
                ++totalNodes;
            }
        }
        else
        {
            if(insertValue > it->value)
            {
                ++it;
                ++insertComparisions;
            }
            else if(insertValue < it->value)
            {
                --it;
                it = it->down;
                --currLevel;
                ++insertComparisions;
            }
        }
    }
}

list<Node>::iterator SkipList::search(int searchValue, ofstream& outFile)
{
    list<Node>::iterator it = skipLists.at(skipLists.size() - 1).begin();
    
    bool found = false;
    int currLevel = skipLists.size() - 1;
    
    while(!found && currLevel >= 0)
    {
        if(searchValue > it->value)
        {
            ++it;
            ++searchComparisions;
        }
        
        else if(searchValue < it->value)
        {
            --it;
            it = it->down;
            --currLevel;
            ++searchComparisions;
        }
        
        else if(it->value == searchValue)
        {
            outFile << "Found " << it->value << endl;
            found = true;
            ++searchComparisions;
        }
    }
    
    if(!found)
    {
        outFile << "Did not find " << searchValue << endl;
        return skipLists.at(0).end();
    }
    
    return it;
}

void SkipList::remove(int removeValue, ofstream& outFile)
{
    
    list<Node>::iterator it = skipLists.at(skipLists.size() - 1).begin();
    
    bool found = false;
    int currLevel = skipLists.size() - 1;
    
    while(!found && currLevel >= 0)
    {
        if(removeValue > it->value)
        {
            ++it;
            ++removeComparisions;
        }
        
        else if(removeValue < it->value)
        {
            --it;
            it = it->down;
            --currLevel;
            ++removeComparisions;
        }
        
        else if(it->value == removeValue)
        {
            outFile << "Found " << it->value << endl;
            found = true;
            ++removeComparisions;
        }
    }
    
    list<Node>::iterator next = it->down;
    
    while(currLevel >= 0)
    {
        skipLists.at(currLevel).erase(it);
        it = next;
        next = it->down;
        --currLevel;
    }
}
