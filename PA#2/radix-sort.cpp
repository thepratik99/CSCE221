//============================================================================
// Name        : radix-sort.cpp
// Author      : 
// Date        :
// Copyright   : 
// Description : Implementation of radix sort in C++
//============================================================================

#include "sort.h"
#include <iostream>
#include <vector>

void
RadixSort::sort(vector<int>& A, int size)
{
	// Find the largest number to know number of digits
	int max = A.at(0);
	for (int i = 1; i < size; i++)
	{
		if (A.at(i) > max)
		{
			max = A.at(i);
		}
	}
	
	int i,digitPlace = 1;
    vector<int> result(size); // resulting array
 
 
    //we run loop until we reach the largest digit place
    while(max/digitPlace > 0)
	{
 
        vector<int> count(10);
        for(int i = 0; i < 10; ++i)
            count.at(i) = 0;
        //Store the count of "keys" or digits in count[]
        for (i = 0; i < size; i++)
            count[(A[i]/digitPlace) % 10]++;
 
        // Change count[i] so that count[i] now contains actual
        //  position of this digit in result[]
        //  Working similar to the counting sort algorithm
        for (i = 1; i < 10; i++)
            count[i] += count[i - 1];
 
        // Build the resulting array
        for (i = size - 1; i >= 0; i--)
        {
            result[count[ (A[i]/digitPlace)%10 ] - 1] = A[i];
            count[ (A[i]/digitPlace)%10 ]--;
        }
 
        // Now main array A[] contains sorted
        // numbers according to current digit place
        for (i = 0; i < size; i++)
            A[i] = result[i];
 
            // Move to next digit place
            digitPlace *= 10;
    }
	
  /*
     Complete this function with the implementation of radix sort
     algorithm.
  */
}
