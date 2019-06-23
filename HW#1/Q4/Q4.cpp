#include <iostream>
#include <vector>

<template typename T>

int BinarySearch(T x, vector<T> a)
{
	int middle;
	int lower = 0;
	int higher = (int) a.size() - 1;

	while(lower <= higher)
	{
		middle = (lower + higher) / 2;
		if(a.at(middle) < x)
			lower = middle + 1;
		else if (a.at(middle) > x)
			higher = middle - 1;
		else
			return middle;
	}
	return -1;
}