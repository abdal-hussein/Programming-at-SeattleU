// Justin Thoreson
// shopping.cpp
// 04/24/2020

#include "shopping.h"
#include <iostream>
#include <string>

ShoppingList::ShoppingList()
{
  maxSize = 4;
  size = 0;
  front = -1;
  rear = -1;
  pItems = new Item[maxSize];
}

ShoppingList::ShoppingList(const ShoppingList& orig)
{
  maxSize = orig.maxSize;
  size = 0;
  front = -1;
  rear = -1;
  pItems = new Item[maxSize];
  copy(orig);
}

ShoppingList::~ShoppingList() { destroy(); }

const ShoppingList& ShoppingList::operator=(const ShoppingList& right)
{
  if (this != &right)
  {
    destroy();
    front = -1;
    rear = -1;
    size = 0;
    pItems = new Item[maxSize];
    copy(right);
  }

  return *this;
}

void ShoppingList::enqueue(string name, float price, string category)
{
  if (isEmpty())
    front++;  
  else if (isFull())
    doubleMaxSize();

  size++;
  rear = front + size - 1;
  pItems[rear%maxSize].name = name;
  pItems[rear%maxSize].price = price;
  pItems[rear%maxSize].category = category;
}

void ShoppingList::dequeue()
{
  if (isEmpty())
    cout << "The list is empty" << endl;
  
  else
  {
    cout << "Bought " << pItems[front%maxSize].name << endl;
    front++;
    size--;
  }
}

bool ShoppingList::isEmpty() const { return size == 0; }

bool ShoppingList::isFull() const { return size == maxSize; }

// PURPOSE: Doubles the maximum size of the queue.
// PRECONDITION: The queue's capacity has exceeded the maximum limit.
//               The queue is full.
// POSTCONDITION: The maximum capacity is doubled. 
void ShoppingList::doubleMaxSize()
{
  Item* temp = new Item[maxSize*2];
  int j = 0;
  for (int i = front; i <= front + size; i++)   
    temp[j++] = pItems[i%maxSize];
 
  destroy();
  pItems = temp;
  front = 0;
  maxSize *= 2;

  cout << "Capacity doubled to " << maxSize << endl;
}

const int ShoppingList::getSize() const { return size; }

const float ShoppingList::getPrice(string name) const
{
  float price = 0;
  for (int i = 0; i < maxSize; i++)
    if (pItems[i].name == name)
      price = pItems[i].price;
  
  return price;
}

void ShoppingList::printList() const
{
  if (isEmpty())
    cout << "The list is empty" << endl;

  else
  {
    cout << "# Name -- Price -- Category"  << endl;
    int itemNum = 0;
    for (int i = front; i < front + size; i++)
    {
      cout << ++itemNum << " "
           << pItems[i%maxSize].name << " -- $" 
           << pItems[i%maxSize].price << " -- "
           << pItems[i%maxSize].category << endl;
    }
  }
  
  cout << endl;
}

// PURPOSE: Assigns all items belonging to one category from the first list to a
//          new list.
// PRECONDITION: An empty list has been created and a category has been
//               specified.
// POSTCONDITION: The new list contains only one category from the first list.
void ShoppingList::createList(ShoppingList& s2, string categ)
{
  for (int i = front; i < front + size; i++)
    if (pItems[i%maxSize].category == categ) 
      s2.enqueue(pItems[i%maxSize].name, pItems[i%maxSize].price, categ);
}

void ShoppingList::copy(const ShoppingList& orig)
{
  for (int i = orig.front; i < orig.front + orig.size; i++)
  {  
    enqueue(orig.pItems[i%maxSize].name, orig.pItems[i%maxSize].price,
            orig.pItems[i%maxSize].category);
  }
}

void ShoppingList::destroy() { delete [] pItems; }
