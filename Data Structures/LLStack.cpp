#include "LLStack.h"
using namespace std;

/*------------------------------------------------------------------------
 Constructors, destructor, and assignment operator

 They all have the same implementation as the one in the LinkedList.
 This is the standard construction and destruction of a Linked list
 but with slightly different data member initializations.
 ------------------------------------------------------------------------*/


LLStack::LLStack()
{
	myTop = NULL;
}

LLStack::LLStack(const LLStack& original)
{
	// mySize = origList.mySize;
	// first = 0;
	
	if (original.empty()) return;

	NodePointer origPtr, lastPtr;
	myTop = new Node(original.myTop->data); // copy first node

	// set pointers to point to the first nodes in both lists respectively
	lastPtr = myTop;
	origPtr = original.myTop->next; // makes origPtr leading by one node

	while (origPtr != 0) //as long as the original list isn't at the end
	{
		// intitializes the next node by the data in origPtr
		lastPtr->next = new Node(origPtr->data);

		// traverses through list
		origPtr = origPtr->next;
		lastPtr = lastPtr->next;
	}
}

LLStack::~LLStack()
{
	NodePointer prev = myTop,
		ptr;
	while (prev != 0)
	{
		ptr = prev->next; // pointer catches the next node in the list
		delete prev; // delete current node
		prev = ptr; // set the current node to next
	}
}

const LLStack& LLStack::operator=(const LLStack& rightSide)
{
	/*--------------------------------------------------------------------
	 The assignment operator uses the copy constructor to assign the
	 right hand side after clearing the current data in the object.
	 --------------------------------------------------------------------*/


	if (rightSide.empty()) return *this;

	if (this != &rightSide)
	{
		this->~LLStack(); // destructs the left hand side
		LLStack(rightSide); // constructs the copy in this object
	}

	return *this;
}

bool LLStack::empty() const
{
	return myTop == NULL;
}

void LLStack::push(const StackElement& value)
{
	NodePointer temp = new Node(value);

	temp->next = myTop;
	myTop = temp;
}

void LLStack::display(ostream& out) const
{
	for (NodePointer ptr = myTop; ptr != 0; ptr = ptr->next)
		out << ptr->data << endl;
}

StackElement LLStack::top() const
{
	return myTop->data;
}

void LLStack::pop()
{
	NodePointer ptr = myTop;
	myTop = myTop->next;
	delete ptr;
}

void LLStack::intersection(const LLStack& s1, LLStack& s2)
{
	NodePointer ptr1, ptr2;
	ptr1 = myTop;
	ptr2 = s1.myTop;
	while (ptr1 != 0)
	{
		while (ptr2 != 0)
		{
			if (ptr1->data == ptr2->data)
			{
				s2.push(ptr2->data);
			}
			else
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}

StackElement LLStack::bottom() const
{
	return StackElement();
}
