/* Justin Thoreson
 * jumpPrime.cpp
 * September 27, 2020
 *
 * Implementation Invariants: 
 *  1. Any numerical value provided to a jumpPrime object will be encapsulated,
 *     but if the value has less than four digits, the encapsulated number is
 *     set to 1000, the lower limit, or if the value has greater than four
 *     digits, the value is set to 9999, the upper limit. If not value is
 *     provided, the value will be set to the default value, which is the lower
 *     limit.
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
 */

#include "jumpPrime.h"

jumpPrime::jumpPrime()
{
  encapVal = LOWEST_VAL;
  upperPrime = findNextPrime(encapVal);
  lowerPrime = findPreviousPrime(encapVal);
  maxQueries = upperPrime - lowerPrime;
  queryCount = 0;
  jumpCount = 0;
  isActive = true;
  permanentlyDeactivated = false;
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
    encapVal = LOWEST_VAL;
  else if (numProvided > HIGHEST_VAL)
    encapVal = HIGHEST_VAL;
  else
  {
    encapVal = numProvided;
    upperPrime = findNextPrime(encapVal);
    lowerPrime = findPreviousPrime(encapVal);
    maxQueries = upperPrime - lowerPrime;
  }
}

bool jumpPrime::getActiveStatus() { return isActive; }

// PRECONDITION: The jumpPrime is active.
// POSTCONDITION: The jumpPrime is permanently deactivated.
void jumpPrime::revive()
{
  if (isActive)
  {
    permanentlyDeactivated = true;
    isActive = false;
  }

  else isActive = !isActive && !permanentlyDeactivated;
}

// PRECONDITION: The jumpPrime may be inactive.
// POSTCONDITION: The encapsulated value is set to its original value.
void jumpPrime::reset(int numProvided)
{
  if (permanentlyDeactivated) return;

  encapVal = numProvided;
  upperPrime = findNextPrime(encapVal);
  lowerPrime = findPreviousPrime(encapVal);
  maxQueries = upperPrime - lowerPrime;
  queryCount = 0;
  jumpCount = 0;
  isActive = true;  
}
