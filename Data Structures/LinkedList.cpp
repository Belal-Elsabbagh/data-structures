#include "LinkedList.h"
#include <iostream>
using namespace std;

//-- Definition of the class constructor
LinkedList::LinkedList() // uses initialization list to set the first pointer and mySize to 0
	: first(0), mySize(0)
{}

//-- Definition of the class copy constructor
LinkedList::LinkedList(const LinkedList& original)
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
LinkedList::~LinkedList()
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

const LinkedList& LinkedList::operator=(const LinkedList& rightSide)
{
	/*--------------------------------------------------------------------
	 The assignment operator is the same as the copy constructor except
	 for some differences.
	 The operator erases the data in the left hand side and copies the
	 right hand side to the left hand side.
	 --------------------------------------------------------------------*/


	if (rightSide.mySize == 0) return *this;

	if (this != &rightSide)
	{
		this->~LinkedList(); // destructs the left hand side

	//-- construct the copy
		NodePointer origPtr, lastPtr;
		first = new Node(rightSide.first->data); // copy first node

		lastPtr = first; // sets left hand side to first node
		origPtr = rightSide.first->next; // sets right hand side to point at the node next to first
		
		while (origPtr != 0)
		{
			// intitializes the next node by the data in origPtr
			lastPtr->next = new Node(origPtr->data);

			// traverses  one node through list
			origPtr = origPtr->next;
			lastPtr = lastPtr->next;
		}
	}
	return *this;
}

//-- Definition of empty()
bool LinkedList::empty()
{
	return mySize == 0; // returns true if mySize = 0 and false otherwise.
}

//-- Definition of insert()
void LinkedList::insert(ElementType dataVal, int index)
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
void LinkedList::erase(int index)
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

void LinkedList::display(ostream& out) const
{
	NodePointer ptr = first;
	while (ptr != 0)
	{
		out << ptr->data << " ";
		ptr = ptr->next;
	}
}

int LinkedList::nodeCount()
{
	// you can do a manual count if you want but that's much easier
	return mySize;
}

void LinkedList::reverse()
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

bool LinkedList::ascendingOrder()
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

int LinkedList::search(ElementType dataVal)
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

void LinkedList::insertUsingInputOperator(istream& in)
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

ostream& operator<<(ostream& out, const LinkedList& aList)
{
	aList.display(out);
	return out;
}

istream& operator>>(istream& in, LinkedList& aList)
{
	aList.insertUsingInputOperator(in);
	return in;
}
