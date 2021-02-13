/* Justin Thoreson
 * strobeBeacon.cs
 * 9 November 2020
 * 
  * Class Invariants:
 *  1. A strobeBeacon contains a distinct positive integer sequence that varies
 *     the charge of the strobeBeacon.
 *  2. The charge of the strobeBeacon is provided by an element in the 
 *     encapsulated sequence. The initial charge is the last element in the
 *     sequence. The charge is zero if the sequence is null.
 *  3. The signal emitted by a strobeBeacon depends on the positveMode of the
 *     strobeBeacon. When in positive mode, the charge is emitted as a signal,
 *     but when not in positve mode (negative mode) the signal emitted is the
 *     negative multiple of the charge. 
 *  4. The charge is reduced to the next element to the
 *     left in the sequence when a signal is emitted. If there are no more 
 *     elements to reduce to, the charge is set to zero.
 *  5. Each class in the hierarchy is denoted by an integer:
 *     0 - beacon
 *     1 - strobeBeacon
 *     2 - quirkyBeacon
 *
 * Interface Invariants:
 *  1. A strobeBeacon is active when it is turned on and it is charged.
 *  2. A valid charge is a positive number. Zero yields not charged.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class strobeBeacon : beacon
    {
        private bool positiveMode;

        public strobeBeacon(uint[] seq) : base(seq)
        {
            type = 1;
            positiveMode = true;
        }

        // PRECONDITION: strobeBeacon is charged and not in positive mode.
        // POSTCONDITION: Negative signal is emitted.
        public override int emitSignal()
        {
            if (on && charged)
            {
                int signal = positiveMode ? base.emitSignal() 
                    : -base.emitSignal();
                positiveMode = !positiveMode;
                return signal;
            }
                
            return 0;
        }
    }
}

/* Implementation Invariants
 *  1. The client can switch a strobeBeacon on or off with no limitations to the
 *     number of times the active state can be switched.
 *  2. Emitting a signal will return the charge value in positive mode and
 *     the negative multiple of the charge value in negative mode. Then the 
 *     charge is reduced to the next element to the left in the sequence.
 *  3. Each time a signal is emitted from a strobeBeacon, the mode is switched.
 *  4. If a strobeBeacon is not on or not charged, the signal emitted is zero.
 *  5. The client can provide a new sequence to the strobeBeacon.
 */