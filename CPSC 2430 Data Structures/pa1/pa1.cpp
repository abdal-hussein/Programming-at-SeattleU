// Justin Thoreson
// pa1.cpp
// 04/24/2020
//
// PURPOSE:
//  The purpose of this assignment was to demonstrate the functionality of a
//  queue implemented through a circular dynamic array. Demonstrating the
//  circular queue is done through a test driver.
//
// INPUT:
//  1. The user must input a category to sort into a new list.
//  2. The user must input an item they want to get the price of.
//
// PROCESSING:
//  1. All the items in a list file are read into a queue.
//  2. If the list is full, enqueueing an item doubles the array size.
//  3. All items in one list that belong to a specified category are copied to a
//     new list with createList().
//  4. thirdList is created and initialized to firstList.
//  5. secondList is assigned the contents of thirdList.
//
// OUTPUT:
//  1. The list is printed with printList().
//  2. If the maximum array size is doubled, the new size is printed.
//  3. Dequeueing an item from the list prints the item name.
//  4. When the user specifies an item to get the price of, the item's price is
//     printed. If the item is not found, the user is notified.
//  5. When the user provides a category in which to make a new list, the items
//     belonging to the specified category are printed.
//
// EXAMPLES:
//  1) Capacity doubled to 8
//     There are 6 items in first list
//
//     First list:
//     # Name -- Price -- Category
//     1 banana -- $3.99 -- food
//     2 shampoo -- $4.79 -- beauty
//     3 chair -- $24.2 -- home
//     4 milk -- $2.59 -- food
//     5 carrot -- $0.69 -- food
//     6 skirt -- $25.99 -- clothing
//
//     What item would you like to get the price of?: banana
//     banana costs $3.99
//     Enter a category to copy to a new list: clothing
//     Creating second list...
//     Second list:
//     # Name -- Price -- Category
//     1 skirt -- $25.99 -- clothing
//
//     Creating third list...
//     Copying all items from first list to third list...
//     Third list:
//     # Name -- Price -- Category
//     1 banana -- $3.99 -- food
//     2 shampoo -- $4.79 -- beauty
//     3 chair -- $24.2 -- home
//     4 milk -- $2.59 -- food
//     5 carrot -- $0.69 -- food
//     6 skirt -- $25.99 -- clothing
//
//     Bought banana
//     Bought shampoo
//
//     Third list:
//     # Name -- Price -- Category
//     1 chair -- $24.2 -- home
//     2 milk -- $2.59 -- food
//     3 carrot -- $0.69 -- food
//     4 skirt -- $25.99 -- clothing
//
//     Assigning thirdList to secondList
//     Second list:
//     # Name -- Price -- Category
//     1 chair -- $24.2 -- home
//     2 milk -- $2.59 -- food
//     3 banana -- $3.99 -- food
//     4 shampoo -- $4.79 -- beauty
//
//     Bought chair
//     Bought milk
//
//     Second list:
//     # Name -- Price -- Category
//     1 banana -- $3.99 -- food
//     2 shampoo -- $4.79 -- beauty
//
// SOURCES:
//  cplusplus.com
//   - using delimiters in getline()
//   - converting string type to float with stof()

#include "shopping.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void readFile(ShoppingList& myList, string fileName);
// PURPOSE: This function reads each item from a file containing a list.
// PRECONDITION: An empty queue exists and a file name is provided.
// POSTCONDITION: All items in the list are equeued into the queue.

int main(int argc, char** argv)
{
  // 1. Create first list and read in items
  ShoppingList firstList;
  string fileName = "items.txt";
  readFile(firstList, fileName);
  
  cout << "There are " << firstList.getSize() << " items in first list" << endl
       << endl << "First list:" << endl;
  firstList.printList();

  // 2. Get the price of an item from the list
  cout << "What item would you like to get the price of?: ";
  string item;
  cin >> item;

  float price = firstList.getPrice(item);
  if (price == 0)
    cout << "This item is not in the list" << endl;
  else
    cout << item << " costs $" << price << endl;
  
  // 3. Create second list containing only the items of one category
  //    in the first list.
  cout << "Enter a category to copy to a new list: ";
  string listCateg;
  cin >> listCateg;
  
  cout << "Creating second list..." << endl;
  ShoppingList secondList;
  firstList.createList(secondList, listCateg);
  
  cout << "Second list:" << endl;
  secondList.printList();
  
  // 4. Create third list
  cout << "Creating third list..." << endl
       << "Copying all items from first list to third list..." << endl;
  ShoppingList thirdList = firstList;  
  cout << "Third list:" << endl;
  thirdList.printList();

  // 5. Buy items / Remove items from third list
  thirdList.dequeue();
  thirdList.dequeue();
  cout << endl << "Third list:" << endl;
  thirdList.printList();
  
  // 6. Assign third list to second list
  secondList = thirdList;
  cout << "Assigning thirdList to secondList" << endl << "Second list:" << endl;
  secondList.printList();

  // 7. Buy items from second list
  secondList.dequeue();
  secondList.dequeue();
  cout << endl << "Second list:" << endl;
  secondList.printList();
  
  return 0;
}

void readFile(ShoppingList& myList, string fileName)
{
  ifstream file(fileName);
  string item;
  string itemName;
  string itemPrice;
  string itemCategory;
  while (getline(file, item) && !file.fail()) 
  {  
    stringstream line(item);
    getline(line, itemName, ',');
    getline(line, itemPrice, ',');
    getline(line, itemCategory, ',');
    myList.enqueue(itemName, stof(itemPrice), itemCategory);
  }
  
  file.close();
}
