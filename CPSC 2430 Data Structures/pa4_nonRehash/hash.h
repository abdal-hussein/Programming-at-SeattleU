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
    
    static const short TABLE_SIZE = 13;
    MovieNode* playlist[TABLE_SIZE];
  
  public:
    HashTable();
    ~HashTable();
    void addToPlaylist(long key, Movie value);
    bool watchMovie(long key);
    void displayMovie(long key) const;
    void displayAll() const;
    void displayGenre(string genre) const;
};

#endif
