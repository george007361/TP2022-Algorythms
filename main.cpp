//Задача № 3 (4 балла)
//Во всех задачах из следующего списка следует написать структуру данных, обрабатывающую команды push* и pop* .
//Формат входных данных.
//В первой строке количество команд n.n ≤ 1000000.
//Каждая команда задаётся как 2 целых числа : a b.
//a = 1 - push front
//a = 2 - pop front
//a = 3 - push back
//a = 4 - pop back
//Команды добавления элемента 1 и 3 заданы с неотрицательным параметром b.
//Для очереди используются команды 2 и 3. Для дека используются все четыре команды.
//Если дана команда pop*, то число b - ожидаемое значение.Если команда pop вызвана для пустой структуры данных, то ожидается “ - 1”.
//Формат выходных данных.
//Требуется напечатать YES - если все ожидаемые значения совпали.Иначе, если хотя бы одно ожидание не оправдалось, то напечатать NO.
//
//3_1.Реализовать очередь с динамическим зацикленным буфером.
//Требования: Очередь должна быть реализована в виде класса.
//

#include <cassert>
#include <iostream>

using namespace std;

enum
{
	POPFRONT = 2,
	PUSHBACK = 3,
};

template<typename T>
class Queue
{
public:
	Queue() : buffer_(nullptr), size_(0), capacity_(0), first_(0) {};
	~Queue();

	// перенос
	Queue<T>(Queue<T>&& srcQ);
	Queue<T>& operator = (Queue<T>&& srcQ);

	// Копирование
	Queue<T>(const Queue<T>& srcQ) = delete;
	Queue<T>& operator = (const Queue<T>& srcQ) = delete;

	// Функции
	bool isEmpty() const { return size_ == 0; }
	void pushBack(const T& elem);
	T popFront();

private:
	void expand();
	void reduce();

private:
	T* buffer_;
	size_t size_, capacity_, first_;
};

template<typename T>
Queue<T>::Queue(Queue<T>&& srcQ) : size_(srcQ.size_), capacity_(srcQ.capacity_), first_(srcQ.first_), buffer_(srcQ.buffer_)
{
	srcQ.capacity_ = srcQ.size_ = srcQ.first_ = 0;
	srcQ.buffer_ = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
	if (buffer_)
	{
		delete[] buffer_;
	}
	buffer_ = nullptr;
	size_ = capacity_ = first_ = 0;
}

template<typename T>
void Queue<T>::expand()
{
	size_t  newCapacity = capacity_ ? capacity_ * 2 : 1;
	T* newBuffer = new T[newCapacity];

	for (size_t i = 0; i < size_; ++i)
	{
		newBuffer[i] = buffer_[(first_ + i) % capacity_];
	}
	capacity_ = newCapacity;
	first_ = 0;
	if (buffer_)
	{
		delete[] buffer_;
	}
	buffer_ = newBuffer;
}

template<typename T>
void Queue<T>::reduce()
{
	if(capacity_ < 2)
	{
		return;
	}

	size_t  newCapacity = capacity_ / 2;
	T* newBuffer = new T[newCapacity];

	for (size_t i = 0; i < size_; ++i)
	{
		newBuffer[i] = buffer_[(first_ + i) % capacity_];
	}

	capacity_ = newCapacity;
	first_ = 0;
	if (buffer_)
	{
		delete[] buffer_;
	}
	buffer_ = newBuffer;
}

template<typename T>
Queue<T>& Queue<T>::operator = (Queue<T>&& srcQ)
{
	if (&srcQ == this)
	{
		return *this;
	}

	~Queue();

	size_ = srcQ.size_;
	capacity_ = srcQ.capacity_;
	first_ = srcQ.first_;
	buffer_ = srcQ.buffer_;

	srcQ.capacity_ = srcQ.size_ = srcQ.first_ = 0;
	srcQ.buffer_ = nullptr;

	return *this;
}

template<typename T>
void Queue<T>::pushBack(const T& elem)
{
	if (size_ == capacity_)
	{
		expand();
	}
	buffer_[(first_ + size_) % capacity_] = elem;
	++size_;
}

template<typename T>
T Queue<T>::popFront()
{
	assert(!isEmpty());

	T elem = buffer_[first_];
	first_ = (first_ + 1) % capacity_;
	--size_;
	if (size_ * 2 <= capacity_)
	{
		reduce();
	}

	return elem;
}

int main()
{
	int countOfCommands;
	cin >> countOfCommands;

	int a;
	bool result = true;
	Queue<int> que;

	for (int i = 0; result && i < countOfCommands; ++i)
	{
		cin >> a;
		int b;
		cin >> b;

		switch (a)
		{
		default:
			break;
		case POPFRONT:
		{
			if (!que.isEmpty())
			{
				result = (b == que.popFront());
			}

			break;
		}
		case PUSHBACK:
		{
			que.pushBack(b);

			break;
		}
		}
	}

	cout << (result ? "YES" : "NO");

	return EXIT_SUCCESS;
}
