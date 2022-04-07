// Дано множество целых чисел из [0..10^9] размера n. 
// Используя алгоритм поиска k-ой порядковой статистики, требуется найти следующие параметры множества:
// 10%  перцентиль
// медиана
// 90%  перцентиль

// Требования: к дополнительной памяти: O(n). 
// Среднее время работы: O(n)
// Должна быть отдельно выделенная функция partition. 
// Рекурсия запрещена. 
// Решение должно поддерживать передачу функции сравнения снаружи.


// Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. 
// Описание для случая прохода от начала массива к концу:
// Выбирается опорный элемент. Опорный элемент меняется с последним элементом массива.
// Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. 
// Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. 
// Последним элементом лежит опорный.
// Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
// Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
// Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j.
// Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
// В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.

// 6_1. Реализуйте стратегию выбора опорного элемента “медиана трёх”. 
// Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.

#include <cassert>
#include <iostream>

using namespace std;

int cmpInt(const int& a, const int& b)
{
	if (a == b)
		return 0;
	return a < b ? 1 : -1;
}

template<typename T>
void swapper(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<typename T>
int medianOfThree(const T* arr, const int left, const int right, int (*pcmp)(const T&, const T&)) // Выбрать средний по значению элемент из трёх (1, последнего, среднего)
{
	int mid = (left + right) / 2;

	if ((pcmp(arr[left], arr[mid]) <= 0 && pcmp(arr[mid], arr[right]) <= 0) || (pcmp(arr[right], arr[mid]) <= 0 && pcmp(arr[mid], arr[left]) <= 0))
	{
		return mid;
	}
	else if ((pcmp(arr[mid], arr[left]) <= 0 && pcmp(arr[left], arr[right]) <= 0) || (pcmp(arr[mid], arr[left]) <= 0 && pcmp(arr[left], arr[right]) <= 0))
	{
		return left;
	}
	else
	{
		return  right;
	}
}

template<typename T>
int partition(T* arr, const int startIndex, const int endIndex, int (*pcmp)(const T&, const T&))
{
	assert(arr);
	if (endIndex - startIndex + 1 <= 1)
	{
		return startIndex;
	}

	int pivotIndex = medianOfThree(arr, startIndex, endIndex, pcmp);
	swapper(arr[endIndex], arr[pivotIndex]);

	const T& pivot = arr[endIndex];

	int i = startIndex;
	int j = startIndex;

	while (j < endIndex)
	{
		if (pcmp(arr[j], pivot) >= 0)
		{
			swapper(arr[i], arr[j]);
			++i;
		}
		++j;
	}
	swapper(arr[j], arr[i]); // Меняем pivot и первый элемент > pivot местами, т.е. i укажет индекс пивота после разделения

	return i;
}

template<typename T>
T& findKStat(T* arr, const int startIndex, const int endIndex, const int k, int (*pcmp)(const T&, const T&))
{
	assert(k >= 0 && k <= endIndex - startIndex);

	int pivotIndex = -1, leftIndex = startIndex, rightIndex = endIndex;
	while (true)
	{
		pivotIndex = partition(arr, leftIndex, rightIndex, pcmp);
		if (pivotIndex == k)
		{
			break;
		}

		if (k < pivotIndex)
		{
			// Смотрим левую часть
			rightIndex = pivotIndex - 1;
		}
		else
		{
			// Смотрим правую часть
			leftIndex = pivotIndex + 1;
		}
	}

	assert(pivotIndex != -1);

	return arr[pivotIndex];
}

template<typename T>
T& findMedian(T* arr, const int startIndex, const int endIndex, int (*pcmp)(const T&, const T&))
{
	assert(arr);
	assert(pcmp);

	return findKStat(arr, startIndex, endIndex, (endIndex - startIndex + 1) / 2, pcmp);
}

template<typename T>
T& findPercentile(T* arr, const int startIndex, const int endIndex, const int percentile, int (*pcmp)(const T&, const T&))
{
	assert(percentile >= 0 && percentile <= 100);
	assert(arr && pcmp);

	int k = (float)(endIndex + 1 - startIndex) / (float)100 * (float)percentile;

	return findKStat(arr, startIndex, endIndex, k, pcmp);
}


int main()
{
	int count;
	cin >> count;
	assert(count > 0);

	int* arr = new int[count];

	for (int i = 0; i < count; i++)
	{
		cin >> arr[i];
	}

	cout << findPercentile(arr, 0, count - 1, 10, cmpInt) << endl;

	cout << findMedian(arr, 0, count - 1, cmpInt) << endl;

	cout << findPercentile(arr, 0, count - 1, 90, cmpInt) << endl;

	delete[] arr;

	return EXIT_SUCCESS;
}
