#include "LLStack.h"
using namespace std;
LLStack::LLStack()
{
	myTop = NULL;
}

LLStack::LLStack(const LLStack& original)
{
	if (original.empty()) 
	{
		myTop = nullptr;
	}

	else 
	{
		NodePointer p = original.myTop;
		NodePointer tmp = new Node(p->data);

		myTop = tmp;
		myTop->next = p->next;

		NodePointer tail = tmp;
		while (p->next != nullptr) 
		{
			p = p->next;
			tmp = new Node(p->data);
			tail->next = tmp;
			tail = tmp;
		}
	}
}

LLStack::~LLStack()
{
	while (!empty())
	{
		pop();
	}
}

const LLStack& LLStack::operator=(const LLStack& rightHandSide)
{
	if (rightHandSide.empty()) 
	{
		myTop = nullptr;
	}
	else 
	{
		this->~LLStack();

		NodePointer p = rightHandSide.myTop;
		NodePointer tmp = new Node(p->data);
		myTop = tmp;
		myTop->next = p->next;
		NodePointer tail = tmp;
		while (p->next != nullptr) 
		{
			p = p->next;
			tmp = new Node(p->data);
			tail->next = tmp;
			tail = tmp;
		}
	}
	return *this;
}

bool LLStack::empty() const
{
	return myTop == NULL;
}

void LLStack::push(const StackElement& value)
{
	NodePointer temp = new Node(value);

	temp->next = myTop;
	myTop = temp;
}

void LLStack::display(ostream& out) const
{
	for (NodePointer ptr = myTop; ptr != 0; ptr = ptr->next)
		out << ptr->data << endl;
}

StackElement LLStack::top() const
{
	return myTop->data;
}

void LLStack::pop()
{
	NodePointer ptr = myTop;
	myTop = myTop->next;
	delete ptr;
}

void LLStack::intersection(const LLStack& s1, LLStack& s)
{
	
}

StackElement LLStack::bottom() const
{
	return StackElement();
}
