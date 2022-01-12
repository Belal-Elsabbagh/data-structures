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
class ModelBST
{
public:
    /***** Function Members *****/
    ModelBST();
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
                    ModelBST<DataType>::BinNodePointer subtreePtr) const;
    /*------------------------------------------------------------------------
     Inorder traversal auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST.
     Postcondition: Subtree with root pointed to by subtreePtr has been
     output to out.
     ------------------------------------------------------------------------*/
    
    void graphAux(ostream & out, int indent,
                  ModelBST<DataType>::BinNodePointer subtreeRoot) const;
    /*------------------------------------------------------------------------
     Graph auxiliary function.
     
     Precondition:  ostream out is open; subtreePtr points to a subtree
     of this BST.
     Postcondition: Graphical representation of subtree with root pointed
     to by subtreePtr has been output to out, indented indent spaces.
     ------------------------------------------------------------------------*/
    //------------------Search & Insert functions recursively------------------
    inline bool SearchReq(const DataType& item) const;
    bool SearchReqAux(BinNodePointer SubtreeRoot, const DataType& item)const;
    
    inline void insertReq(const DataType& item);
    void insertReqAux(BinNodePointer & SubtreeRoot, const DataType& item);
    
    /***** Data Members *****/
    
    BinNodePointer myRoot;
    
}; // end of class template declaration

//--- Definition of constructor
template <typename DataType>
inline ModelBST<DataType>::ModelBST()
: myRoot(0)
{}

//--- Definition of empty()
template <typename DataType>
inline bool ModelBST<DataType>::empty() const
{ return myRoot == 0; }

//--- Definition of search()
template <typename DataType>
bool ModelBST<DataType>::search(const DataType & item) const
{
    ModelBST<DataType>::BinNodePointer locptr = myRoot;
    bool found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    return found;
}

//--- Definition of insert()
template <typename DataType>
inline void ModelBST<DataType>::insert(const DataType & item)
{
    ModelBST<DataType>::BinNodePointer
    locptr = myRoot,   // search pointer
    parent = 0;        // pointer to parent of current node
    bool found = false;     // indicates if item already in BST
    while (!found && locptr != 0)
    {
        parent = locptr;
        if (item < locptr->data)       // descend left
            locptr = locptr->left;
        else if (locptr->data < item)  // descend right
            locptr = locptr->right;
        else                           // item found
            found = true;
    }
    if (!found)
    {                                 // construct node containing item
        locptr = new ModelBST<DataType>::BinNode(item);
        if (parent == 0)               // empty tree
            myRoot = locptr;
        else if (item < parent->data )  // insert to left of parent
            parent->left = locptr;
        else                           // insert to right of parent
            parent->right = locptr;
    }
    else
        cout << "Item already in the tree\n";
}

//--------- Definition of remove() -----------------------------------------------
template <typename DataType>
void ModelBST<DataType>::remove(const DataType & item)
{
    bool found;                      // signals if item is found
    ModelBST<DataType>::BinNodePointer
    x,                            // points to node to be deleted
    parent;                       //    "    " parent of x and xSucc
    search2(item, found, x, parent);
    
    if (!found){  //item not found
        cout << "Item not in the BST\n";
        return;
    }
    //else
    if (x->left != 0 && x->right != 0){   // node has 2 children
        // Find x's inorder successor and its parent
        ModelBST<DataType>::BinNodePointer xSucc = x->right;
        parent = x;
        while (xSucc->left != 0){       // descend left
            parent = xSucc;
            xSucc = xSucc->left;
        }
        // Move contents of xSucc to x and change x
        // to point to successor, which will be removed.
        x->data = xSucc->data;
        x = xSucc;
    } // end if node has 2 children
    
    // Now proceed with case where node has 0 or 1 child
    ModelBST<DataType>::BinNodePointer
    subtree = x->left;             // pointer to a subtree of x
    if (subtree == 0)
        subtree = x->right;
    if (parent == 0)                  // root being removed
        myRoot = subtree;
    else if (parent->left == x)       // left child of parent
        parent->left = subtree;
    else                              // right child of parent
        parent->right = subtree;
    delete x;
}

//--- Definition of inorder()
template <typename DataType>
inline void ModelBST<DataType>::inorder(ostream & out) const
{
    inorderAux(out, myRoot);
}

//--- Definition of graph()
template <typename DataType>
inline void ModelBST<DataType>::graph(ostream & out) const
{ graphAux(out, 0, myRoot); }

//--- Definition of search2()
template <typename DataType>
void ModelBST<DataType>::search2(const DataType & item, bool & found,
                            ModelBST<DataType>::BinNodePointer & locptr,
                            ModelBST<DataType>::BinNodePointer & parent) const
{
    locptr = myRoot;
    parent = 0;
    found = false;
    while (!found && locptr != 0)
    {
        if (item < locptr->data)       // descend left
        {
            parent = locptr;
            locptr = locptr->left;
        }
        else if (locptr->data < item)  // descend right
        {
            parent = locptr;
            locptr = locptr->right;
        }
        else                           // item found
            found = true;
    }
}

//--- Definition of inorderAux()
template <typename DataType>
void ModelBST<DataType>::inorderAux(ostream & out,
                               ModelBST<DataType>::BinNodePointer subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        inorderAux(out, subtreeRoot->left);    // L operation
        out << subtreeRoot->data << "  ";      // V operation
        inorderAux(out, subtreeRoot->right);   // R operation
    }
}

//--- Definition of graphAux()
template <typename DataType>
void ModelBST<DataType>::graphAux(ostream & out, int indent,
                             ModelBST<DataType>::BinNodePointer subtreeRoot) const
{
    if (subtreeRoot != 0)
    {
        graphAux(out, indent + 8, subtreeRoot->right);
        out << setw(indent) << " " << subtreeRoot->data << endl;
        graphAux(out, indent + 8, subtreeRoot->left);
    }
}

//------------ Definition of SearchReq -------------------------------------
template <typename DataType>
inline bool ModelBST<DataType>::SearchReq(const DataType & item) const
{
    return SearchReqAux(myRoot, item);
}

//----------- Definition of SearchReqAux -------------------------------------
template <typename DataType>
bool ModelBST<DataType>::SearchReqAux(ModelBST<DataType>::BinNodePointer SubtreeRoot, const DataType& item)const
{
    if(SubtreeRoot==0)      //empty subtree
        return false;
    // else there is a nonempty subtree
    if(item<SubtreeRoot->data)          // search left subtree
        return SearchReqAux(SubtreeRoot->left, item);
    else if(item>SubtreeRoot->data)     // search right subtree
        return SearchReqAux(SubtreeRoot->right, item);
    else                                // Item is found
        return true;
}

//--------- Definition of insertReq --------------------------------------------
template <typename DataType>
void ModelBST<DataType>::insertReq(const DataType & item)
{
    return insertReqAux(myRoot, item);
}

//--------- Definition of SearchReqAux ------------------------------------------
template <typename DataType>
void ModelBST<DataType>::insertReqAux(ModelBST<DataType>::BinNodePointer &SubtreeRoot, const DataType& item)
{
    if(SubtreeRoot==0)      //empty tree
        SubtreeRoot= new ModelBST<DataType>::BinNode(item);
    // else there is a nonempty tree. insert into:
    else if(item < SubtreeRoot->data)          // search left subtree
        insertReqAux(SubtreeRoot->left, item);
    else if(item > SubtreeRoot->data)     // search right subtree
        insertReqAux(SubtreeRoot->right, item);
    else
        cerr<<"Item already in the tree\n";
}

#endif /* MyBST_h */