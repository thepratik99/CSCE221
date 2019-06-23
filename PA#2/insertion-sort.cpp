//============================================================================
// Name        : insertion-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of insertion sort in C++
//============================================================================

#include "sort.h"
#include <vector>

void
InsertionSort::sort(vector<int>& a, int size)				// main entry point
{
  /* Complete this function with the implementation of insertion sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
	if(size > 1)
	{
	    for(int i = 1; i < size; ++i)
		{
	      int j = i - 1;
	      int key = a.at(i);

	      while(j >= 0 && a.at(j) > key && ++num_cmps)
		  {
	        a.at(j+1) = a.at(j);
	        --j;
	      }
	      a.at(j+1) = key;
	    }
  	}
}
