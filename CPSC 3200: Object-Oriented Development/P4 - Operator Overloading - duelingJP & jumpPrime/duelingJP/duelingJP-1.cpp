/* Justin Thoreson
 * duelingJP.cpp
 * 28 October 2020
 * 
 * Implementation Invariants:
 *  1. An array of provided distinct values are given to a duelingJP object.
 *     The object creates multiple jumpPrime objects and provides them one of
 *     the given values such that it may be encapsulated in the respective
 *     jumpPrime.
 *  2. The number of collisions and the number of inversions within a duelingJP
 *     are incremented each time there is an occurence.
 *  3. Whenever a jumpPrime becomes inactive, it is reset to its original state.
 *
 *  OPERATOR OVERLOADING:
 *  1. Relational Operators:
 *     - The equality or inequality of two objects depends on each data member.
 *     - Operators greater than and less than depend on the cardinality of
 *       objects.
 *     - Operators involvion equal to and greater than or less than 
 *  2. Addition:
 *     - Non-destructive addition is supported.
 *       - An integer can be added to an object.
 *         - Pre and post increment are thus supported.
 *         - An integer is added to each jumpPrime object contained in a
 *           duelingJP. Then the number of collision and inversions are
 *           recalculated.
 *       - An object can be added to another object.
 *         - When obj1 + obj2, each corresponding jumpPrime element in obj2 is
 *           added to obj1 until the greatest number of jumpPrimes in obj1 or
 *           obj2 is reached. 
 *     - Operator+= is supported, but calls operator+ before assigning.
 *  3. Subtraction:
 *     - Non-destructive Subtraction is supported.
 *       - An integer can be subtracted from an object.
 *         - Pre and post decrement are thus supported.
 *         - An integer is subtracted from each jumpPrime object, then the
 *           number of collisions an inversions are recalculated.
 *       - An object can be subtracted from another object.
 *         - When obj1 - obj2, the corresponding jumpPrime elements in obj2 are
 *           subtracted from obj1 until number of jumpPrimes in either object is
 *           reached or both.
 *     - Operator-= is supported. Calls operator- before assigning.
 *  4. Communative addition and subtraction for object and integer operations
 *     are not supported. When adding an integer to an object, the object should
 *     be the left hand operand and the integer should be the right hand operand.
 *     This is to improve readability. If one is to add an int to an object, it
 *     should be clear, and thus we want a consistent method for doing so.
 *     Obj + int syntactically reads differently than int + obj. 
 *  5. Operator<< is overloaded.
 *     - Displays the total collisions and inversions.
 */

#include "duelingJP.h"

duelingJP::duelingJP()
  : numJPs(0), collisions(0), inversions(0) {}

