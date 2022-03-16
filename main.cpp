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

#include "Array.h"
#include "MinHeap.h"

using namespace std;

struct MinHeapElement
{
    Array<int>* arr;
    size_t index;
    MinHeapElement() : arr(nullptr), index(-1) { cout << "ctor elem: " << arr << endl; }
    MinHeapElement(Array<int>* arr, size_t index = 0) : arr(arr), index(index) { /*assert(arr != null);*/ }
    //MinHeapElement(const MinHeapElement&) = default;
    bool next();
};

int comrareElements(MinHeapElement& a, MinHeapElement& b)
{
    if ((*a.arr)[a.index] == (*b.arr)[b.index])
        return 0;
    return (*a.arr)[a.index] > (*b.arr)[b.index] ? 1 : -1;
}

Array<int> mergeArrays(Array<Array<int>>& arrays)
{
    size_t totalCount = 0;
    auto heapArray = Array<MinHeapElement>();

    for (size_t i = 0; i < arrays.getSize(); i++)
    {
        totalCount += arrays[i].getSize();
        heapArray.pushBack(MinHeapElement(&arrays[i]));
    }

    MinHeap<MinHeapElement> heap = MinHeap<MinHeapElement>(heapArray, comrareElements);
    auto merged = Array<int>(totalCount);

    for (size_t i = 0; i < totalCount; i++)
    {
        auto root = heap.peekMin();
        merged[i] = root
    }

    return Array<int>();
}

int main()
{

    int countOfArrays = 3;
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

    mergeArrays(arrays);
    return EXIT_SUCCESS;
}

bool MinHeapElement::next()
{
    ++index; 
    return index < arr->getSize() ? true : false;
}
