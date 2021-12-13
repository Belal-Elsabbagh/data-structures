#include <iostream>

//-- Structure Headers
#include "StaticList.h"
#include "DynamicList.h"
#include "LinkedList.h"
#include "LLStack.h"
#include "DStack.h"
#include "TQueue.h"
#include "TPriorityQueue.h"
#include "LLQueue.h"
#include "LLPriorityQueue.h"

using namespace std;

void LLStackTest();
void TPriorityQueueTest();
void LLPriorityQueueTest();

int main()
{
    LLPriorityQueueTest();
}

void LLStackTest()
{
    LLStack stack;
    stack.empty() ? cout << "Empty\n" : cout << "Not Empty\n";
    
    for (size_t i = 0; i < 10; i++)
    {
        stack.push(i);
    }

    stack.display(cout);
    cout << endl;

    stack.pop();
    stack.display(cout);

    cout << "\nTop is: "  << stack.top()    << endl
         << "Bottom is: " << stack.bottom() << endl;
}

void TPriorityQueueTest()
{
    TPriorityQueue<int> q1;
    q1.enqueue(40);
    q1.enqueue(60);
    q1.enqueue(50);

    TPriorityQueue<int> q2 = q1;
    q2.display(cout);

    q2.dequeue();
    q2.display(cout);
}

void LLQueueTest()
{
    LLQueue<int> q1;
    q1.enqueue(40);
    q1.enqueue(60);
    q1.enqueue(50);

    LLQueue<int> q2 = q1;
    q2.display(cout);

    q2.dequeue();
    q2.display(cout);
}

void LLPriorityQueueTest()
{
    LLPriorityQueue<int> q1;
    q1.enqueue(9, 5);
    q1.enqueue(8, 1);
    q1.enqueue(4, 3);

    LLPriorityQueue<int> q2 = q1;
    q2.display(cout);
    cout << endl;
    q2.dequeue();
    q2.display(cout);
}

void LinkedListTest()
{
    LinkedList q1;
    q1.insert(40, 0);
    q1.insert(50, 1);
    q1.insert(60, 2);

    LinkedList q2 = q1;
    q2.display(cout);

    q2.erase(1);
    q2.display(cout);
}