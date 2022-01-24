// Justin Thoreson
// hash.h
// 6/5/20

#ifndef HASH_H
#define HASH_H
#include "movie.h"
#include <string>

using namespace std;

class HashTable
{
  private:
    struct MovieNode
    {
      long key;
      Movie value;
      MovieNode* next;
    };

    const float LOAD_FACTOR = 0.7; 
    int numMovies;
    int tableSize;
    MovieNode** playlist;
  
  public:
    HashTable();
    ~HashTable();
    int hashFunc(long key) const;
    void addToPlaylist(long key, Movie value);
    bool watchMovie(long key);
    void displayMovie(long key) const;
    void displayAll() const;
    void displayGenre(string genre) const;
    void rehash();
    bool isPrime(int num);
    int nextPrime(int num);
};

#endif
