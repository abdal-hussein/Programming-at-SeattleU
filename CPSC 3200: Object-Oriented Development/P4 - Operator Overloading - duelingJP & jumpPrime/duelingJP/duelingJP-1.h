/* Justin Thoreson
 * duelingJP.h
 * 28 October 2020
 *
 * Class Invariants:
 *  1. Each duelingJP must contain a number of jumpPrime objects, each of which
 *     is distict, having their own uniquely provided encapsulated value.
 *  2. The number of jumpPrimes can vary between duelingJP objects, as the
 *     cardinality is not constant. 
 *  3. If two jumpPrimes have same prime values for each up() or for each down(),
 *     it is a collision, and if two jumpPrimes have the same prime value for an
 *     up() and a down() or vice-versa, it is an inversion. The number of
 *     collisions and the number of inversions are tracked for each duelingJP.
 * 
 * Interface Invariants:
 *  1. The jumpPrimes within a duelingJP must be active to ensure collisions and
 *     inversions are counted.
 *  2. Operator overloading is supported.
 *     - Addition, subtraction, relation.
 */

#include <iostream>
#include "jumpPrime.h"

using namespace std;

class duelingJP
{
  private:
   jumpPrime* jpObjs = nullptr;
   unsigned numJPs;
   unsigned collisions;
   unsigned inversions;

   void copy(const duelingJP& orig);
   void destroy();
   duelingJP increment();
   duelingJP decrement();
  
  public:
   duelingJP();
   duelingJP(unsigned values[], int numValues);
   duelingJP(const duelingJP& orig);
   duelingJP(duelingJP&& orig);
   duelingJP& operator=(const duelingJP& orig);
   duelingJP& operator=(duelingJP&& orig);
   ~duelingJP();
   duelingJP operator+(const duelingJP& rhs);
   duelingJP operator+(int num) const;
   duelingJP& operator+=(const duelingJP& rhs);
   duelingJP& operator+=(int num);
   duelingJP operator++();
   duelingJP operator++(int dummy);
   duelingJP operator-(const duelingJP& rhs);
   duelingJP operator-(int num) const;
   duelingJP& operator-=(const duelingJP& rhs);
   duelingJP& operator-=(int num);
   duelingJP operator--();
   duelingJP operator--(int dummy);
   bool operator>(const duelingJP& rhs);
   bool operator<(const duelingJP& rhs);
   bool operator==(const duelingJP& rhs);
   bool operator!=(const duelingJP& rhs);
   bool operator>=(const duelingJP& rhs);
   bool operator<=(const duelingJP& rhs);

   friend ostream& operator<<(ostream& os, const duelingJP& obj)
   {
     os << "Collisions: " << obj.collisions << " Inversions: " << obj.inversions;
     return os;
   }

   void swapAdrs(jumpPrime* adr1, jumpPrime* adr2);
   void swapVals(unsigned& num1, unsigned& num2);
   void countCollisions();
   void countInversions();
   unsigned getCollisions();
   unsigned getInversions();
};
