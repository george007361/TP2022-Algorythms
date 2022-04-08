// RK1_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cassert>
#include <string>

using namespace std;

template<typename T>
class stack
{
public:
	stack() : top(0) {}
	~stack();
	stack(const stack<T>&) = delete;
	stack& operator=(const stack<T>&) = delete;
	stack(stack<T>&&) = delete;
	stack& operator=(stack<T>&&) = delete;
	void push(const T& data);
	T pop();
	bool isEmpty() { return top ? false : true; };

private:
	struct Node
	{
		T data;
		Node* next;
	};
	Node* top;
};

template<typename T>
stack<T>::~stack()
{
	while (top)
	{
		Node* work = top;
		top = top->next;
		delete work;
	}
}


template<typename T>
void stack<T>::push(const T& data)
{
	Node* work = new Node;
	work->data = data;
	work->next = top;
	top = work;
}

template<typename T>
T stack<T>::pop()
{
	assert(!isEmpty());
	Node* work = top;
	top = top->next;
	T data = work->data;
	delete work;
	return data;
}

bool isCorrect(string& str)
{
	stack<char> st;

	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == '(')
		{
			st.push(str[i]);
		}
		if (str[i] == ')')
		{
			if (st.isEmpty())
				return false;
			else
				st.pop();
		}
	}
	return st.isEmpty() ? true : false;
}

int main()
{
	string str;
	cin >> str;

	cout << (isCorrect(str) ? "YES" : "NO");

	return EXIT_SUCCESS;
}
