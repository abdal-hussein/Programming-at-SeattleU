// Justin Thoreson
// recursiveStack.cpp
// 05/06/2020

#include "recursiveStack.h"
#include <iostream>

using namespace std;

RecursiveStack::RecursiveStack()
  : head(nullptr)
{}

RecursiveStack::RecursiveStack(const RecursiveStack& orig)
  : head(nullptr)
{ copy(orig); }

const RecursiveStack& RecursiveStack::operator=(const RecursiveStack& right)
{
  if (this != &right)
  {
    destroy();
    copy(right);
  }

  return *this;
}

RecursiveStack::~RecursiveStack() { destroy(); }

void RecursiveStack::push(int dgt)
{
  RecStkNode* newNode = new RecStkNode;
  newNode->digit = dgt;
  newNode->next = nullptr;

  if (isEmpty())
    head = newNode;
  else
  {
    RecStkNode* temp = head;
    head = newNode;
    newNode->next = temp;
  }
}

int RecursiveStack::pop()
{
  int dgt = -1;
  if (!isEmpty())
  {
    dgt = head->digit;
    RecStkNode* temp = head->next;
    delete head;
    head = temp;
  }
  return dgt;
}

int RecursiveStack::top() const { return head->digit; }

bool RecursiveStack::isEmpty() const { return head == nullptr; }

// PURPOSE: Takes a value and inserts each individual digit into the stack.
// PRECONDITION: An positive integer is provided by the user.
// POSTCONDITION: Each digit of the integer is stored in the stack.
void RecursiveStack::recInsert(int value)
{
  if (value < 10)
    push(value);
  else
  {
    push(value%10);
    recInsert(value/10);
  }
}

// PURPOSE: Prints each digit in the stack in the form of asterisks (*).
//          The number of asterisks printed in a single line represents
//          the quantity of a digit in the stack. The digit 0 is represented
//          by a hyphen (-).
// PRECONDITION: A stack, empty or nonempty, exists.
// POSTCONDITION: Each digit is printed as a string of asterisks. 
void RecursiveStack::printStars() const
{
  if (isEmpty())
    cout << "The stack is empty" << endl;
  else
  {
    RecStkNode* nodePtr = head;    
    while (nodePtr)
    {
      if (nodePtr->digit == 0)
        cout << '-';
      else 
        for (int i = 0; i < nodePtr->digit; i++)
          cout << '*';

      cout << endl;
      nodePtr = nodePtr->next;
    }
  }
}

void RecursiveStack::print() const
{
  if (isEmpty())
    cout << "The stack is empty" << endl;
  else
  {
    RecStkNode* nodePtr = head;
    while (nodePtr)
    {  
      cout << nodePtr->digit;
      nodePtr = nodePtr->next;
      if (nodePtr)
        cout << ", ";
    }
    cout << endl;
  }
}

void RecursiveStack::copy(const RecursiveStack& orig)
{
  if (orig.isEmpty())
    head = nullptr;
  else
  {
    RecStkNode* nodePtr = orig.head;
    head = new RecStkNode;
    head->digit = nodePtr->digit;
    head->next = nullptr;

    RecStkNode* currentNode = head;
    while (nodePtr->next)
    {
      currentNode->next = new RecStkNode;
      currentNode->next->digit = nodePtr->next->digit;
      currentNode->next->next = nullptr;
      currentNode = currentNode->next;
      nodePtr = nodePtr->next;
    }
  }
}

void RecursiveStack::destroy()
{
  while (head)
  {  
    RecStkNode* temp = head->next;
    delete head;
    head = temp;
  } 
}
