//============================================================================
// Name        : bubble-sort.cpp
// Author      : Pratik Patel
// Date        : 02/10/2019
// Copyright   : 
// Description : Implementation of bubble sort in C++
//============================================================================

#include "sort.h"

void 
BubbleSort::sort(vector<int>& a, int size)			// main entry point
{
  /* Complete this function with the implementation of bubble sort algorithm 
     Record number of comparisons in variable num_cmps of class Sort
  */

	for(int i = 1; i < size; ++i)
	{
		bool isSorted = true;
		for(int j = 0; j < size - i; ++j)
		{
			if(++num_cmps, a.at(j) > a.at(j+1))
			{
				int temp = a.at(j+1);
				a.at(j+1) = a.at(j);
				a.at(j) = temp;
				isSorted = false;
			}
		}
		if(isSorted)
			break;
	}
}