duelingJP::duelingJP(unsigned values[], int numValues)
  : numJPs(numValues), collisions(0), inversions(0)
{
  jpObjs = new jumpPrime[numJPs];
  for (unsigned i = 0; i < numJPs; i++)   
    jpObjs[i].setEncapVal(values[i]);  
  countCollisions();
  countInversions();
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
  if (this == &orig) return *this;
  destroy();    
  copy(orig);
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

duelingJP duelingJP::increment()
{
  for (unsigned i = 0; i < numJPs; i++)
    jpObjs[i]++;
  countCollisions();
  countInversions();
  return *this;
}

duelingJP duelingJP::decrement()
{
  for (unsigned i = 0; i < numJPs; i++)
    jpObjs[i]--;
  countCollisions();
  countInversions();
  return *this;
}

duelingJP duelingJP::operator+(const duelingJP& rhs)
{ 
  if (numJPs + rhs.numJPs == 0) return *this;
  duelingJP local;
  local.numJPs = (numJPs < rhs.numJPs) ? rhs.numJPs : numJPs;
  local.jpObjs = new jumpPrime[numJPs];
  for (unsigned i = 0; i < numJPs; i++)
    local.jpObjs[i] = jpObjs[i];
  for (unsigned j = 0; j < rhs.numJPs; j++)
    local.jpObjs[j] += rhs.jpObjs[j];  
  local.countCollisions();
  local.countInversions();
  return local;
}

duelingJP duelingJP::operator+(int num) const
{  
  if (numJPs == 0) return *this;
  duelingJP local;
  local.numJPs = numJPs;
  local.jpObjs = new jumpPrime[numJPs];
  for (unsigned i = 0; i < numJPs; i++)
    local.jpObjs[i] = jpObjs[i] + num;
  local.countCollisions();
  local.countInversions();
  return local;
}

duelingJP& duelingJP::operator+=(const duelingJP& rhs)
{
  *this = *this + rhs;
  return *this; 
}

duelingJP& duelingJP::operator+=(int num)
{
  *this = *this + num;
  return *this;
}

duelingJP duelingJP::operator++() { return increment(); }

duelingJP duelingJP::operator++(int dummy)
{
  duelingJP oldState = *this;
  increment();
  return oldState;
}

duelingJP duelingJP::operator-(const duelingJP& rhs)
{
  if (numJPs == 0) return *this;  
  duelingJP local;
  local.numJPs = numJPs;
  local.jpObjs = new jumpPrime[numJPs];

  if (numJPs <= rhs.numJPs)
    for (unsigned i = 0; i < numJPs; i++)
      local.jpObjs[i] = jpObjs[i] - rhs.jpObjs[i];
  else
  {  
    for (unsigned i = 0; i < numJPs; i++)
      local.jpObjs[i] = jpObjs[i];
    for (unsigned j = 0; j < rhs.numJPs; j++)
      local.jpObjs[j] -= rhs.jpObjs[j];
  }
  
  local.countCollisions();
  local.countInversions();
  return local;
}

duelingJP duelingJP::operator-(int num) const
{
  if (numJPs == 0) return *this;
  duelingJP local;
  local.numJPs = numJPs;
  local.jpObjs = new jumpPrime[numJPs];
  for (unsigned i = 0; i < numJPs; i++)
    local.jpObjs[i] = jpObjs[i] - num;
  local.countCollisions();
  local.countInversions();
  return local;
}

duelingJP& duelingJP::operator-=(const duelingJP& rhs)
{
  *this = *this - rhs;
  return *this;
}

duelingJP& duelingJP::operator-=(int num)
{
  *this = *this - num;
  return *this;
}

duelingJP duelingJP::operator--() { return decrement(); }

duelingJP duelingJP::operator--(int dummy)
{
  duelingJP oldState = *this;
  decrement();
  return oldState;
}

bool duelingJP::operator>(const duelingJP& rhs) { return numJPs > rhs.numJPs; }
bool duelingJP::operator<(const duelingJP& rhs) { return numJPs < rhs.numJPs; }

bool duelingJP::operator==(const duelingJP& rhs)
{
  if (numJPs == rhs.numJPs) return true;
  if (collisions == rhs.collisions) return true;
  if (inversions == rhs.inversions) return true;
  for (unsigned i = 0; i < numJPs; i++)
    if (jpObjs[i] == rhs.jpObjs[i]) return true;
  return false;
}

bool duelingJP::operator!=(const duelingJP& rhs)
{
  if (numJPs != rhs.numJPs) return true;
  if (collisions != rhs.collisions) return true;
  if (inversions != rhs.inversions) return true;
  for (unsigned i = 0; i < numJPs; i++)
    if (jpObjs[i] != rhs.jpObjs[i]) return true;
  return false;
}

bool duelingJP::operator>=(const duelingJP& rhs)
{
  if (numJPs > rhs.numJPs) return true;
  if (collisions != rhs.collisions) return false;
  if (inversions != rhs.inversions) return false;
  for (unsigned i = 0; i < numJPs; i++)
    if (jpObjs[i] != rhs.jpObjs[i]) return false;
  return true;
}

bool duelingJP::operator<=(const duelingJP& rhs)
{
  if (numJPs < rhs.numJPs) return true;
  if (collisions != rhs.collisions) return false;
  if (inversions != rhs.inversions) return false;
  for (unsigned i = 0; i < numJPs; i++)
    if (jpObjs[i] != rhs.jpObjs[i]) return false;
  return true;
}

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
void duelingJP::countCollisions()
{
  for (unsigned i = 0; i < numJPs; i++)
  {
    for (unsigned j = i + 1; j < numJPs; j++)
    {
      if (jpObjs[i].up() == jpObjs[j].up()
          || jpObjs[i].down() == jpObjs[j].down())
        collisions++;
      if (!jpObjs[i].getActiveStatus()) jpObjs[i].reset();
      if (!jpObjs[j].getActiveStatus()) jpObjs[j].reset();
    }
  }
}

// PRECONDITION: The duelingJP object contains jumpPrimes.
// POSTCONDITION: The number of jumpPrime inversions may be >= zero.
void duelingJP::countInversions()
{
  for (unsigned i = 0; i < numJPs; i++)
  {
    for (unsigned j = i + 1; j < numJPs; j++)
    {
      if (jpObjs[i].up() == jpObjs[j].down()
          || jpObjs[i].down() == jpObjs[j].up())
        inversions++;
      if (!jpObjs[i].getActiveStatus()) jpObjs[i].reset();
      if (!jpObjs[j].getActiveStatus()) jpObjs[j].reset();
    }
  }
}

unsigned duelingJP::getCollisions() { return collisions; }
unsigned duelingJP::getInversions() { return inversions; }
