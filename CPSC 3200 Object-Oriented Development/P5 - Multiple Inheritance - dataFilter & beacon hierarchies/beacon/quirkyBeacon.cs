/* Justin Thoreson
 * quirkyBeacon.cs
 * 9 November 2020
 * 
 * Class Invariants:
 *  1. A quirkyBeacon contains a distinct positive integer sequence that varies
 *     the charge of the quirkyBeacon.
 *  2. The charge of the quirkyBeacon is provided by an element in the 
 *     encapsulated sequence. The initial charge is the last element in the
 *     sequence. The charge is zero if the sequence is null.
 *  3. A SIGNAL_FACTOR determines the signal emitted. If the charge is evenly
 *     divisible by the SIGNAL_FACTOR, the signal emitted is the charge divided
 *     by the SIGNAL_FACTOR. Otherwise, the signal is the charge multiplied by
 *     the SIGNAL_FACTOR.
 *  4. Each class in the hierarchy is denoted by an integer:
 *     0 - beacon
 *     1 - strobeBeacon
 *     2 - quirkyBeacon
 *      
 * Interface Invariants:
 *  1. A quirkyBeacon is active when it is turned on and it is charged.
 *  2. A quirkyBeacon can be switched on or off a limited number of times.
 *  3. A valid charge is a positive number. Zero yields not charged.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class quirkyBeacon : beacon
    {
        private const int SIGNAL_FACTOR = 3;
        private const int ON_OFF_LIMIT = 4;
        private int timesSwitchedOnOff;
        private bool offIndefinitely;

        public quirkyBeacon(uint[] seq) : base(seq) 
        {
            type = 2;
            timesSwitchedOnOff = 0;
            bool offIndefinitely = false;
        }

        public override void switchOnOff()
        {
            if (!offIndefinitely)
            {
                base.switchOnOff();
                timesSwitchedOnOff++;
            }

            offIndefinitely = timesSwitchedOnOff == ON_OFF_LIMIT;
        }

        // PRECONDITION: quirkyBeacon is on and charged, charge is odd number.
        // POSTCONDITION: A multiple of the charge is emitted as the signal.
        public override int emitSignal()
        {
            if (on && charged)
            {
                int signal = base.emitSignal();
                signal = (signal % SIGNAL_FACTOR == 0) ? signal / SIGNAL_FACTOR 
                    : signal * SIGNAL_FACTOR;
                return signal;
            }

            return 0;
        }
    }
}

/* Implementation Invariants
 *  1. The client can switch a quirkyBeacon on or off a set number of times.
 *  2. When emitting a signal, if the charge is evenly divisible by the
 *     SIGNAL_FACTOR, the signal emitted is the charge / SIGNAL_FACTOR. If the
 *     charge is not evenly divisible by the SIGNAL_FACTOR, the signal emitted
 *     is the charge * SIGNAL_FACTOR.
 *  3. If a quirkyBeacon is not on or not charged, the signal emitted is zero.
 *  4. The client can provide a new sequence to the quirkyBeacon.
 */