#include <iostream>
#include <math.h>

using namespace std;

class Progression
{
	Progression(a, d)
	{
		this.a = a;
		this.d = d;
	}

public:
	virtual int sum() = 0;
	virtual int getNext(int current) = 0;

private:
	int a;
	int d;
}

class ArithmeticProgession : public Progression
{
	ArithmeticProgession(a, d) : Progression(a, d){ ;}

	int sum(n)
	{
		int totalA = n*a;
		int totalDifference = ((n * (n + 1)) / 2) * d;

		return totalA + totalDifference;
	}

	int getNext(int current)
	{
		return current + d;
	}
}

class GeometricProgession : public Progression
{
	GeometricProgession(a, d) : Progression(a, d){ ;}

	int sum(n)
	{
		return ((a * (1 - pow(d, n))) / (1 - d));
	}

	int getNext(int current)
	{
		return current * d;
	}
}