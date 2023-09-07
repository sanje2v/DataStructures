// Stack.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Stack.h"


int main()
{
    Stack<int> stack(2);
    stack.push(1);
    stack.push(2);
    stack.push(3);

    std::cout << stack;

    return 0;
}