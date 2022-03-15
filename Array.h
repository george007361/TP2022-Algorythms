#pragma once

#include <cassert>

template<typename T>
class Array
{
public:
    // Конструкоторы
    Array<T>() : arr(nullptr), size(0), capacity(0) {}
    Array<T>(size_t size_) : size(size_), capacity(size_), arr(new T[size_]){ }

    // Функции
    size_t sizeArray() { return this->size; }
    void pushBack(T elem);
    T& operator [](size_t index);

    // Деструктор
    ~Array<T>();

    //Перенос
    Array<T>(Array<T>&& srcArr);
    Array<T>& operator = (Array<T>&& srcArr);

    //Копирование
    Array<T>(const Array<T>& srcArr);

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
    delete arr;
    arr = nullptr;
    size = capacity = 0;
}

// Копирование
template<typename T>
Array<T>::Array(const Array<T>& srcArr)
{
    this->size = srcArr.size;
    this->capacity = srcArr.capacity;
    this->arr = new T[this->capacity];

    for (size_t i = 0; i < size; i++)
    {
        this->arr[i] = srcArr.arr[i];
    }
}

//Перенос
template<typename T>
Array<T>& Array<T>::operator=(Array<T>&& srcArr)
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
void Array<T>::pushBack(T elem)
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
    if (arr)
        delete arr;
    arr = newArr;
}