// Justin Thoreson
// movie.cpp
// 6/5/20

#include "movie.h"
#include <iostream>

Movie::Movie()
  :title(""), genre(""), contentRating(""), tagline(""), director(""),
   id(0), year(0)
{}

Movie::Movie(string ttl, string gnr, string rating, string tag,
             string drctr, long filmID, int yr)
{
  title = ttl;
  genre = gnr;
  contentRating = rating;
  tagline = tag;
  director = drctr;
  id = filmID;
  year = yr;
}

void Movie::displayMovieInfo() const
{
  cout << "\nIMDb ID: " << id << endl
       << "Title: " << title << endl
       << "Director: " << director << endl
       << "Tagline: " << tagline << endl
       << "Year: " << year << endl
       << "Rating: " << contentRating << endl << endl;
}

string Movie::getTitle() const { return title; }

string Movie::getGenre() const { return genre; }
