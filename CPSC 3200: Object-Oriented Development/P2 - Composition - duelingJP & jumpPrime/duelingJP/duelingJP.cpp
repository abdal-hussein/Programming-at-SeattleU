/* Justin Thoreson
 *  duelingJP.cpp
 *  September 27, 2020
 * 
 * Implementation Invariants:
 *  1. An array of provided distinct values are given to a duelingJP object.
 *     The object creates multiple jumpPrime objects and provides them one of
 *     the given values such that it may be encapsulated in the respective
 *     jumpPrime.
 *  2. The number of collisions and the number of inversions within a duelingJP
 *     are incremented each time there is an occurence.
 *  3. Whenever a jumpPrime becomes inactive, it is reset to its original state.
 */

#include "duelingJP.h"

duelingJP::duelingJP(unsigned values[], int numValues)
  : numJPs(numValues), collisions(0), inversions(0)
{ 
  jpObjs = new jumpPrime[numJPs];
  for (unsigned i = 0; i < numJPs; i++)   
    jpObjs[i].setEncapVal(values[i]);
        
  countCollisions(values);
  countInversions(values);
}

duelingJP::duelingJP(const duelingJP& orig) { copy(orig); }

duelingJP::duelingJP(duelingJP&& orig)
{
  jpObjs = orig.jpObjs;
  numJPs = orig.numJPs;
  collisions = orig.collisions;
  inversions = orig.inversions;

  orig.jpObjs = nullptr;
  orig.numJPs = 0;
  orig.collisions = 0;
  orig.inversions = 0;
}

duelingJP& duelingJP::operator=(const duelingJP& orig)
{ 
  if (this != &orig)
  {
    destroy();    
    copy(orig);
  }

  return *this;
}

duelingJP& duelingJP::operator=(duelingJP&& orig)
{
  swapAdrs(jpObjs, orig.jpObjs);
  swapVals(numJPs, orig.numJPs);
  swapVals(collisions, orig.collisions);
  swapVals(inversions, orig.inversions);
  return *this;
}

duelingJP::~duelingJP() { destroy(); } 

void duelingJP::copy(const duelingJP& orig)
{  
  jpObjs = new jumpPrime[orig.numJPs];
  for (unsigned i = 0; i < orig.numJPs; i++)
    jpObjs[i] = orig.jpObjs[i];

  numJPs = orig.numJPs;  
  collisions = orig.collisions;
  inversions = orig.inversions;
}

void duelingJP::destroy() { delete [] jpObjs; }

void duelingJP::swapAdrs(jumpPrime* adr1, jumpPrime* adr2)
{
  jumpPrime* temp = adr1;
  adr1 = adr2;
  adr2 = temp;
}

void duelingJP::swapVals(unsigned& num1, unsigned& num2)
{
  unsigned temp = num1;
  num1 = num2;
  num2 = temp;
}

// PRECONDITION: The object contains jumpPrimes.
// POSTCONDITION: The number of jumpPrime collisions may be >= zero.
void duelingJP::countCollisions(unsigned values[])
{
  for (unsigned i = 0; i < numJPs; i++)
  {
    for (unsigned j = i + 1; j < numJPs; j++)
    {
      if (jpObjs[i].up() == jpObjs[j].up()
          || jpObjs[i].down() == jpObjs[j].down())
        collisions++;

      if (!jpObjs[i].getActiveStatus()) jpObjs[i].reset(values[i]);

      if (!jpObjs[j].getActiveStatus()) jpObjs[j].reset(values[j]);
    }
  }
}

// PRECONDITION: The duelingJP object contains jumpPrimes.
// POSTCONDITION: The number of jumpPrime inversions may be >= zero.
void duelingJP::countInversions(unsigned values[])
{
  for (unsigned i = 0; i < numJPs; i++)
  {
    for (unsigned j = i + 1; j < numJPs; j++)
    {
      if (jpObjs[i].up() == jpObjs[j].down()
          || jpObjs[i].down() == jpObjs[j].up())
        inversions++;

      if (!jpObjs[i].getActiveStatus()) jpObjs[i].reset(values[i]);

      if (!jpObjs[j].getActiveStatus()) jpObjs[j].reset(values[j]);
    }
  }
}

unsigned duelingJP::getCollisions() { return collisions; }

unsigned duelingJP::getInversions() { return inversions; }
