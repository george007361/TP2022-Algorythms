// Задача 2. Порядок обхода (4 балла)
// Обязательная задача
// Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K 
// добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
// 2_3. Выведите элементы в порядке post-order (снизу вверх).

#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

template<typename T, typename Comparator>
class BinaryTree
{
public:
	explicit BinaryTree(const Comparator& comp) : cmp(comp), root(nullptr) {};
	~BinaryTree();

	BinaryTree(const BinaryTree&) = delete;
	BinaryTree& operator =(const BinaryTree&) = delete;
	BinaryTree(BinaryTree&&);
	BinaryTree& operator = (BinaryTree&&);

	void insert(const T& key);
	void postOrderPrint() const;


private:
	struct BinaryTreeNode
	{
		T key;
		BinaryTreeNode* parent;
		BinaryTreeNode* left;
		BinaryTreeNode* right;
		BinaryTreeNode(const T& key_, BinaryTreeNode* parent_) : key(key_), left(nullptr), right(nullptr), parent(parent_) {}
		~BinaryTreeNode()
		{
			if (left)
			{
				delete left;
				left = nullptr;
			}
			if (right)
			{
				delete right;
				right = nullptr;
			}
			parent = nullptr;
		}
	};

	BinaryTreeNode* root;
	Comparator cmp;
};

template<typename T, typename Comparator>
BinaryTree<T, Comparator>::~BinaryTree()
{
	if (root)
	{
		delete root;
		root = nullptr;
	}
}

template<typename T, typename Comparator>
BinaryTree<T, Comparator>::BinaryTree(BinaryTree&& src)
{
	root = src.root;
	cmp = src.cmp;

	src.root = nullptr;
}

template<typename T, typename Comparator>
BinaryTree<T, Comparator>& BinaryTree<T, Comparator>::operator=(BinaryTree&& src)
{
	if (this == &src)
	{
		return *this;
	}
	~BinaryTree();

	root = src.root;
	cmp = src.cmp;

	src.root = nullptr;

	return *this;
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::insert(const T& key)
{
	BinaryTreeNode* newNode = new BinaryTreeNode(key, nullptr);
	if (root == nullptr)
	{
		root = newNode;
		return;
	}

	BinaryTreeNode* head = root;
	while (head != nullptr)
	{
		if (cmp(newNode->key, head->key) > 0)
		{
			if (head->right != nullptr)
			{
				head = head->right;
			}
			else
			{
				newNode->parent = head;
				head->right = newNode;
				break;
			}
		}
		else
		{
			if (head->left != nullptr)
			{
				head = head->left;
			}
			else
			{
				newNode->parent = head;
				head->left = newNode;
				break;
			}
		}
	}
}

template<typename T, typename Comparator>
void BinaryTree<T, Comparator>::postOrderPrint() const
{
	if (!root)
	{
		return;
	}

	BinaryTreeNode* head = root;
	stack<BinaryTreeNode*> st;
	st.push(head);

	while (!st.empty()) {
		BinaryTreeNode* next = st.top();

		bool finishedSubtrees = (next->right == head || next->left == head);
		bool isLeaf = (next->left == nullptr && next->right == nullptr);
		if (finishedSubtrees || isLeaf)
		{
			st.pop();
			cout << (next->key) << " ";
			head = next;
		}
		else
		{
			if (next->right != nullptr)
			{
				st.push(next->right);
			}
			if (next->left != nullptr)
			{
				st.push(next->left);
			}
		}
	}
}


class IntComparator
{
public:
	int operator() (const int& a, const int& b)
	{
		return a - b;
	}
};

int main()
{

	IntComparator cmp;
	BinaryTree<int, IntComparator> bt(cmp);

	int N;
	cin >> N;
	assert(N > 0);
	for (int i = 0; i < N; ++i)
	{
		int elem;
		cin >> elem;
		bt.insert(elem);
	}

	bt.postOrderPrint();

	return EXIT_SUCCESS;
}