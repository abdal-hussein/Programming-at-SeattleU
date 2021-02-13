/* Justin Thoreson
 * jumpPrime.cpp
 * 28 October 2020
 *
 * Implementation Invariants: 
 *  1. Must use setEncapVal() to properly instantiate the object with
 *     a value. Any numerical value provided to a jumpPrime object will be
 *     encapsulated, but if the value has less than three digits, the
 *     encapsulated number is set to 100, the lower limit, or if the value has
 *     greater than four digits, the value is set to 9999, the upper limit. If no
 *     value is provided, the value will be set to the default value, which is
 *     the lower limit.
 *  2. The number encapsulated by a jumpPrime will jump to a value that is 1
 *     greater than the closest prime greater than the number, or to a value
 *     1 less than the closest prime less than the number, if the number of
 *     up/down querries reaches the querry limit. This limit is determined 
 *     uniquely as the distance between the two aforementioned primes.
 *  3. The active state of a jumpPrime object will be evaluated to false if the
 *     number of jumps exceeds the specified bound.
 *  4. The active status will change back to true if the jumpPrime is revived or
 *     reset. 
 *  5. Reviving an active jumpPrime will permanently deactivate it. The object
 *     can not be revived or reset after permanent deactivation.
 *
 *  OPERATOR OVERLOADING:
 *  1. Relational Operators
 *     - Operators ==, !=, >=, and <= prioritize the active state of each object.
 *       - Permanent deactivation status is compared first, then general active
 *         status.
 *       - If the active conditions are false, the remaining data member are
 *         checked.
 *     - Operators > and < do not rely on the active state, just the other
 *       data members.
 *  2. Addition
 *     - Non-destructive addition is supported.
 *       - An integer can be added to an object.
 *         - Pre and post increment are thus supported.
 *         - An integer is added to the encapsulated value in a jumpPrime object.
 *           Then the upper prime and lower prime are recalculated.
 *       - An object can be added to another object.
 *         - When obj1 + obj2, the encapsulated value in obj2 is added to the
 *           one contained in obj1. Nearest primes are recalculated.
 *     - Operator+= is supported, but calls operator+ before assigning.
 *  3. Subtraction:
 *     - Non-destructive Subtraction is supported.
 *       - An integer can be subtracted from an object.
 *         - Pre and post decrement are thus supported.
 *         - An integer is subtracted from the encapsulated value in a jumpPrime
 *           object, then the nearest primes are calculated.
 *       - An object can be subtracted from another object.
 *         - When obj1 - obj2, the encapsulated value in obj2 is subtraced from
 *           from the one in obj1.
 *     - Operator-= is supported. Calls operator- before assigning.
 *  4. Communative addition and subtraction for object and integer operations
 *     are not supported. When adding an integer to an object, the object should
 *     be the left hand operand and the integer should be the right hand operand.
 *     This is to improve readability. If one is to add an int to an object, it
 *     should be clear, and thus we want a consistent method for doing so.
 *     Obj + int syntactically reads differently than int + obj.
 */

#include "jumpPrime.h"

jumpPrime::jumpPrime() : queryCount(0), jumpCount(0),
  isActive(true), permanentlyDeactivated(false) { }

jumpPrime& jumpPrime::operator=(const jumpPrime& rhs)
{
  if (this == &rhs || !this->isActive) return *this;
  setEncapVal(rhs.encapVal);
  return *this;
}

bool jumpPrime::isPrime(int n)
{
  if (n <= 1) return false;
  for (int i = 2; i < n; i++)
    if (n % i == 0) return false;
  return true;
}

int jumpPrime::findNextPrime(int n)
{
  while (!isPrime(++n)) {}
  return n;
}

int jumpPrime::findPreviousPrime(int n)
{
  while (!isPrime(--n)) {}
  return n;
}

jumpPrime jumpPrime::increment()
{
  if (isActive) setEncapVal(encapVal + 1);
  return *this;
}

