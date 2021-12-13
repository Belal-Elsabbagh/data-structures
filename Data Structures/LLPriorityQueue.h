#pragma once
#include <iostream>
using namespace std;

template<class QueueElement>
class LLPriorityQueue
{
public:
	/***** Function Members *****/
	/***** Constructors *****/
	LLPriorityQueue();
	/*-----------------------------------------------------------------------
	 Construct a Queue object.

	 Precondition:  None.
	 Postcondition: An empty Queue object has been constructed.
	 (myFront and myBack are initialized to null pointers).
	 -----------------------------------------------------------------------*/

	LLPriorityQueue(const LLPriorityQueue& original);
	/*-----------------------------------------------------------------------
	 Copy Constructor

	 Precondition:  original is the queue to be copied and is received
	 as a const reference parameter.
	 Postcondition: A copy of original has been constructed.
	 -----------------------------------------------------------------------*/

	 /***** Destructor *****/
	~LLPriorityQueue();
	/*-----------------------------------------------------------------------
	 Class destructor

	 Precondition:  None.
	 Postcondition: The linked list in the queue has been deallocated.
	 -----------------------------------------------------------------------*/

	 /***** Assignment *****/
	const LLPriorityQueue& operator= (const LLPriorityQueue& rightHandSide);
	/*-----------------------------------------------------------------------
	 Assignment Operator

	 Precondition:  rightHandSide is the queue to be assigned and is
	 received as a const reference parameter.
	 Postcondition: The current queue becomes a copy of rightHandSide
	 and a reference to it is returned.
	 -----------------------------------------------------------------------*/

	bool empty() const;
	/*-----------------------------------------------------------------------
	 Check if queue is empty.

	 Precondition:  None.
	 Postcondition: Returns true if queue is empty and false otherwise.
	 -----------------------------------------------------------------------*/

	void enqueue(const QueueElement& value, const int& priority);
	/*-----------------------------------------------------------------------
	 Add a value to a queue.

	 Precondition:  value is to be added to this queue.
	 Postcondition: value is added at back of queue.
	 -----------------------------------------------------------------------*/

	void display(ostream& out) const;
	/*-----------------------------------------------------------------------
	 Display values stored in the queue.

	 Precondition:  ostream out is open.
	 Postcondition: Queue's contents, from front to back, have been
	 output to out.
	 -----------------------------------------------------------------------*/

	QueueElement front() const;
	/*-----------------------------------------------------------------------
	 Retrieve value at front of queue (if any).

	 Precondition:  Queue is nonempty.
	 Postcondition: Value at front of queue is returned, unless the queue
	 is empty; in that case, an error message is displayed.
	 -----------------------------------------------------------------------*/

	void dequeue();
	/*-----------------------------------------------------------------------
	 Remove value at front of queue (if any).

	 Precondition:  Queue is nonempty.
	 Postcondition: Value at front of queue has been removed, unless
	 queue is empty; in that case, an error message is displayed
	 and execution allowed to proceed.
	 -----------------------------------------------------------------------*/

private:

	/*** Node class ***/
	class Node
	{
	public:
		QueueElement data;
		int priority; // lower is better (like first class and second class)
		Node* next;

		//--- Node constructor
		Node(QueueElement value, int p) { data = value; next = 0; priority = p;}
		/*-------------------------------------------------------------------
		 Precondition:  value and link are received
		 Postcondition: A Node has been constructed with value in its
		 data part and its next part set to link (default 0).
		 ------------------------------------------------------------------*/

		Node(Node* orig) { data = orig->data; next = orig->next; priority = orig->priority; }
	};

	typedef Node* NodePointer;

	/***** Data Members *****/
	NodePointer myFront,      // pointer to front of queue
		myBack;       // pointer to back of queue

}; // end of class declaration

template <class QueueElement>
LLPriorityQueue<QueueElement>::LLPriorityQueue()
{
	myFront = myBack = 0;
}

template<class QueueElement>
LLPriorityQueue<QueueElement>::LLPriorityQueue(const LLPriorityQueue& original)
{
	NodePointer origPtr;
	NodePointer lastPtr;
	myFront = new Node(original.myFront); // copy first node

	// set pointers to point to the first nodes in both lists respectively
	lastPtr = myFront;
	origPtr = original.myFront->next; // makes origPtr leading by one node

	while (origPtr != original.myBack) //as long as the original list isn't at the end
	{
		// intitializes the next node by the data in origPtr
		lastPtr->next = new Node(origPtr);

		// traverses through list
		origPtr = origPtr->next;
		lastPtr = lastPtr->next;
	}
	myBack = lastPtr;
}

template<class QueueElement>
LLPriorityQueue<QueueElement>::~LLPriorityQueue()
{
	NodePointer prev = myFront;
	NodePointer ptr;
	while (prev != myBack)
	{
		ptr = prev->next; // pointer catches the next node in the list
		delete prev; // delete current node
		prev = ptr; // set the current node to next
	}
	myBack = myFront;
}

template<class QueueElement>
const LLPriorityQueue<QueueElement>& LLPriorityQueue<QueueElement>::operator=(const LLPriorityQueue<QueueElement>& rightSide)
{
	/*--------------------------------------------------------------------
	 The assignment operator uses the copy constructor to assign the
	 right hand side after clearing the current data in the object.
	 --------------------------------------------------------------------*/

	if (rightSide.empty()) return *this;

	if (this != &rightSide)
	{
		this->~LLPriorityQueue(); // destructs the left hand side
		LLPriorityQueue(rightSide); // constructs the copy in this object
	}

	return *this;
}

template<class QueueElement>
bool LLPriorityQueue<QueueElement>::empty() const
{
	return myBack == myFront;
}

template<class QueueElement>
void LLPriorityQueue<QueueElement>::enqueue(const QueueElement& value, const int& priority)
{
	Node* start = myFront;

	// Create new Node
	NodePointer temp = new Node(value, priority);

	// Special Case: The head of list has
	// lesser priority than new node. So
	// insert newnode before head node
	// and change head node.
	if (this->empty())
	{
		myFront = temp;
		return;
	}
	if (myFront->priority > priority)
	{

		// Insert New Node before head
		temp->next = myFront;
		myFront = temp;
		return;
	}

	// Traverse the list and find a
	// position to insert new node
	while (start->next != NULL && start->next->priority < temp->priority)
	{
		start = start->next;
	}
	// Either at the ends of the list
	// or at required position
	temp->next = start->next;
	start->next = temp;
}

template<class QueueElement>
void LLPriorityQueue<QueueElement>::display(ostream& out) const
{
	NodePointer ptr = myFront;
	while (ptr != 0)
	{
		out << ptr->priority << ") " << ptr->data << "\n";
		ptr = ptr->next;
	}
}

template<class QueueElement>
QueueElement LLPriorityQueue<QueueElement>::front() const
{
	return myFront;
}

template<class QueueElement>
void LLPriorityQueue<QueueElement>::dequeue()
{
	// If queue is empty, return NULL.
	if (myFront == NULL)
		return;

	// Store previous front and
	// move front one node ahead
	NodePointer temp = myFront;
	myFront = myFront->next;

	// If front becomes NULL, then
	// change rear also as NULL
	if (myFront == NULL)
		myBack = NULL;

	delete temp;
}