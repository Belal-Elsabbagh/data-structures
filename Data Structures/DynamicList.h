
//
//  DList.hpp
//  DynamicList
//
//  Created by Ashraf AbdelRaouf on 9/22/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//
/*-- DynamicList.h --------------------------------------------------------------

 This header file defines the data type List for processing lists.
 Basic operations are:
 Constructor
 Destructor
 Copy constructor
 Assignment operator
 empty:    Check if list is empty
 insert:   Insert an item
 erase:    Remove an item
 display:  Output the list
 << :      Output operator
 -------------------------------------------------------------------------*/
#pragma once
#include <iostream>
#include <cassert>
#include <new>
using namespace std;

/*----------------------------------------------------------------------
  IMPORTANT NOTE

  This is a standard implementation of a simple list. The only
  difference is that it uses a dynamic array which sets the max capacity
  with a user defined value.

  There won't be any difference in functions.

  The main changes will be in constructor, copy constructor,
  assignment operator, and destructor.
  ----------------------------------------------------------------------*/
template<class ElementType>
class DynamicList
{
private:
    /******** Data Members ********/
    int mySize;                // current size of list
    int myCapacity;            // capacity of array
    ElementType* myArray;     // pointer to dynamic array

public:
    /******** Function Members ********/
    /***** Class constructor *****/
    DynamicList(int maxSize = 1024);
    /*----------------------------------------------------------------------
     Construct a List object.

     Precondition:  maxSize is a positive integer with default value 1024.
     Postcondition: An empty List object is constructed; myCapacity ==
     maxSize (default value 1024); myArray points to a dynamic
     array with myCapacity as its capacity; and mySize is 0.
     -----------------------------------------------------------------------*/

     /***** Class destructor *****/
    ~DynamicList();
    /*----------------------------------------------------------------------
     Destroys a List object.

     Precondition:  The life of a List object is over.
     Postcondition: The memory dynamically allocated by the constructor
     for the array pointed to by myArray has been returned to the heap.
     -----------------------------------------------------------------------*/

     /***** Copy constructor *****/
    DynamicList(const DynamicList& origList);
    /*----------------------------------------------------------------------
     Construct a copy of a List object.

     Precondition:  A copy of origList is needed; origList is a const
     reference parameter.
     Postcondition: A copy of origList has been constructed.
     -----------------------------------------------------------------------*/

     /***** Assignment operator *****/
    const DynamicList& operator=(const DynamicList& rightHandSide);
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
    void reverse();
    const DynamicList operator+(DynamicList rightHandSide);
    /*----------------------------------------------------------------------
     Remove a value from the list at a given position.

     Precondition:  The list is not empty and the position satisfies
     0 <= pos < mySize.
     Postcondition: element at the position determined by pos has been
     removed (provided pos is a legal position).
     ----------------------------------------------------------------------*/

     /***** output *****/
    void display(std::ostream& out) const;
    /*----------------------------------------------------------------------
     Display a list.

     Precondition:  The ostream out is open.
     Postcondition: The list represented by this List object has been
     inserted into out.
     -----------------------------------------------------------------------*/

    ostream& operator<<(ostream& out);

}; //--- end of List class

template<class ElementType>
DynamicList<ElementType>::DynamicList(int maxSize) : mySize(0), myCapacity(maxSize)
{
    myArray = new(nothrow) ElementType[myCapacity];
    assert(myArray != 0);
}

template<class ElementType>
DynamicList<ElementType>::~DynamicList()
{
    delete[] myArray;
}

template<class ElementType>
DynamicList<ElementType>::DynamicList(const DynamicList<ElementType>& origList) 
    : mySize(origList.mySize), myCapacity(origList.myCapacity)
{
    myArray = new(nothrow) ElementType[origList.myCapacity];
    if (myArray == 0)
    {
        cerr << "\nCouldn't allocate memory. Exiting...\n\a";
        exit(1);
    }
    for (int i = 0; i < mySize; i++)
        myArray[i] = origList.myArray[i];
}

template<class ElementType>
const DynamicList<ElementType>& DynamicList<ElementType>::operator=(const DynamicList<ElementType>& rightHandSide)
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
            exit(1);
        }
        mySize = rightHandSide.mySize;
        for (int i = 0; i < mySize; i++)
            myArray[i] = rightHandSide.myArray[i];
    }
    return *this;
}

/*----------------------------------------------------------------------
  Check notes in StaticList.cpp for studying.
  ----------------------------------------------------------------------*/

template<class ElementType>
bool DynamicList<ElementType>::empty() const
{
    return mySize == 0;
}

template<class ElementType>
void DynamicList<ElementType>::insert(ElementType item, int pos)
{
    if (pos < 0 || pos > mySize || mySize == myCapacity)
    {
        cout << "Invalid Insertion. Operation Terminated with no change.\n\a";
        return;
    }

    for (int i = mySize; i > pos; i--)
    {
        myArray[i] = myArray[i - 1];
    }
    myArray[pos] = item;
    mySize++;
}

template<class ElementType>
void DynamicList<ElementType>::erase(int pos)
{
    if (pos < 0 || pos >= mySize || mySize == 0)
    {
        cerr << "Invalid Deletion. Operation Terminated with no change.\n\a";
        return;
    }

    for (int i = pos; i < mySize; i++)
    {
        myArray[i] = myArray[i + 1];
    }
    mySize--;
}

template<class ElementType>
void DynamicList<ElementType>::reverse()
{
    for (int i = 0; i < mySize / 2; i++)
    {
        ElementType temp = myArray[i];
        myArray[i] = myArray[mySize - 1 - i];
        myArray[mySize - 1 - i] = temp;
    }
}

template<class ElementType>
const DynamicList<ElementType> DynamicList<ElementType>::operator+(DynamicList<ElementType> rightHandSide)
{
    for (int i = mySize; i < mySize + rightHandSide.mySize; i++)
        myArray[i] = rightHandSide.myArray[i];
    mySize += rightHandSide.mySize;
    return *this;
}

template<class ElementType>
void DynamicList<ElementType>::display(ostream& out) const
{
    out << "\nDisplaying List...\n";
    for (int i = 0; i < mySize; i++)
    {
        out << myArray[i] << ", ";
    }
}

ostream& DynamicList<ElementType>::operator<<(ostream& out)
{
    this->display(out);
    return out;
}

