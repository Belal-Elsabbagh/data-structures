#include "LinkedList.h"
#include <iostream>
using namespace std;

//-- Definition of the class constructor
LinkedList::LinkedList() 
	: first(0), mySize(0)
{}

//-- Definition of the class constructor
LinkedList::LinkedList(const LinkedList& origList)
	: first(0), mySize(origList.mySize)
{
	//mySize = origList.mySize;
	//first = 0;
	if (mySize == 0) return;
	NodePointer origPtr, lastPtr;
	first = new Node(origList.first->data); // copy first node
	
	// set pointers in their first positions
	lastPtr = first;
	origPtr = origList.first->next; // makes origPtr leading by one node

	while (origPtr != 0)
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
		ptr = prev->next;
		delete prev;
		prev = ptr;
	}
}

const LinkedList& LinkedList::operator=(const LinkedList& rightSide)
{
	mySize = rightSide.mySize;
	first = 0;
	if (mySize == 0) return *this;
	if (this != &rightSide)
	{
		this->~LinkedList();
		NodePointer origPtr, lastPtr;
		first = new Node(rightSide.first->data); // copy first node

		// set pointers in their first positions
		lastPtr = first;
		origPtr = rightSide.first->next; // makes origPtr leading by one node
		
		while (origPtr != 0)
		{
			// intitializes the next node by the data in origPtr
			lastPtr->next = new Node(origPtr->data);

			// traverses through list
			origPtr = origPtr->next;
			lastPtr = lastPtr->next;
		}
	}
	return *this;
}

//-- Definition of empty()
bool LinkedList::empty()
{
	return mySize == 0;
}

//-- Definition of insert()
void LinkedList::insert(ElementType dataVal, int index)
{
	if (index < 0 || index > mySize)
	{
		cerr << "Illegal location to insert -- " << index << endl;
		return;
	}
	mySize++;
	NodePointer newPtr = new Node(dataVal), 
				predPtr = first;
	if (index == 0)
	{
		newPtr->next = first;
		first = newPtr;
	}
	else
	{
		// traverse to node before required index
		for (int i = 1; i < index; i++)
			predPtr = predPtr->next;

		newPtr->next = predPtr->next;
		predPtr->next = newPtr;
	}
}

//-- Definition of erase()
void LinkedList::erase(int index)
{
	if (index < 0 || index > mySize)
	{
		cerr << "Illegal location to inser -- " << index << endl;
		return;
	}
	mySize--;
	NodePointer ptr,
		predPtr = first;
	if (index == 0)
	{
		ptr = first;
		first = ptr->next;
		delete ptr;
	}
	else
	{
		// traverse to node before required index
		for (int i = 1; i < index; i++)
			predPtr = predPtr->next;

		ptr = predPtr->next;
		predPtr->next = ptr->next;
		delete ptr;
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
	return mySize;
}

void LinkedList::reverse()
{
}
