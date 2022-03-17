#pragma once

#include <cassert>

template<typename T>
class Array
{
public:
    // �������������
    Array<T>() : arr_(nullptr), size_(0), capacity_(0) {}
    Array<T>(const size_t size) : size_(size), capacity_(size), arr_(new T[size]) {}
    
    // ����������
    ~Array();

    //�������
    Array(Array&& srcArr);
    Array<T>& operator = (Array<T>&& srcArr);

    //�����������
    Array(const Array& srcArr);
    Array<T>& operator = (const Array& srcArr);
    
    // ���������
    T& operator [](const size_t index);

    // �������
    bool isEmpty() const { return this->size_ > 0 ? false : true; }
    T getLast() const { return arr_[size_ - 1]; }
    size_t getSize() const { return this->size_; }
    void pushBack(const T& elem);
    void deleteLast() { --size_; }
    void reallocArray(const size_t newSize);

private:
    void extendArray();

private:
    T* arr_;
    size_t size_;
    size_t capacity_;
};


// ����������
template<typename T>
Array<T>::~Array()
{
    if (arr_)
        delete[] arr_;
    arr_ = nullptr;
    size_ = capacity_ = 0;

    //cout << "dtor: " << arr_ << endl;
}

// �����������
template<typename T>
Array<T>::Array(const Array& srcArr)
{
    this->size_ = srcArr.size_;
    this->capacity_ = srcArr.capacity_;
    this->arr_ = new T[this->capacity_];

    for (size_t i = 0; i < size_; i++)
    {
        this->arr_[i] = srcArr.arr_[i];
    }
}

template<typename T>
Array<T>& Array<T>::operator=(const Array& srcArr)
{
    this->size_ = srcArr.size_;
    this->capacity_ = srcArr.capacity_;
    this->arr_ = new T[this->capacity_];

    for (size_t i = 0; i < size_; i++)
    {
        this->arr_[i] = srcArr.arr_[i];
    }
    return *this;
}

//�������
template<typename T>
Array<T>& Array<T>::operator=(Array&& srcArr)
{
    if (&srcArr == this)
        return *this;

    ~Array();

    this->size_ = srcArr.size_;
    this->arr_ = srcArr.arr_;
    this->capacity_ = srcArr.capacity_;

    srcArr.size_ = srcArr.capacity_ = 0;

    return *this;
}

template<typename T>
Array<T>::Array(Array<T>&& srcArr)
{
    this->arr_ = srcArr.arr_;
    this->size_ = srcArr.size_;
    this->capacity_ = srcArr.capacity_;

    srcArr.arr_ = nullptr;
    srcArr.capacity_ = srcArr.size_ = 0;
}

// �������
template<typename T>
void Array<T>::pushBack(const T& elem)
{
    if (size_ == capacity_)
        extendArray();
    arr_[size_++] = elem;
}

template<typename T>
T& Array<T>::operator[](const size_t index)
{
    assert(index >= 0 && index < size_);
    return arr_[index];
}

template<typename T>
void Array<T>::extendArray()
{
    T* newArr = new T[capacity_ = capacity_ ? capacity_ *= 2 : 1];
    for (size_t i = 0; i < size_; i++)
    {
        newArr[i] = arr_[i];
    }
    if (arr_)
        delete arr_;
    arr_ = newArr;
}

template<typename T>
void Array<T>::reallocArray(const size_t newSize)
{
    if (arr_)
        delete[] arr_;
    arr_ = new T[newSize];
    capacity_ = size_ = newSize;
}