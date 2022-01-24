// Justin Thoreson
// pa4.cpp
// 6/5/20
//
// PURPOSE:
//  This program creates a playlist of movies read from a movie file.
//  The program implements the use of hashing and separate chainging.
//
// INPUT:
//  1. When prompted with a menu, the user must enter a value from 1 to 5 to
//     specify what they want to do with the playlist.
//  2. If the user wishes to view all movies of one genre, they must specify the
//     genre.
//  3. When necessary, the user must provide the IMDb ID of a movie. This is
//     when the user wants to watch or see more information of a specific film.
//
// PROCESS:
//  1. All the movie details in a file are read into an array via hashing and
//     separate chaining. Each movie is stored as a node at a specific index
//     of an array. Nodes can form linked-lists at these indices if multiple
//     movies share the same hash value/index.
//  2. Traversing the movies is done from index 0 to the last index. Within
//     each index, the linked-lists are traversed starting from the head as
//     usual.
//
// OUTPUT:
//  1. The user is prompted with a menu, giving them 5 options.
//  2. If the user chooses to browse all movies, the ID and title of every movie
//     is printed onto the console.
//  3. If the user wishes to browse by genre, the ID and title of the movies
//     belonging to a user-specified genre will be printed.
//  4. If the user wishes to watch a movie, the specific movie is declared as
//     watched.
//  5. If the user wishes to see more information of a specific movie, the ID,
//     title, genre, year, rating, tagline, and director of the movie are
//     printed.
//  6. If any input provided by the user is invalid or if a provided genre or
//     movie cannot be found, the user will be notified.
//
// SOURCES:
//  CPSC 2430: pa3.cpp
//   - modified file reading function  
//  geeksforgeeks.com & algolist.net
//   - tips on hashing and separate chaining
//   - tips on creating an array of nodes
//  cplusplus.com & stackoverflow.com
//   - understaning why TABLE_SIZE needed to be static

#include "hash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void readMovies(HashTable& movieList, string fileName);
// PURPOSE: Reads all movies from a file and stores the into a playlist.
// PRECONDITION: An empty playlist and a file name are provided.
// POSTCONDITION: The playlist contains the movies read from the file.

void menu(unsigned short& choice);
// PURPOSE: Provides a menu and obtains their menu choice.
// PRECONDITION: A playlist has been created and movies have been read into it.
// POSTCONDITION: A valid user choice is stored.

void executeChoice(HashTable& movieList, unsigned short& choice);
// PURPOSE: Executes the user's choice from the menu.
// PRECONDITION: The user has chosen what to do with the playlist.
// POSTCONDITION: The given choice is executed.

int main(int argc, char** argv)
{
  HashTable movieList;
  readMovies(movieList, "movies.csv");

  cout << "Welcome!\n";
  unsigned short choice = 0;
  while (choice != 5)
  {
    menu(choice);    
    executeChoice(movieList, choice);
  }

  cout << "Goodbye!\n";  
  return 0;
}

void readMovies(HashTable& movieList, string fileName)
{
  ifstream file(fileName);
  string movie, title, genre, contentRating, tagline, director, id, year;
  
  if (file.fail())
  {
    cout << "ERROR: The file " << fileName << " failed to open" << endl;
    exit(1);
  }

  getline(file, movie); // ignore header line
  while (getline(file, movie) && !file.fail())
  {
    stringstream line(movie);
    getline(line, id, ',');
    getline(line, title, ',');
    getline(line, genre, ',');
    getline(line, year, ','); 
    getline(line, contentRating, ',');
    getline(line, tagline, ',');
    getline(line, director);

    long movieID = stol(id);
    int yr = stoi(year);
   
    Movie film(title, genre, contentRating, tagline, director, movieID, yr);
    movieList.addToPlaylist(movieID, film);
  }

  file.close();
}

void menu(unsigned short& choice)
{
  cout << "****************************\n"
       << "What would you like to do?\n"
       << "1 - Browse all movies\n"
       << "2 - Browse by genre\n"
       << "3 - Watch a movie\n"
       << "4 - View more information about a movie\n"
       << "5 - Exit\n"
       << "Enter your choice: ";
  cin >> choice;

  while (choice < 1 || choice > 5)
  {
    cout << "Invalid input. Enter a value from 1 to 5: ";
    cin >> choice;
  }
}

void executeChoice(HashTable& movieList, unsigned short& choice)
{
  switch (choice)
  {
    case 1:
    {
      movieList.displayAll();
      break;
    }

    case 2:
    {
      cout << "Please specify a genre: ";
      string genre;
      cin >> genre;
      movieList.displayGenre(genre);
      break;
    }

    case 3:
    {
      cout << "Enter the ID of the movie you want to watch: ";
      long idWatch;
      cin >> idWatch;
      if (!movieList.watchMovie(idWatch))
        cout << "\nThe movie is not in the playlist.\n\n";
      break;
    }

    case 4:
    {
      cout << "Enter the ID of the movie: ";
      long idInfo;
      cin >> idInfo;
      movieList.displayMovie(idInfo);
      break;
    }
  }
}
