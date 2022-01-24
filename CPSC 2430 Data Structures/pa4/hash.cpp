// Justin Thoreson
// hash.cpp
// 6/5/20

#include "hash.h"
#include <iostream>

HashTable::HashTable()
  : numMovies(0), tableSize(13), playlist(new MovieNode*[tableSize])
{
  for (int i = 0; i < tableSize; i++)
    playlist[i] = nullptr;
}

HashTable::~HashTable()
{
  for (int i = 0; i < tableSize; i++)
  {
    while (playlist[i])
    {
      MovieNode* temp = playlist[i]->next;
      delete playlist[i];
      playlist[i] = temp;
    }
  }

  delete [] playlist;
}

int HashTable::hashFunc(long key) const { return key % tableSize; }

// PURPOSE: Adds a single movie to a playlist via hashing and separate chaining.
// PRECONDITION: A movie and it's key are provided.
// POSTCONDITION: The movie is inserted into a playlist.
void HashTable::addToPlaylist(long key, Movie value)
{
  MovieNode* newNode = new MovieNode;
  newNode->key = key;
  newNode->value = value;
  newNode->next = nullptr;
  
  int hashIndex = hashFunc(key);
  if (!playlist[hashIndex])
    playlist[hashIndex] = newNode;
  else
  {
    MovieNode* nodePtr = playlist[hashIndex];
    while (nodePtr->next)
      nodePtr = nodePtr->next;
    nodePtr->next = newNode; 
  }

  numMovies++;
  if (numMovies / tableSize > LOAD_FACTOR)
    rehash();
}

// PURPOSE: States whether a movie has been watched and removes it if it has.
// PRECONDITION: The movie's ID is provided.
// POSTCONDITION: The movie is removed from the list if it has been watched.
bool HashTable::watchMovie(long key)
{
  MovieNode* nodePtr;
  bool watched;
  int index = hashFunc(key);
  if (!playlist[index])
    watched = false;
  else if (playlist[index]->key == key)
  {
    cout << "\nWatched " << playlist[index]->value.getTitle()
         << ". Removing it from the playlist.\n\n";
      
    nodePtr = playlist[index]->next;
    delete playlist[index];
    playlist[index] = nodePtr;
    watched = true;
  }
  else
  {
    nodePtr = playlist[index];
    MovieNode* previous = nullptr;
    while (nodePtr->next && nodePtr->key != key)
    {
      previous = nodePtr;
      nodePtr = nodePtr->next;
    }

    if (!nodePtr)
      watched = false;
    else if (nodePtr->key == key)
    {
      cout << "\nWatched " << nodePtr->value.getTitle()
           << ". Removing it from the playlist\n\n";

      previous->next = nodePtr->next;
      delete nodePtr;
      watched = true;
    }
  }

  return watched;
}

// PURPOSE: Displays a movie's ID and title.
// PRECONDITION: The movie's ID is provided.
// POSTCONDITION: The movie's ID and Title are displayed.
void HashTable::displayMovie(long key) const
{
  int index = hashFunc(key);
  if (!playlist[index])
    cout << "\nThe movie is not in the playlist.\n\n";
  else
  {
    MovieNode* nodePtr = playlist[index];
    while (nodePtr->next && nodePtr->key != key)
      nodePtr = nodePtr->next;

    if (nodePtr->key == key)
      nodePtr->value.displayMovieInfo();
    else
      cout << "\nThe movie is not in the playlist.\n\n";
  }
}

void HashTable::displayAll() const
{
  cout << endl;
  for (int i = 0; i < tableSize; i++)
  {
    MovieNode* nodePtr = playlist[i];
    while (nodePtr)
    {
      cout << "IMDb ID: " << nodePtr->key << endl
           << "Title: " << nodePtr->value.getTitle() << endl << endl;
      nodePtr = nodePtr->next;
    }
  }
}

void HashTable::displayGenre(string genre) const
{
  cout << endl;
  int moviesDisplayed = 0;
  for (int i = 0; i < tableSize; i++)
  {
    MovieNode* nodePtr = playlist[i];
    while (nodePtr)
    {
      if (nodePtr->value.getGenre() == genre)
      {
        cout << "IMDb ID: " << nodePtr->key << endl
             << "Title: " << nodePtr->value.getTitle() << endl << endl;
        moviesDisplayed++;
      }
      
      nodePtr = nodePtr->next;
    }
  }

  if (!moviesDisplayed)
    cout << "There are no movies in the playlist belonging to this genre.\n\n";
}

void HashTable::rehash()
{
  int oldSize = tableSize;
  tableSize = nextPrime(tableSize * 2);

  MovieNode** newTable = new MovieNode*[tableSize];
  for (int i = 0; i < tableSize; i++)
    newTable[i] = nullptr;

  MovieNode* nodePtr = nullptr;
  MovieNode* current = nullptr;
  for (int i = 0; i < oldSize; i++)
  {
    nodePtr = playlist[i];
    while (nodePtr)
    {
      current = nodePtr;
      nodePtr = nodePtr->next;

      MovieNode*& temp = newTable[hashFunc(current->key) % tableSize];
      current->next = temp;
      temp = current;
    }
  }

  delete [] playlist;
  playlist = newTable;
}

bool HashTable::isPrime(int num)
{
  if (num < 2 || num % 2 == 0)
    return false;
  else if (num == 2)
    return true;
  
  for (int i = 3; i*i <= num; i+=2)
    if (num % i == 0)
      return false;
  return true;
}

int HashTable::nextPrime(int num)
{
  while (!isPrime(++num)) {}
  return num;
}
  
