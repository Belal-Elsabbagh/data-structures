#include "DynamicList.h"
#include <cassert>
#include <new>
DynamicList::DynamicList(int maxSize) : mySize(0), myCapacity(maxSize)
{
	myArray = new(nothrow) ElementType[myCapacity];
	assert(myArray != 0);
}

DynamicList::~DynamicList()
{
	delete[] myArray;
}

DynamicList::DynamicList(const DynamicList& origList) : mySize(origList.mySize), myCapacity(origList.myCapacity)
{
	myArray = new(nothrow) ElementType[origList.myCapacity];
	if (myArray == 0)
	{
		cerr << "\nCouldn't allocate memory. Exiting...\n\a";
		exit;
	}
	for (int i = 0; i < mySize; i++)
		myArray[i] = origList.myArray[i];
}

const DynamicList& DynamicList::operator=(const DynamicList& rightHandSide)
{
	if (this != &rightHandSide)
	{
		if (myCapacity != rightHandSide.myCapacity)
		{
			delete[] myArray;
			myCapacity = rightHandSide.myCapacity;
			myArray = new ElementType[myCapacity];
		}
		if (myArray == 0)
		{
			cout << "\nCouldn't allocate memory. Exiting...\n\a";
			exit;
		}
		mySize = rightHandSide.mySize;
		for (int i = 0; i < mySize; i++)
			myArray[i] = rightHandSide.myArray[i];
	}

	return *this;
}

bool DynamicList::empty() const
{
	return mySize == 0;
}

void DynamicList::insert(ElementType item, int pos)
{
	if (pos < 0 || pos > mySize || mySize == myCapacity)
	{
		cout << "Invalid Insertion. Operation Terminated with no change.\n\a";
	}
	else
	{
		for (int i = mySize; i > pos; i--)
		{
			myArray[i] = myArray[i - 1];
		}
		myArray[pos] = item;
		mySize++;
	}
}

void DynamicList::erase(int pos)
{
	if (pos < 0 || pos >= mySize || mySize == 0)
		cerr << "Invalid Deletion. Operation Terminated with no change.\n\a";
	else
	{
		for (int i = pos; i < mySize; i++)
		{
			myArray[i] = myArray[i + 1];
		}
		mySize--;
	}
}

void DynamicList::reverse()
{
	for (int i = 0; i < mySize/2; i++)
	{
		ElementType temp = myArray[i];
		myArray[i] = myArray[mySize - 1 - i];
		myArray[mySize - 1 - i] = temp;
	}
}

const DynamicList DynamicList::operator+(DynamicList rightHandSide)
{
	for(int i = mySize; i < mySize +rightHandSide.mySize; i++)
		myArray[i] = rightHandSide.myArray[i];
	mySize += rightHandSide.mySize;
}

void DynamicList::display(ostream& out) const
{
	out << "\nDisplaying List...\n";
	for (int i = 0; i < mySize; i++)
	{
		out << myArray[i] << ", ";
	}
}

ostream& operator<<(ostream& out, const DynamicList& aList)
{
	aList.display(out);
	return out;
}
