// Justin Thoreson
// pa3.cpp
// 05/18/2020
//
// PURPOSE:
//  The purpose of this assignment is to create a Binary Search Tree that
//  contains cities and their respective countries and populations. The
//  functions of the BST are demonstrated through a student-made driver source.
//
// INPUT:
//  1. The user provides the name of a city to be printed.
//  2. The user provides the name of a city to be removed.
//
// PROCESSING:
//  1. The file containing the list of cities is read, and each city is inserted
//     into a BST. The cities are ordered alphabetically with respect to the
//     name. The city consists of a name, a country, and a population.
//  2. The cities are printed inorder, which is in alphabetical order.
//  3. When a user declares a city, that city is searched for in the BST. If the
//     city is found, its name, country, and population is displayed.
//  4. When a user declares a city, the city is searched for and removed from
//     the BST if found.
//  5. By searching through the BST, the city with the highest population is
//     found so that it may be displayed.
//  6. The height of the BST is found and displayed. 
//  7. A BST of cities may be initialized or assigned to another BST of cities.
//
// OUTPUT:
//  1. The list of cities are printed out to the console.
//  2. A single user-specified city along with its country and population is
//     printed out to the console.
//  3. An updated list is printed after a user specified city is removed from
//     the BST.
//  4. The most populated city in the BST is printed.
//  5. The height of the BST is printed.
//
// EXAMPLES:
//  1) Hello! Reading the cities.csv file.
//     Printing the tree:
//     Buenos Aires
//     Cairo
//     Chicago
//     Jakarta
//     Karachi
//     Lagos
//     Lima
//     New York
//     Osaka
//     Paris
//     Sao Paulo
//     Taipei
//     Tokyo
//
//     Which city do you want to print?: Buenos Aires
//     City: Buenos Aires
//     Country: Argentina
//     Population: 12795000
//
//     Which city do you want to remove?: Lima
//     Lima has been removed. Printing updated tree:
//     Buenos Aires
//     Cairo
//     Chicago
//     Jakarta
//     Karachi
//     Lagos
//     New York
//     Osaka
//     Paris
//     Sao Paulo
//     Taipei
//     Tokyo
//
//     The biggest city is Tokyo
//     The height of the first tree is 9
//
//  2) ...
//     Which city do you want to print?: Seattle
//     The city of Seattle is not in the tree.
//
//     Which city do you want to remove?: Portland
//     The city of Portland is not in the tree.
//
//     The tree is empty. No highest population.
//     The tree is empty. The height is 0.
//     ...
//
//  3) Printing the tree:
//     The tree is empty.
//
// SOURCES:
//  1. CPSC 2430: PA1 - pa1.cpp
//     - my file reading function that
//  2. cplusplus.com
//     - tips on recursion and finding the height of a BST
//     - understanding the conditional ternary operator (?:)
//  3. stackoverflow.com
//     - tips on BST copy constructors
//  4. stackoverflow.com/questions/7276826/c-format-number-with-commas
//     - printing the population with commas

#include "citybst.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

void readCities(CityBST& cities, string fileName);
// PURPOSE: Processes a file containing cities.
// PRECONDITION: The name of a file is provided and an empty BST is created.
// POSTCONDITION: All cities in the file are inserted into the BST.

int main(int argc, char** argv)
{
  // 1. Create first tree.
  CityBST cities1;
  cout << "Hello! Processing the cities.csv file." << endl << endl;
  readCities(cities1, "cities.csv");

  cout << "Printing the first tree:" << endl;
  cities1.print();

  //  a. Ask user for a city to print.
  cout << endl << "Which city do you want to print?: ";
  string city;
  getline(cin, city);
  cities1.printCity(city);

  //  b. Ask user for a city to remove.
  cout << endl << "Which city do you want to remove?: ";
  getline(cin, city);
  if (cities1.remove(city))
  {
    cout << city << " has been removed. Printing updated tree: " << endl;
    cities1.print();
  }
  else
    cout << "The city of " << city << " is not in the tree." << endl;

  //  c. Display the most populated city.
  string mostPopulated = cities1.biggestCity();
  if (mostPopulated == "")
    cout << endl << "The first tree is empty. No highest population." << endl;
  else
    cout << endl << "The biggest city is " << mostPopulated << endl;

  //  d. Print the height of the first tree.
  int height = cities1.getHeight();
  if (height > 0)
    cout << "The height of the first tree is " << height << endl;
  else
    cout << "The first tree is empty. The height is 0." << endl;
  
  // 2. Initialize second tree to the first.
  CityBST cities2 = cities1;
  cout << endl << "Initializing second tree with first tree..."
       << endl << "Printing the second tree:" << endl;
  cities2.print();

  // 3. Create third tree.
  CityBST cities3;
  cout << endl << "Printing the third tree:" << endl;
  cities3.print();

  //  a. Assign the third tree to the first.
  cities1 = cities3;
  cout << endl << "Assigning third tree to first tree..."
       << endl << "Printing the first tree:" << endl;
  cities1.print();

  //  b. Display the most populated city in the first tree.
  mostPopulated = cities1.biggestCity();
  if (mostPopulated == "")
    cout << "The first tree is empty. No highest population." << endl;
  else
    cout << endl << "The biggest city is " << mostPopulated << endl;

  return 0;
}

void readCities(CityBST& cities, string fileName)
{
  ifstream file(fileName);
  string city;
  string cityName;
  string country;
  string population;

  if (file.fail())
  {
    cout << "ERROR: The file " << fileName << " failed to open" << endl;
    exit(1);
  }
  
  getline(file, city); // discard first/header line  
  while (getline(file, city) && !file.fail())
  {
    stringstream line(city);
    getline(line, cityName, ',');
    getline(line, country, ',');
    getline(line, population, ',');
    cities.insert(cityName, country, stoi(population));
  }

  file.close();
}
