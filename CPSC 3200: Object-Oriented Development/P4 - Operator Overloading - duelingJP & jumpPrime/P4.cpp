/* Justin Thoreson
 * P4.cpp
 * 28 October 2020
 *
 * SUMMARY:
 *  - This assignment is mainly meant to demonstrate the implementation of
 *    operator overloading via class design.
 *  - Relational, addition, and subtraction operators are supported in both the
 *    duelingJP and jumpPrime classes.
 *  - The operators overloaded for jumpPrime are incorporated in duelingJP class.
 *  - For both classes, operators + and - are implemented in their respective
 *    += and -= operators.
 *  - The driver tests the functionality of 5 main operator overload types:
 *     1. Relational operators
 *     2. Object & integer addition
 *     3. Object & object addition
 *     4. Object & integer subtraction
 *     5. Object & object subtraction
 *     Note: Overload operator<< is also tested.
 *  - The collisions and inversions of each duelingJP are output when introduced
 *    or after an operation has occured.
 */

#include <iostream>
#include "duelingJP.h"

using namespace std;

void testRelation();
void testIntegerAddition();
void testObjectAddition();
void testIntegerSubtraction();
void testObjectSubtraction();

int main(int argc, char** argv)
{
  cout << "Test -- Relational Operators" << endl;
  testRelation();
  cout << "Test -- Addition Operators" << endl;
  testIntegerAddition();
  testObjectAddition();  
  cout << "Test -- Subtraction Operators" << endl;
  testIntegerSubtraction();
  testObjectSubtraction();
  
  return 0;
}

void testRelation()
{
  // Test -- Two equal objects
  const int NUM_OBJS = 3;
  const int NUM_ELEMS1 = 5;
  const int NUM_ELEMS2 = 6;
  unsigned values1[NUM_ELEMS1] = {99, 100, 102, 104, 105};
  unsigned values2[NUM_ELEMS2] = {999, 1000, 2001, 2020, 9999, 10000};
  duelingJP myObjs[NUM_OBJS] = {{values1, NUM_ELEMS1}, {values1, NUM_ELEMS1},
                                {values2, NUM_ELEMS2}};
  cout << "Objects:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;
  
  // Test -- Two equal objects
  cout << endl << "Test Equal Objects:" << endl
       << "obj1 == obj2: " << (myObjs[0] == myObjs[1] ? "true" : "false") << endl
       << "obj1 != obj2: " << (myObjs[0] != myObjs[1] ? "true" : "false") << endl
       << "obj1 > obj2: " << (myObjs[0] > myObjs[1] ? "true" : "false") << endl
       << "obj1 < obj2: " << (myObjs[0] < myObjs[1] ? "true" : "false") << endl
       << "obj1 >= obj2: " << (myObjs[0] >= myObjs[1] ? "true" : "false") << endl
       << "obj1 <= obj2: " << (myObjs[0] <= myObjs[1] ? "true" : "false") << endl;
  // Test -- Two inequal objects
    cout << endl << "Test Inequal Objects:" << endl
       << "obj2 == obj3: " << (myObjs[1] == myObjs[2] ? "true" : "false") << endl
       << "obj2 != obj3: " << (myObjs[1] != myObjs[2] ? "true" : "false") << endl
       << "obj2 > obj3: " << (myObjs[1] > myObjs[2] ? "true" : "false") << endl
       << "obj2 < obj3: " << (myObjs[1] < myObjs[2] ? "true" : "false") << endl
       << "obj2 >= obj3: " << (myObjs[1] >= myObjs[2] ? "true" : "false") << endl
       << "obj2 <= obj3: " << (myObjs[1] <= myObjs[2] ? "true" : "false") << endl
       << endl;
}

