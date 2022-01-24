// Justin Thoreson
// movie.h
// 6/5/20

#ifndef MOVIE_H
#define MOVIE_H
#include <string>

using namespace std;

class Movie
{
  private:
    string title, genre, contentRating, tagline, director;
    long id;
    int year;
    
  public:
    Movie();
    Movie(string ttl, string gnr, string rating, string tag,
          string drctr, long filmID, int yr);
    void displayMovieInfo() const;
    string getTitle() const;
    string getGenre() const;
};

#endif
