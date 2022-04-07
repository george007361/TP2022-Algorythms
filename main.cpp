//Задача № 4 (4 балла)
//Обязательная задача
//Требование для всех вариантов Задачи 4
//Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
//Решение должно поддерживать передачу функции сравнения снаружи.
//Куча должна быть динамической.
//
//4.1 Слияние массивов.
//Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
//Требования: время работы O(N* logK).Ограничение на размер кучи O(K)..
//Формат входных данных : Сначала вводится количество массивов K.Затем по очереди размер каждого массива
//и элементы массива.Каждый массив упорядочен по возрастанию.
//Формат выходных данных : Итоговый отсортированный массив.

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

//---------------------------------------
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
//---------------------------------------------

class  MinHeapElement
{
private:
	Array<int>* pArr_; // указатель на массив
	size_t index_; // текущий "первый" элемент, оно же смещение
public:
	MinHeapElement() : pArr_(nullptr), index_(-1) {}
	MinHeapElement(Array<int>* arr, size_t index = 0) : pArr_(arr), index_(index) {}

	bool next(); // перейти к следущему элементу 
	int getElem(); // достать текущий элемент
	static int comrareElements(const MinHeapElement& a, const MinHeapElement& b);
};

int MinHeapElement::comrareElements(const MinHeapElement& a, const MinHeapElement& b)
{
	if ((*a.pArr_)[a.index_] == (*b.pArr_)[b.index_])
	{
		return 0;
	}
	
	return (*a.pArr_)[a.index_] > (*b.pArr_)[b.index_] ? 1 : -1;
}

bool MinHeapElement::next()
{
	assert(pArr_ != nullptr);
	++index_;

	return index_ < pArr_->getSize() ? true : false;
}

int MinHeapElement::getElem()
{
	assert(pArr_ != nullptr);

	return (*pArr_)[index_];
}

Array<int> mergeArrays(Array<Array<int>>& arrays)
{
	size_t totalCount = 0; // сумма всех элементов
	auto heapArray = Array<MinHeapElement>(); //  массив для создания кучи, размер соответствует количеству объединяемых массивов, содержит первые элементы соединяемых массивов.

	for (size_t i = 0; i < arrays.getSize(); i++)
	{
		totalCount += arrays[i].getSize();
		heapArray.pushBack(MinHeapElement(&arrays[i]));
	}

	auto heap = MinHeap<MinHeapElement>(heapArray, MinHeapElement::comrareElements); // куча, в корне - самый маленький элемент

	auto merged = Array<int>(totalCount); // выходной массив

	for (size_t i = 0; i < totalCount; i++) // перебираем все элементы
	{
		auto minElem = heap.peekMin(); // Достаём меньший элемент из кучи, т.е. самый маленький из соединяемых массивов.
		merged[i] = minElem.getElem(); // переносим в выходной массив
		if (minElem.next()) // если в массиве, из которого достали элемент, еще есть элементы, вставляем следущий в кучу
		{
			heap.replaceMin(minElem);
		}
		else
		{
			heap.exctractMin();
		}
	}

	return merged;
}

int main()
{
	int countOfArrays;
	cin >> countOfArrays;

	Array<Array<int>> arrays(countOfArrays);
	
	for (size_t i = 0; i < arrays.getSize(); i++)
	{
		int sizeOfiArray;
		cin >> sizeOfiArray;
	
		arrays[i].reallocArray(sizeOfiArray);
		
		for (size_t j = 0; j < arrays[i].getSize(); j++)
		{
			cin >> (arrays[i])[j];
		}
	}

	auto merged = mergeArrays(arrays);
	
	for (size_t i = 0; i < merged.getSize(); i++)
	{
		cout << merged[i] << " ";
	}
	cout << endl;

	return EXIT_SUCCESS;
}
