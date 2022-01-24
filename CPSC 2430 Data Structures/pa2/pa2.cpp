// Justin Thoerson
// pa2.cpp
// 05/06/2020
//
// PURPOSE:
//  The purpose of this program is to demonstrate the use of a stack implemented
//  through a singly-linked list. Demonstration of a recursive function is also
//  done through this program. The stack stores single digits that could be
//  entered in the form of a multi-digit value.
//
// INPUT:
//  1. When prompted, the user must enter a non-negative integer to be stored in
//     the stack.
//
// PROCESSING:
//  1. The user's input is separated into individual digits.
//  2. Each digit of the user's input is stored into individual nodes of a
//     stack.
//  3. A new stack can be initialized to an existing stack and an existing stack
//     can be assigned to a different existing stack.
//
// OUTPUT:
//  1. Each digit is printed on a single line in the form of asterisks.
//     The asterisks represent the quantity of the digit. If the digit is 0,
//     a hyphen is printed instead.
//  2. Each digit in the stack is printed, each separated by a comma.
//
// EXAMPLES:
//  1) Enter a positive integer: 2021
//     Values in stack1: 2, 0, 2, 1
//     **
//     -
//     **
//     *
//     Popping 2
//     Popping 0
//     Values in stack1: 2, 1
//
//     Initializing stack2 with stack1
//     Values in stack2: 2, 1
//     Pushing 9
//     Pushing 7
//     Values in stack2: 7, 9, 2, 1
//     *******
//     *********
//     **
//     *
//
//     Creating empty stack3
//     Pushing 2
//     Pushing 0
//     Pushing 5
//     Top of stack3 is 5
//     Assigning stack3 to stack1
//     Values in stack1: 5, 0, 2
//     *****
//     -
//     ** 
//
//  2) Enter a positive integer: 54
//     Values in stack1: 5, 4
//     *****
//     ****
//     Popping 5
//     Popping 4
//     Values in stack1: The stack is empty
//
//     Initializing stack2 with stack1
//     Values in stack2: The stack is empty
//     Pushing 9
//     Pushing 7
//     Values in stack2: 7, 9
//     *******
//     *********
//
//  3) Enter a positive integer: 1
//     Values in stack1: 1
//     *
//     Popping 1
//     The stack is empty. Cannot pop values.
//     Values in stack1: The stack is empty


#include "recursiveStack.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
  // 1. Create stack1 and get user input
  RecursiveStack stack1;

  cout << "Enter a positive integer: ";
  int value;
  cin >> value;

  while (value <= 0)
  {
    cout << "Invalid input. Enter a positive integer: ";
    cin >> value;
  }
  
  stack1.recInsert(value);
  cout << "Values in stack1: ";
  stack1.print();
  stack1.printStars();

  // 2. Pop values from stack1
  int popVal = stack1.pop();
  if (popVal == -1)
    cout << "The stack is empty. Cannot pop values." << endl;
  else
    cout << "Popping " << popVal << endl;

  popVal = stack1.pop();
  if (popVal == -1)
    cout << "The stack is empty. Cannot pop values." << endl;
  else
    cout << "Popping " << popVal << endl;
  
  cout << "Values in stack1: ";
  stack1.print();
  cout << endl;
  
  // 3. Initialize stack2 with stack1
  cout << "Initializing stack2 with stack1" << endl;
  RecursiveStack stack2 = stack1;
  cout << "Values in stack2: ";
  stack2.print();
  
  // 4. Push values into stack2
  cout << "Pushing 9" << endl;
  stack2.push(9);
  cout << "Pushing 7" << endl;
  stack2.push(7);
  cout << "Values in stack2: ";
  stack2.print();
  stack2.printStars();
 
  // 4. Create stack3 and push values
  cout << endl << "Creating empty stack3" << endl;
  RecursiveStack stack3;
  cout << "Pushing 2" << endl;
  stack3.push(2);
  cout << "Pushing 0" << endl;
  stack3.push(0);
  cout << "Pushing 5" << endl;
  stack3.push(5);
  cout << "Top of stack3 is " << stack3.top() << endl;
  
  // 5. Assign stack3 to stack1
  cout << "Assigning stack3 to stack1" << endl;
  stack1 = stack3;
  cout << "Values in stack1: ";
  stack1.print();
  stack1.printStars();
  
  return 0;
}
