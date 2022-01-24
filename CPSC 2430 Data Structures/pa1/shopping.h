// Justin Thoreson
// shopping.h
// 04/24/2020

#ifndef SHOPPING_H
#define SHOPPING_H
#include <string>

using namespace std;

class ShoppingList
{
  private:
    struct Item
    {
      string name;
      float price;
      string category;
    };

    Item* pItems;
    int front;
    int rear;
    int maxSize;
    int size;
    void copy(const ShoppingList& orig);
    void destroy();
    
  public:
    ShoppingList();
    ShoppingList(const ShoppingList& orig);
    ~ShoppingList();
    const ShoppingList& operator=(const ShoppingList& orig);
    void enqueue(string name, float price, string category);
    void dequeue();
    bool isEmpty() const;
    bool isFull() const;
    void doubleMaxSize();
    const int getSize() const;
    const float getPrice(string name) const;
    void printList() const;
    void createList(ShoppingList& s2, string categ);
};

#endif
