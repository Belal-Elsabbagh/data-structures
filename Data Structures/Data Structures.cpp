#include <iostream>
#include "StaticList.h"
#include "DynamicList.h"
#include "LinkedList.h"
#include "LLStack.h"
#include "DStack.h"
#include "TQueue.h"
using namespace std;

int main()
{
    LLStack stack;
    stack.empty() ? cout<<"Empty\n" : cout<<"Not Empty\n";
    for (int i = 0; i < 10; i++)
    {
        stack.push(i);
    }
    stack.display(cout);
    cout << endl;

    stack.pop();
    stack.display(cout);

}
