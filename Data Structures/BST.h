
template <class DataType>
class BST
{
	class BinNode
	{
	public:
		DataType data;
		BinNode* left, right;

		BinNode() : left(0), right(0)
		{}

		BinNode(DataType item) : data(item), left(0), right(0)
		{}
	};

	typedef BinNode* BinNodePointer;
	
	BinNodePointer myRoot;

	bool search(const DataType& item);
	void insert(const DataType& item);
	void remove(const DataType& item);
};

template<class DataType>
bool BST<DataType>::search(const DataType& item)
{
	function<void(BinNodePointer subRoot) const> searchAUX; //definition of the search function
	searchAUX = [&](BinNodePointer subRoot)
	{
		if (subRoot == 0)
			return false;
		if (item < subRoot->data)
			return searchAUX(subRoot->left);
		else if
			return searchAUX(subRoot->right);
		else
			return true;
	};

	return searchAUX(root);
}

template<class DataType>
void BST<DataType>::insert(const DataType& item)
{
	function<void(BinNodePointer subRoot) const> insertAUX; //definition of the search function
	insertAUX = [&](BinNodePointer subRoot)
	{
		if (subRoot == 0)
			subRoot = new BinNode(item);
		if (item < subRoot->data)
			insertAUX(subRoot->left);
		else if
			insertAUX(subRoot->right);
		else
			cerr << "Item is already in tree\n";
	};

	return insertAUX(root);
}

template<class DataType>
void BST<DataType>::remove(const DataType& item)
{
	bool found;
	BST<DataType>::BinNodePointer, x, parent;

	search2(item, found, x, parent);

	if (!found)
	{
		cout << "Item is not in the BST\n";
		return;
	}

	if (x->left != 0 && x-> != 0)
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
