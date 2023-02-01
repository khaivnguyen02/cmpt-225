// Write your name and date here
#include "PlayList.h"
// PlayList method implementations go here

// Constructors and destructor
// POST: head of list is set to nullptr
PlayList::PlayList() : head(nullptr), numberOfSongs(0) {}

// PARAM: pl - PlayList to be copied
// POST: new PlayList is created that is a deep copy of pl
PlayList::PlayList(const PlayList &pl)
{
    this->head = nullptr;

    PlayListNode *temp = pl.head;
    unsigned int index = 0;

    while (temp != nullptr)
    {
        this->insert(temp->song, index++);
        temp = temp->next;
    }
    this->numberOfSongs = pl.numberOfSongs;
}

// POST: dynamic memory associated with object is deallocated
PlayList::~PlayList()
{
    PlayListNode *temp = head;

    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }

    this->numberOfSongs = 0;
}

// PARAM: pl - PlayList to be copied
// POST: dynamic memory of calling object deallocated (except
//	 under self-assignment), calling object is set to a
//	 a deep copy of pl
PlayList &PlayList::operator=(const PlayList &pl)
{
    if (this == &pl)
    {
        return *this;
    }
    else
    {
        this->~PlayList();

        PlayListNode *temp = pl.head;
        unsigned int index = 0;

        while (temp != nullptr)
        {
            this->insert(temp->song, index++);
            temp = temp->next;
        }

        this->numberOfSongs = pl.numberOfSongs;

        return *this;
    }
}

// Mutators
// PRE: 0 <= i <= length of list
// PARAM: pos - 0-based insertion position
// sng - Song to be inserted pos
void PlayList::insert(Song sng, unsigned int pos)
{
    if (head == nullptr)
    {
        // If the calling object's list is empty
        PlayListNode *newNode = new PlayListNode(sng, nullptr);
        head = newNode;
    }
    else if (pos == 0)
    {
        // Insert at the head of the calling object's list
        PlayListNode *newNode = new PlayListNode(sng, head);
        head = newNode;
    }
    else
    {
        PlayListNode *prev = nullptr;
        PlayListNode *curr = head;

        while (curr != nullptr && pos--)
        {
            prev = curr;
            curr = curr->next;
        }

        PlayListNode *newNode = new PlayListNode(sng, curr);
        prev->next = newNode;
    }
    this->numberOfSongs++;
}

// PRE: 0 <= pos <= length of list-1
// PARAM: pos - 0-based position of element to be removed and returned
// POST: Song at position pos is removed and returned
Song PlayList::remove(unsigned int pos)
{
    if (head == nullptr)
    {
        // If the calling object's list is empty
        return Song("none", "none", 1);
    }
    else
    {
        PlayListNode *curr = head;
        PlayListNode *prev = nullptr;

        if (pos == 0)
        {
            // Remove the first node of the calling object's list
            Song removedSong(curr->song.getName(), curr->song.getArtist(), curr->song.getLength());
            head = head->next;
            delete curr;
            this->numberOfSongs--;
            return removedSong;
        }
        else
        {
            while (curr != nullptr && pos--)
            {
                prev = curr;
                curr = curr->next;
            }
            Song removedSong(curr->song.getName(), curr->song.getArtist(), curr->song.getLength());
            prev->next = curr->next;
            delete curr;
            this->numberOfSongs--;

            return removedSong;
        }
    }
}

// PRE: 0 <= pos1, pos2 <= length of list-1
// PARAM: pos1, pos2 - 0-based positions of elements to be swapped
// POST: Songs at positions pos1 and pos2 are swapped
void PlayList::swap(unsigned int pos1, unsigned int pos2)
{
    if (pos1 == pos2)
    {
        return;
    }

    PlayListNode *prev1 = nullptr;
    PlayListNode *curr1 = head;
    while (curr1 != nullptr && pos1--)
    {
        prev1 = curr1;
        curr1 = curr1->next;
    }

    PlayListNode *prev2 = nullptr;
    PlayListNode *curr2 = head;
    while (curr2 != nullptr && pos2--)
    {
        prev2 = curr2;
        curr2 = curr2->next;
    }

    if (prev1 != nullptr)
    { // If node at pos1 is not the head of PlayList
        prev1->next = curr2;
    }
    else
    {
        head = curr2;
    }

    if (prev2 != nullptr)
    { // If node at pos2 is not the head of PlayList
        prev2->next = curr1;
    }
    else
    {
        head = curr1;
    }
    // Swap the next pointer of curr1 and curr2
    PlayListNode *temp = curr2->next;
    curr2->next = curr1->next;
    curr1->next = temp;
}
// // Accessor
// PRE: 0 <= pos <= length of list-1
// PARAM: pos - 0-based position of element to be removed and returned
// POST: returns the Song at position pos
Song PlayList::get(unsigned int pos) const
{
    PlayListNode *curr = head;

    while (curr != nullptr && pos--)
        curr = curr->next;

    return curr->song;
}

// POST: returns the number of songs in the PlayList
unsigned int PlayList::size() const
{
    return numberOfSongs;
}