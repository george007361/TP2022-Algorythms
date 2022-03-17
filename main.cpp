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
#include "Array.h"
#include "MinHeap.h"
using namespace std;

struct MinHeapElement
{
public:
	Array<int>* pArr; // указатель на массив
	size_t index; // текущий "первый" элемент, смещение
public:
	MinHeapElement() : pArr(nullptr), index(-1) {}
	MinHeapElement(Array<int>* arr, size_t index = 0) : pArr(arr), index(index) {}

	bool next(); // перейти к следущему элементу 
	int getElem(); // достать текущий элемент
};

int comrareElements(MinHeapElement& a, MinHeapElement& b)
{
	if ((*a.pArr)[a.index] == (*b.pArr)[b.index])
		return 0;
	return (*a.pArr)[a.index] > (*b.pArr)[b.index] ? 1 : -1;
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

	auto heap = MinHeap<MinHeapElement>(heapArray, comrareElements); // куча, в корне - самый маленький элемент

	auto merged = Array<int>(totalCount); // выходной массив

	for (size_t i = 0; i < totalCount; i++) // перебираем все элементы
	{
		auto minElem = heap.peekMin(); // Достаём меньший элемент из кучи, т.е. самый маленький из соединяемых массивов.
		merged[i] = minElem.getElem(); // переносим в выходной массив
		if (minElem.next()) // если в массиве, из которого достали элемент, еще есть элементы, вставляем следущий в кучу
			heap.replaceMin(minElem);
		else
			heap.exctractMin();
	}

	return merged;
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

	auto merged = mergeArrays(arrays);
	
	for (size_t i = 0; i < merged.getSize(); i++)
	{
		cout << merged[i] << " ";
	}
	cout << endl;

	return EXIT_SUCCESS;
}

bool MinHeapElement::next()
{
	assert(pArr != nullptr);
	++index;
	return index < pArr->getSize() ? true : false;
}

int MinHeapElement::getElem()
{
	assert(pArr != nullptr);
	return (*pArr)[index];
}
