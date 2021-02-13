/* Justin Thoreson
 * P2.cpp
 * September 27, 2020
 * 
 * PURPOSE:
 *  This assignment is meant to demonstrate composition, move semantics and the
 *  use of smart pointers.
 *
 * PROCESSING:
 *  1. Three unique pointers are tested for collisions, inversions, and copying.
 *  2. Three shared pointers are tested for collisions, inversions, and copying.
 *  3. Each object is assigned various distinct values.
 *  4. Copying is tested via initilization and assignment.
 *  5. Two unique pointers and one shared pointer are tested. Testing for
 *     collisions and inversions emulates a similar process to steps 1 through 4,
 *     however, copying is tested via an STL container; a vector. The three
 *     objects are instantiated as smart pointers, but are used to initialize a
 *     a vector of three duelingJP objects.
 *
 * OUTPUT:
 *  1. The collisions and inversions of each object are output.
 *  2. The collisions and inversions of an object are displayed again if copying
 *     was tested on said object.
 *
 * SOURCES:
 *  geeksforgeeks.org & stackoverflow.com
 *   - Smart pointer information: mainly make_unique & make_shared
 *  cplusplus.com
 *   - STL information
 */

#include <iostream>
#include <memory>
#include <vector>
#include "duelingJP.h"

using namespace std;

void testUniquePtr();
void testSharedPtr();
void testSTL();

int main(int argc, char** argv)
{
  testUniquePtr();
  testSharedPtr();
  testSTL();
  
  return 0;
}

void testUniquePtr()
{
  // Unique 1
  const int NUM_ELEMS_UNIQUE = 5;
  unsigned valuesUnique[NUM_ELEMS_UNIQUE] = {999, 1001, 2020, 9966, 10000};
  unique_ptr<duelingJP> myObj
    = make_unique<duelingJP>(valuesUnique, NUM_ELEMS_UNIQUE);

  cout << "UNIQUE POINTER TEST:" << endl
       << "Unique Obj 1:\n" << "Collisions: " << myObj->getCollisions()
       << " Inversions: " << myObj->getInversions() << endl;
  
  // Unique 2 -- Test Copy
  unique_ptr<duelingJP> myObj2 = make_unique<duelingJP>(*myObj);
  cout << "Unique Obj 2:\n" << "Collisions: " << myObj2->getCollisions()
       << " Inversions: " << myObj2->getInversions() << endl;

  // Unique 3 -- Test Assignment
  const int NUM_ELEMS_UNIQUE_2 = 7;
  unsigned valuesUnique2[NUM_ELEMS_UNIQUE_2]
    = {5555, 5556, 5557, 5558, 5559, 5560, 5561};
  unique_ptr<duelingJP> myObj3
    = make_unique<duelingJP>(valuesUnique2, NUM_ELEMS_UNIQUE_2);

  cout << "Unique Obj 3:\n" << "Collisions: " << myObj3->getCollisions()
       << " Inversions: " << myObj3->getInversions() << endl;

  *myObj = *myObj3;
  cout << "Unique Obj 1:\n" << "Collisions: " << myObj->getCollisions()
       << " Inversions: " << myObj->getInversions() << endl;
}

void testSharedPtr()
{
  // Shared 1
  const int NUM_ELEMS_SHARED = 5;
  unsigned valuesShared[NUM_ELEMS_SHARED] = {999, 1001, 1002, 1003, 1004};
  shared_ptr<duelingJP> myObj
    = make_shared<duelingJP>(valuesShared, NUM_ELEMS_SHARED);

  cout << endl << "SHARED POINTER TEST:" << endl
       << "Shared Obj 1:\n" << "Collisions: " << myObj->getCollisions()
       << " Inversions: " << myObj->getInversions() << endl;

  // Shared 2 -- Test Copy 
  shared_ptr<duelingJP> myObj2 = make_shared<duelingJP>(*myObj);
  cout << "Shared Obj 2:\n" << "Collisions: " << myObj2->getCollisions()
       << " Inversions: " << myObj2->getInversions() << endl;

  // Shared 3 -- Test Assignment
  const int NUM_ELEMS_SHARED_2 = 4;
  unsigned valuesShared2[NUM_ELEMS_SHARED_2] = {3003, 3007, 7013, 7017};
  shared_ptr<duelingJP> myObj3
    = make_shared<duelingJP>(valuesShared2, NUM_ELEMS_SHARED_2);

  cout << "Shared Obj 3:\n" << "Collisions: " << myObj3->getCollisions()
       << " Inversions: " << myObj3->getInversions() << endl;

  *myObj = *myObj3;
  cout << "Shared Obj 1:\n" << "Collisions: " << myObj->getCollisions()
       << " Inversions: " << myObj->getInversions() << endl;
}

void testSTL()
{
  // Smart Pointers
  const int NUM_ELEMS_STL = 3;
  unsigned valuesSTL[NUM_ELEMS_STL] = {4480, 4482, 3384};
  unique_ptr<duelingJP> myObj = make_unique<duelingJP>(valuesSTL, NUM_ELEMS_STL);

  const int NUM_ELEMS_STL_2 = 4;
  unsigned valuesSTL2[NUM_ELEMS_STL_2] = {4000, 5000, 6000, 7000};
  unique_ptr<duelingJP> myObj2 = make_unique<duelingJP>(valuesSTL2, NUM_ELEMS_STL_2);

  const int NUM_ELEMS_STL_3 = 5;
  unsigned valuesSTL3[NUM_ELEMS_STL_3] = {1234, 1235, 5678, 5679, 5684};
  shared_ptr<duelingJP> myObj3 = make_shared<duelingJP>(valuesSTL3, NUM_ELEMS_STL_3);
  
  cout << endl << "STL TEST:" << endl
       << "Unique Obj 1:\n" << "Collisions: " << myObj->getCollisions()
       << " Inversions: " << myObj->getInversions() << endl
       << "Unique Obj 2:\n" << "Collisions: " << myObj2->getCollisions()
       << " Inversions: " << myObj2->getInversions() << endl
       << "Shared Obj 1:\n" << "Collisions: " << myObj3->getCollisions()
       << " Inversions: " << myObj3->getInversions() << endl;

  // STL -- Vector
  vector<duelingJP> myVector = {*myObj, *myObj2, *myObj3};
  for (unsigned i = 0; i < myVector.size(); i++)
  {
    cout << "STL Obj " << i + 1 << ":\n"
         << "Collisions: " << myVector[i].getCollisions()
         << " Inversions: " << myVector[i].getInversions() << endl;
  }
}
