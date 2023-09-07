// DataStructures.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "LinkedList.h"


int main()
{
    LinkedList<int> llist;
    llist.insertLast(1);
    llist.insertLast(2);
    llist.insertLast(3);
    llist.insertLast(4);
    llist.insertFirst(0);
    llist.removeFirst();
    llist.removeLast();
    llist.removeLast();
    llist.removeFirst();
    llist.reverse();

    std::cout << llist;

    return 0;
}
