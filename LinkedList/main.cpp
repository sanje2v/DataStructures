// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LinkedList.h"


int main()
{
    LinkedList<int> llist;
    llist.insertBack(1);
    llist.insertBack(2);
    llist.insertBack(3);
    llist.insertBack(4);
    llist.insertFront(0);
    llist.removeFirst();
    llist.removeLast();
    llist.removeLast();
    llist.removeFirst();
    llist.reverse();

    std::cout << llist;

    return 0;
}
