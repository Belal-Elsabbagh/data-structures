#include "StaticList.h"

StaticList::StaticList()
{
	mySize = 0;
}

StaticList::StaticList(const StaticList& origList) : mySize(origList.mySize)
{
	for (int i = 0; i < mySize; i++)
		myArray[i] = origList.myArray[i];
}

const StaticList& StaticList::operator=(const StaticList& rightHandSide)
{
	// TODO: insert return statement here
}

bool StaticList::empty() const
{
	return mySize == 0;
}

void StaticList::insert(ElementType item, int pos)
{

	if (pos < 0 || pos > mySize || mySize == CAPACITY)
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

void StaticList::erase(int pos)
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

void StaticList::display(ostream& out) const
{
	cout << "\nDisplaying List...\n";
	for (int i = 0; i < mySize; i++)
	{
		cout << myArray[i] << ", ";
	}
}

void StaticList::leftRotation(int numOfRotations)
{
	for (int j = 0; j < numOfRotations; j++)
	{
		ElementType temp = myArray[0];
		for (int i = 0; i < mySize; i++)
		{
			myArray[i] = myArray[i + 1];
		}
		myArray[mySize - 1] = temp;
	}
}

void StaticList::removeDuplicates()
{
	for (int i = 0; i < mySize; i++)
	{
		for (int j = i + 1; j < mySize; j++)
		{
			if (myArray[i] == myArray[j])
				this->erase(j);
		}
	}
}

void StaticList::deleteByValue(ElementType item)
{
	for (int i = 0; i < mySize; i++)
	{
		if (item == myArray[i])
			this->erase(i);
	}
}

ostream& operator<<(ostream& out, const StaticList& aList)
{
	aList.display(out);
	return out;
}