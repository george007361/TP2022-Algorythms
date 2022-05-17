// Задача 3. B-дерево (4 балла)

// Постройте B-дерево минимального порядка _t и выведите его по слоям.
// В качестве ключа используются числа, лежащие в диапазоне 0..232 -1

// Требования: 
// B-дерево должно быть реализовано в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.

// Формат входных данных
// Сначала вводится минимальный порядок дерева _t.
// Затем вводятся элементы дерева.

// Формат выходных данных
// Программа должна вывести B-дерево по слоям. Каждый слой на новой строке, элементы должны выводится
//  в том порядке, в котором они лежат в узлах.

#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <string>
#include <cstring>

using namespace std;

template<typename T, class Comparator>
class BTree
{
public:
	BTree(const size_t _t, const Comparator& cmp) : _t(_t), _cmp(cmp), _root(nullptr) {}
	~BTree() { delete _root; }

	BTree(const BTree&) = delete;
	BTree& operator = (const BTree&) = delete;

	BTree(BTree&& src);
	BTree& operator = (BTree&& src);

	void insert(const T& key);
	void levelOrder(ostream& os);
	size_t levelCount();

private:
	struct Node
	{
		Node(const bool _isLeaf) : isLeaf(_isLeaf) {}
		~Node() {
			for (Node *child : children) {
				delete child;
			}
		}
		bool isLeaf;
		vector<T> keys;
		vector<Node*> children;
	};

	Node* _root;
	size_t _t;
	Comparator _cmp;

private:
	bool isFullNode(Node* node) const { return node->keys.size() == 2 * _t - 1; }
	void insertNotFull(Node* node, const T& key);
	void splitChild(Node* X, long index);
};

template<typename T, class Comparator>
BTree<T, Comparator>::BTree(BTree&& src)
{
	_t = src._t;
	_root = src._root;
	_cmp = src._cmp;
}
template<typename T, class Comparator>

BTree<T, Comparator>& BTree<T, Comparator>::operator = (BTree&& src)
{
	if (this == &src)
	{
		return *this;
	}
	_t = src._t;
	_root = src._root;
	_cmp = src._cmp;

	return *this;
}

template<typename T, class Comparator>
void BTree<T, Comparator>::insert(const T& key)
{
	if (!_root)
	{
		_root = new Node(true);
		_root->keys.push_back(key);
		return;
	}
	if (isFullNode(_root))
	{
		Node* newRoot = new Node(false);
		newRoot->children.push_back(_root);
		_root = newRoot;
		splitChild(_root, 0);
	}
	insertNotFull(_root, key);
}

template<typename T, class Comparator>
void BTree<T, Comparator>::levelOrder(ostream& os)
{
	vector<int> counts(levelCount());
	memset(&counts[0], 0, counts.size() * sizeof(int));

	queue<Node*> que;
	
	size_t currentLevel = 0;

	counts[currentLevel] = 1;
	que.push(_root);

	while (!que.empty())
	{
		Node* node = que.front();
		que.pop();

		for (size_t i = 0; i < node->keys.size(); ++i)
		{
			os << node->keys[i] << " ";
		}

		for (size_t i = 0; i < node->children.size(); ++i)
		{
			que.push(node->children[i]);
			++counts[currentLevel + 1];
		}

		if ((--counts[currentLevel]) == 0)
		{
			++currentLevel;
			os << endl;
		}
	}
}

template<typename T, class Comparator>
size_t BTree<T, Comparator>::levelCount()
{
	size_t count = 0;
	Node* node = _root;
	while (!node->isLeaf)
	{
		++count;
		node = node->children[0];
	}
	return ++count;
}


template<typename T, class Comparator>
void BTree<T, Comparator>::insertNotFull(Node* node, const T& key)
{
	if (node->isLeaf)
	{
		long index = node->keys.size() - 1;
		node->keys.resize(node->keys.size() + 1);
		while (index >= 0 && _cmp(key, node->keys[index]) < 0)
		{
			node->keys[index + 1] = node->keys[index];
			--index;
		}
		node->keys[index + 1] = key;
	}
	else
	{
		long index = node->keys.size() - 1;
		while (index >= 0 && _cmp(key, node->keys[index]) < 0)
		{
			--index;
		}
		if (isFullNode(node->children[index + 1]))
		{
			splitChild(node, index + 1);
			if (_cmp(key, node->keys[index + 1]) > 0)
			{
				++index;
			}
		}
		insertNotFull(node->children[index + 1], key);
	}
}

template<typename T, class Comparator>
void BTree<T, Comparator>::splitChild(Node* X, long index)
{
	Node *Y = X->children[index];
	Node *Z = new Node(Y->isLeaf);

	Z->keys.resize(_t - 1);
	for (long i = _t - 2; i >= 0; i--)
	{
		Z->keys[i] = Y->keys[_t + i];
		Y->keys.erase(Y->keys.begin() + (_t + i));
	}
	
	if (!Y->isLeaf)
	{
		Z->children.resize(_t);
		for (long i = _t - 1; i >= 0; --i)
		{
			Z->children[i] = Y->children[_t + i];
			Y->children.erase(Y->children.begin() + (_t + i));
		}
	}

 	X->children.resize( X->children.size() + 1);
	for (long i = X->children.size() - 2; i >= index + 1; --i)
	{
		X->children[i + 1] = X->children[i];
	}
	X->children[index + 1] = Z;

	X->keys.resize( X->keys.size() + 1);
	for (long i = X->keys.size() - 2; i >= index; --i)
	{
		X->keys[i + 1] = X->keys[i];
	}

	X->keys[index] = Y->keys[_t - 1];
	Y->keys.erase(Y->keys.begin() + _t - 1);
}

class IntComparator
{
public:
	int operator()(const int& a, const int& b)
	{
		return a - b;
	}
};

int main()
{
	IntComparator cmp;
	size_t t;

	cin >> t;

	BTree<int, IntComparator> tree(t, cmp);

	while (!cin.eof()) {
		string str;
		cin >> str;
		if (!str.empty())
		{
			tree.insert(stoi(str));
		}
	}

	tree.levelOrder(cout);

	return EXIT_SUCCESS;
}
