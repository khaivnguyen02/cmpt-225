


// Desc:  Implementation of an int sequence with push/pop in a LIFO order
class Stack {

    private:

        // Desc:  arr = static array of capacity STACKCAP
        //        size = the number of elements presently in the stack
        //  Inv:  Follows the A2 Spec, namely that the stack elements 
        //        are in order within A[0..size-1], where the top of
        //        the stack is A[0].
        static const unsigned STACKCAP = 8;
        int arr[STACKCAP];
        unsigned size;

    public:

        // Desc:  Object constructor
        // Post:  size of stack is set to 0
        Stack();


        // Desc:  Insert element x to the top of the stack.
        //  Pre:  size <= STACKCAP
        // Post:  Element x is inserted at index 0
        void push(int x);


        // Desc:  Remove and return element at the top of the stack.
        //  Pre:  size > 0
        // Post:  Element at index 0 is removed and returned
        int pop();


        // Desc:  Return the topmost element of the stack.
        //  Pre:  size > 0
        // Post:  Element at index 0 is returned without remove
        int peek() const;


        // Desc:  Check if the stack is empty
        // Post:  Return true if the stack is empty, return false otherwise
        bool isEmpty() const;

};


