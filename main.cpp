// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка [Li, Ri]. 
// Найти сумму длин частей числовой прямой, окрашенных ровно в один слой.
// N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 10^9].

// Формат ввода
// В первой строке записано количество отрезков.
// В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.

// Формат вывода
// Выведите целое число — длину окрашенной в один слой части.

// Требование для всех вариантов Задачи 5
// Во всех задачах данного раздела необходимо реализовать и использовать сортировку слиянием в виде шаблонной функции. 
// Решение должно поддерживать передачу функции сравнения снаружи.
// Общее время работы алгоритма O(n log n).

#include <cassert>
#include <iostream>

using namespace std;

///////////////////Array///////////////////////
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
	const T& operator[](const size_t index) const;

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

template<typename T>
const T& Array<T>::operator[](const size_t index) const
{
	assert(index >= 0 && index < size_);
	return arr_[index];
}

///////////////////////Point//////////////////////////////////////////////

class Point
{
public:
	Point() = default;
	Point(int x, int type) : _x(x), _type(type) {}
	Point(Point&&) = default;
	Point(const Point&) = default;
	Point& operator=(Point&&) = default;
	Point& operator=(const Point&) = default;
	~Point() = default;

	static int compare(const Point& a, const Point& b) { return a._x - b._x; }
	static void printPoints(const Array<Point>& arr);

	int getX() const { return _x; }
	int getType() const { return _type; }
	void printPoint() const { cout << "[ x=" << _x << "; Type: " << _type << " ] "; }

public:
	enum
	{
		LineStart,
		LineEnd
	};

private:
	int _x;
	int _type;
};

void Point::printPoints(const Array<Point>& arr)
{
	cout << endl;
	for (size_t i = 0; i < arr.getSize(); ++i)
	{
		arr[i].printPoint();
	}
	cout << endl;
}

//////////////////////////////Merge sort///////////////////////////////
template<typename T>
void mergeSort(Array<T>& arr, int (*pcmp)(const T&, const T&))
{
	assert(pcmp);

	for (size_t currSubarraySize = 1; currSubarraySize <= arr.getSize() - 1; currSubarraySize *= 2)
	{
		for (size_t leftSubarrayStarts = 0; leftSubarrayStarts < arr.getSize() - 1; leftSubarrayStarts += 2 * currSubarraySize)
		{
			size_t leftSubarrayEnds = min(leftSubarrayStarts + currSubarraySize - 1, arr.getSize() - 1);
			size_t rightSubarrayEnds = min(leftSubarrayStarts + 2 * currSubarraySize - 1, arr.getSize() - 1);
			merge(arr, leftSubarrayStarts, leftSubarrayEnds, rightSubarrayEnds, pcmp);
		}
	}
}

template<typename T>
void merge(Array<T>& arr, size_t leftSubarrayStarts, size_t leftSubarrayEnds, size_t rightSubarrayEnds, int (*pcmp)(const T&, const T&))
{
	assert(pcmp);

	size_t i, j, k;
	size_t leftSubarraySize = leftSubarrayEnds - leftSubarrayStarts + 1;
	size_t rightSubarraySize = rightSubarrayEnds - leftSubarrayEnds;
	Array<T> leftSubarray(leftSubarraySize);
	Array<T> rightSubarray(rightSubarraySize);

	for (i = 0; i < leftSubarraySize; ++i)
	{
		leftSubarray[i] = arr[leftSubarrayStarts + i];
	}

	for (j = 0; j < rightSubarraySize; ++j)
	{
		rightSubarray[j] = arr[leftSubarrayEnds + 1 + j];
	}

	i = 0;
	j = 0;
	k = leftSubarrayStarts;

	for (; i < leftSubarraySize && j < rightSubarraySize; ++k)
	{
		if (pcmp(leftSubarray[i], rightSubarray[j]) <= 0)
		{
			arr[k] = leftSubarray[i];
			++i;
		}
		else
		{
			arr[k] = rightSubarray[j];
			++j;
		}
	}

	for (; i < leftSubarraySize; arr[k++] = leftSubarray[i++]);

	for (; j < rightSubarraySize; arr[k++] = rightSubarray[j++]);
}

///////////////////Task////////////////////////

size_t findOneLayerLength(Array<Point>& arr)
{
	assert(!arr.isEmpty());

	mergeSort(arr, Point::compare);

	size_t oneLayerLen = 0;
	int layersCount = 0;

	int oneLayerStartX, oneLayerEndX;

	for (size_t i = 0; i < arr.getSize(); ++i)
	{
		if (arr[i].getType() == Point::LineStart)
		{
			if (layersCount == 0)
			{
				oneLayerStartX = arr[i].getX();
			}
			if (layersCount == 1)
			{
				oneLayerLen += arr[i].getX() - oneLayerStartX;
			}
			++layersCount;
		}
		if (arr[i].getType() == Point::LineEnd)
		{
			if (layersCount == 2)
			{
				oneLayerStartX = arr[i].getX();
			}
			if (layersCount == 1)
			{
				oneLayerLen += arr[i].getX() - oneLayerStartX;
			}
			--layersCount;
		}
	}

	return oneLayerLen;
}

///////////////////////main////////////////////////////
int main()
{
	size_t linesCount;
	cin >> linesCount;
	Array<Point> arr(linesCount * 2);

	size_t pIndex = 0;
	for (size_t i = 0; i < linesCount; ++i, pIndex += 2)
	{
		int L, R;
		cin >> L;
		cin >> R;
		assert(L < R);

		arr[pIndex] = Point(L, Point::LineStart);
		arr[pIndex + 1] = Point(R, Point::LineEnd);
	}

	cout << findOneLayerLength(arr);

	return EXIT_SUCCESS;
}