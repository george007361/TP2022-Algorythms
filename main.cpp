#include <cassert>
#include <iostream>

#include "Array.h"

using namespace std;

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

template<typename T>
class MergeSort
{
	MergeSort() = delete;
	MergeSort(MergeSort&&) = delete;
	MergeSort(const MergeSort&) = delete;
	MergeSort& operator=(MergeSort&&) = delete;
	MergeSort& operator=(const MergeSort&) = delete;

public:
	static void sort(Array<T>& arr, int (*pcmp)(const T&, const T&))
	{
		assert(pcmp);

		size_t currSubarraySize;
		size_t leftSubarrayStarts;

		for (currSubarraySize = 1; currSubarraySize <= arr.getSize() - 1; currSubarraySize *= 2)
		{
			for (leftSubarrayStarts = 0; leftSubarrayStarts < arr.getSize() - 1; leftSubarrayStarts += 2 * currSubarraySize)
			{
				size_t leftSubarrayEnds = min(leftSubarrayStarts + currSubarraySize - 1, arr.getSize() - 1);
				size_t rightSubarrayEnds = min(leftSubarrayStarts + 2 * currSubarraySize - 1, arr.getSize() - 1);
				merge(arr, leftSubarrayStarts, leftSubarrayEnds, rightSubarrayEnds, pcmp);
			}
		}
	}

private:
	static void merge(Array<T>& arr, size_t leftSubarrayStarts, size_t leftSubarrayEnds, size_t rightSubarrayEnds, int (*pcmp)(const T&, const T&))
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
};

size_t findOneLayerLength(Array<Point>& arr)
{
	assert(arr.getSize());
	
	MergeSort<Point>::sort(arr, Point::compare);

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
			if(layersCount == 1)
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

int main()
{
	int linesCount;
	cin >> linesCount;
	Array<Point> arr(linesCount * 2);
	
	for (size_t i = 0; i < arr.getSize(); ++i)
	{
		int x;
		cin >> x;
		arr[i] = Point(x, i % 2);
	}

	//Point::printPoints(arr);
	cout << findOneLayerLength(arr);
	//Point::printPoints(arr);
	
	return EXIT_SUCCESS;
}