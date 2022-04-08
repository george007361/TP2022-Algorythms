// RK1_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cassert>
#include <string>

using namespace std;


int findStartIndex(int* arr, int size)
{
	int a = 0,  b = size - 1;
	
	while (a < b)
	{
		if (arr[a] > arr[a + 1])
			return a + 1;
		if (arr[b] < arr[b - 1])
			return b;
		a++; b--;
	}

	return a;
}

int main()
{
	int size;
	cin >> size;
	int* arr = new int[size];
	for (int i = 0; i < size; i++)
	{
		cin >> arr[i];
	}

	cout << findStartIndex(arr, size);

	delete[] arr;
	return EXIT_SUCCESS;
}
