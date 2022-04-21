#include <cassert>
#include <iostream>

#include "Array.h"

using namespace std;

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

		int i, j, k;
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

class Line
{
public:
	Line() = default;
	Line(int l, int r) : _l(l), _r(r) {	assert(_l < _r); }
	Line(Line&&) = default;
	Line(const Line&) = default;
	Line& operator=(Line&&) = default;
	Line& operator=(const Line&) = default;

	static int cmpLeftDot(const Line& a, const Line& b) { return a._l - b._l; }
	static int findMaxRightDot(Array<Line>& arr);
	static void printLines(Array<Line>& arr);
	static size_t findOneLayerLength(Array<Line>& arr);
	
	int getL() const { return _l; };
	int getR() const { return _r; };
	void printLine() const;

private:
	int _l, _r;
};

void Line::printLines(Array<Line>& arr)
{
	cout << endl;
	for (int i = 0; i < arr.getSize(); ++i)
	{
		arr[i].printLine();
	}
	cout << endl;
}

void Line::printLine() const
{
	cout << "[ " << _l << " ; " << _r << " ]" << endl;
}

int Line::findMaxRightDot(Array<Line>& arr)
{
	assert(arr.getSize());
	int x = arr[0].getR();
	for (size_t i = 0; i < arr.getSize(); i++)
	{
		if (x < arr[i].getR())
		{
			x = arr[i].getR();
		}
	}
	return x;
}

size_t Line::findOneLayerLength(Array<Line>& arr)
{
	assert(arr.getSize());
	
	MergeSort<Line>::sort(arr, Line::cmpLeftDot);

	size_t oneLayerLen = 0;
	int layerCount = 0;
	int xMin = arr[0].getL();
	int xMax = Line::findMaxRightDot(arr);

	for (int x = xMin; x <= xMax; ++x)
	{
		for (size_t i = 0; i < arr.getSize(); ++i)
		{
			if (x == arr[i].getL())
			{
				++layerCount;
			}
			if (x == arr[i].getR())
			{
				--layerCount;
			}
		}
		if (layerCount == 1)
		{
			++oneLayerLen;
		}
	}
	
	return oneLayerLen;
}

int main()
{
	int linesCount;
	cin >> linesCount;
	Array<Line> arr(linesCount);

	for (int i = 0; i < arr.getSize(); ++i)
	{
		int start, end;
		cin >> start;
		cin >> end;
		arr[i] = Line(start, end);
	}

	cout << Line::findOneLayerLength(arr);

	return EXIT_SUCCESS;
}
