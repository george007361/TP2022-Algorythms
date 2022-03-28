#pragma once

#include "Array.h"
#include <cassert>

template<typename T>
class MinHeap
{
public:
	// ������������
	MinHeap() = delete;
	explicit MinHeap(const Array<T>& arr) : arr_(arr), pcmp_(defComparer) {};
	explicit MinHeap(const Array<T>& arr, int (*pcmp)(const T&, const T&));

	// ����������
	~MinHeap() = default;

	// �����������
	MinHeap(const MinHeap<T>& srcHeap) = delete;
	MinHeap<T>& operator = (const MinHeap<T>& srcHeap) = delete;

	// �������
	MinHeap(MinHeap<T>&& srcHeap);
	MinHeap<T>& operator = (MinHeap<T>&& srcHeap);

	// �������
	T& exctractMin();
	const T& peekMin() { return arr_[0]; }
	void insertElement(const T& elem);
	void replaceMin(const T& elem) { arr_[0] = elem;  heapifyMin(0); }

private:
	static int defComparer(const T& a, const T& b) { return a - b; }
	void buildMinHeap();
	void swap(const size_t indexA, const size_t indexB);
	void heapifyMin(const size_t index);

private:
	Array<T> arr_;
	int (*pcmp_)(const T&, const T&);
};


// �������
template<typename T>
T& MinHeap<T>::exctractMin()
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
void MinHeap<T>::insertElement(const T& elem)
{
	arr_.pushBack(elem);
	heapifyMin(arr_.getSize() - 1);
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
void MinHeap<T>::heapifyMin(const size_t parentIndex)
{
	size_t index = parentIndex;
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

// �����������
template<typename T>
MinHeap<T>::MinHeap(const Array<T>& arr, int(*pcmp)(const T&, const T&)) : arr_(arr), pcmp_(pcmp)
{
	assert(pcmp != nullptr);
	buildMinHeap();
}

// �������
template<typename T>
MinHeap<T>::MinHeap(MinHeap<T>&& srcHeap)
{
	arr_ = srcHeap.arr_;
	pcmp_ = srcHeap.pcmp_;

	srcHeap.~MinHeap();
}

template<typename T>
MinHeap<T>& MinHeap<T>::operator = (MinHeap<T>&& srcHeap)
{
	if (&srcHeap == this)
	{
		return *this;
	}

	~MinHeap();

	arr_ = srcHeap.arr_;
	pcmp_ = srcHeap.pcmp_;

	srcHeap.~MinHeap();

	return *this;
}
