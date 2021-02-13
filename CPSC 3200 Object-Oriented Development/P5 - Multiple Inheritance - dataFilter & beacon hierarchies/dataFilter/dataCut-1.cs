/* Justin Thoreson
 * dataCut.cs
 * 9 November 2020
 * 
 * Class Invariants:
 *  1. A dataCut is-a dataFilter. 
 *  2. Like the base class dataFilter, dataCut encapsulates a prime number,
 *     a sequence, and a copy of the initially provided sequence.
 *  3. A dataCut contains an array lastScrambled that stores all values that
 *     appeared in a previous scramble query.
 *  4. The sequence can be filtered or scrambled. Overrides base functions.
 *  5. Each class in the hierarchy is denoted by an integer:
 *     0 - dataFilter
 *     1 - dataMod
 *     2 - dataCut
 *     
 * Interface Invariants:
 *  1. The active state of a dataCut has the same requirements as the base.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class dataCut : dataFilter
    {
        private uint[] lastScrambled;

        public dataCut(uint inPrime, uint[] seq = null) : base(inPrime, seq) 
            { type = 2; }

        // PRECONDITION: A new sequence is provided.
        // POSTCONDITION: All values in the last scramble request are removed
        // from the newly provided sequence.
        private uint[] removePrevScramble(uint[] origSeq, uint[] lastScrambled)
        {
            uint removeCount = 0;
            for (int i = 0; i < origSeq.Length; i++)
            {
                for (int j = 0; j < lastScrambled.Length; j++)
                {
                    if (origSeq[i] == lastScrambled[j])
                    {
                        origSeq[i] = 0;
                        removeCount++;
                    }
                }
            }

            uint[] newSeq = new uint[origSeq.Length - removeCount];
            for (int i = 0, j = 0; i < origSeq.Length; i++)
                if (origSeq[i] != 0)
                    newSeq[j++] = origSeq[i];
            return newSeq;
        }

        // PRECONDITION: A non-null sequence is contained in the dataCut obj.
        // POSTCONDITION: The sequence is filtered via base dataFilter and
        // either the maximum or minimum value is removed based on the mode
        // (LARGE or SMALL).
        public override uint[] filter()
        {
            if (!getActiveStatus()) return null;
            uint[] filteredSeq = base.filter();
            if (filteredSeq.Length == 1 && filteredSeq[0] == prime)
                return filteredSeq;

            uint[] filteredSeqValRemoved = new uint[filteredSeq.Length - 1];
            if (largeMode)
            {
                uint largest = uint.MinValue;
                for (int i = 0; i < filteredSeq.Length; i++)
                    if (filteredSeq[i] > largest)
                        largest = filteredSeq[i];
                for (int i = 0, j = 0; i < filteredSeq.Length; i++)
                    if (filteredSeq[i] != largest)
                        filteredSeqValRemoved[j++] = filteredSeq[i];
            }

            else
            {
                uint smallest = uint.MaxValue;
                for (int i = 0; i < filteredSeq.Length; i++)
                    if (filteredSeq[i] < smallest)
                        smallest = filteredSeq[i];
                for (int i = 0, j = 0; i < filteredSeq.Length; i++)
                    if (filteredSeq[i] != smallest)
                        filteredSeqValRemoved[j++] = filteredSeq[i];
            }

            return filteredSeqValRemoved;
        }

        // PRECONDITION: A non-null sequence is contained in the dataCut obj.
        // POSTCONDITION: The values within a previous scramble request are
        // removed from a newly provided sequence. The new sequence is
        // scrambled before it replaces the old sequence.
        public override uint[] scramble(uint[] seq = null)
        {
            if (!getActiveStatus()) return null;
            uint[] scrambled = copySeq(seq);
            if (scrambled != null && lastScrambled != null)
                scrambled = removePrevScramble(scrambled, lastScrambled);
            lastScrambled = base.scramble(scrambled);
            return copySeq(lastScrambled);
        }
    }
}

/* Implementation Invariants
 *  1. A prime value and a sequence are provided by the client and are
 *     encapsulated at object construction. 
 *     a. If no sequence is provided by the client, it is set to null.
 *        Otherwise, the sequence is sorted, made distinct and encapsulated.
 *     b. A prime number must be provided by the client. If the number provided
 *        is not prime, the smallest prime number greater than the number
 *        provided is encapsulated instead.
 *  2. Filtering a sequence overrides the base filter. Filtering will remove
 *     the maximum value in the sequence in LARGE mode and remove the minimum
 *     value in SMALL mode after base filtering. 
 *  3. Scrambling a sequence overrides the base scramble. Scrambling will
 *     remove all values in a previous scramble request from a newly provided
 *     sequence before base scrambling.
 *  4. The client can request to reset the sequence back to the orignially
 *     encapsulated sequence at any time.
 *  5. The client can request to switch the mode of an object, but only once.
 *     Any futher attempt to change the mode will deactivate the object.
 *  6. Inactive dataCuts return null sequences whenever a filter() or
 *     scramble() is queried.
 */