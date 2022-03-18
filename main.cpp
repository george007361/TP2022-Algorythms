#include <iostream>
#include <cassert>

using namespace std;

int cmpInt(const int a, const int b)
{
    if (a == b)
        return 0;
    return a < b ? 1 : -1;
}

template<typename T>
void swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
int medianOfThree(const T* arr, const int left, const int right, int (*pcmp)(T&, T&)) // Выбрать средний по значению элемент из трёх (1, последнего, среднего)
{ 
    int mid = (left + right) / 2;
    if ( ( pcmp(arr[mid], arr[left]) <= 0 && pcmp(arr[left], arr[right]) <= 0 ) || ( pcmp(arr[mid], arr[right]) >= 0 && pcmp(arr[left], arr[right]) >= 0 ) )
    {
        return left;
    }
    else if ( ( pcmp(arr[mid], arr[left]) >= 0 && pcmp(arr[mid], arr[right]) ) <= 0 || ( pcmp(arr[mid], arr[right]) >= 0 && pcmp(arr[mid], arr[left]) <= 0 ) )
    {
        return mid;
    }
    else
    {
        return right;
    }
}

int partition(int *arr, const int startIndex, const int endIndex)
{
    int pivotIndex = medianOfThree(arr, startIndex, endIndex);
    swap(arr[endIndex], arr[pivotIndex]);

    int pivot = arr[pivotIndex];
    int i = startIndex;
    int j = startIndex;

    while (j < endIndex)
    {
        if (arr[j] <= pivot)
        {
            swap(arr[i], arr[j]);
            ++i;
        }
        ++j;
    }
    swap(arr[j], arr[i]); // Меняем pivot и первый элемент > pivot местами, т.е. i укажет индекс пивота после разделения
    return i;
}

int findKStat(int* arr, const int startIndex, const int endIndex, const int k)
{
    int pivotIndex = -1, leftIndex = startIndex, rightIndex = endIndex;
    while (true)
    {
        pivotIndex = partition(arr, leftIndex, rightIndex);
        if (pivotIndex == k) // Если нашли позицию, то выходим
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


int findMedian(int* arr, const int startIndex, const int endIndex)
{
    if ((endIndex - startIndex + 1) % 2 == 1)
    {
        return findKStat(arr, len(l) / 2, pivot_fn)
    }
    else
    {
        return 0.5 * (quickselect(l, len(l) / 2 - 1, pivot_fn) +
            quickselect(l, len(l) / 2, pivot_fn))
    }
}

int main()
{
    int arr[] = { 3, 2, 6, 0, 2, 3 };
    cout << findKStat(arr, 0, 5, 5);

    return EXIT_SUCCESS;
}
