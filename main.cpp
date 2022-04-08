﻿// Задача № 7 (3 балла)
// 7_1. MSD для строк.
// Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
// IN Out
// ab a
// aa aa
// a aaa
// aaa ab

#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

template<typename T>
class Array
{
public:
	// Функции
	bool isEmpty() const { return size_ > 0 ? false : true; }
	size_t getSize() const { return size_; }
	const T& getLast() const;
	void pushBack(const T& elem);
	void deleteLast();
	void reallocArray(const size_t newSize);

	// Конструкоторы
	Array<T>() : arr_(nullptr), size_(0), capacity_(0) {}
	Array<T>(const size_t size) : size_(size), capacity_(size), arr_(new T[size]) { }
	Array<T>(const size_t size, const T& val);

	//Перенос
	Array<T>(Array<T>&& srcArr);
	Array<T>& operator = (Array<T>&& srcArr);

	//Копирование
	Array<T>(const Array<T>& srcArr);
	Array<T>& operator = (const Array<T>& srcArr) = delete;

	// Деструктор
	~Array<T>();

	// Операторы
	T& operator [](const size_t index);

private:
	void extendArray();

private:
	T* arr_;
	size_t size_;
	size_t capacity_;
};


// Конст
template<typename T>
Array<T>::Array(const size_t size, const T& val) : size_(size), capacity_(size), arr_(new T[size])
{
	for (size_t i = 0; i < size_; i++)
	{
		arr_[i] = val;
	}
}

// Деструктор
template<typename T>
Array<T>::~Array()
{
	if (arr_)
	{
		delete[] arr_;
	}
	arr_ = nullptr;
	size_ = capacity_ = 0;
}

// Копирование
template<typename T>
Array<T>::Array(const Array<T>& srcArr)
{
	size_ = srcArr.size_;
	capacity_ = srcArr.capacity_;
	arr_ = new T[capacity_];

	for (size_t i = 0; i < size_; i++)
	{
		arr_[i] = srcArr.arr_[i];
	}
}

//Перенос
template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& srcArr)
{
	if (&srcArr == this)
	{
		return *this;
	}

	this->~Array();

	size_ = srcArr.size_;
	arr_ = srcArr.arr_;
	capacity_ = srcArr.capacity_;

	srcArr.size_ = srcArr.capacity_ = 0;
	srcArr.arr_ = nullptr;

	return *this;
}

template<typename T>
Array<T>::Array(Array<T>&& srcArr)
{
	this->~Array();

	arr_ = srcArr.arr_;
	size_ = srcArr.size_;
	capacity_ = srcArr.capacity_;

	srcArr.arr_ = nullptr;
	srcArr.capacity_ = srcArr.size_ = 0;
}

// Функции
template<typename T>
const T& Array<T>::getLast() const
{
	assert(!isEmpty());
	return arr_[size_ - 1];
}

template<typename T>
void Array<T>::deleteLast()
{
	assert(!isEmpty());
	--size_;
}

template<typename T>
void Array<T>::pushBack(const T& elem)
{
	if (size_ == capacity_)
	{
		extendArray();
	}
	arr_[size_++] = elem;
}

template<typename T>
void Array<T>::extendArray()
{
	T* newArr = new T[capacity_ = capacity_ ? capacity_ *= 2 : 1];
	for (size_t i = 0; i < size_; i++)
	{
		newArr[i] = arr_[i];
	}
	if (arr_)
	{
		delete[] arr_;
	}
	arr_ = newArr;
}

template<typename T>
void Array<T>::reallocArray(const size_t newSize)
{
	if (arr_)
	{
		delete[] arr_;
	}
	arr_ = new T[newSize];
	capacity_ = size_ = newSize;
}


// Операторы
template<typename T>
T& Array<T>::operator[](const size_t index)
{
	assert(index >= 0 && index < size_);
	return arr_[index];
}


//
//void radixSort(Array<string>& arr, Array<int>& indexArr, int offset, const int alphSize)
//{
//	if (indexArr.getSize() <= 1)
//	{
//		return;
//	}
//
//	Array<Array<int>> sortedIndexArr(alphSize);
//	for (size_t i = 0; i < indexArr.getSize(); i++)
//	{
//		sortedIndexArr[arr[indexArr[i]][offset]].pushBack(indexArr[i]);
//	}
//	++offset;
//
//
//	for (size_t i = 0; i < sortedIndexArr.getSize(); i++)
//	{
//		if (i != TERMINATOR)
//		{
//			radixSort(arr, sortedIndexArr[i], offset, alphSize);
//		}
//	}
//
//	int index = 0;
//	for (int i = 0; i < sortedIndexArr.getSize(); ++i)
//	{
//		for (int j = 0; j < sortedIndexArr[i].getSize(); ++j)
//		{
//			indexArr[index] = sortedIndexArr[i][j];
//			++index;
//		}
//	}
//
//}
//
//void sort(Array<string>& arr, const int alphSize)
//{
//	Array<int> indexArr(arr.getSize());
//	for (int i = 0; i < arr.getSize(); i++)
//	{
//		indexArr[i] = i;
//	}
//
//	radixSort(arr, indexArr, 0, alphSize);
//
//	Array<string> sortedArr(arr.getSize());
//	for (int i = 0; i < arr.getSize(); i++)
//	{
//		sortedArr[i] = arr[indexArr[i]];
//	}
//	arr = std::move(sortedArr);
//}

template<class T, class TGetKey>
void CountingSort2(Array<T>& arr, const int startIndex, const int endIndex, TGetKey getKey) {
	if (endIndex - startIndex + 1 < 2)
		return;
	//if (getKey.offset == 1)
		//cout << "dwadad";
	int max = getKey(arr[startIndex]);
	for (int i = startIndex; i <= endIndex; ++i) {
		if (max < getKey(arr[i])) {
			max = getKey(arr[i]);
		}
	}

	Array<int> c(max + 1, 0);
	for (int i = startIndex; i <= endIndex; ++i)
		++c[getKey(arr[i])];

	for (int i = 1; i <= max; ++i) {
		c[i] += c[i - 1]; // Концы групп.
	}

	Array<T> b(endIndex - startIndex + 1);
	Array<int> cc(c);
	for (int i = endIndex; i >= startIndex; --i) {// Проход с конца.
		b[--c[getKey(arr[i])]] = arr[i];
	}


	for (size_t i = 0; i < b.getSize(); i++)
	{
		arr[startIndex + i] = b[i];
	}

	getKey.next();
	for (int i = 1; i <= max; ++i)
	{
		CountingSort2(arr, startIndex + cc[i - 1], startIndex + cc[i] - 1, getKey);
	}
}


class CmpStrByte
{
public:
	CmpStrByte() : offset(0) {}
	~CmpStrByte() = default;
	void next() { ++offset; }
	int getKey(string& str) { return static_cast<int>(str.length() > offset ? str[offset] : '\0'); }
	int operator()(string& str) { return getKey(str); }

public:
	size_t offset;
};



int main()
{
	int countOfStrings;
	cin >> countOfStrings;

	Array<string> arr(countOfStrings);

	for (int i = 0; i < arr.getSize(); i++)
	{
		cin >> arr[i];
	}

	CmpStrByte comp;
	CountingSort2(arr, 0, arr.getSize() - 1, comp);

	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}

	return EXIT_SUCCESS;
}
