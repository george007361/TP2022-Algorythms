#pragma once

#include <cassert>
#include <iostream>
using namespace std;

template<typename T>
class Array
{
public:
    // Конструкоторы
    Array<T>() : arr(nullptr), size(0), capacity(0) { cout << "ctor: " << arr << endl; }
    Array<T>(size_t size_) : size(size_), capacity(size_), arr(new T[size_]) { cout << "ctor: " << arr << endl; }
    
    // Функции
    T getLast() const { return arr[size - 1]; }
    void deleteLast() { --size; }
    size_t getSize() const { return this->size; }
    bool isEmpty() const { return this->size > 0 ? true : false; }
    void pushBack(const T& elem);
    void reallocArray(const size_t newSize);
    T& operator [](size_t index);

    // Деструктор
    ~Array();

    //Перенос
    Array(Array&& srcArr);
    Array<T>& operator = (Array<T>&& srcArr);

    //Копирование
    Array(const Array& srcArr);
    Array<T>& operator = (const Array& srcArr);

private:
    void extendArray();

private:
    T* arr;
    size_t size;
    size_t capacity;
};


// Деструктор
template<typename T>
Array<T>::~Array()
{
    if (arr)
        delete[] arr;
    arr = nullptr;
    size = capacity = 0;

    cout << "dtor: " << arr << endl;
}

// Копирование
template<typename T>
Array<T>::Array(const Array& srcArr)
{
    this->size = srcArr.size;
    this->capacity = srcArr.capacity;
    this->arr = new T[this->capacity];

    for (size_t i = 0; i < size; i++)
    {
        this->arr[i] = srcArr.arr[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& srcArr)
{
    this->size = srcArr.size;
    this->capacity = srcArr.capacity;
    this->arr = new T[this->capacity];

    for (size_t i = 0; i < size; i++)
    {
        this->arr[i] = srcArr.arr[i];
    }
    return *this;
}

//Перенос
template<typename T>
Array<T>& Array<T>::operator=(Array&& srcArr)
{
    if (&srcArr == this)
        return *this;

    ~Array();

    this->size = srcArr.size;
    this->arr = srcArr.arr;
    this->capacity = srcArr.capacity;

    srcArr.size = srcArr.capacity = 0;

    return *this;
}

template<typename T>
Array<T>::Array(Array<T>&& srcArr)
{
    this->arr = srcArr.arr;
    this->size = srcArr.size;
    this->capacity = srcArr.capacity;

    srcArr.arr = nullptr;
    srcArr.capacity = srcArr.size = 0;
}

// Функции
template<typename T>
void Array<T>::pushBack(const T& elem)
{
    if (size == capacity)
        extendArray();
    arr[size++] = elem;
}

template<typename T>
T& Array<T>::operator[](size_t index)
{
    assert(index >= 0 && index < size);
    return arr[index];
}

template<typename T>
void Array<T>::extendArray()
{
    T* newArr = new T[capacity = capacity ? capacity *= 2 : 1];
    for (size_t i = 0; i < size; i++)
    {
        newArr[i] = arr[i];
    }
    if (arr)
        delete arr;
    arr = newArr;
}

template<typename T>
void Array<T>::reallocArray(const size_t newSize)
{
    if (arr)
        delete[] arr;
    arr = new T[newSize];
    capacity = size = newSize;
}