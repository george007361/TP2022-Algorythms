//Требование для всех вариантов Задачи 4
//Решение должно поддерживать передачу функции сравнения снаружи.
//
//4_2.Порядковые статистики.Дано число N и N строк.Каждая строка содержит команду добавления или удаления 
//натуральных чисел, а также запрос на получение k - ой порядковой статистики.Команда добавления числа A 
//задается положительным числом A, команда удаления числа A задается отрицательным числом “ - A”.Запрос на 
//получение k - ой порядковой статистики задается числом k.
//Требования: скорость выполнения запроса - O(log n).

#include <iostream>
#include <cassert>

using namespace std;

template<typename T, class Comparator>
class AVLTree
{
public:
	// Constructor
	explicit AVLTree(const Comparator& cmp_) : cmp(cmp_), root(nullptr) {}

	// Destructor
	~AVLTree() { delete root; }

	// Copy
	AVLTree(const AVLTree&) = delete;
	AVLTree& operator=(const AVLTree&) = delete;

	// Move
	AVLTree(AVLTree&&);
	AVLTree& operator =(AVLTree&&);

	// Public methods
	void insert(const T& key) { root = _insert(root, key); }
	void remove(const T& key) { root = _remove(root, key); }
	const T& getMin() const { return _getMin(root)->key; }
	const T& findKStat(const size_t k) const;

protected:
	struct Node
	{
		Node(const T& key_) : key(key_), height(1), count(1), left(nullptr), right(nullptr) {}
		~Node()
		{
			delete left;
			delete right;
		}

		T key;
		unsigned char height;
		size_t count;
		Node* left;
		Node* right;
	};

	// Private methods

	// Subtree height
	unsigned char _getHeight(const Node* subtree) const { return subtree ? subtree->height : 0; }
	void _updateHeight(Node* subtree) { subtree->height = std::max(_getHeight(subtree->left), _getHeight(subtree->right)) + 1; }

	// Subtree count of nodes
	size_t _getCount(const Node* subtree) const { return subtree ? subtree->count : 0; }
	void _updateCount(Node* subtree) { subtree->count = 1 + _getCount(subtree->left) + _getCount(subtree->right); }

	// AVL subtree property
	int _getBalance(const Node* subtree) const { return _getHeight(subtree->right) - _getHeight(subtree->left); }
	Node* _updateBalance(Node* p);
	Node* _rotateR(Node* p);
	Node* _rotateL(Node* q);

	// Private methods
	Node* _getMin(Node* subtree) const { return subtree->left == nullptr ? subtree : _getMin(subtree->left); };
	Node* _insert(Node* p, const T& key);
	Node* _remove(Node* node, const T& key);

private:

	Node* root;
	Comparator cmp;
};

template<typename T, class Comparator>
AVLTree<T, Comparator>::AVLTree(AVLTree&& src)
{
	root = src->root;
	cmp = src->cmp;

	src->root = nullptr;
}

template<typename T, class Comparator>
AVLTree<T, Comparator>& AVLTree<T, Comparator>::operator=(AVLTree&& src)
{
	if (&src == this)
	{
		return *this;
	}
	~AVLTree();

	root = src->root;
	cmp = src->cmp;

	src->root = nullptr;

	return *this;
}

template<typename T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_rotateR(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	_updateHeight(p);
	_updateCount(p);
	_updateHeight(q);
	_updateCount(q);

	return q;
}

template<typename T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_rotateL(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	_updateHeight(q);
	_updateCount(q);
	_updateHeight(p);
	_updateCount(p);

	return p;
}

template<typename T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_updateBalance(Node* p)
{
	_updateHeight(p);
	_updateCount(p);

	if (_getBalance(p) == 2)
	{
		if (_getBalance(p->right) < 0)
		{
			p->right = _rotateR(p->right);
		}

		return _rotateL(p);
	}
	if (_getBalance(p) == -2)
	{
		if (_getBalance(p->left) > 0)
		{
			p->left = _rotateL(p->left);
		}

		return _rotateR(p);
	}

	return p;
}

template<typename T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_insert(Node* node, const T& key)
{
	if (!node)
	{
		return new Node(key);
	}
	else if (cmp(key, node->key) < 0)
	{
		node->left = _insert(node->left, key);
	}
	else
	{
		node->right = _insert(node->right, key);
	}

	return _updateBalance(node);
}

template<typename T, typename Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::_remove(Node* node, const T& key) {
	if (node == nullptr)
	{
		return nullptr;
	}

	if (cmp(key, node->key) < 0)
	{
		node->left = _remove(node->left, key);
	}
	else if (cmp(key, node->key) > 0)
	{
		node->right = _remove(node->right, key);
	}
	else {
		if (node->left == nullptr || node->right == nullptr)
		{
			Node* temp = node->left ? node->left : node->right;

			if (temp == nullptr)
			{
				temp = node;
				node = nullptr;
			}
			else
			{
				*node = *temp;
			}
			delete temp;
		}
		else
		{
			Node* temp = _getMin(node->right);
			node->key = temp->key;
			node->right = _remove(node->right, temp->key);
		}
	}

	if (node == nullptr)
	{
		return node;
	}

	return _updateBalance(node);
}

template<typename T, typename Comparator>
const T& AVLTree<T, Comparator>::findKStat(const size_t k) const
{
	assert(k < _getCount(root));
	Node* node = root;
	size_t pos = _getCount(root->left);

	while (pos != k)
	{
		if (k > pos)
		{
			node = node->right;
			pos += 1 + _getCount(node->left);
		}
		else
		{
			node = node->left;
			pos -= 1 + _getCount(node->right);
		}
	}

	return node->key;
}

class IntComparator
{
public:
	int operator() (const int& a, const int& b) { return a - b; }
};

int main()
{
	IntComparator cmp;
	AVLTree<int, IntComparator> tree(cmp);
	size_t N = 0, k = 0;
	int A = 0;

	cin >> N;

	for (size_t i = 0; i < N; ++i)
	{
		cin >> A >> k;

		if (A > 0)
		{
			tree.insert(A);
		}
		else if (A < 0)
		{
			tree.remove(std::abs(A));
		}
		else
		{
			assert(false);
		}

		cout << tree.findKStat(k) << endl;
	}

	return EXIT_SUCCESS;
}
