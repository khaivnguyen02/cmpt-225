#include "Queue.h"
#include <stdexcept>
// Desc:  Constructor
Queue::Queue() : size(0), capacity(INITIAL_SIZE), frontindex(0), backindex(0)
{
    arr = new int[capacity];
} // constructor

// Desc:  Destructor
Queue::~Queue()
{
    size = 0;
    frontindex = 0;
    backindex = 0;
    delete[] arr;
} // destructor

// Desc:  Copy Constructor
Queue::Queue(const Queue &other)
{
    if (this != &other)
    {
        size = other.size;
        capacity = other.capacity;
        frontindex = other.frontindex;
        backindex = other.backindex;

        arr = new int[capacity];

        for (unsigned i = 0; i < size; i++)
        {
            arr[i] = other.arr[i];
        }
    }
} // copy constructor

// Desc:  Assignment operator
Queue &Queue::operator=(const Queue &rhs)
{
    if (this != &rhs)
    {
        size = rhs.size;
        capacity = rhs.capacity;
        frontindex = rhs.frontindex;
        backindex = rhs.backindex;

        arr = new int[capacity];

        for (unsigned i = 0; i < size; i++)
        {
            arr[i] = rhs.arr[i];
        }
    }
    return *this;
} // lhs = rhs

// Desc:  Inserts element x at the back (O(1))
void Queue::enqueue(int x)
{
    if (size == capacity)
    {
        capacity *= 2;
        int *temp = new int[capacity];
        for (int i = 0; i <= (capacity / 2); i++)
        {
            temp[i] = arr[frontindex];
            frontindex = (frontindex + 1) % (capacity / 2);
        }
        delete[] arr;
        arr = temp;
        backindex = size;
        frontindex = 0;
    }
    size++;
    arr[backindex] = x;
    backindex = (backindex + 1) % capacity;
} // enqueue

// Desc:  Removes the frontmost element (O(1))
//  Pre:  Queue not empty
void Queue::dequeue()
{
    if (size == 0) // if queue is empty, throw an error
    {
        throw std::logic_error("The Queue is empty");
    }

    if ((size < (capacity / 4)) && ((capacity / 2) >= INITIAL_SIZE))
    {
        capacity /= 2;
        int *temp = new int[capacity];
        for (int i = 0; i < size; i++)
        {
            temp[i] = arr[frontindex];
            frontindex = (frontindex + 1) % (capacity * 2);
        }
        delete[] arr;
        arr = temp;
        frontindex = 0;
    }

    size--;
    frontindex = (frontindex + 1) % capacity;

} // dequeue

// Desc:  Returns a copy of the frontmost element (O(1))
//  Pre:  Queue not empty
int Queue::peek() const
{
    if (isEmpty())
    {
        throw std::logic_error("The Queue is empty");
    }
    return arr[frontindex];
} // top

// Desc:  Returns true if and only if queue empty (O(1))
bool Queue::isEmpty() const
{
    return size == 0;
} // isempty