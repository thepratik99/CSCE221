//
//  main.cpp
//  SkipList
//
//  Created by Pratik Patel on 4/13/19.
//  Copyright © 2019 TAMU. All rights reserved.
//

//including header files
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <limits>
#include <ctime>
#include <fstream>
#include <string>
#include "SkipList.h"

using namespace std;

int main()
{
    srand(time(NULL));
    
    //variable for filename
    string filename;
    //instance of class SkipList
    SkipList* sl = new SkipList();
    
    //getting the name of the file
    cout << "Please enter the name of the file: " ;
    cin >> filename;
    
    //opening a file
    ifstream inFile;
    inFile.open(filename);
    
    //error checking the file
    if(!inFile)
    {
        cout << "The file does not exist." << filename << endl;
        return -1;
    }
    
    //declaring neccesary variables
    int temp;
    vector<int> insertThese;
    
    //getting the inputs and storing in a vector
    while(inFile >> temp)
    {
        insertThese.push_back(temp);
    }
    
    //inserting them in the skipList
    for(int i = 0; i < insertThese.size(); ++i)
    {
        sl->insert(insertThese.at(i));
    }
    
    //outFile to output the results
    ofstream outFile;
    outFile.open(filename + "_skipList.txt");
    
    //printing the inputted SkipList
    sl->printSkipList(outFile);
    outFile << endl;
    
    //removing all the integers form the vector
    for(int i = insertThese.size() - 1; i >= 0; --i)
    {
        sl->remove(insertThese.at(i), outFile);
    }
    
    //printing the empty skipList in the file
    outFile << endl;
    sl->printSkipList(outFile);
    outFile << endl;
    
    //printing the average costs
    outFile << "Average Insert Comparisions: " << ((double)(sl->insertComparisions))/(sl->totalNodes) << endl;
    outFile << "Average Remove Comparisions: " << ((double)(sl->removeComparisions))/(sl->totalNodes) << endl;
    
    return 0;
}
