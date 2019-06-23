

#include <iostream>
#include <queue>

void push(T elem, queue<T> queue)
{
	queue.push_back(elem);
}

T pop(queue<T> queue)
{
	queue queue2;

	while(queue.size() > 1)
		queue2.push_back(queue.pop_front());

	T temp = queue.pop_front();

	while(queue2.isEmpty())
		queue.push_back(queue2.pop_front());

	return temp;
}