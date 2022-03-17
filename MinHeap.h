#pragma once

#include "Array.h"
#include <cassert>

template<typename T>
class MinHeap
{
public:
	MinHeap() = delete;
	explicit MinHeap(const Array<T>& arr);
	explicit MinHeap(const Array<T>& arr, int (*pcmp)(T&, T&));
	~MinHeap() = default;

	T exctractMin();
	T peekMin() { return arr_[0]; };
	void insertElement(T elem);
	void replaceMin(const T elem) { arr_[0] = elem;  heapifyMin(0); }

private:
	int defComparer(T& a, T& b) { return a - b; }
	void buildMinHeap();
	void swap(size_t indexA, size_t indexB);
	void heapifyMin(size_t index);

public:
	Array<T> arr_;
	int (*pcmp_)(T&, T&);
};


// Interface
template<typename T>
T MinHeap<T>::exctractMin()
{
	assert(!arr_.isEmpty());

	T result = arr_[0];

	arr_[0] = arr_.getLast();
	arr_.deleteLast();
	
	if (!arr_.isEmpty()) {
		heapifyMin(0);
	}

	return result;
}

template<typename T>
void MinHeap<T>::insertElement(T elem)
{
	arr_.pushBack(elem);
	heapifyMin(arr_.getSize() - 1);
}

// Heap
template<typename T>
MinHeap<T>::MinHeap(const Array<T>& arr) : arr_(arr)
{
	pcmp_ = defComparer;
}

template<typename T>
MinHeap<T>::MinHeap(const Array<T>& arr, int(*pcmp)(T&, T&)) : arr_(arr), pcmp_(pcmp)
{
	assert(pcmp != nullptr);
	 buildMinHeap(); 
}

template<typename T>
void MinHeap<T>::buildMinHeap()
{
	for (int i = arr_.getSize() / 2 - 1; i >= 0; --i) {
		heapifyMin(i);
	}
}

template<typename T>
void MinHeap<T>::swap(size_t indexA, size_t indexB)
{
	assert(!arr_.isEmpty());
	T tmp = arr_[indexA];
	arr_[indexA] = arr_[indexB];
	arr_[indexB] = tmp;
}

template<typename T>
void MinHeap<T>::heapifyMin(size_t index)
{
	while (true)
	{
		size_t leftIndex = (index * 2) + 1;
		size_t rightIndex = (index * 2) + 2;
		size_t smallestIndex = index;

		if (leftIndex < arr_.getSize() && pcmp_(arr_[leftIndex], arr_[index]) < 0) {
			smallestIndex = leftIndex;
		}

		if (rightIndex < arr_.getSize() && pcmp_(arr_[rightIndex], arr_[smallestIndex]) < 0) {
			smallestIndex = rightIndex;
		}

		if (smallestIndex == index) {
			break;
		}	
		swap(index, smallestIndex);
		index = smallestIndex;
		
	}
}
