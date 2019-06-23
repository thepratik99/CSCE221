//============================================================================
// Name        : selection-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of selection sort in C++
//============================================================================

#include "sort.h"
#include <vector>

void
SelectionSort::sort(vector<int>& A, int size)				// main entry point
{
  /* Complete this function with the implementation of selection sort algorithm 
  Record number of comparisons in variable num_cmps of class Sort
  */
  int smallest;
  int smallestIndex;
  int temp;
  num_cmps = 0;
  
  for(int i = 0; i < size-1; ++i)
  {
	  ++num_cmps;
	  smallest = A[i];
	  smallestIndex = i;
	  for(int j = i+1; j < size; ++j)
	  {
		  if(A[j] < smallest)
		  {
			  ++num_cmps;
			  smallest = A[j];
			  smallestIndex = j;
		  }
	  }
	  temp = A[i];
	  A[i] = A[smallestIndex];
	  A[smallestIndex] = temp;
  }
}
