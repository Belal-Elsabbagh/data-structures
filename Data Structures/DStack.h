/*-- DStack.h --------------------------------------------------------------

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
#include <iostream>
#include <algorithm>
#include <cassert>
#include <new>
using namespace std;

typedef int StackElement;

class DStack 
{
private:
	/***** Data Members *****/
	int myCapacity;
	int myTop;
	StackElement* myArray;
public:
	/***** Function Members *****/
	/***** Constructors *****/
	DStack(int numElements = 128);
	DStack(const DStack& original);
	//-- Same documentation as in Figure 7.8
	const DStack& operator= (const DStack& righthandside);
	/*------------------------------------------------------------------------
	 Assignment Operator
	 Precondition:  rightHandSide is the stack to be assigned and is
	 received as a const reference parameter.
	 Postcondition: The current stack becomes a copy of rightHandSide
	 and a const reference to it is returned.
	 ------------------------------------------------------------------------*/
	~DStack();
	/*------------------------------------------------------------------------
	Class destructor

	 Precondition:  None
	 Postcondition: The linked list in the stack has been deallocated.
	 ------------------------------------------------------------------------*/
	bool empty() const;
	/*------------------------------------------------------------------------
	 Check if stack is empty.

	 Precondition: None
	 Postcondition: Returns true if stack is empty and false otherwise.
	 -----------------------------------------------------------------------*/

	void push(const StackElement value);
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

}; // end of class declaration

/*------------------------------------------------------------------------
 Constructors, destructor, and assignment operator

 They all have the same implementation as the one in the DynamicList.
 This is the standard construction and destruction of a Dynamic array
 but with slightly different data member initializations.
 ------------------------------------------------------------------------*/

DStack::DStack(int numElements) : myCapacity(numElements), myTop(-1)
{
	myArray = new(nothrow) StackElement[myCapacity];
	assert(myArray != 0);
}

DStack::DStack(const DStack& original) : myCapacity(original.myCapacity)
{
	myArray = new(nothrow) StackElement[original.myCapacity];
	if (myArray == 0)
	{
		cerr << "\nCouldn't allocate memory. Exiting...\n\a";
		exit(1);
	}
	myTop = original.myTop;
	//TODO create copy algorithm
}

const DStack& DStack::operator=(const DStack& rightHandSide)
{
	if (this != &rightHandSide)
	{
		if (myCapacity != rightHandSide.myCapacity)
		{
			delete[] myArray;
			myCapacity = rightHandSide.myCapacity;
			myArray = new StackElement[myCapacity];
		}
		if (myArray == 0)
		{
			cout << "\nCouldn't allocate memory. Exiting...\n\a";
			exit(1);
		}
		myTop = rightHandSide.myTop;
		for (int i = 0; i < myCapacity; i++)
			myArray[i] = rightHandSide.myArray[i];
	}
	return *this;
}

DStack::~DStack()
{
	delete[] myArray;
}

bool DStack::empty() const
{
	return myTop == -1;
}

void DStack::push(const StackElement value)
{
	if (myTop == myCapacity - 1)
	{
		cerr << "\nStack Overflow. Exiting...\n\a";
		return;
	}
	myTop++;
	myArray[myTop] = value;
}

void DStack::display(ostream& out) const
{
	out << "\nDisplaying List...\n";
	for (int i = myTop; i >= 0; i--)
	{
		out << myArray[i] << ", ";
	}
}

StackElement DStack::top() const
{
	return myArray[myTop];
}

void DStack::pop()
{
	if (myTop <= -1)
		cerr << "Stack Underflow" << endl;
	else
		myTop--;
}