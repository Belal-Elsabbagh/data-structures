//
//  List.h
//  ArrayList
//
/*-- List.h ---------------------------------------------------------------

 This header file defines the data type List for processing lists.
 Basic operations are:
 Constructor
 empty:    Check if list is empty
 insert:   Insert an item
 erase:    Remove an item
 display:  Output the list
 <<:       Output operator
 -------------------------------------------------------------------------*/

#include <iostream>
using std::ostream;
#ifndef STATICLIST
#define STATICLIST

const int CAPACITY = 1024;
typedef int ElementType;

template<class ElementType>
class StaticList
{

private:
    /******** Data Members ********/
    int mySize;                     // current size of list stored in myArray
    std::array<ElementType,CAPACITY> myArray;  // array to store list elements


public:
    /******** Function Members ********/
    /***** Class constructor *****/
    StaticList();
    /*----------------------------------------------------------------------
     Construct a List object.

     Precondition:  None
     Postcondition: An empty List object has been constructed; mySize is 0.
     -----------------------------------------------------------------------*/
     
     /***** Copy constructor *****/
    StaticList(const StaticList<ElementType>& origList);
    /*----------------------------------------------------------------------
     Construct a copy of a List object.

     Precondition:  A copy of origList is needed; origList is a const
     reference parameter.
     Postcondition: A copy of origList has been constructed.
     -----------------------------------------------------------------------*/
     
     /***** Assignment operator *****/
    const StaticList& operator=(const StaticList<ElementType>& rightHandSide);
    /*----------------------------------------------------------------------
     Assign a copy of a List object to the current object.

     Precondition: none
     Postcondition: A copy of rightHandSide has been assigned to this
     object. A const reference to this list is returned.
     -----------------------------------------------------------------------*/

     /***** empty operation *****/
    bool empty() const;
    /*----------------------------------------------------------------------
     Check if a list is empty.

     Precondition:  None
     Postcondition: true is returned if the list is empty, false if not.
     -----------------------------------------------------------------------*/

     /***** insert and erase *****/
    void insert(ElementType item, int pos);
    /*----------------------------------------------------------------------
     Insert a value into the list at a given position.

     Precondition:  item is the value to be inserted; there is room in
     the array (mySize < CAPACITY); and the position satisfies
     0 <= pos <= mySize.
     Postcondition: item has been inserted into the list at the position
     determined by pos (provided there is room and pos is a legal
     position).
     -----------------------------------------------------------------------*/

    void erase(int pos);
    /*----------------------------------------------------------------------
     Remove a value from the list at a given position.

     Precondition:  The list is not empty and the position satisfies
     0 <= pos < mySize.
     Postcondition: element at the position determined by pos has been
     removed (provided pos is a legal position).
     ----------------------------------------------------------------------*/

     /***** output *****/
    void display(ostream& out) const;
    /*----------------------------------------------------------------------
     Display a list.

     Precondition:  The ostream out is open.
     Postcondition: The list represented by this List object has been
     inserted into out.
     -----------------------------------------------------------------------*/

    void leftRotation(int numOfRotations);
    void removeDuplicates();
    void deleteByValue(ElementType item);
	std::ostream& operator<<(std::ostream& out);

}; //--- end of List class

//------ Prototype of output operator
ostream& operator<< (ostream& out, const StaticList<ElementType>& aList);

#endif

template<class ElementType>
StaticList<ElementType>::StaticList()
{
	mySize = 0;
}

template<class ElementType>
StaticList<ElementType>::StaticList(const StaticList<ElementType>& origList) : mySize(origList.mySize)
{
	for (int i = 0; i < mySize; i++)
		myArray[i] = origList.myArray[i];
}

template<class ElementType>
const StaticList<ElementType>& StaticList<ElementType>::operator=(const StaticList<ElementType>& rightHandSide)
{
	// TODO: insert return statement here
	return *this;
}

template<class ElementType>
bool StaticList<ElementType>::empty() const
{
	return mySize == 0;
}

template<class ElementType>
void StaticList<ElementType>::insert(ElementType item, int pos)
{
	if (mySize == CAPACITY)
	{
		cerr << "No space to insert.\n\a";
		exit(1);
	}
	if (pos < 0 || pos > mySize)
	{
		cerr << "Invalid Insertion. Operation Terminated with no change.\n\a";
		return;
	}
	else // after validating size and index...
	{
		// shift elements to the right
		for (int i = mySize; i > pos; i--)
		{
			myArray[i] = myArray[i - 1];
		}

		myArray[pos] = item; // insert element
		mySize++; // increase size by 1
	}
}

template<class ElementType>
void StaticList<ElementType>::erase(int pos)
{
	if (pos < 0 || pos >= mySize || mySize == 0)
		cerr << "Invalid Deletion. Operation Terminated with no change.\n\a";
	else
	{
		// shift elements to the left & overwrite the element to be erased
		for (int i = pos; i < mySize; i++)
		{
			myArray[i] = myArray[i + 1];
		}
		mySize--;
	}
}

template<class ElementType>
void StaticList<ElementType>::display(ostream& out) const
{
	cout << "\nDisplaying List...\n";
	for (int i = 0; i < mySize; i++)
	{
		cout << myArray[i] << ", ";
	}
}

template<class ElementType>
void StaticList<ElementType>::leftRotation(int numOfRotations)
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

template<class ElementType>
void StaticList<ElementType>::removeDuplicates()
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

template<class ElementType>
void StaticList<ElementType>::deleteByValue(ElementType item)
{
	for (int i = 0; i < mySize; i++)
	{
		if (item == myArray[i])
		{
			this->erase(i);
			return;
		}
	}
}

ostream& StaticList<ElementType>::operator<<(ostream& out)
{
	this->display(out);
	return out;
}