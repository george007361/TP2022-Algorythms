#pragma once

#include "Array.h"

template<typename T>
class MinHeap
{
public:
	MinHeap() = default;
	explicit MinHeap(const Array<T>& arr) : arr(arr) { buildMinHeap(); }
	explicit MinHeap(const Array<T>& arr, int (*pcmp)(T&, T&) = defComparer) : arr(arr), pcmp(pcmp) { buildMinHeap(); }
	//explicit MinHeap(const size_t arr_size) : arr(Array<T>(arr_size)) {}
	~MinHeap() = default;
	T exctractMin();
	T peekMin() const { return arr[0]; };
private:
	Array<T> arr;
	int (*pcmp)(T&, T&);
	int defComparer(T& a, T& b) { return a - b; }
	void buildMinHeap();
	void swap(size_t indexA, size_t indexB);
	void heapifyMin(size_t index);
};

template<typename T>
T MinHeap<T>::exctractMin()

{
	assert(!arr.isEmpty());

	// Запоминаем значение корня.
	T result = arr[0];

	// Переносим последний элемент в корень.
	arr[0] = arr.getLast();
	arr.deleteLast();
	
	// Вызываем SiftDown для корня.
	if (!arr.isEmpty()) {
		siftDown(0);
	}

	return result;
}

template<typename T>
void MinHeap<T>::buildMinHeap()
{
	for (int i = arr.getSize() / 2 - 1; i >= 0; --i) {
		heapifyMin(i);
	}
}

template<typename T>
void MinHeap<T>::swap(size_t indexA, size_t indexB)
{
	T tmp = arr[indexA];
	arr[indexA] = arr[indexB];
	arr[indexB] = tmp;
}

template<typename T>
void MinHeap<T>::heapifyMin(size_t index)
{
	while (true)
	{
		size_t leftIndex = (index * 2) + 1;
		size_t rightIndex = (index * 2) + 2;
		size_t smallestIndex = index;

		if (leftIndex < arr.getSize() && pcmp(arr[smallestIndex], arr[leftIndex]) > 0) {
			smallestIndex = leftIndex;
		}

		if (rightIndex < arr.getSize() && pcmp(arr[smallestIndex], arr[rightIndex]) > 0) {
			smallestIndex = rightIndex;
		}

		if (smallestIndex == index) {
			break;
		}
		swap(index, smallestIndex);
	}



	/*size_t leftIndex = (index * 2) + 1;
	size_t rightIndex = (index * 2) + 2;
	size_t smallestIndex = index;

	if (leftIndex < arr.getSize() && arr[smallestIndex] > arr[leftIndex]) {
		smallestIndex = leftIndex;
	}

	if (rightIndex < arr.getSize() && arr[smallestIndex] > arr[rightIndex]) {
		smallestIndex = rightIndex;
	}

	if (smallestIndex != index) {
		swap(index, smallestIndex);
		heapifyMin(index);
	}*/

}
