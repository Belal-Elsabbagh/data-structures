#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<class QueueElement>
class TPriorityQueue
{
public:
	/***** Function Members *****/
	//(3) - Apply the required changes to each function definition from the following


	/***** Constructors *****/
	TPriorityQueue();
	/*-----------------------------------------------------------------------
	 Construct a Queue object.

	 Precondition:  None.
	 Postcondition: An empty Queue object has been constructed.
	 (myFront and myBack are initialized to null pointers).
	 -----------------------------------------------------------------------*/

	TPriorityQueue(const TPriorityQueue& original);
	/*-----------------------------------------------------------------------
	 Copy Constructor

	 Precondition:  original is the queue to be copied and is received
	 as a const reference parameter.
	 Postcondition: A copy of original has been constructed.
	 -----------------------------------------------------------------------*/

	 /***** Destructor *****/
	~TPriorityQueue();
	/*-----------------------------------------------------------------------
	 Class destructor

	 Precondition:  None.
	 Postcondition: The linked list in the queue has been deallocated.
	 -----------------------------------------------------------------------*/

	 /***** Assignment *****/
	const TPriorityQueue& operator= (const TPriorityQueue& rightHandSide);
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
TPriorityQueue<QueueElement>::TPriorityQueue() {}

template<class QueueElement>
TPriorityQueue<QueueElement>::TPriorityQueue(const TPriorityQueue& original)
{
	myArray = original.myArray;
}

template<class QueueElement>
TPriorityQueue<QueueElement>::~TPriorityQueue()
{
	myArray.clear();
}

template<class QueueElement>
bool TPriorityQueue<QueueElement>::empty() const
{
	return myArray.empty();
}

template<class QueueElement>
void TPriorityQueue<QueueElement>::enqueue(const QueueElement& value)
{
	if (empty())
		myArray.insert(myArray.begin(), value);
	else
	{
		cout << "vector size: " << myArray.size() << endl;

		typename vector<QueueElement>::iterator end = myArray.end();
		for (int i = myArray.size(); i > 0; i--)
		{
			int x = i - 1;

			if (value < myArray[x])
				break;
			else
				end = prev(end);
		}

		myArray.insert(end, value);
	}
}

template<class QueueElement>
void TPriorityQueue<QueueElement>::display(ostream& out) const
{
	for (const QueueElement& item : myArray) 
	{
		out << item << ", ";
	}
}

template<class QueueElement>
QueueElement TPriorityQueue<QueueElement>::front() const
{
	return myArray.front();
}

template<class QueueElement>
void TPriorityQueue<QueueElement>::dequeue()
{
	myArray.erase(0);
}