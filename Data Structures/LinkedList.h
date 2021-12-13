#pragma once
//
//  List.hpp
//  LinkedList
//
//  Created by Ashraf AbdelRaouf on 9/23/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//

#include <iostream>
using namespace std;

template<class ElementType>
class LinkedList
{
private:

    class Node {
    public:

        //------ Node DATA MEMBERS
        ElementType data;
        Node* next;

        //------ Node OPERATIONS
        //-- Default constrctor: initializes next member to Node()
        Node()
            : next(0)
        {}

        //-- Explicit-value constructor:  initializes data member to dataValue
        //--                             and next member to 0
        Node(ElementType dataValue)
            : data(dataValue), next(0)
        {}
    }; //--- end of Node class

    typedef Node* NodePointer;


    //------ DATA MEMBERS
    NodePointer first;
    int mySize;

public:
    //------ List OPERATIONS
    LinkedList();
    /*--------------------------------------------------------------------
     Default constructor: builds an empty List object.
     Precondition:  None
     Postcondition: first is 0 and mySize is 0.
     --------------------------------------------------------------------*/
    LinkedList(const LinkedList& origList);
    /*--------------------------------------------------------------------
     Copy constructor
     Precondition:  A copy of origList is needed.
     Postcondition: A distincr copy of origList has been constructed.
     --------------------------------------------------------------------*/
    ~LinkedList();
    /*--------------------------------------------------------------------
     Destructor
     Precondition:  This list's lifetime is over.
     Postcondition: This list has been destroyed.
     --------------------------------------------------------------------*/
    const LinkedList& operator=(const LinkedList& rightSide);
    /*--------------------------------------------------------------------
     Assignment operator
     Precondition:  This list must be assigned a value.
     Postcondition: A copy of rightSide has been assigned to this list.
     --------------------------------------------------------------------*/
    bool empty();
    /*--------------------------------------------------------------------
     Check if this list is empty
     Precondition:  None.
     Postcondition: true is returned if this list is empty, false if not.
     --------------------------------------------------------------------*/
    void insert(ElementType dataVal, int index);
    /*--------------------------------------------------------------------
     Insert a value into a list at a given index.
     Precondition:  index is a valid list index: 0 <= index <= mySize,
     Postcondition: dataVal has been inserted into the list at position
     index, provided index is valid..
     --------------------------------------------------------------------*/
    void erase(int index);
    /*--------------------------------------------------------------------
     Remove a value from a list at a given index.
     Precondition:  index is a valid list index:  0 <= index < mySize
     Postcondition: dataVal at list position index has been removed,
     provided index is valid.
     --------------------------------------------------------------------*/

    void display(ostream& out) const;
    /*--------------------------------------------------------------------
     Display the contensts of this list.
     Precondition:  ostream out is open
     Postcondition: Elements of this list have been output to out.
     --------------------------------------------------------------------*/
    int nodeCount();
    /*--------------------------------------------------------------------
     Count the elements of this list.
     Precondition:  None
     Postcondition: Number of elements in this list is returned.
     --------------------------------------------------------------------*/
    void reverse();
    /*--------------------------------------------------------------------
     Reverse this list.
     Precondition:  None
     Postcondition: Elements in this list have been reversed.
     --------------------------------------------------------------------*/
    bool ascendingOrder();
    /*--------------------------------------------------------------------
     Check if the elements of this list are in ascending order.
     Precondition:  None
     Postcondition: true is returned if the list elements are in
     ascending order, false if not.
     --------------------------------------------------------------------*/
    int search(ElementType dataVal);
    /*--------------------------------------------------------------------
     Search for an data value in this list.
     Precondition:  None
     Postcondition: Index of node containing dataVal is returned
     if such a node is found, -1r if not.
     --------------------------------------------------------------------*/
    void insertUsingInputOperator(istream& in);
    /*--------------------------------------------------------------------
     implementation of operator>> 
     Precondition:  istream out is open
     Postcondition: Elements entered have been inserted to the LinkedList
     --------------------------------------------------------------------*/

}; //--- end of List class

//-- Definition of the class constructor
template <class ElementType>
LinkedList<ElementType>::LinkedList() // uses initialization list to set the first pointer and mySize to 0
	: first(0), mySize(0)
{}

//-- Definition of the class copy constructor
template <class ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList& original)
	: first(0), mySize(original.mySize)
{
	//mySize = origList.mySize;
	//first = 0;
	if (mySize == 0) return;

	NodePointer origPtr, lastPtr;
	first = new Node(original.first->data); // copy first node

	// set pointers to point to the first nodes in both lists respectively
	lastPtr = first;
	origPtr = original.first->next; // makes origPtr leading by one node

	while (origPtr != 0) //as long as the original list isn't at the end
	{
		// intitializes the next node by the data in origPtr
		lastPtr->next = new Node(origPtr->data);

		// traverses through list
		origPtr = origPtr->next;
		lastPtr = lastPtr->next;
	}
}

