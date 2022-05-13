
#include <cassert>
#include <iostream>
#include <stack>
#include <string>

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
	size_t findMinWay() const { return _findMinWay(root); };


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

private:

	size_t _findMinWay(BinaryTreeNode *node) const;
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
size_t BinaryTree<T, Comparator>::_findMinWay(BinaryTreeNode *node) const
{
	if (!node)
		return 0;
	size_t left = _findMinWay(node->left);
	size_t right = _findMinWay(node->right);
	if (left > 0 && right > 0)
		return std::min(left, right) + 1;
	else
		return (left ? left : right) + 1;
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

	while (!cin.eof()) {
		string str;
		cin >> str;
		if (!str.empty())
		{
			bt.insert(stoi(str));
		}
	}

	cout << bt.findMinWay();

	return EXIT_SUCCESS;
}