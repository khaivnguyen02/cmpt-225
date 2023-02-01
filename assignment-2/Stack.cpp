
#include "Stack.h"

#include <stdexcept>
#include <iostream>

// Desc:  Object constructor
// Post:  size of stack is set to 0
Stack::Stack(): size(0) {}

// Desc:  Insert element x to the top of the stack.
//  Pre:  size < STACKCAP
// Post:  Element x is inserted at index 0
void Stack::push(int x)
{
    if (size == STACKCAP)
    {
        throw std::logic_error("Stack's capacity is full!");
    }

    // Increase the size by 1
    size++;

    // Shift all elements one position forward
    for(int i = size - 1; i >= 0; i--)
        arr[i] = arr[i - 1];
    
    // Insert x at index 0
    arr[0] = x;
}

// Desc:  Remove and return element at the top of the stack.
//  Pre:  size > 0
// Post:  Element at index 0 is removed and returned
int Stack::pop()
{
    if (size == 0)
    {
        throw std::logic_error("Stack is empty!");
    }

    size--;

    int pop = arr[0];

    for (int i = 0; i < size; i++)
    {
        arr[i] = arr[i + 1];
    }

    return pop;
}

// Desc:  Return the topmost element of the stack.
//  Pre:  size > 0
// Post:  Element at index 0 is returned without remove
int Stack::peek() const
{
    if (size == 0)
    {
        throw std::logic_error("Stack is empty!");
    }
    return arr[0];
}

// Desc:  Check if the stack is empty
// Post:  Return true if the stack is empty, return false otherwise
bool Stack::isEmpty() const
{
    return (size == 0);
}
