// Задача № 7 (3 балла)
// 7_1. MSD для строк.
// Дан массив строк. Количество строк не больше 105. Отсортировать массив методом поразрядной сортировки MSD по символам. Размер алфавита - 256 символов. Последний символ строки = ‘\0’.
// IN Out
// ab a
// aa aa
// a aaa
// aaa ab

#include <cassert>
#include <iostream>

#define TERMINATOR '\0'

using namespace std;

template<typename T>
class Array
{
public:
	// Конструкоторы
	Array<T>() : arr_(nullptr), size_(0), capacity_(0) {}
	Array<T>(const size_t size) : size_(size), capacity_(size), arr_(size ? new T[size] : nullptr) {}

	// Деструктор
	~Array();

	//Перенос
	Array(Array&& srcArr) noexcept;
	Array<T>& operator = (Array<T>&& srcArr);

	//Копирование
	Array(const Array& srcArr);
	Array<T>& operator = (const Array& srcArr);

	// Операторы
	T& operator [](const size_t index);

	// Функции
	bool isEmpty() const { return this->size_ > 0 ? false : true; }
	T getLast() const { return arr_[size_ - 1]; }
	size_t getSize() const { return this->size_; }
	void pushBack(const T& elem);
	void deleteLast() { --size_; }
	void reallocArray(const size_t newSize);

private:
	void extendArray();

private:
	T* arr_;
	size_t size_;
	size_t capacity_;
};


// Деструктор
template<typename T>
Array<T>::~Array()
{
	if (arr_)
		delete[] arr_;
	arr_ = nullptr;
	size_ = capacity_ = 0;
}

// Копирование
template<typename T>
Array<T>::Array(const Array& srcArr)
{
	this->size_ = srcArr.size_;
	this->capacity_ = srcArr.capacity_;
	this->arr_ = new T[this->capacity_];

	for (size_t i = 0; i < size_; i++)
	{
		this->arr_[i] = srcArr.arr_[i];
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& srcArr)
{
	this->size_ = srcArr.size_;
	this->capacity_ = srcArr.capacity_;
	this->arr_ = new T[this->capacity_];

	for (size_t i = 0; i < size_; i++)
	{
		this->arr_[i] = srcArr.arr_[i];
	}
	return *this;
}

//Перенос
template<typename T>
Array<T>& Array<T>::operator=(Array&& srcArr)
{
	if (&srcArr == this)
		return *this;

	~Array();

	this->size_ = srcArr.size_;
	this->arr_ = srcArr.arr_;
	this->capacity_ = srcArr.capacity_;

	srcArr.size_ = srcArr.capacity_ = 0;

	return *this;
}

template<typename T>
Array<T>::Array(Array<T>&& srcArr) noexcept
{
	this->arr_ = srcArr.arr_;
	this->size_ = srcArr.size_;
	this->capacity_ = srcArr.capacity_;

	srcArr.arr_ = nullptr;
	srcArr.capacity_ = srcArr.size_ = 0;
}

// Функции
template<typename T>
void Array<T>::pushBack(const T& elem)
{
	if (size_ == capacity_)
		extendArray();
	arr_[size_++] = elem;
}

template<typename T>
T& Array<T>::operator[](const size_t index)
{
	assert(index >= 0 && index < size_);
	return arr_[index];
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
		delete arr_;
	arr_ = newArr;
}

template<typename T>
void Array<T>::reallocArray(const size_t newSize)
{
	if (arr_)
		delete[] arr_;
	arr_ = new T[newSize];
	capacity_ = size_ = newSize;
}

void radixSort(Array<string>&  arr, Array<int>& indexArr, int offset, const int alphSize)
{
	if (indexArr.getSize() <= 1)
	{
		return;
	}

	Array<Array<int>> sortedIndexArr(alphSize);
	for (size_t i = 0; i < indexArr.getSize(); i++)
	{
		sortedIndexArr[arr[indexArr[i]][offset]].pushBack(indexArr[i]);
	}
	++offset;


	for (size_t i = 0; i < sortedIndexArr.getSize(); i++)
	{
		if (i != TERMINATOR)
		{
			radixSort(arr, sortedIndexArr[i], offset, alphSize);
		}
	}

	int index = 0;
	for (int i = 0; i < sortedIndexArr.getSize(); ++i)
	{
		for (int j = 0; j < sortedIndexArr[i].getSize(); ++j)
		{
			indexArr[index] = sortedIndexArr[i][j];
			++index;
		}
	}

}

void sort(Array<string>& arr, const int alphSize)
{
	Array<int> indexArr(arr.getSize());
	for (int i = 0; i < arr.getSize(); i++)
	{
		indexArr[i] = i;
	}

	radixSort(arr, indexArr, 0, alphSize);

	Array<string> sortedArr(arr.getSize());
	for (int i = 0; i < arr.getSize(); i++)
	{
		sortedArr[i] = arr[indexArr[i]];
	}
	arr = sortedArr;
}

int main()
{
	int countOfStrings;
	cin >> countOfStrings;

	Array<string> arr(countOfStrings);

	for (int i = 0; i < arr.getSize(); i++)
	{
		cin >> arr[i];
	}

	sort(arr, 256);

	for (int i = 0; i < arr.getSize(); i++)
	{
		cout << arr[i] << endl;
	}

	return EXIT_SUCCESS;
}
