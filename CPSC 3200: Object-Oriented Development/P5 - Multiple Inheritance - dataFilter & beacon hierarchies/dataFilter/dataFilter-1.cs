/* Justin Thoreson
 * dataFilter.cs
 * 9 November 2020
 * 
 * Class Invariants:
 *  1. A dataFilter encapsulates a distinct sequence and a prime number.
 *  2. The original state of a dataFilter is active and in LARGE mode.
 *  3. The encapsulated sequence can be filtered and scrambled, and even
 *     replaced by a newly provided sequence.
 *  4. The elements in the sequence are paired on a complementary basis.
 *     ex: index i is paired with index seq.Length - i - 1
 *  5. A copy of the original sequence is encapsulate, but cannot be altered.
 *     a. This ensures that the encapsulated sequence can be reset to its
 *        origninal array.
 *  6. Each class in the hierarchy is denoted by an integer:
 *     0 - dataFilter
 *     1 - dataMod
 *     2 - dataCut
 *      
 * Interface Invariants:
 *  1. A dataFilter is usable when it is in LARGE or SMALL mode.
 *  2. A dataFilter can undergo one mode change at the client's request.
 *     ex: If the object is in LARGE mode, it switches to SMALL mode.
 *  3. If the client requests a mode change more than once, the dataFilter is
 *     redered inactive and cannot be reactivated.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class dataFilter
    {

        protected bool modeChanged;
        protected bool active;
        protected uint[] origSequence;
        protected uint[] sequence;
        protected uint prime;
        protected bool largeMode;
        protected uint type;

        public dataFilter(uint inPrime, uint[] seq = null)
        {
            modeChanged = false;
            active = true;
            origSequence = (seq != null) ? makeDistinct(seq) : null;
            sequence = copySeq(origSequence);
            prime = (isPrime(inPrime)) ? inPrime : findNextPrime(inPrime);
            largeMode = true;
            type = 0;
        }

        private void swap(ref uint num1, ref uint num2)
        {
            uint temp = num1;
            num1 = num2;
            num2 = temp;
        }

        protected bool isPrime(uint val)
        {
            if (val <= 1) return false;
            for (int i = 2; i < val; i++)
                if (val % i == 0) return false;
            return true;
        }

        protected uint findNextPrime(uint val)
        {
            while (!isPrime(++val)) { }
            return val;
        }

        // PRECONDITION: A non-null sequence is provided.
        // POSTCONDITION: The sequence is sorted and all duplicates are removed.
        protected uint[] makeDistinct(uint[] seq)
        {
            if (seq == null) return seq;
            uint[] origSeq = copySeq(seq);
            Array.Sort(origSeq);

            uint[] temp = new uint[origSeq.Length];
            uint newSeqSize = 0;
            for (int i = 0; i < origSeq.Length - 1; i++)
                if (origSeq[i] != origSeq[i + 1] && origSeq[i] != 0)
                    temp[newSeqSize++] = origSeq[i];
            temp[newSeqSize++] = origSeq[origSeq.Length - 1];

            uint[] seqDistinct = new uint[newSeqSize];
            for (int i = 0; i < newSeqSize; i++)
                seqDistinct[i] = temp[i];
            return seqDistinct;
        }

        protected uint[] copySeq(uint[] seq)
        {
            if (seq == null) return null;
            uint[] seqCopy = new uint[seq.Length];
            for (int i = 0; i < seq.Length; i++)
                seqCopy[i] = seq[i];
            return seqCopy;
        }

        // PRECONDITION: A non-null sequence is contained in a dataFilter obj.
        // POSTCONDITION: All elements either <= or >= the contained prime are
        // removed depending on the mode (LARGE or SMALL).
        public virtual uint[] filter()
        {
            if (!getActiveStatus()) return null;
            uint[] filteredSeq;
            if (sequence == null) filteredSeq = new uint[] { prime };
            else if (largeMode)
            {
                uint newSeqSize = 0;
                for (int i = 0; i < sequence.Length; i++)
                    if (sequence[i] > prime)
                        newSeqSize++;

                if (newSeqSize == 0)
                {
                    sequence = new uint[] { prime };
                    return copySeq(sequence);
                }

                filteredSeq = new uint[newSeqSize];
                for (int i = 0, j = 0; i < sequence.Length; i++)
                    if (sequence[i] > prime)
                        filteredSeq[j++] = sequence[i];
            }

            else
            {
                uint newSeqSize = 0;
                for (int i = 0; i < sequence.Length; i++)
                    if (sequence[i] < prime)
                        newSeqSize++;

                if (newSeqSize == 0)
                {
                    sequence = new uint[] { prime };
                    return copySeq(sequence);
                }

                filteredSeq = new uint[newSeqSize];
                for (int i = 0, j = 0; i < sequence.Length; i++)
                    if (sequence[i] < prime)
                        filteredSeq[j++] = sequence[i];
            }

            sequence = copySeq(filteredSeq);
            return filteredSeq;
        }

        // PRECONDITION: A non-null sequence is contained in a dataFilter obj.
        // POSTCONDITION: Paired elements (elements with complementary indexes)
        // are swapped in the sequence.
        public virtual uint[] scramble(uint[] seq = null)
        {
            if (!getActiveStatus()) return null;
            if (seq != null) sequence = copySeq(seq);
            if (sequence != null)
            {
                if (largeMode)
                {
                    for (int i = 0; i < sequence.Length / 2; i++)
                        if (sequence[i] < sequence[sequence.Length - i - 1])
                            swap(ref sequence[i],
                                ref sequence[sequence.Length - i - 1]);
                }

                else
                {
                    for (int i = 0; i < sequence.Length / 2; i++)
                        if (sequence[i] > sequence[sequence.Length - i - 1])
                            swap(ref sequence[i], ref sequence[sequence.Length - i - 1]);
                }
            }

            return copySeq(sequence);
        }

        // PRECONDITION: Object has already undergone a mode switch
        // POSTCONDITION: A second requested switch result in deactivation.
        public void switchMode()
        {
            if (modeChanged) active = false;
            else
            {
                largeMode = !largeMode;
                modeChanged = !modeChanged;
            }
        }

        public void resetToOrigSeq() { sequence = copySeq(origSequence); }

        public uint whoAmI() { return type; }

        public bool getActiveStatus() { return active; }
    }
}

/* Implementation Invariants:
 *  1. A prime value and a sequence are provided by the client and are
 *     encapsulated at object construction. 
 *     a. If no sequence is provided by the client, it is set to null.
 *        Otherwise, the sequence is sorted, made distinct and encapsulated.
 *     b. A prime number must be provided by the client. If the number provided
 *        is not prime, the smallest prime number greater than the number
 *        provided is encapsulated instead.
 *  2. Filtering a sequence removes all values less than or equal to the 
 *     encapsulated prime in LARGE mode, and removes all values greater than or
 *     equal to the encapsulated prime in SMALL mode.
 *  3. Scrambling a sequence compares an index with its complementary index
 *     (index i is compared to index seq.Length - 1 - i).
 *     a. In LARGE mode, if the index is less than its complement, swap the two.
 *     b. In SMALL mode, if index is greater than its complement, swap the two.
 *     c. The client may pass in a new sequence as a parameter to scramble().
 *        The new sequence will be scrambled and will replace the old sequence.
 *  4. The client can request to reset the sequence back to the orignially
 *     encapsulated sequence at any time.
 *  5. The client can request to switch the mode of an object, but only once.
 *     Any futher attempt to change the mode will deactivate the object.
 *  6. Inactive dataFilters return null sequences whenever a filter() or
 *     scramble() is queried.
 */