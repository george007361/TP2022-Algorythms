// C ++ программа для объединения k отсортированных массивов размером n каждый.
#include<iostream>
#include<limits.h>

using namespace std;


#define n 4

// Узел минимальной кучи

struct MinHeapNode

{

	int element; // Элемент, который будет сохранен

	int i; // индекс массива, из которого взят элемент

	int j; // индекс следующего элемента, который будет выбран из массива

};


// Прототип служебной функции для замены двух минимальных узлов кучи

void swap(MinHeapNode* x, MinHeapNode* y);


// Класс для Min Heap

class MinHeap

{

	MinHeapNode* harr; // указатель на массив элементов в куче

	int heap_size; // размер кучи мин

public:

	// Конструктор: создает минимальную кучу заданного размера

	MinHeap(MinHeapNode a[], int size);



	// сложить поддерево с корнем по заданному индексу

	void MinHeapify(int);



	// получить индекс левого потомка узла по индексу i

	int left(int i) { return (2 * i + 1); }



	// получить индекс правого потомка узла по индексу i

	int right(int i) { return (2 * i + 2); }



	// чтобы получить рут

	MinHeapNode getMin() { return harr[0]; }



	// заменить корень новым узлом x и heapify () новым корнем

	void replaceMin(MinHeapNode x) { harr[0] = x;  MinHeapify(0); }

};


// Эта функция принимает массив массивов в качестве аргумента и
// Предполагается, что все массивы отсортированы. Это объединяет их
// и выводит окончательный отсортированный вывод.

int* mergeKArrays(int arr[][n], int k)

{

	int* output = new int[n * k];  // Для сохранения выходного массива



	// Создать минимальную кучу с k узлами кучи. Каждый узел кучи

	// имеет первый элемент массива

	MinHeapNode* harr = new MinHeapNode[k];

	for (int i = 0; i < k; i++)

	{

		harr[i].element = arr[i][0]; // Сохраняем первый элемент

		harr[i].i = i;  // индекс массива

		harr[i].j = 1;  // Индекс следующего элемента, который будет сохранен из массива

	}

	MinHeap hp(harr, k); // Создать кучу



	// Теперь один за другим получаем минимальный элемент из min

	// куча и заменить его следующим элементом массива

	for (int count = 0; count < n * k; count++)

	{

		// Получить минимальный элемент и сохранить его на выходе

		MinHeapNode root = hp.getMin();

		output[count] = root.element;



		// Найти следующий элемент, который заменит текущий

		// корень кучи. Следующий элемент принадлежит тому же

		// массив в качестве текущего корня.

		if (root.j < n)

		{

			root.element = arr[root.i][root.j];

			root.j += 1;

		}

		// Если корень был последним элементом своего массива

		else root.element = INT_MAX; // INT_MAX для бесконечного



		// Заменить корень на следующий элемент массива

		hp.replaceMin(root);

	}



	return output;

}


// СЛЕДУЮЩИЕ РЕАЛИЗАЦИИ СТАНДАРТНЫХ МЕТОДОВ MIN MIN HEAP
// ИЗ КОРМЕНСКОЙ КНИГИ
// Конструктор: строит кучу из заданного массива a [] заданного размера

MinHeap::MinHeap(MinHeapNode a[], int size)

{

	heap_size = size;

	harr = a;  // сохранить адрес массива

	int i = (heap_size - 1) / 2;

	while (i >= 0)

	{

		MinHeapify(i);

		i--;

	}

}


// Рекурсивный метод, чтобы накапливать поддерево с корнем по заданному индексу
// Этот метод предполагает, что поддеревья уже сложены

void MinHeap::MinHeapify(int i)

{

	int l = left(i);

	int r = right(i);

	int smallest = i;

	if (l < heap_size && harr[l].element < harr[i].element)

		smallest = l;

	if (r < heap_size && harr[r].element < harr[smallest].element)

		smallest = r;

	if (smallest != i)

	{

		swap(&harr[i], &harr[smallest]);

		MinHeapify(smallest);

	}

}


// Утилита для замены двух элементов

void swap(MinHeapNode* x, MinHeapNode* y)

{

	MinHeapNode temp = *x;  *x = *y;  *y = temp;

}


// Утилита для печати элементов массива

void printArray(int arr[], int size)

{

	for (int i = 0; i < size; i++)

		cout << arr[i] << " ";

}


// Программа драйвера для проверки вышеуказанных функций

int main_old()

{

	// Изменить n вверху, чтобы изменить количество элементов

	// в массиве

	int arr[][n] = { {2, 6, 12, 34},

					 {1, 9, 20, 1000},

					 {23, 34, 90, 2000} };

	int k = sizeof(arr) / sizeof(arr[0]);



	int* output = mergeKArrays(arr, k);



	cout << "Merged array is " << endl;

	printArray(output, n * k);



	return 0;

}