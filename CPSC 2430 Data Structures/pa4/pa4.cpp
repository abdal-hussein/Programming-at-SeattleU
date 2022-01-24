// Justin Thoreson
// pa4.cpp
// 6/5/20
//
// PURPOSE:
//  This program creates a playlist of movies read from a movie file.
//  The program implements the use of hashing and separate chainging.
//  The programs serves as an interface for users who wish to view details about
//  movies and/or watch them.
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
//  3. When the table's load factor exceeds 0.7, the table is rehashed. The next
//     prime of double the old table size becomes the new table size. 
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
// EXAMPLES:
//  1) Welcome!
//     ****************************
//     What would you like to do?
//     1 - Browse all movies
//     2 - Browse by genre
//     3 - Watch a movie
//     4 - View more information about a movie
//     5 - Exit
//     Enter your choice: 1
//
//     IMDb ID: 905372
//     Title: The Thing
//
//     IMDb ID: 99685
//     Title: Goodfellas
//
//     IMDb ID: 88763
//     Title: Back to the Future
//
//     IMDb ID: 81398
//     Title: Raging Bull
//
//     IMDb ID: 66921
//     Title: A Clockwork Orange
//
//     IMDb ID: 268978
//     Title: A Beautiful Mind
//
//     IMDb ID: 112641
//     Title: Casino
//
//     IMDb ID: 110357
//     Title: The Lion King
//
//     IMDb ID: 1291584
//     Title: Warrior
//
//     IMDb ID: 848228
//     Title: The Avengers
//
//     IMDb ID: 70735
//     Title: The Sting
//
//     IMDb ID: 133093
//     Title: The Matrix
//
//  2) ****************************
//     What would you like to do?
//     1 - Browse all movies
//     2 - Browse by genre
//     3 - Watch a movie
//     4 - View more information about a movie
//     5 - Exit
//     Enter your choice: 2
//     Please specify a genre: Action
//
//     IMDb ID: 848228
//     Title: The Avengers
//
//     IMDb ID: 133093
//     Title: The Matrix
//
//  3) ****************************
//     What would you like to do?
//     1 - Browse all movies
//     2 - Browse by genre
//     3 - Watch a movie
//     4 - View more information about a movie
//     5 - Exit
//     Enter your choice: 4
//     Enter the ID of the movie: 848228
// 
//     IMDb ID: 848228
//     Title: The Avengers
//     Director: Joss Whedon
//     Tagline: Some assembly required.
//     Year: 2012
//     Rating: PG-13    
//
//  4) ****************************
//     What would you like to do?
//     1 - Browse all movies
//     2 - Browse by genre
//     3 - Watch a movie
//     4 - View more information about a movie
//     5 - Exit
//     Enter your choice: 3
//     Enter the ID of the movie you want to watch: 848228
//
//     Watched The Avengers. Removing it from the playlist.
//
//  5) ****************************
//     What would you like to do?
//     1 - Browse all movies
//     2 - Browse by genre
//     3 - Watch a movie
//     4 - View more information about a movie
//     5 - Exit
//     Enter your choice: 5
//     Goodbye! 
//
// SOURCES:
//  CPSC 2430: pa3.cpp
//   - modified file reading function  
//  geeksforgeeks.org & algolist.net
//   - tips on hashing and separate chaining
//   - tips on creating an array of nodes
//  cplusplus.com & stackoverflow.com
//   - tips on rehashing and memory allocation
//   - checking if a number is prime

#include "hash.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void readMovies(HashTable& playlist, string fileName);
// PURPOSE: Reads all movies from a file and stores the into a playlist.
// PRECONDITION: An empty playlist and a file name are provided.
// POSTCONDITION: The playlist contains the movies read from the file.

void menu(unsigned short& choice);
// PURPOSE: Provides a menu and obtains their menu choice.
// PRECONDITION: A playlist has been created and movies have been read into it.
// POSTCONDITION: A valid user choice is stored.

void executeChoice(HashTable& playlist, unsigned short& choice);
// PURPOSE: Executes the user's choice from the menu.
// PRECONDITION: The user has chosen what to do with the playlist.
// POSTCONDITION: The given choice is executed.

int main(int argc, char** argv)
{
  HashTable playlist;
  readMovies(playlist, "movies.csv");

  cout << "Welcome!\n";
  unsigned short choice = 0;
  while (choice != 5)
  {
    menu(choice);    
    executeChoice(playlist, choice);
  }

  cout << "Goodbye!\n";  
  return 0;
}

void readMovies(HashTable& playlist, string fileName)
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
    playlist.addToPlaylist(movieID, film);
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

void executeChoice(HashTable& playlist, unsigned short& choice)
{
  switch (choice)
  {
    case 1:
    {
      playlist.displayAll();
      break;
    }

    case 2:
    {
      cout << "Please specify a genre: ";
      string genre;
      cin >> genre;
      playlist.displayGenre(genre);
      break;
    }

    case 3:
    {
      cout << "Enter the ID of the movie you want to watch: ";
      long idWatch;
      cin >> idWatch;
      if (!playlist.watchMovie(idWatch))
        cout << "\nThe movie is not in the playlist.\n\n";
      break;
    }

    case 4:
    {
      cout << "Enter the ID of the movie: ";
      long idInfo;
      cin >> idInfo;
      playlist.displayMovie(idInfo);
      break;
    }
  }
}
