/* Justin Thoreson
 * dataMod.cs
 * 11 October 2020
 * 
 * Class Invariants:
 *   1. A dataMod is-a dataFilter.
 *   2. Like the base class dataFilter, dataMod encapsulates a prime number,
 *      a sequence, and a copy of the initially provided sequence.
 *   3. A dataMode contains a constant REPLACE_PRIMES_WITH which stores a set
 *      value to replace all prime numbers in a sequence with.
 *   4. The sequence can be filtered or scrambled. Overrides base funstions.
 *   
 * Interface Invariants:
 *   1. The active state of a dataMod has the same requirements as the base.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P3
{
    public class dataMod : dataFilter
    {
        private const int REPLACE_PRIMES_WITH = 2;

        public dataMod(int inPrime, int[] seq = null) : base(inPrime, seq) { }

        // PRECONDITION: A non-null sequence is contained in the dataMod obj.
        // POSTCONDITION: Data members are filtered via base dataFilter then
        // either incremented or decremented depending on the mode.
        public override int[] filter()
        {
            if (!getActiveStatus()) return null;

            int[] filteredSeq = base.filter();
            if (!(filteredSeq.Length == 1 && filteredSeq[0] == prime))
                for (int i = 0; i < filteredSeq.Length; i++)
                    filteredSeq[i] = (mode == Mode.LARGE) ? filteredSeq[i] + 1 
                        : filteredSeq[i] - 1;
            return filteredSeq;
        }

        // PRECONDITION: A non-null sequence is contained in the dataMod obj.
        // POSTCONDITION: All primes in the sequence are replaced by a set
        // value REPLACE_PRIMES_WITH before executing the base dataFilter 
        // scramble.
        public override int[] scramble(int[] seq = null)
        {
            if (!getActiveStatus()) return null;

            int[] replacedSeq;

            if (sequence == null && seq != null)
            {
                int[] origSeq = makeDistinct(seq);
                for (int i = 0; i < origSeq.Length; i++)
                    if (isPrime(origSeq[i])) origSeq[i] = REPLACE_PRIMES_WITH;
                replacedSeq = copySeq(origSeq);
            }

            else
            {
                for (int i = 0; i < sequence.Length; i++)
                    if (isPrime(sequence[i])) sequence[i] = REPLACE_PRIMES_WITH;
                replacedSeq = copySeq(sequence);
            }

            return base.scramble(replacedSeq);
        }
    }
}

/* Implementation Invariants
 *   1. A prime value and a sequence are provided by the client and are
 *      encapsulated at object construction. 
 *     a. If no sequence is provided by the client, it is set to null.
 *        Otherwise, the sequence is sorted, made distinct and encapsulated.
 *     b. A prime number must be provided by the client. If the number provided
 *        is not prime, the smallest prime number greater than the number
 *        provided is encapsulated instead.
 *   2. Filtering a sequence overrides the base filter. Filtering will increment
 *      the elements of the sequence in LARGE mode and decrement the elements in
 *      small mode after base filtering. 
 *   3. Scrambling a sequence overrides the base scramble. Scrambling will
 *      replace all prime numbers in the sequence with a set value 
 *      REPLACE_PRIMES_WITH before base scrambling.
 *   4. The client can request to reset the sequence back to the orignially
 *      encapsulated sequence at any time.
 *   5. The client can request to switch the mode of an object, but only once.
 *      Any futher attempt to change the mode will deactivate the object.
 *   6. Inactive dataMods return null sequences whenever a filter() or
 *      scramble() is queried.
 */