//-- Definition of the class destructor
template <class ElementType>
LinkedList<ElementType>::~LinkedList()
{
	NodePointer prev = first,
		ptr;
	while (prev != 0)
	{
		ptr = prev->next; // pointer catches the next node in the list
		delete prev; // delete current node
		prev = ptr; // set the current node to next
	}
}

template <class ElementType>
const LinkedList<ElementType>& LinkedList<ElementType>::operator=(const LinkedList& rightSide)
{
	/*--------------------------------------------------------------------
	 The assignment operator uses the copy constructor to assign the
	 right hand side after clearing the current data in the object.
	 --------------------------------------------------------------------*/


	if (rightSide.mySize == 0) return *this;

	if (this != &rightSide)
	{
		this->~LinkedList(); // destructs the left hand side
		LinkedList(rightSide); // constructs the copy in this object
	}

	return *this;
}

//-- Definition of empty()
template <class ElementType>
bool LinkedList<ElementType>::empty()
{
	return mySize == 0; // returns true if mySize = 0 and false otherwise.
}

//-- Definition of insert()
template <class ElementType>
void LinkedList<ElementType>::insert(ElementType dataVal, int index)
{
	if (index < 0 || index > mySize) // checks invalidity of index.
	{
		// error message and termination
		cerr << "Illegal location to insert -- " << index << endl;
		return;
	}
	// after index validity is confirmed
	mySize++; // increase size by 1

	NodePointer newPtr = new Node(dataVal), // creates node with the value entered
		predPtr = first; // sets traversing pointer

	if (index == 0) //special case if adding to first node
	{
		newPtr->next = first;
		first = newPtr;
	}
	else
	{
		// traverse to node before required index
		for (int i = 1; i < index; i++)
			predPtr = predPtr->next;

		newPtr->next = predPtr->next; // sets new node to point to the next node of its previous node

		predPtr->next = newPtr; // sets previous node to point to the new node
	}
}

//-- Definition of erase()
template <class ElementType>
void LinkedList<ElementType>::erase(int index)
{
	if (index < 0 || index > mySize) // checks invalidity of index.
	{
		// error message and termination
		cerr << "Illegal location to erase -- " << index << endl;
		return;
	}
	// after index validity is confirmed
	mySize--; // decrease size by 1

	NodePointer ptr,
		predPtr = first; //sets traversing node

	if (index == 0) //special case if erasing the first node
	{
		ptr = first; // holds the first node (node to be erased)
		first = ptr->next; // sets first node to point to the node next to first
		delete ptr; // deletes node
	}
	else
	{
		// traverse to node before required index
		for (int i = 1; i < index; i++)
			predPtr = predPtr->next;

		ptr = predPtr->next; // holds node to be erased
		predPtr->next = ptr->next; // sets previous node to skip the node to be erased
		delete ptr; // erases node
	}
}

template <class ElementType>
void LinkedList<ElementType>::display(ostream& out) const
{
	NodePointer ptr = first;
	while (ptr != 0)
	{
		out << ptr->data << " ";
		ptr = ptr->next;
	}
}

template <class ElementType>
int LinkedList<ElementType>::nodeCount()
{
	// you can do a manual count if you want but that's much easier
	return mySize;
}

template <class ElementType>
void LinkedList<ElementType>::reverse()
{
	NodePointer prevP = 0,
		currentP = first,
		nextP;

	while (currentP != 0)
	{
		nextP = currentP->next;
		currentP->next = prevP;
		prevP = currentP;
		currentP = nextP;
	}
	first = prevP; // new head of (reversed) LinkedList
}

template <class ElementType>
bool LinkedList<ElementType>::ascendingOrder()
{
	if (mySize <= 1)
		// empty or one element list
		return true;
	NodePointer prevP = first,
		tempP = first->next;
	while (tempP != 0 && prevP->data <= tempP->data)
	{
		prevP = tempP;
		tempP = tempP->next;
	}
	if (tempP != 0)
		return false;
	return true;
}

int LinkedList<ElementType>::search(ElementType dataVal)
{
	int loc;
	NodePointer tempP = first;
	for (loc = 0; loc < mySize; loc++)
	{
		if (tempP->data == dataVal)
			return loc;
		else
			tempP = tempP->next;
	}
	return -1;
}

template <class ElementType>
void LinkedList<ElementType>::insertUsingInputOperator(istream& in)
{
	int numOfElements;
	in >> numOfElements;
	ElementType dataVal;

	for (int i = 0; i < numOfElements; i++)
	{
		in >> dataVal;
		insert(dataVal, i);
	}
}

ostream& operator<<(ostream& out, const LinkedList<ElementType>& aList)
{
	aList.display(out);
	return out;
}

istream& operator>>(istream& in, LinkedList<ElementType>& aList)
{
	aList.insertUsingInputOperator(in);
	return in;
}



