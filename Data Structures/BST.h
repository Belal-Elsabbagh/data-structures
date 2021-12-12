#include <functional>
#include <iostream>

template <class DataType>
class BST
{
public:
	class BinNode
	{
	public:
		DataType data;
		BinNode* left;
		BinNode* right;

		BinNode() : left(0), right(0)
		{}

		BinNode(DataType item) : data(item), left(0), right(0)
		{}
	};

	typedef BinNode* BinNodePointer;

	bool empty() const;

	bool searchAux(BinNodePointer subRoot, const DataType& item);
	bool search(const DataType& item);
	
	void insertAux(BinNodePointer subRoot, const DataType& item);
	void insert(const DataType& item);
	
	void remove(const DataType& item);

private:
	BinNodePointer myRoot;
};

template<class DataType>
bool BST<DataType>::empty() const
{
	return myRoot == 0;
}

template<class DataType>
bool BST<DataType>::searchAux(BinNodePointer subRoot, const DataType& item)
{
	if (!subRoot)
		return false;
	else if (item < subRoot->data)
		return searchAux(subRoot->left, item);
	else if (item > subRoot->data)
		return searchAux(subRoot->right, item);
	else
		return true;
}

template<class DataType>
bool BST<DataType>::search(const DataType& item)
{
	return searchAux(myRoot, item);
}

template<class DataType>
void BST<DataType>::insertAux(BinNodePointer subRoot, const DataType& item)
{
	if (!subRoot)
		subRoot = new BinNode(item);
	else if (item < subRoot->data)
		insertAux(subRoot->left, item);
	else if (item > subRoot->data)
		insertAux(subRoot->right, item);
	else
		cerr << "Item is already in tree\n";
}

template<class DataType>
void BST<DataType>::insert(const DataType& item)
{

	return insertAux(myRoot, item);
}

template<class DataType>
void BST<DataType>::remove(const DataType& item)
{
	bool found;
	BST<DataType>::BinNodePointer x, parent;

	search2(item, found, x, parent);

	if (!found)
	{
		cout << "Item is not in the BST\n";
		return;
	}

	if (x->left != 0 && x->right != 0)
	{
		BST<DataType>::BinNodePointer xSucc = x->right;
		parent = x;
		
		while (xSucc->left != 0)
		{
			parent = xSucc;
			xSucc = xSucc->left;
		}

		x->data = xSucc->data;
		x = xSucc;

	}

	BST<DataType>::BinNodePointer subtree = x->left;

	if (subtree == 0)
		subtree = x->right;
	if (parent == 0)
		myRoot = subtree;
	else if (parent->left == x)
		parent->left = subtree;
	else
		parent->right = subtree;
	delete x;
}