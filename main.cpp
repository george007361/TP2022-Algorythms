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

#include <iostream>

using namespace std;

enum
{
	POPFRONT = 2,
	PUSHBACK = 3,
};

class Queue
{
public:
	Queue() : buffer_(nullptr), size_(0), capacity_(0), first_(0) {};
	~Queue();
	void pushBack(int elem);
	int popFront();
private:
	void expand();
	void reduce();
private:
	int *buffer_;
	size_t size_, capacity_, first_;
};

Queue::~Queue()
{
	if (buffer_)
	{
		delete[] buffer_;
	}
}

void Queue::pushBack(int elem)
{
	if (size_ == capacity_)
	{
		expand();
	}
	buffer_[(first_ + size_) % capacity_] = elem;
	++size_;
}

int Queue::popFront()
{
	int elem = -1;
	if (size_)
	{
		elem = buffer_[first_];
		first_ = (first_ + 1) % capacity_;
		--size_;
		if (size_ >= 2 * capacity_)
		{
			reduce();
		}
	}
	return elem;
}

void Queue::expand()
{
	size_t  newCapacity = capacity_ ? capacity_ * 2 : 1;
	int* newBuffer = new int[newCapacity];

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

void Queue::reduce()
{
	size_t  newCapacity = capacity_ ? capacity_ / 2 : 1;
	int* newBuffer = new int[newCapacity];

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

int main()
{
	int countOfCommands;
	cin >> countOfCommands;
	
	int a;
	bool result = true;
	auto que = Queue();

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
			if (b != que.popFront())
			{
				result = false;
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
