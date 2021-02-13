/* Justin Thoreson
 * jumpPrime.h
 * September 27, 2020
 *
 * Class Invariants:
 *  1. The number encapsulated by jumpPrime must be four digits long, which sets
 *     the lowest value at 1000 and the highest value at 9999.
 *  2. The number of times the encapsulated value can jump is specified by a
 *     jump bound. This bound is the same for all jumpPrimes.
 *  3. When a number becomes encapsulated in a jumpPrime, the initial sate of 
 *     the object is set to active. The number of querries and the number of
 *     jumps are set to zero.
 *  4. The closest primes greater than and less than the encapsulated value
 *     are calculated and accessed through the up() and down() methods
 *     respectfully.
 *
 * Interface Invariants:
 *  1. A jumpPrime object is not usable when inactive. The object becomes
 *     inactive when the number of jumps exceeds the specified bound.
 *  2. A jumpPrime object can be reactivated if and only if it is inactive but
 *     not permanently inactive.
 */

class jumpPrime
{
  private:
    static const int LOWEST_VAL = 1000;
    static const int HIGHEST_VAL = 9999;
    static const int JUMP_BOUND = 2;

    int encapVal;
    int upperPrime;
    int lowerPrime;
    int maxQueries;
    int queryCount;
    int jumpCount;
    bool isActive;
    bool permanentlyDeactivated;

    bool isPrime(int n);
    int findNextPrime(int n);
    int findPreviousPrime(int n);
  
  public:
    jumpPrime();
    void jump();
    void checkQueries();
    void checkJumps();
    int up();
    int down();
    void setEncapVal(int numProvided);
    bool getActiveStatus();
    void revive();
    void reset(int numProvided);
};
   
