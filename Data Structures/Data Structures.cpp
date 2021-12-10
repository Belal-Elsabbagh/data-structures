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
#include "BST.h"

using namespace std;

void LLStackTest();
void TPriorityQueueTest();
void BinaryTreeTest();

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

void BinaryTreeTest()
{
    
}