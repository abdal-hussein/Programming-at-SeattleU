// Justin Thoreson
// recursiveStack.h
// 05/06/2020

#ifndef RECURSIVESTACK_H
#define RECURSIVESTACK_H

class RecursiveStack
{
  private:
    struct RecStkNode
    {
      int digit;
      RecStkNode* next;
    };

    RecStkNode* head;
    void copy(const RecursiveStack& orig);
    void destroy();
    
  public:
    RecursiveStack();
    RecursiveStack(const RecursiveStack& orig);
    const RecursiveStack& operator=(const RecursiveStack& right);
    ~RecursiveStack();
    void push(int dgt);
    int pop();
    int top() const; 
    bool isEmpty() const;
    void recInsert(int value);
    void printStars() const;
    void print() const;
};

#endif
