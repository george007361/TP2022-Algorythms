//2_4.Дан отсортированный массив различных целых чисел A[0..n - 1] 
//и массив целых чисел B[0..m - 1].Для каждого элемента массива B[i] 
//найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].
//Требования: Время работы поиска для каждого элемента B[i] : O(log(k)).
//Внимание!В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного
//поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать 
//бинарный поиск.
//
//n ≤ 110000, m ≤ 1000.


#include <iostream>

#include "Array.h"
using namespace std;


//int findClosestElementInArr(vector<int>& arr, int val);
//void expSearch(int& startIndex, int& endIndex, const vector<int>& arr, const int val);
//int binarySearch(const vector<int>& arr, const int val, const int startIndex, const int endIndex);

int main()
{
    //b = f();
    //int count, val;

    //vector<int> A;
    //cin >> count;
    //for (int i = 0; i < count; i++)
    //{
    //    cin >> val;
    //    A.push_back(val);
    //}

    //vector<int> B;
    //cin >> count;
    //for (int i = 0; i < count; i++)
    //{
    //    cin >> val;
    //    B.push_back(val);
    //}

    //for (int i = 0; i < B.size(); i++)
    //{
    //    cout << findClosestElementInArr(A, B[i]);
    //}


    return EXIT_SUCCESS;
}

//int findClosestElementInArr(const vector<int>& arr, const int val)
//{
//    int startIndex, endIndex;
//    expSearch(startIndex, endIndex, arr, val);
//    return binarySearch(arr, val, startIndex, endIndex);
//}
//
//void expSearch(int& startIndex, int& endIndex, const vector<int>& arr, const int val)
//{
//
//}
//
//int binarySearch(const vector<int> &arr, const int val, const int startIndex, const int endIndex)
//{
//
//}