void testIntegerAddition()
{
  const int NUM_OBJS = 5;
  const int NUM_ELEMS1 = 3;
  const int NUM_ELEMS2 = 5;
  const int NUM_ELEMS3 = 7;
  const int NUM_ELEMS4 = 9;
  const int NUM_ELEMS5 = 11;
  unsigned values1[NUM_ELEMS1] = {210, 220, 222};
  unsigned values2[NUM_ELEMS2] = {100, 105, 200, 209, 300};
  unsigned values3[NUM_ELEMS3] = {1000, 2319, 2321, 2323, 4004, 4012, 5000};
  unsigned values4[NUM_ELEMS4] = {404, 555, 557, 404, 555, 666, 777, 888, 999}; 
  unsigned values5[NUM_ELEMS5] = {808, 999, 1001, 1003, 7137, 7138, 8008, 8015, 8017, 8021, 8023};
  duelingJP myObjs[NUM_OBJS] = {{values1, NUM_ELEMS1}, {values2, NUM_ELEMS2},
                                {values3, NUM_ELEMS3}, {values4, NUM_ELEMS4},
                                {values5, NUM_ELEMS5}};
  cout << "Original -- Object & Integer:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;

  cout << "After += 100:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
  {
    myObjs[i] += 100;  
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;
  }

  cout << "After pre++:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << ++myObjs[i] << endl;
  
  cout << "Before post++:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i]++ << endl;  
  cout << "After post++:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;
  cout << endl;
}

void testObjectAddition()
{
  const int NUM_OBJS = 3;
  const int NUM_ELEMS = 3;
  unsigned values1[NUM_ELEMS] = {404, 408, 412};
  unsigned values2[NUM_ELEMS] = {808, 812, 816};
  unsigned values3[NUM_ELEMS] = {1212, 1220, 1228};
  duelingJP myObjs[NUM_OBJS] = {{values1, NUM_ELEMS}, {values2, NUM_ELEMS},
                                {values3, NUM_ELEMS}};
  cout << "Original -- Object & Object:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;

  myObjs[0] += myObjs[1];
  cout << "After myObj1 += myObj2:" << endl
       << "myObj1: " << myObjs[0] << endl
       << "myObj3: " << myObjs[2] << endl << endl;
}

void testIntegerSubtraction()
{
  const int NUM_OBJS = 5;
  const int NUM_ELEMS1 = 3;
  const int NUM_ELEMS2 = 5;
  const int NUM_ELEMS3 = 7;
  const int NUM_ELEMS4 = 9;
  const int NUM_ELEMS5 = 11;
  unsigned values1[NUM_ELEMS1] = {210, 220, 222};
  unsigned values2[NUM_ELEMS2] = {100, 105, 200, 209, 300};
  unsigned values3[NUM_ELEMS3] = {1000, 2319, 2321, 2323, 4004, 4012, 5000};
  unsigned values4[NUM_ELEMS4] = {404, 555, 557, 404, 555, 666, 777, 888, 999};
  unsigned values5[NUM_ELEMS5] = {808, 999, 1001, 1003, 7137, 7138, 8008, 8015, 8017, 8021, 8023};
  duelingJP myObjs[NUM_OBJS] = {{values1, NUM_ELEMS1}, {values2, NUM_ELEMS2},
                                {values3, NUM_ELEMS3}, {values4, NUM_ELEMS4},
                                {values5, NUM_ELEMS5}};
  cout << "Original -- Object & Integer:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;

  cout << "After -= 100:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
  {
    myObjs[i] -= 100;
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;
  }

  cout << "After pre--:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << --myObjs[i] << endl;

  cout << "Before post--:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i]-- << endl;
  cout << "After post--:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;
  cout << endl;
}

void testObjectSubtraction()
{
  const int NUM_OBJS = 3;
  const int NUM_ELEMS = 3;
  unsigned values1[NUM_ELEMS] = {404, 408, 412};
  unsigned values2[NUM_ELEMS] = {808, 812, 816};
  unsigned values3[NUM_ELEMS] = {1212, 1220, 1228};
  duelingJP myObjs[NUM_OBJS] = {{values1, NUM_ELEMS}, {values2, NUM_ELEMS},
                                {values3, NUM_ELEMS}};
  cout << "Original -- Object & Object:" << endl;
  for (int i = 0; i < NUM_OBJS; i++)
    cout << "myObj" << i + 1 << ": " << myObjs[i] << endl;

  myObjs[2] -= myObjs[0];
  cout << "After myObj3 -= myObj1:" << endl
       << "myObj2: " << myObjs[1] << endl
       << "myObj3: " << myObjs[2] << endl;
}
