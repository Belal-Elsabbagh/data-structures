/*-- LLStack.h --------------------------------------------------------------

 This header file defines a Stack data type.
 Basic operations:
 constructor:  Constructs an empty stack
 empty:        Checks if a stack is empty
 push:         Modifies a stack by adding a value at the top
 top:          Accesses the top stack value; leaves stack unchanged
 pop:          Modifies stack by removing the value at the top
 display:      Displays all the stack elements
 Note: Execution terminates if memory isn't available for a stack element.
 --------------------------------------------------------------------------*/
#pragma once
#include <stdio.h>
#include <iostream>
using namespace std;

template<class StackElement>
class LLStack
{
private:
	/*** Node class ***/
	class Node
	{
	public:
		StackElement data;
		Node* next;
		//--- Node constructor
		Node(StackElement data, Node* next = 0)
			/*-------------------------------------------------------------------
			 Precondition:  None.
			 Postcondition: A Node has been constructed with value in its data
			 part and its next part set to link (default 0).
			 -------------------------------------------------------------------*/
			: data(data), next(next)
		{}
	};

	typedef Node* NodePointer;

	/***** Data Members *****/
	NodePointer myTop;      // pointer to top of stack

public:
	/***** Function Members *****/
	/***** Constructors *****/
	LLStack();
	/*-----------------------------------------------------------------------
	 Construct a Stack object.
	 Precondition:  None.
	 Postcondition: An empty Stack object has been constructed
	 (myTop is initialized to a null pointer).
	 ------------------------------------------------------------------------*/

	LLStack(const LLStack& original);
	//-- Same documentation as in Figure 7.8

	/***** Destructor *****/
	~LLStack();
	/*------------------------------------------------------------------------
	 Class destructor

	 Precondition:  None
	 Postcondition: The linked list in the stack has been deallocated.
	 ------------------------------------------------------------------------*/

	 /***** Assignment *****/
	const LLStack& operator= (const LLStack& rightHandSide);
	/*------------------------------------------------------------------------
	 Assignment Operator
	 Precondition:  rightHandSide is the stack to be assigned and is
	 received as a const reference parameter.
	 Postcondition: The current stack becomes a copy of rightHandSide
	 and a const reference to it is returned.
	 ------------------------------------------------------------------------*/

	bool empty() const;
	/*------------------------------------------------------------------------
	 Check if stack is empty.
	 Precondition: None
	 Postcondition: Returns true if stack is empty and false otherwise.
	 -----------------------------------------------------------------------*/

	void push(const StackElement& value);
	/*------------------------------------------------------------------------
	 Add a value to a stack.

	 Precondition:  value is to be added to this stack
	 Postcondition: value is added at top of stack provided there is space;
	 otherwise, a stack-full message is displayed and execution is
	 terminated.
	 -----------------------------------------------------------------------*/

	void display(ostream& out) const;
	/*------------------------------------------------------------------------
	 Display values stored in the stack.

	 Precondition:  ostream out is open.
	 Postcondition: Stack's contents, from top down, have been output to out.
	 -----------------------------------------------------------------------*/

	StackElement top() const;
	/*------------------------------------------------------------------------
	 Retrieve value at top of stack (if any).

	 Precondition:  Stack is nonempty
	 Postcondition: Value at top of stack is returned, unless the stack is
	 empty; in that case, an error message is displayed and a "garbage
	 value" is returned.
	 -----------------------------------------------------------------------*/

	void pop();
	/*------------------------------------------------------------------------
	 Remove value at top of stack (if any).

	 Precondition:  Stack is nonempty.
	 Postcondition: Value at top of stack has been removed, unless the stack
	 is empty; in that case, an error message is displayed and
	 execution allowed to proceed.
	 -----------------------------------------------------------------------*/

	void intersection(const LLStack& s1, LLStack& s);

	StackElement bottom() const;

}; // end of class declaration

/*------------------------------------------------------------------------
 Constructors, destructor, and assignment operator

 They all have the same implementation as the one in the LinkedList.
 This is the standard construction and destruction of a Linked list
 but with slightly different data member initializations.
 ------------------------------------------------------------------------*/

template<class StackElement>
LLStack<StackElement>::LLStack()
{
	myTop = NULL;
}

template<class StackElement>
LLStack<StackElement>::LLStack(const LLStack& original)
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

template<class StackElement>
LLStack<StackElement>::~LLStack()
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

template<class StackElement>
const LLStack<StackElement>& LLStack<StackElement>::operator=(const LLStack<StackElement>& rightSide)
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

template<class StackElement>
bool LLStack<StackElement>::empty() const
{
	return myTop == NULL;
}

template<class StackElement>
void LLStack<StackElement>::push(const StackElement& value)
{
	NodePointer temp = new Node(value);

	temp->next = myTop;
	myTop = temp;
}

template<class StackElement>
void LLStack<StackElement>::display(ostream& out) const
{
	for (NodePointer ptr = myTop; ptr != 0; ptr = ptr->next)
		out << ptr->data << endl;
}

template<class StackElement>
StackElement LLStack<StackElement>::top() const
{
	return myTop->data;
}

template<class StackElement>
void LLStack<StackElement>::pop()
{
	NodePointer ptr = myTop;
	myTop = myTop->next;
	delete ptr;
}

template<class StackElement>
void LLStack<StackElement>::intersection(const LLStack<StackElement>& s1, LLStack<StackElement>& s2)
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

template<class StackElement>
StackElement LLStack<StackElement>::bottom() const
{
	LLStack<StackElement> temp(*this);
	NodePointer ptr = temp.myTop;

	while (ptr->next)
	{
		ptr = ptr->next;
	}
	return ptr->data;

	temp.~LLStack();
}

template<class StackElement>
ostream& operator<<(ostream& out, const LLStack<StackElement>& obj)
{
	obj.display(out);
	return out;
}