// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>

#include "Stack.h"
#include "StackWithLinkedList.h"


int main()
{
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << stack;

    return 0;
}