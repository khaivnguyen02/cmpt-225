#include <iostream>
#include <cstring>
#include <string>

using namespace std;

const unsigned scale = 225;

// * * * replace with your own personal modulus * * * //
const unsigned M = 3373;

// Desc:  Dynamic Set of strings using a Hash Table (generic version)
//  Pre:  class T must have an attribute key of type string
template <class T>
class Set
{
private:
    T *A[M];

    // * * * Add attributes and helper methods here if you wish. * * * //
    int hashing(string) const;

public:
    // Desc:  Default constructor.  Initialize table to NULL.
    Set()
    {
        memset(A, 0, sizeof(T *) * M);
    }

    // Desc:  Insert x into the Set, according to its ->key.
    //        If ->key is already present, then replace it by x.
    //        Collisions are resolved via quadratic probing sequence.
    // Post:  returns the table index where x was inserted
    //        returns -1 if x was not inserted
    int insert(T *x);

    // Desc:  Returns T * x such that x->key == key, if and only if
    //        key is in the Set.
    //        Returns NULL if and only if key is not in the Set.
    // Post:  Set is unchanged
    T *search(string key) const;
};

// Desc:  Insert x into the Set, according to its ->key.
//        If ->key is already present, then replace it by x.
//        Collisions are resolved via quadratic probing sequence.
// Post:  returns the table index where x was inserted
//        returns -1 if x was not inserted
template <class T>
int Set<T>::insert(T *x)
{
    int index = hashing(x->key);

    if (A[index] == NULL || A[index]->key == x->key)
    {
        A[index] = x;
        return index;
    }

    // Resolving collisions by quadratic probing
    for (int i = 0; i < M; i++)
    {
        int possibleIndex = (index + i * i) % M;
        if (A[possibleIndex] == NULL || A[index]->key == x->key)
        {
            A[possibleIndex] = x;
            return possibleIndex;
        }
    }

    return -1;
}

// Desc:  Returns T * x such that x->key == key, if and only if
//        key is in the Set.
//        Returns NULL if and only if key is not in the Set.
// Post:  Set is unchanged
template <class T>
T *Set<T>::search(string key) const
{

    int index = hashing(key);
    if (A[index] == NULL)
        return NULL;

    if (A[index]->key == key)
        return A[index];
        
    for (int i = 0; i < M; i++)
    {
        int possibleIndex = (index + i * i) % M;
        if (A[index]->key == key)
        {
            return A[possibleIndex];
        }
    }
    return NULL;
}

template <class T>
int Set<T>::hashing(string str) const
{
    int hashValue = 0;
    int len = str.length();
    int m = len;

    while (len--)
    {
        char curr = str.at(m - len - 1);
        if (hashValue != 0)
        {
            hashValue = hashValue * 64;
            hashValue = hashValue % M;
        }

        if ('a' <= curr && curr <= 'z')
        {
            hashValue += (curr - 87);
        }
        else if ('A' <= curr && curr <= 'Z')
        {
            hashValue += (curr - 29);
        }
        else if ('0' <= curr && curr <= '9')
        {
            hashValue += (curr - 48);
        }
        else if (curr == '_')
        {
            hashValue += (curr - 33);
        }
    }
    hashValue = hashValue * 225;
    hashValue = hashValue % M;
    return hashValue;
}