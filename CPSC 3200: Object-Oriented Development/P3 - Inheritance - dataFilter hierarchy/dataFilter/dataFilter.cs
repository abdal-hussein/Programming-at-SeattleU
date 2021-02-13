/* Justin Thoreson
 * dataFilter.cs
 * 11 October 2020
 * 
 * Class Invariants:
 *   1. A dataFilter encapsulates a distinct sequence and a prime number.
 *   2. The original state of a dataFilter is active and in LARGE mode.
 *   3. The encapsulated sequence can be filtered and scrambled, and even
 *      replaced by a newly provided sequence.
 *   4. The elements in the sequence are paired on a complementary basis.
 *     ex: index i is paired with index seq.Length - i - 1
 *   5. A copy of the original sequence is encapsulate, but cannot be altered.
 *     a. This ensures that the encapsulated sequence can be reset to its
 *        origninal array.
 *  
 * Interface Invariants:
 *   1. A dataFilter is usable when it is in LARGE or SMALL mode.
 *   2. A dataFilter can undergo one mode change at the client's request.
 *     ex: If the object is in LARGE mode, it switches to SMALL mode.
 *   3. If the client requests a mode change more than once, the dataFilter is
 *      redered inactive and cannot be reactivated.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P3
{
    public class dataFilter
    {

        private bool modeChanged;
        protected bool isActive;
        protected int[] origSequence;
        protected int[] sequence;
        protected int prime;

        protected enum Mode { LARGE, SMALL };
        protected Mode mode;

        public dataFilter(int inPrime, int[] seq = null)
        {
            modeChanged = false;
            isActive = true;
            origSequence = (seq != null) ? makeDistinct(seq) : null;
            sequence = copySeq(origSequence);
            prime = (isPrime(inPrime)) ? inPrime : findNextPrime(inPrime);
            mode = Mode.LARGE;
        }

        // PRECONDITION: A non-null sequence is contained in a dataFilter obj.
        // POSTCONDITION: All elements either <= or >= the contained prime are
        // removed depending on the mode (LARGE or SMALL).
        public virtual int[] filter()
        {
            if (!getActiveStatus()) return null;
            int[] filteredSeq;
            if (sequence == null) filteredSeq = new int[] { prime };
            else if (mode == Mode.LARGE)
            {
                int newSeqSize = 0;
                for (int i = 0; i < sequence.Length; i++)
                    if (sequence[i] > prime)
                        newSeqSize++;

                if (newSeqSize == 0)
                {
                    sequence = new int[] { prime };
                    return copySeq(sequence);
                }

                filteredSeq = new int[newSeqSize];
                for (int i = 0, j = 0; i < sequence.Length; i++)
                    if (sequence[i] > prime)
                        filteredSeq[j++] = sequence[i];
            }

            else
            {
                int newSeqSize = 0;
                for (int i = 0; i < sequence.Length; i++)
                    if (sequence[i] < prime)
                        newSeqSize++;

                if (newSeqSize == 0)
                {
                    sequence = new int[] { prime };
                    return copySeq(sequence);
                }

                filteredSeq = new int[newSeqSize];
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
        public virtual int[] scramble(int[] seq = null)
        {
            if (!getActiveStatus()) return null;

            if (seq != null) sequence = copySeq(seq);

            if (sequence != null)
            {
                if (mode == Mode.LARGE)
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
            if (modeChanged) isActive = false;
            else
            {
                mode = (mode == Mode.LARGE) ? Mode.SMALL : Mode.LARGE;
                modeChanged = true;
            }
        }

        public void resetToOrigSeq() { sequence = copySeq(origSequence); }

        public bool getActiveStatus() { return isActive; }

        private void swap(ref int num1, ref int num2)
        {
            int temp = num1;
            num1 = num2;
            num2 = temp;
        }

        protected bool isPrime(int val)
        {
            if (val <= 1) return false;
            for (int i = 2; i < val; i++)
                if (val % i == 0) return false;
            return true;
        }

        protected int findNextPrime(int val)
        {
            while (!isPrime(++val)) { }
            return val;
        }

        // PRECONDITION: A non-null sequence is provided.
        // POSTCONDITION: The sequence is sorted and all duplicates are removed.
        protected int[] makeDistinct(int[] seq)
        {
            int[] origSeq = copySeq(seq);
            Array.Sort(origSeq);

            int[] temp = new int[origSeq.Length];
            int newSeqSize = 0;
            for (int i = 0; i < origSeq.Length - 1; i++)
                if (origSeq[i] != origSeq[i + 1])
                    temp[newSeqSize++] = origSeq[i];
            temp[newSeqSize++] = origSeq[origSeq.Length - 1];

            int[] seqDistinct = new int[newSeqSize];
            for (int i = 0; i < newSeqSize; i++)
                seqDistinct[i] = temp[i];

           // for (int i = 0; i < newSeqSize; i++)
              //  Console.WriteLine(i + " : " + seqDistinct[i] + " : " + seq[i]);

            return seqDistinct;
        }

        protected int[] copySeq(int[] seq)
        {
            if (seq == null) return null;
            int[] seqCopy = new int[seq.Length];
            for (int i = 0; i < seq.Length; i++)
                seqCopy[i] = seq[i];
            return seqCopy;
        }
    }
}

/* Implementation Invariants:
 *   1. A prime value and a sequence are provided by the client and are
 *      encapsulated at object construction. 
 *     a. If no sequence is provided by the client, it is set to null.
 *        Otherwise, the sequence is sorted, made distinct and encapsulated.
 *     b. A prime number must be provided by the client. If the number provided
 *        is not prime, the smallest prime number greater than the number
 *        provided is encapsulated instead.
 *   2. Filtering a sequence removes all values less than or equal to the 
 *      encapsulated prime in LARGE mode, and removes all values greater than or
 *      equal to the encapsulated prime in SMALL mode.
 *   3. Scrambling a sequence compares an index with its complementary index
 *      (index i is compared to index seq.Length - 1 - i).
 *     a. In LARGE mode, if the index is less than its complement, swap the two.
 *     b. In SMALL mode, if index is greater than its complement, swap the two.
 *     c. The client may pass in a new sequence as a parameter to scramble().
 *        The new sequence will be scrambled and will replace the old sequence.
 *   4. The client can request to reset the sequence back to the orignially
 *      encapsulated sequence at any time.
 *   5. The client can request to switch the mode of an object, but only once.
 *      Any futher attempt to change the mode will deactivate the object.
 *   6. Inactive dataFilters return null sequences whenever a filter() or
 *      scramble() is queried.
 */