jumpPrime jumpPrime::decrement()
{
  if (isActive) setEncapVal(encapVal - 1);
  return *this;
}

jumpPrime jumpPrime::operator+(const jumpPrime& rhs)
{
  if (!isActive) return *this;
  jumpPrime local;
  local.setEncapVal(encapVal + rhs.encapVal);
  return local;
}

jumpPrime jumpPrime::operator+(int num) const
{
  if (!isActive) return *this;
  jumpPrime local;
  local.setEncapVal(encapVal + num);
  return local;
}

jumpPrime& jumpPrime::operator+=(const jumpPrime& rhs)
{
  if (isActive) setEncapVal(encapVal + rhs.encapVal);
  return *this;
}

jumpPrime& jumpPrime::operator+=(int num)
{
  if (isActive) setEncapVal(encapVal + num);
  return *this;
}

jumpPrime jumpPrime::operator++() { return increment(); }

jumpPrime jumpPrime::operator++(int dummy)
{
  jumpPrime oldState = *this;
  increment();
  return oldState;
}

jumpPrime jumpPrime::operator-(const jumpPrime& rhs)
{
  if (!isActive) return *this;
  jumpPrime local;
  local.setEncapVal(encapVal - rhs.encapVal);
  return local;
}

jumpPrime jumpPrime::operator-(int num) const
{
  if (!isActive) return *this;
  jumpPrime local;
  local.setEncapVal(encapVal - num);
  return local;
}

jumpPrime operator-(int num, jumpPrime& obj) { return obj - num; }

jumpPrime& jumpPrime::operator-=(const jumpPrime& rhs)
{
  if (isActive) *this = *this - rhs;
  return *this;
}

jumpPrime& jumpPrime::operator-=(int num)
{
  if (isActive) *this = *this - num;
  return *this;
}

jumpPrime jumpPrime::operator--() { return decrement(); }

jumpPrime jumpPrime::operator--(int dummy)
{
  jumpPrime oldState = *this;
  decrement();
  return oldState;
}

bool jumpPrime::operator>(const jumpPrime& rhs)
{
  if (encapVal <= rhs.encapVal) return false;
  if (upperPrime <= rhs.upperPrime) return false;
  if (lowerPrime <= rhs.lowerPrime) return false;
  if (maxQueries <= rhs.maxQueries) return false;
  if (queryCount <= rhs.queryCount) return false;
  if (jumpCount <= rhs.jumpCount) return false;
  return true;
}

bool jumpPrime::operator<(const jumpPrime& rhs)
{
  if (encapVal >= rhs.encapVal) return false;
  if (upperPrime >= rhs.upperPrime) return false;
  if (lowerPrime >= rhs.lowerPrime) return false;
  if (maxQueries >= rhs.maxQueries) return false;
  if (queryCount >= rhs.queryCount) return false;
  if (jumpCount >= rhs.jumpCount) return false;
  return true;
}

bool jumpPrime::operator==(const jumpPrime& rhs)
{
  if (permanentlyDeactivated != rhs.permanentlyDeactivated) return false;
  if (isActive != rhs.isActive) return false;
  if (encapVal != rhs.encapVal) return false;
  if (upperPrime != rhs.upperPrime) return false;
  if (lowerPrime != rhs.lowerPrime) return false;
  if (maxQueries != rhs.maxQueries) return false;
  if (queryCount != rhs.queryCount) return false;
  if (jumpCount != rhs.jumpCount) return false;
  return true;
}
  
bool jumpPrime::operator!=(const jumpPrime& rhs)
{
  if (permanentlyDeactivated == rhs.permanentlyDeactivated) return false;
  if (isActive == rhs.isActive) return false;
  if (encapVal == rhs.encapVal) return false;
  if (upperPrime == rhs.upperPrime) return false;
  if (lowerPrime == rhs.lowerPrime) return false;
  if (maxQueries == rhs.maxQueries) return false;
  if (queryCount == rhs.queryCount) return false;
  if (jumpCount == rhs.jumpCount) return false;
  return true;
}

