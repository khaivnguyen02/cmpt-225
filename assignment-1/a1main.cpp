// O Notation worst-case running time
// PlayList Methods
/*
    + Default constructor: O(1) - constant: since only has 2 statements: initialize head pointer to nullptr and numberOfSongs to 0.
    + Destructor: O(n) - linear: with n is the size of the calling object, we need to traverse the linked list,
                  and delete each node until the head pointer point to null
                  (PlayList becomes empty) and set the numberOfSongs to 0.
    + Copy constructor: O(n) - linear: with n is the size of the copied list. Traverse through n nodes of the copied list
                        , and insert each nodes into calling object, assign calling object's size to copied list's.
    + Overloaded assignment operator: O(n) - linear: 1. Deallocates dynamic memory associated with the calling object's list (O(n1))
                                                     2. Traverse the parameter list and insert each node of its to the calling object's list (O(n2))
                                                     3. Assigns the numOfSongs of parameter list to numOfSongs of calling object (O(1))
                                                     4. Return the reference to the calling object list (O(1))
    + Insert: O(n): worst case: insert at the end of calling object list. We need to traverse to the last node (O(n) n is the size of list),
                                , and then rearrange the pointers.
    + Remove: O(n): worst case: remove the node at the end of calling object list. We need to traverse to the last node (O(n) n is the size of list),
                                , and then delete that node, make the previous node pointing to null.
    + Get: O(n): worst case: get the last node of calling object's list. We need to traverse to the last node (O(n) n is the size of list),
                                , and then return the song data of it.
    + Swap: O(n): worst case: 1 swap position is at the end of calling object list so we need to traverse through n nodes (n is the size of list),
                              my algorithms traverse 2 times to get nodes at pos1 and pos2 and then rearrange the pointers.
    + Size: O(1): access the numberOfSongs private variable and return it.
*/
// Main Function Commands
/*
    + Enter a song: O(n): n is the size of calling object insert at the end of play list,
                          ask for the inserted position (1 statement) so the running time ~ insert() method
    + Remove a song: O(n): remove the last song in the list. n is the size of the list so the running time ~ remove() method, and print the removed song
                           by getName() function in Song.cpp
    + Swap two songs: O(n): get in 2 positions. if 1 position is at the end of the list -> need to traverse to the end node (O(n))
                            , so the running time ~ swap() method.
    + Print all the songs: O(n^2) Traverse through the calling object's list(n times): with each i in the loop,
                           use get() and getters of Song class - O(n) to access the songName, artist and length.
*/
#include <iostream>
#include <string>
#include "Song.h"
#include <limits>
#include "PlayList.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

void mainMenu()
{
    cout << "Menu: " << endl;
    cout << "1 - Enter a song in the play list at a given position" << endl;
    cout << "2 - Remove a song from the play list at a given position" << endl;
    cout << "3 - Swap two songs in the play list" << endl;
    cout << "4 - Print all the songs in the play list" << endl;
    cout << "5 - Quit" << endl;
    cout << endl;
}
void insertPosition(PlayList &pl)
{
    // Available position for inserting
    if (pl.size() == 0)
    {
        cout << "(1): ";
    }
    else
    {
        cout << "(1 to " << pl.size() + 1 << "): ";
    }
}
void availablePos(PlayList &pl)
{
    // Available position for removing and swapping
    if (pl.size() == 1)
    {
        cout << "(1): ";
    }
    else
    {
        cout << "(1 to " << pl.size() << "): ";
    }
}
void printPlayList(PlayList &pl)
{
    for (unsigned i = 0; i < pl.size(); i++)
    {
        cout << "   " << i + 1 << " " << pl.get(i).getName() << " (" << pl.get(i).getArtist() << ") " << pl.get(i).getLength() << "s" << endl;
    }
    cout << "There are " << pl.size() << " songs in the play list." << endl;
}

int main()
{
    mainMenu();
    string userInput;
    PlayList myList;
    do
    {
        cout << "Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        std::getline(cin, userInput);
        while (userInput != "1" && userInput != "2" && userInput != "3" && userInput != "4" && userInput != "5")
        {
            std::getline(cin, userInput);
        }
        if (userInput == "1")
        {
            string songName;
            cout << "Song name: ";
            std::getline(cin, songName);
            while (songName == "")
            {
                std::getline(cin, songName);
            }

            string artist;
            cout << "Artist: ";
            std::getline(cin, artist);
            while (artist == "")
            {
                std::getline(cin, artist);
            }

            int len = 0;
            cout << "Length: ";
            cin >> len;
            while (len < 1)
            {
                cout << "Invalid length , please try again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> len;
            }

            Song newSong(songName, artist, len);
            // Get in inserted position
            cout << "Position ";
            insertPosition(myList);
            unsigned int position;
            cin >> position;
            while (position < 1 || position > (myList.size() + 1))
            {
                // If the input position invalid, ask the user to enter it again
                cout << "Invalid position for inserting, please try again: ";
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin >> position;
            }
            myList.insert(newSong, position - 1);
            cout << "You entered " << songName << " at position " << position << " in the play list \n\n";
        }
        else if (userInput == "2")
        {
            if (myList.size() == 0)
            {
                cout << "The play list is empty. Nothing to remove!" << endl;
            }
            else
            {
                unsigned int position;

                cout << "Position ";
                availablePos(myList);

                cin >> position;

                while (position < 1 || position > myList.size())
                {
                    // If the input position invalid, ask the user to enter it again
                    cout << "Invalid position for removing, please try again: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> position;
                }

                Song removedSong = myList.remove(position - 1);
                cout << "You removed " << removedSong.getName() << " from the play list"
                     << "\n\n";
            }
        }
        else if (userInput == "3")
        {
            if (myList.size() == 0)
            {
                cout << "The play list is empty. Nothing to swap!"
                     << "\n\n";
            }
            else if (myList.size() == 1)
            {
                cout << "Not enough songs to swap!"
                     << "\n\n";
            }
            else
            {
                unsigned int pos1, pos2;
                cout << "Swap song at position ";
                availablePos(myList);
                cin >> pos1;
                while (pos1 < 1 || pos1 > myList.size())
                {
                    // If the input position invalid, ask the user to enter it again
                    cout << "Invalid position for swapping, please try again: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> pos1;
                }
                cout << endl
                     << "with the song at position ";
                availablePos(myList);
                cin >> pos2;
                while (pos2 < 1 || pos2 > myList.size())
                {
                    // If the input position invalid, ask the user to enter it again
                    cout << "Invalid position for swapping, please try again: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    cin >> pos2;
                }
                myList.swap(pos1 - 1, pos2 - 1);
                cout << "You swapped the songs at positions " << pos1 << " and " << pos2 << "\n\n";
            }
        }
        else if (userInput == "4")
        {
            printPlayList(myList);
            cout << endl;
        }
        else if (userInput == "5")
        {
            cout << "You have chosen to quit the program."
                 << "\n\n";
            break;
        }
    } while (userInput != "5");

    return 0;
}