#include "LLStack.h"
using namespace std;

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
	 The assignment operator is the same as the copy constructor except
	 for some differences.
	 The operator erases the data in the left hand side and copies the
	 right hand side to the left hand side.
	 --------------------------------------------------------------------*/

	if (rightSide.empty()) return *this;

	if (this != &rightSide)
	{
		this->~LLStack(); // destructs the left hand side

	//-- construct the copy
		NodePointer origPtr, lastPtr;
		myTop = new Node(rightSide.myTop->data); // copy first node

		lastPtr = myTop; // sets left hand side to first node
		origPtr = rightSide.myTop->next; // sets right hand side to point at the node next to first

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
