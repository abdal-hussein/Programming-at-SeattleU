/* Justin Thoreson
 * beacon.cs
 * 9 November 2020
 * 
 * Class Invariants:
 *  1. A beacon contains a distinct positive integer sequence that varies the
 *     charge of the beacon.
 *  2. The charge of the beacon is provided by an element in the encapsulated
 *     sequence. The initial charge is the last element in the sequence. The
 *     charge is zero if the sequence is null.
 *  3. The charge can be emitted as a signal, but when a signal is emitted, the
 *     charge is reduced to the next element to the left in the sequence. If
 *     there are no more elements to reduce to, the charge is set to zero.
 *  4. Each class in the hierarchy is denoted by an integer:
 *     0 - beacon
 *     1 - strobeBeacon
 *     2 - quirkyBeacon
 *
 * Interface Invariants:
 *  1. A beacon is active when it is turned on and it is charged.
 *  2. A valid charge is a positive number. Zero yields not charged.
 *  3. A beacon's initial state is off, and thus must initially be turned on.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class beacon
    {
        protected uint[] origSequence;
        protected uint[] sequence;
        protected uint charge;
        protected uint timesChargeReduced;
        protected bool charged;
        protected bool on;
        protected uint type;

        public beacon(uint[] seq = null)
        {
            origSequence = makeDistinct(seq);
            sequence = copySeq(origSequence);
            charge = (sequence != null) ? sequence[sequence.Length - 1] : 0;
            timesChargeReduced = 0;
            charged = charge > 0;
            on = false;
            type = 0;
        }

        protected uint[] copySeq(uint[] seq)
        {
            if (seq == null) return null;
            uint[] seqCopy = new uint[seq.Length];
            for (int i = 0; i < seq.Length; i++)
                seqCopy[i] = seq[i];
            return seqCopy;
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

        // PRECONDITION: beacon is charged, charge is positive.
        // POSTCONDITION: Charge is reduced, old charge is returned.
        protected uint reduceCharge()
        {
            if (!on || !charged) return 0;
            uint oldCharge = charge;
            if (++timesChargeReduced == sequence.Length)
            {
                charge = 0;
                charged = !charged;
            }

            else charge = sequence[sequence.Length - timesChargeReduced - 1];
            return oldCharge;
        }
 
        public void newSeq(uint[] seq) 
        { 
            sequence = copySeq(seq);
            charge = (sequence != null) ? sequence[sequence.Length - 1] : 0;
            timesChargeReduced = 0;
            charged = charge > 0;
        }

        public void resetToOrigSeq() 
        { 
            sequence = copySeq(origSequence);
            charge = (sequence != null) ? sequence[sequence.Length - 1] : 0;
            timesChargeReduced = 0;
            charged = charge > 0;
        }

        public virtual void switchOnOff() { on = !on; }

        // PRECONDITION: beacon is charged.
        // POSTCONDITION: Positive signal is emitted.
        public virtual int emitSignal() 
        { 
            if (on && charged) return (int)reduceCharge();
            return 0;
        }

        public bool getOnStatus() { return on; }

        public uint whoAmI() { return type; }
    }
}

/* Implementation Invariants
 *  1. The client can switch a beacon on or off with no limitations to the
 *     number of times the active state can be switched.
 *  2. Emitting a signal will return the charge value, then reduce the charge
 *     to the next element to the left in the sequence.
 *  3. If a beacon is not on or not charged, the signal emitted is zero.
 *  4. The client can provide a new sequence to the beacon, but it will not be
 *     made distinct. The sequence is made distinct only on initialization.
 */