bool jumpPrime::operator>=(const jumpPrime& rhs)
{
  if (permanentlyDeactivated == rhs.permanentlyDeactivated) return true;
  if (isActive == rhs.isActive) return true;
  if (encapVal < rhs.encapVal) return false;
  if (upperPrime < rhs.upperPrime) return false;
  if (lowerPrime < rhs.lowerPrime) return false;
  if (maxQueries < rhs.maxQueries) return false;
  if (queryCount < rhs.queryCount) return false;
  if (jumpCount < rhs.jumpCount) return false;
  return true;
}

bool jumpPrime::operator<=(const jumpPrime& rhs)
{
  if (permanentlyDeactivated == rhs.permanentlyDeactivated) return true;
  if (isActive == rhs.isActive) return true;
  if (encapVal > rhs.encapVal) return false;
  if (upperPrime > rhs.upperPrime) return false;
  if (lowerPrime > rhs.lowerPrime) return false;
  if (maxQueries > rhs.maxQueries) return false;
  if (queryCount > rhs.queryCount) return false;
  if (jumpCount > rhs.jumpCount) return false;
  return true;
}

void jumpPrime::checkQueries() { if (queryCount == maxQueries) jump(); }

void jumpPrime::checkJumps() { isActive = !(jumpCount >= JUMP_BOUND); }

// PRECONDITION: Number of up/down querries has been reached.
// POSTCONDITION: The encapsulated value jumps to upperPrime + 1
//                or lowerPrime - 1.
void jumpPrime::jump()
{
  if (upperPrime - encapVal > encapVal - lowerPrime || lowerPrime < LOWEST_VAL)
    encapVal = upperPrime + 1;
  else if (upperPrime - encapVal <= encapVal - lowerPrime)
    encapVal = lowerPrime - 1;

  upperPrime = findNextPrime(encapVal);
  lowerPrime = findPreviousPrime(encapVal);
  maxQueries = upperPrime - lowerPrime;
  queryCount = 0;
  jumpCount++;
  checkJumps();
}

int jumpPrime::up()
{
  queryCount++;
  checkQueries();
  return upperPrime;
}

int jumpPrime::down()
{
  queryCount++;
  checkQueries();
  return lowerPrime;
}

void jumpPrime::setEncapVal(int numProvided = LOWEST_VAL)
{
    if (numProvided < LOWEST_VAL)
    {
      origVal = LOWEST_VAL;  
      encapVal = origVal;
    }
    
    else if (numProvided > HIGHEST_VAL)
    {
      origVal = HIGHEST_VAL;
      encapVal = origVal;
    }
    
    else
    {
      origVal = numProvided;
      encapVal = origVal;
    }

    upperPrime = findNextPrime(encapVal);
    lowerPrime = findPreviousPrime(encapVal);
    maxQueries = upperPrime - lowerPrime;
    queryCount = 0;
    jumpCount = 0;
}

bool jumpPrime::getActiveStatus() { return isActive; }

// PRECONDITION: The jumpPrime is active.
// POSTCONDITION: The jumpPrime is permanently deactivated.
void jumpPrime::revive()
{
  if (isActive)
  {
    permanentlyDeactivated = true;
    isActive = !isActive;
  }

  else isActive = !isActive && !permanentlyDeactivated;
}

// PRECONDITION: The jumpPrime may be inactive.
// POSTCONDITION: The encapsulated value is set to its original value.
void jumpPrime::reset()
{
  if (permanentlyDeactivated) return;
  encapVal = origVal;
  upperPrime = findNextPrime(encapVal);
  lowerPrime = findPreviousPrime(encapVal);
  maxQueries = upperPrime - lowerPrime;
  queryCount = 0;
  jumpCount = 0;
  isActive = true;  
}
