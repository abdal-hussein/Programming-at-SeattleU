/* Justin Thoreson
 * dataBeacon.cs
 * 9 November 2020
 * 
 * Class Invariants:
 *  1. A dataFilterBeacon simulates multiple inheritance via double composition
 *     by encapsulating a reference to a type from each dataFilter and beacon
 *     class hierarchy.
 *  2. A dataFilterBeacon represents the child of the two base classes. 
 *     The name of the class is meant to represent this basic form.
 *     A child of the two hierarchies could also be: 
 *     dataFilterStrobeBeacon, dataFilterQuirkyBeacon,
 *     dataModBeacon, dataModStrobeBeacon, dataModQuirkyBeacon,
 *     dataCutBeacon, dataCutStrobeBeacon, dataCutQuirkyBeacon.
 *  3. There are three dataFilter types and three beacon types, therefore,
 *     there are nine possible combinations for the cross product of the
 *     two types.
 *  4. A dataFilterBeacon inherits functionality from both a dataFilter type
 *     and a beacon type.
 *     - Functions from dataFilter: filter, scramble, switchMode
 *     - Functions from beacon: switchOnOff, emitSignal.
 *  5. Client must specify the desired cross product of a dataFilter beacon via
 *     constructor injection. The first two arguments in the constructor
 *     yield the dataFilter type and the beacon type respectively.
 *     
 *     - For dataFilter:       For beacon: 
 *       0 -- dataFilter       0 -- beacon
 *       1 -- dataMod          1 -- strobeBeacon
 *       2 -- dataCut          2 -- quirkyBeacon
 *       
 *  6. The last two parameters in the constructor are a prime number and a
 *     postitive integer sequence. The prime is required for the dataFilter
 *     type. The sequence is required for both the dataFilter type and the
 *     beacon type.
 *  7. The dataFilter and beacon type work in tandum, "sharing" the same
 *     sequence. Whatever happens to the sequence in dataFilterType happens to
 *     the sequence in beaconType;
 *  
 * Interface Invariants:
 *  1. An initialized dataFilterBeacon starts active. A dataFilterBeacon will
 *     start and forever remain inactive if the client passes in an integer 
 *     that does not reflect a type in either heirarchy. 
 *     (see #4 in Class Invaraiants)
 *  2. The active status of the dataFilterBeacon relies on both the dataFilter
 *     and the beacon.
 *     - If the dataFilter is inactive, the dataFilter beacon is inactive.
 *     - If a quirkyBeacon is off indefinitely, an attempt to turn it back on
 *       will deactivate the dataFilterBeacon.
 *  3. An inactive dataFilterBeacon cannot be reactivated.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace P5
{
    public class dataFilterBeacon
    {
        private dataFilter dataFilterType;
        private beacon beaconType;
        bool active;

        public dataFilterBeacon(uint dft, uint bt, uint prime, uint[] seq) 
        {
            active = !(dft > 2 || bt > 2);
            if (!active)
            {
                dataFilterType = null; 
                beaconType = null;
            }

            if (dft == 0) dataFilterType = new dataFilter(prime, seq);
            else if (dft == 1) dataFilterType = new dataMod(prime, seq);
            else dataFilterType = new dataCut(prime, seq);

            if (bt == 0) beaconType = new beacon(seq);
            else if (bt == 1) beaconType = new strobeBeacon(seq);
            else beaconType = new quirkyBeacon(seq);
        }

        // PRECONDITION: The dataFilter and beacon types contain a sequence.
        // POSTCONDITION: The dataFilter sequence is filtered and assigned to
        // the beacon sequence. Signals from before and after the filter are
        // returned from the beacon.
        public int[] filterSignal()
        {
            if (!active) return null;
            int[] signals = new int[2];
            signals[0] = beaconType.emitSignal();
            beaconType.newSeq(dataFilterType.filter());
            signals[1] = beaconType.emitSignal();
            return signals;
        }

        // PRECONDITION: The dataFilter and beacon types contain a sequence.
        // POSTCONDITION: The dataFilter sequence is scrambled and assigned to
        // the beacon sequence. Signals from before and after the scramble are
        // returned from the beacon.
        public int[] scrambleSignal()
        {
            if (!active) return null;
            int[] signals = new int[2];
            signals[0] = beaconType.emitSignal();
            beaconType.newSeq(dataFilterType.scramble());
            signals[1] = beaconType.emitSignal();
            return signals;
        }

        // PRECONDITION: The dataFilter type is in LARGE mode.
        // POSTCONDITION: The dataFilter type is in SMALL mode.
        public void switchMode() 
        {
            if (!active) return;
            dataFilterType.switchMode();
            active = dataFilterType.getActiveStatus();
        }

        // PRECONDITION: The beacon type is off.
        // POSTCONDITION: The beacon type is on.
        public void switchOnOff() 
        {
            if (!active) return;
            if (beaconType.whoAmI() != 2) beaconType.switchOnOff();
            else 
            {
                bool isOff = !beaconType.getOnStatus();
                beaconType.switchOnOff();
                active = !(isOff == !beaconType.getOnStatus());
            }
        }

        public int emitSignal() { return beaconType.emitSignal(); }

        public bool getActiveStatus() { return active; }

        public uint[] whoAmI()
        {
            uint[] types = new uint[2];
            types[0] = dataFilterType.whoAmI();
            types[1] = beaconType.whoAmI();
            return types;
        }

        public void reset()
        {
            dataFilterType.resetToOrigSeq();
            beaconType.resetToOrigSeq();
        }
    }
}

/* Implementation Invariants
 *  1. The sequence encapsulated is filtered and scrambled via the 
 *     dataFilterType. This sequence change is reflected in both the
 *     dataFilterType and the beaconType.
 *  2. The dataFilterType can change modes per client request.
 *  3. The on/off state of the beaconType can be changed per client request.
 *     - If the beaconType is a quirkyBeacon, and the quirkyBeacon is off
 *       indefinitely, an attempt to turn it on will deactivate the
 *       dataFilterBeacon.
 *  4. A signal can be emitted by the beaconType per client request.
 *  5. The client can check the active status of a dataFilterBeacon per request.
 *  6. The client can check the type via whoAmI(). Checking the type of the
 *     dataFilterBeacon will return a uint array containing two elements. First
 *     element is the dataFilter type. Second element is the beaconType.
 *     (see #4 in Class Invariants)
 */