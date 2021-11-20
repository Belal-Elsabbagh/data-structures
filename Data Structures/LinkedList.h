#pragma once
//
//  List.hpp
//  LinkedList
//
//  Created by Ashraf AbdelRaouf on 9/23/15.
//  Copyright © 2015 Ashraf AbdelRaouf. All rights reserved.
//

#include <iostream>
using namespace std;
typedef int ElementType;

class LinkedList
{



private:

    class Node {
    public:

        //------ Node DATA MEMBERS
        ElementType data;
        Node* next;

        //------ Node OPERATIONS
        //-- Default constrctor: initializes next member to Node()
        Node()
            : next(0)
        {}

        //-- Explicit-value constructor:  initializes data member to dataValue
        //--                             and next member to 0
        Node(ElementType dataValue)
            : data(dataValue), next(0)
        {}
    }; //--- end of Node class

    typedef Node* NodePointer;


    //------ DATA MEMBERS
    NodePointer first;
    int mySize;

public:
    //------ List OPERATIONS
    LinkedList();
    /*--------------------------------------------------------------------
     Default constructor: builds an empty List object.
     Precondition:  None
     Postcondition: first is 0 and mySize is 0.
     --------------------------------------------------------------------*/
    LinkedList(const LinkedList& origList);
    /*--------------------------------------------------------------------
     Copy constructor
     Precondition:  A copy of origList is needed.
     Postcondition: A distincr copy of origList has been constructed.
     --------------------------------------------------------------------*/
    ~LinkedList();
    /*--------------------------------------------------------------------
     Destructor
     Precondition:  This list's lifetime is over.
     Postcondition: This list has been destroyed.
     --------------------------------------------------------------------*/
    const LinkedList& operator=(const LinkedList& rightSide);
    /*--------------------------------------------------------------------
     Assignment operator
     Precondition:  This list must be assigned a value.
     Postcondition: A copy of rightSide has been assigned to this list.
     --------------------------------------------------------------------*/
    bool empty();
    /*--------------------------------------------------------------------
     Check if this list is empty
     Precondition:  None.
     Postcondition: true is returned if this list is empty, false if not.
     --------------------------------------------------------------------*/
    void insert(ElementType dataVal, int index);
    /*--------------------------------------------------------------------
     Insert a value into a list at a given index.
     Precondition:  index is a valid list index: 0 <= index <= mySize,
     Postcondition: dataVal has been inserted into the list at position
     index, provided index is valid..
     --------------------------------------------------------------------*/
    void erase(int index);
    /*--------------------------------------------------------------------
     Remove a value from a list at a given index.
     Precondition:  index is a valid list index:  0 <= index < mySize
     Postcondition: dataVal at list position index has been removed,
     provided index is valid.
     --------------------------------------------------------------------*/

    void display(ostream& out) const;
    /*--------------------------------------------------------------------
     Display the contensts of this list.
     Precondition:  ostream out is open
     Postcondition: Elements of this list have been output to out.
     --------------------------------------------------------------------*/
    int nodeCount();
    /*--------------------------------------------------------------------
     Count the elements of this list.
     Precondition:  None
     Postcondition: Number of elements in this list is returned.
     --------------------------------------------------------------------*/
    void reverse();
    /*--------------------------------------------------------------------
     Reverse this list.
     Precondition:  None
     Postcondition: Elements in this list have been reversed.
     --------------------------------------------------------------------*/
    bool ascendingOrder();
    /*--------------------------------------------------------------------
     Check if the elements of this list are in ascending order.
     Precondition:  None
     Postcondition: true is returned if the list elements are in
     ascending order, false if not.
     --------------------------------------------------------------------*/
    int search(ElementType dataVal);
    /*--------------------------------------------------------------------
     Search for an data value in this list.
     Precondition:  None
     Postcondition: Index of node containing dataVal is returned
     if such a node is found, -1r if not.
     --------------------------------------------------------------------*/
    void insertUsingInputOperator(istream& in);
    /*--------------------------------------------------------------------
     implementation of operator>> 
     Precondition:  istream out is open
     Postcondition: Elements entered have been inserted to the LinkedList
     --------------------------------------------------------------------*/

}; //--- end of List class

ostream& operator<<(ostream& out, const LinkedList& aList);
istream& operator>>(istream& in, LinkedList& aList);



