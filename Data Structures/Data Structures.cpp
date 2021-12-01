#include <iostream>
#include "StaticList.h"
#include "DynamicList.h"
#include "LinkedList.h"
#include "LLStack.h"
#include "DStack.h"
#include "TQueue.h"
#include "TPriorityQueue.h"
using namespace std;

void LLStackTest();
void TPriorityQueueTest();

int main()
{
    TPriorityQueueTest();
}

void LLStackTest()
{
    LLStack stack;
    stack.empty() ? cout << "Empty\n" : cout << "Not Empty\n";
    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
    }
    stack.display(cout);
    cout << endl;

    stack.pop();
    stack.display(cout);
}

void TPriorityQueueTest()
{
    TPriorityQueue<int> q;
    q.enqueue(40);
    q.enqueue(60);
    q.enqueue(50);

    q.display(cout);
}
