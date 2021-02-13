/* Justin Thoreson
 * jumpPrime.cs
 * 17 September 2020
 * 
 * Interface Invariants:
 * 
 * 1. The number encapsulated by jumpPrime must be at least four digits long,
 *    which sets the lowest value at 1000.
 * 2. The number of times the encapsulated value can jump is specified by a
 *    jump bound. This bound is the same for all jumpPrimes.
 * 3. When a number becomes encapsulated in a jumpPrime, the initial sate of 
 *    the object is set to active. The number of querries and the number of
 *    jumps are set to zero.
 * 4. The closest primes greater than and less than the encapsulated value
 *    are calculated and accessed through the up() and down() methods
 *    respectfully. 
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P1
{
    public class jumpPrime
    {
        private const int LOWEST_VAL = 1000;
        private const int JUMP_BOUND = 2;

        private int encapVal;
        private int upperPrime;
        private int lowerPrime;
        private int maxQuerries;
        private int queryCount;
        private int jumpCount;
        private bool isActive;
        private bool permanentlyDeactivated;

        private bool isPrime(int n)
        {
            if (n <= 1)
                return false;

            for (int i = 2; i < n; i++)
                if (n % i == 0)
                    return false;

            return true;
        }

        private int findNextPrime(int n)
        {
            while (!isPrime(++n)) { }
            return n;
        }

        private int findPreviousPrime(int n)
        {
            while (!isPrime(--n)) { }
            return n;
        }

        private void initialize(int numProvided)
        {
            encapVal = (numProvided < LOWEST_VAL) ? LOWEST_VAL : numProvided;
            upperPrime = findNextPrime(encapVal);
            lowerPrime = findPreviousPrime(encapVal);
            maxQuerries = upperPrime - lowerPrime;
            queryCount = 0;
            jumpCount = 0;
            isActive = encapVal >= LOWEST_VAL;
            permanentlyDeactivated = false;
        }

        public jumpPrime(int numProvided) { initialize(numProvided); }

        public void checkQuerries() { if (queryCount == maxQuerries) jump(); }

        public void checkJumpCount() { isActive = !(jumpCount >= JUMP_BOUND); }

        // PRECONDITION: Number of up/down querries has been reached.
        // POSTCONDITION: The encapsulated value jumps to upperPrime + 1
        //                or lowerPrime - 1.
        public void jump()
        {
            if (upperPrime - encapVal > encapVal - lowerPrime || lowerPrime < LOWEST_VAL)
                encapVal = upperPrime + 1;
            else if (upperPrime - encapVal <= encapVal - lowerPrime)
                encapVal = lowerPrime - 1;

            upperPrime = findNextPrime(encapVal);
            lowerPrime = findPreviousPrime(encapVal);
            maxQuerries = upperPrime - lowerPrime;
            queryCount = 0;
            jumpCount++;
            checkJumpCount();
        }

        public int up()
        {
            queryCount++;
            checkQuerries();
            return upperPrime;
        }

        public int down()
        {
            queryCount++;
            checkQuerries();
            return lowerPrime;
        }

        public bool getActiveStatus() { return isActive; }

        // PRECONDITION: The jumpPrime is active.
        // POSTCONDITION: The jumpPrime is permanently deactivated.
        public void revive() 
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
        public void reset(int numProvided) 
            { if (!permanentlyDeactivated) initialize(numProvided); }
    }
}

/* Implementation Invariants
 * 
 * 1. Any numerical value provided to a jumpPrime object will be encapsulated,
 *    but if the value is less than four digits, the encapsulated number is
 *    set to 1000, the lower limit.
 * 2. The number encapsulated by a jumpPrime will jump to a value that is 1
 *    greater than the closest prime greater than the number, or to a value
 *    1 less than the closest prime less than the number, if the number of
 *    up/down querries reaches the querry limit. This limit is determined 
 *    uniquely as the distance between the two aforementioned primes.
 * 3. The active state of a jumpPrime object will be evaluated to false if the
 *    number of jumps exceeds the specified bound.
 * 4. The active status will change back to true if the jumpPrime is revived or
 *    reset. 
 * 5. Reviving an active jumpPrime will permanently deactivate it. The object
 *    can not be revived or reset after permanent deactivation.
 * 
 */
