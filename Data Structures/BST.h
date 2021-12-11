//
//  MyBST.h
//  BST
//
//  Created by Ashraf AbdelRaouf on 11/26/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//
/* BST.h contains the declaration of class template BST.
 Basic operations:
 Constructor: Constructs an empty BST
 empty:       Checks if a BST is empty
 search:      Search a BST for an item
 insert:      Inserts a value into a BST
 remove:      Removes a value from a BST
 inorder:     Inorder traversal of a BST -- output the data values
 graph:       Output a grapical representation of a BST
 Private utility helper operations:
 search2:     Used by delete
 inorderAux:  Used by inorder
 graphAux:    Used by graph
 Other operations described in the exercises:
 destructor
 copy constructor
 assignment operator
 preorder, postorder, and level-by-level traversals
 level finder
 Note: Execution terminates if memory isn't available for a new BST node.
 ---------------------------------------------------------------------------*/

#include <iostream>
using namespace std;
#include <iomanip>
#ifndef MyBST_h
#define MyBST_h

template <typename DataType>
class BST
{
public:
    /***** Function Members *****/
    BST();
    /*------------------------------------------------------------------------
     Construct a BST object.
     
     Precondition:  None.
     Postcondition: An empty BST has been constructed.
     -----------------------------------------------------------------------*/
    
    bool empty() const;
    /*------------------------------------------------------------------------
     Check if BST is empty.
     
     Precondition:  None.
     Postcondition: Returns true if BST is empty and false otherwise.
     -----------------------------------------------------------------------*/
    
    bool search(const DataType & item) const;
    /*------------------------------------------------------------------------
     Search the BST for item.
     
     Precondition:  None.
     Postcondition: Returns true if item found, and false otherwise.
     -----------------------------------------------------------------------*/
    
    void insert(const DataType & item);
    /*------------------------------------------------------------------------
     Insert item into BST.
     
     Precondition:  None.
     Postcondition: BST has been modified with item inserted at proper
     position to maintain BST property.
     ------------------------------------------------------------------------*/
    
    void remove(const DataType & item);
    /*------------------------------------------------------------------------
     Remove item from BST.
     
     Precondition:  None.
     Postcondition: BST has been modified with item removed (if present);
     BST property is maintained.
     Note: remove uses auxiliary function search2() to locate the node
     containing item and its parent.
     ------------------------------------------------------------------------*/
    
    void inorder(ostream & out) const;
    /*------------------------------------------------------------------------
     Inorder traversal of BST.
     
     Precondition:  ostream out is open.
     Postcondition: BST has been inorder traversed and values in nodes
     have been output to out.
     Note: inorder uses private auxiliary function inorderAux().
     ------------------------------------------------------------------------*/
    
    void graph(ostream & out) const;
    /*------------------------------------------------------------------------
     Graphic output of BST.
     
     Precondition:  ostream out is open.
     Postcondition: Graphical representation of BST has been output to out.
     Note: graph() uses private auxiliary function graphAux().
     ------------------------------------------------------------------------*/
    
private:
    /***** Node class *****/
    class BinNode
    {
    public:
        DataType data;
        BinNode * left;
        BinNode * right;
        
        // BinNode constructors
        // Default -- data part is default DataType value; both links are null.
        BinNode()
        : left(0), right(0)
        {}
        
        // Explicit Value -- data part contains item; both links are null.
        BinNode(DataType item)
        : data(item), left(0), right(0)
        {}
        
    };// end of class BinNode declaration
    
    typedef BinNode * BinNodePointer;
    
    /***** Private Function Members *****/
    void search2(const DataType & item, bool & found,
                 BinNodePointer & locptr, BinNodePointer & parent) const;
    /*------------------------------------------------------------------------
     Locate a node containing item and its parent.
     
     Precondition:  None.
     Postcondition: locptr points to node containing item or is null if
     not found, and parent points to its parent.#include <iostream>
     ------------------------------------------------------------------------*/
    
    void inorderAux(ostream & out,
                    BST<DataType>::BinNodePointer subtreePtr) const;
    /*------------------------------------------------------------------------
     Inorder traversal auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST.
     Postcondition: Subtree with root pointed to by subtreePtr has been
     output to out.
     ------------------------------------------------------------------------*/
    
    void graphAux(ostream & out, int indent,
                  BST<DataType>::BinNodePointer subtreeRoot) const;
    /*------------------------------------------------------------------------
     Graph auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST.
     Postcondition: Graphical representation of subtree with root pointed
     to by subtreePtr has been output to out, indented indent spaces.
     ------------------------------------------------------------------------*/
    
