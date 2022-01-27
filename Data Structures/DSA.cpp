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
#include "ModelBinarySearchTree.h"
#include "Sorting.h"
#include <list>

void LLStackTest();
void TPriorityQueueTest();
void LLPriorityQueueTest();
void LinkedListTest();
void ModelBSTTest();
void SortingTest();

int main()
{
    SortingTest();
}

void LLStackTest()
{
    LLStack<int> stack;
    stack.empty() ? std::cout << "Empty\n" : std::cout << "Not Empty\n";
    
    for (size_t i = 0; i < 10; i++)
    {
        stack.push(i);
    }

    std::cout << stack;
    std::cout << "\n";

    stack.pop();
    stack.display(std::cout);

    std::cout << "\nTop is: "  << stack.top()    << "\n"
         << "Bottom is: " << stack.bottom() << "\n";
}

void TPriorityQueueTest()
{
    TPriorityQueue<int> q1;
    q1.enqueue(40);
    q1.enqueue(60);
    q1.enqueue(50);

    TPriorityQueue<int> q2 = q1;
    q2.display(std::cout);

    q2.dequeue();
    q2.display(std::cout);
}

void LLQueueTest()
{
    LLQueue<int> q1;
    q1.enqueue(40);
    q1.enqueue(60);
    q1.enqueue(50);

    LLQueue<int> q2 = q1;
    q2.display(std::cout);

    q2.dequeue();
    q2.display(std::cout);
}

void LLPriorityQueueTest()
{
    LLPriorityQueue<int> q1;
    q1.enqueue(9, 5);
    q1.enqueue(8, 1);
    q1.enqueue(4, 3);

    LLPriorityQueue<int> q2 = q1;
    
    q2.display(std::cout);
    std::cout << "\n";
    q2.dequeue();
    q2.display(std::cout);
}

void LinkedListTest()
{
    LinkedList<int> q1;
    q1.insert(40, 0);
    q1.insert(50, 1);
    q1.insert(60, 2);

    LinkedList<int> q2 = q1;
    q2.display(std::cout);

    q2.erase(1);
    q2.display(std::cout);
}

void ModelBSTTest()
{
    ModelBST<int> tree;

    tree.insert(96);
    tree.insert(39);
    tree.insert(96);
    tree.insert(42);
    tree.insert(9);
    tree.insert(482);
    tree.insert(55);

    tree.graph(std::cout);

    tree.remove(42);

    tree.graph(std::cout);
}

void SortingTest()
{
    std::list<int> list {527,373,789,3,67,372,672,683};
    Sorting s;
    s.RadixSort(list, 3);
    for (int i : list)
        cout << i << " ";
}

