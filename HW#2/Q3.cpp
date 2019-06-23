

#include <iostream>

using namespace std;

int findMax(int[], int, int, int);

int main()
{
	int temp[5] = {12, 13, 5, 14, 7};

	cout << "Below is an array:" << endl;

	for(int i = 0; i < 5; ++i)
	{
		cout << temp[i] << " " ;
	}
	cout << endl << endl;

	cout << "The maximum number returned by the function is " << findMax(temp, 0, temp[0], 5) << endl;
	return 0;
}

int findMax(int arr[], int index, int max, int size)
{
	if(arr[index] > max)
	{
		if(index == size - 1)
			return arr[index];
		else
			return findMax(arr, ++index, arr[index-1], size);
	}

	else
	{
		if(index == size - 1)
			return max;
		else
			return findMax(arr, ++index, max, size);
	}
}