	//-----------------------Search & Insert functions recursively-----------------------
    inline bool SearchReq(const DataType& item) const;
    bool SearchReqAux(BinNodePointer SubtreeRoot, const DataType& item)const;
    
    inline void insertReq(const DataType& item);
    void insertReqAux(BinNodePointer & SubtreeRoot, const DataType& item);
	
    /***** Data Members *****/
    
    BinNodePointer myRoot;
    
}; // end of class template declaration

#endif /* MyBST_h */
template<class DataType>
bool BST<DataType>::searchReq(const DataType& item)
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

	return searchReqAux(root);
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

template<typename DataType>
BST<DataType>::BST()
{
	myRoot = new BinNode();
}

template<typename DataType>
bool BST<DataType>::empty() const
{
	return myRoot == 0;
}

template<typename DataType>
bool BST<DataType>::search(const DataType& item) const
{
	BinNodePointer ptr = myRoot;

	while (ptr)
	{
		if (item > ptr->data)
			ptr = ptr->right;
		else if (item < ptr->data)
			ptr = ptr->left;
		else
			return true;
	}
	return false;
}

template<typename DataType>
void BST<DataType>::insert(const DataType& item)
{
	BinNodePointer ptr = myRoot;

	while (true)
	{
		if (!ptr)
		{
			ptr = new BinNode(item);
			return;
		}

		else if (item > ptr->data)
			ptr = ptr->right;
		else if (item < ptr->data)
			ptr = ptr->left;
		else
		{
			cerr << "Item already in the tree\n";
			return;
		}
	}
}

template<typename DataType>
void BST<DataType>::remove(const DataType& item)
{
	bool found;
	BinNodePointer x, parent;
	search2(item, found, x, parent);

	if (!found)
	{
		cerr << "Item not in BST\n";
		return;
	}

	if (x->right != 0 && x->left != 0)
	{
		BinNodePointer xSucc = x->right;
		parent = x;

		while (xSucc->left)
		{
			parent = xSucc;
			xSucc = xSucc->left;
		}
		x = xSucc;
		xSucc = xSucc->left;
	}
	BinNodePointer subtree = x->left;
	
	if (!subtree)
		subtree = x->right;
	if (!parent)
		myRoot = subtree;
	else if (parent->left == x)
		parent->left = subtree;
	else
		parent->right = subtree;
	delete x;
}

template<typename DataType>
void BST<DataType>::inorder(ostream& out) const
{
	inorderAux(out,myRoot);
}

template<typename DataType>
void BST<DataType>::graph(ostream& out) const
{
	graphAux(out, 4, root);
}

template<typename DataType>
void BST<DataType>::search2(const DataType& item, bool& found, BinNodePointer& locptr, BinNodePointer& parent) const
{
	BinNodePointer locptr = myRoot;
	found = 0;
	while (locptr)
	{
		if (item > locptr->data)
		{
			parent = locptr;
			locptr = locptr->right;

		}
		else if (item < locptr->data)
		{
			parent = locptr;
			locptr = locptr->left;

		}
		else
		{
			found == 1;
			return;
		}	
	}
	return;
}

template<typename DataType>
void BST<DataType>::inorderAux(ostream& out, BST<DataType>::BinNodePointer subtreePtr) const
{
	if (!subtreePtr)
		return;
	inorderAux(out, subtreePtr->left);
	out << subtreePtr->data << " ";
	inorderAux(out, subtreePtr->right);
}

template<typename DataType>
void BST<DataType>::graphAux(ostream& out, int indent, BST<DataType>::BinNodePointer subtreeRoot) const
{

}

template<typename DataType>
inline bool BST<DataType>::SearchReq(const DataType& item) const
{
	return SearchReqAux(myRoot, item);
}

template<typename DataType>
bool BST<DataType>::SearchReqAux(BinNodePointer SubtreeRoot, const DataType& item) const
{
	if (subRoot == 0)
		return false;
	if (item < subRoot->data)
		return SearchReqAux(subRoot->left, item);
	else if
		return SearchReqAux(subRoot->right, item);
	else
		return true;
}

template<typename DataType>
inline void BST<DataType>::insertReq(const DataType& item)
{
	insertReqAux(myRoot, item);
}

template<typename DataType>
void BST<DataType>::insertReqAux(BinNodePointer& SubtreeRoot, const DataType& item)
{
	if (SubtreeRoot == 0)      //empty tree
		SubtreeRoot = new BST<DataType>::BinNode(item);
	// else there is a nonempty tree. insert into:
	else if (item < SubtreeRoot->data)          // search left subtree
		insertReqAux(SubtreeRoot->left, item);
	else if (item > SubtreeRoot->data)     // search right subtree
		insertReqAux(SubtreeRoot->right, item);
	else
		cerr << "Item already in the tree\n";
}
