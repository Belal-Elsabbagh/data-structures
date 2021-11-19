#include <iostream>
using namespace std;
typedef int StackElement;

class DStack {
public:
	DStack(int numElements = 128);
	DStack(const DStack& original);
	const DStack& operator= (const DStack& righthandside);
	bool empty() const;
	void push(const StackElement& value);
	~DStack();
	void display(ostream& out) const;
	StackElement top() const;
	void pop();
private:
	int mycapacity;
	int mytop;
	StackElement* myarray;

};