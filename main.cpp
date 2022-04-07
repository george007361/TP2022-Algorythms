//2_4.Дан отсортированный массив различных целых чисел A[0..n - 1] 
//и массив целых чисел B[0..m - 1].Для каждого элемента массива B[i] 
//найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i] : O(log(k)).
//Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного
//поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать 
//бинарный поиск.
//
//n ≤ 110000, m ≤ 1000.

#include <iostream>
#include <cassert>

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

	void findClosestElementInterval(const T& elem, size_t& left, size_t& right);
	size_t findClosestElementIndex(const T& elem);

	// Конструкоторы
	Array<T>() : arr_(nullptr), size_(0), capacity_(0) {}
	Array<T>(const size_t size) : size_(size), capacity_(size), arr_(new T[size]) { }

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
	bool checkArrayOrder() const;
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

	~Array();

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
		delete [] arr_;
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
template<typename T>
bool Array<T>::checkArrayOrder() const
{
	bool order = true;
	for (size_t i = 0; i < size_ - 1 && order; i++)
	{
		if (arr_[i + 1] < arr_[i])
		{
			order = false;
		}
	}
	return order;
}

template<typename T>
void Array<T>::findClosestElementInterval(const T& elem, size_t& left, size_t& right)
{
	assert(checkArrayOrder());
	left = 0;
	right = size_ - 1;
	if (arr_[left] >= elem)
	{
		left = right = 0;
		return;
	}

	size_t i = 1;
	while (i < size_ && arr_[i] <= elem)
	{
		left = i;
		i *= 2;
		right = i < size_ ? i : size_ - 1;
	}
}

template<typename T>
size_t Array<T>::findClosestElementIndex(const T& elem)
{
	size_t left, right;
	findClosestElementInterval(elem, left, right);
	
	if (left == 0 && right == 0)
		return 0;

	while (left < right)
	{
		size_t mid = (left + right) / 2;
		if (arr_[mid] < elem)
			left = mid + 1;
		else
			right = mid;
	}

	if (left > 0 && arr_[left] != elem && abs(arr_[left - 1] - elem) <= abs(arr_[left] - elem))
	{
		return left - 1;

	}
	else
	{
		return left;
	}
}

int main()
{
	int count, val;
	cin >> count;
	Array<int> A = Array<int>(count);

	for (size_t i = 0; i < A.getSize(); i++)
	{
		cin >> val;
		A[i] = val;
	}

	cin >> count;
	Array<int> B = Array<int>(count);
	for (size_t i = 0; i < B.getSize(); i++)
	{
		cin >> val;
		B[i] = val;
	}

	for (size_t i = 0; i < B.getSize(); i++)
	{
		cout << A.findClosestElementIndex(B[i]) << " ";
	}

	return EXIT_SUCCESS;
}
