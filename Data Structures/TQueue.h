/*-- TQueue.h -------------------------------------------------------------

 This header file defines a Queue data type.
 Basic operations:
 constructor:  Constructs an empty queue
 empty:        Checks if a queue is empty
 enqueue:      Modifies a queue by adding a value at the back
 front:        Accesses the top queue value; leaves queue unchanged
 dequeue:      Modifies queue by removing the value at the front
 display:      Displays all the queue elements
 Note: Execution terminates if memory isn't available for a queue element.
 ---------------------------------------------------------------------------*/

#include<iostream>
#include<vector>
using namespace std;

template<class QueueElement>
class TQueue
{
public:
	/***** Function Members *****/
	//(3) - Apply the required changes to each function definition from the following


	/***** Constructors *****/
	TQueue();
	/*-----------------------------------------------------------------------
	 Construct a Queue object.

	 Precondition:  None.
	 Postcondition: An empty Queue object has been constructed.
	 (myFront and myBack are initialized to null pointers).
	 -----------------------------------------------------------------------*/

	TQueue(const TQueue& original);
	/*-----------------------------------------------------------------------
	 Copy Constructor

	 Precondition:  original is the queue to be copied and is received
	 as a const reference parameter.
	 Postcondition: A copy of original has been constructed.
	 -----------------------------------------------------------------------*/

	 /***** Destructor *****/
	~TQueue();
	/*-----------------------------------------------------------------------
	 Class destructor

	 Precondition:  None.
	 Postcondition: The linked list in the queue has been deallocated.
	 -----------------------------------------------------------------------*/

	 /***** Assignment *****/
	const TQueue& operator= (const TQueue& rightHandSide);
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

	void enqueue(const QueueElement& value);
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

	//(4) - The member variable here will be a Vector from the Standard Template Library in C++
	// Therefore, you need to remove the LinkedList used and replace it with this Vector that you'll create
	//Hint: use #include <vector> at the begining of the file

	vector<QueueElement> myArray;
};

/*-----------------------------------------------------------------------
 the vector library already has its constructors, destructors,
 overloaded operators.
 There's not really a need to implement more things.
 -----------------------------------------------------------------------*/

template<class QueueElement>
TQueue<QueueElement>::TQueue(const TQueue& original)
{
	myArray = original.myArray;
}

template<class QueueElement>
TQueue<QueueElement>::~TQueue()
{
	myArray.clear();
}

template<class QueueElement>
bool TQueue<QueueElement>::empty() const
{
	return myArray.empty();
}

template<class QueueElement>
void TQueue<QueueElement>::enqueue(const QueueElement& value)
{
	myArray.push_back(value);
}

template<class QueueElement>
void TQueue<QueueElement>::display(ostream& out) const
{
	for (const QueueElement& item : myArray)
	{
		out << item << ", ";
	}
}

template<class QueueElement>
QueueElement TQueue<QueueElement>::front() const
{
	return myArray.front();
}

template<class QueueElement>
void TQueue<QueueElement>::dequeue()
{
	myArray.erase(0);
}
