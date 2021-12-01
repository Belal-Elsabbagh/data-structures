#include "DStack.h"
#include <cassert>
#include <new>

DStack::DStack(int numElements) : myCapacity(numElements), myTop(-1)
{
	myArray = new(nothrow) StackElement[myCapacity];
	assert(myArray != 0);
}

DStack::DStack(const DStack& original)
{
	myArray = new(nothrow) StackElement[original.myCapacity];
	if (myArray == 0)
	{
		cerr << "\nCouldn't allocate memory. Exiting...\n\a";
		exit;
	}
	myTop = original.myTop;
	for (int i = 0; i < myCapacity; i++)
		myArray[i] = original.myArray[i];
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
	if (myTop == myCapacity-1)
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