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
	const DStack& operator= (const DStack& righthandside);
	~DStack();
	bool empty() const;
	void push(const StackElement& value);
	void display(ostream& out) const;
	StackElement top() const;
	void pop();
};