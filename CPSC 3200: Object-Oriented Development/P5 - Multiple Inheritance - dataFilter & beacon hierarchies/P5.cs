/* Justin Thoreson
 * P5.cs
 * 9 November 2020
 * 
 * SUMMARY:
 *  1. The objective of this assingment is to simulate the concept of multiple
 *     inheritance using two class hierarchies, dataFilter and beacon.
 *  2. Multiple inheritance is simulated through the dataFilterBeacon class via
 *     double composition.
 *  3. The driver tests the functionality of the dataFilterBeacon hierarchy via
 *     a series of operations.
 *     - turnOnObjects
 *     - whoAreWe (gets the type of dataFilterBeacon in the simulated hierarchy)
 *     - reset
 *     - switchModes (switches the dataFilter component from LARGE to SMALL)
 *     - testGetActive
 *     - testFilterSignals
 *     - testScrambleSignals
 *     - testEmitSignals
 * 
 * OUTPUT:
 *  1. The type of each object is printed to the console (whoAreWe).
 *  2. The active status of each object is displayed.
 *  3. The signal emitted from an object before and after a filter or a scramble
 *     is printed.
 *  4. A single signal emitted from each object is displayed (tesetEmitSignals).
 * 
 * SOURCES:
 *  https://www.csharp-examples.net/align-string-with-spaces/
 */

using System;
using System.Runtime.Versioning;

namespace P5
{
    class P5
    {
        static void Main(string[] args)
        {
            uint prime = 7;
            uint[] seq = new uint[] { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21 };
            const int NUM_OBJS = 9;
            dataFilterBeacon[] myObjs = new dataFilterBeacon[NUM_OBJS];
            setObjects(myObjs, prime, seq);
            turnOnObjects(myObjs, NUM_OBJS);
            whoAreWe(myObjs, NUM_OBJS);
            testGetActive(myObjs, NUM_OBJS);
            testFilterSignals(myObjs, NUM_OBJS);
            resetObjs(myObjs, NUM_OBJS);
            testScrambleSignals(myObjs, NUM_OBJS);
            switchModes(myObjs, NUM_OBJS);
            testFilterSignals(myObjs, NUM_OBJS);
            resetObjs(myObjs, NUM_OBJS);
            testScrambleSignals(myObjs, NUM_OBJS);
            resetObjs(myObjs, NUM_OBJS);
            testEmitSignals(myObjs, NUM_OBJS);
        }

        static void setObjects(dataFilterBeacon[] myObjs, uint prime, uint[] seq)
        {
            int index = 0;
            for (uint i = 0; i < 3; i++)
                for (uint j = 0; j < 3; j++)
                    myObjs[index++] = new dataFilterBeacon(i, j, prime, seq);
        }

        static void turnOnObjects(dataFilterBeacon[] myObjs, int numObjs)
        {
            for (int i = 0; i < numObjs; i++)
                myObjs[i].switchOnOff();
        }

        static void whoAreWe(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Who are we?");
            uint[] whoAreWe = new uint[2];
            for (int i = 0; i < numObjs; i++)
            {
                whoAreWe = myObjs[i].whoAmI();
                Console.Write($"myObj{i + 1}: ");
                if (whoAreWe[0] == 0) Console.Write("dataFilter");
                else if (whoAreWe[0] == 1) Console.Write("dataMod");
                else Console.Write("dataCut");
                if (whoAreWe[1] == 0) Console.WriteLine("Beacon");
                else if (whoAreWe[1] == 1) Console.WriteLine("StrobeBeacon");
                else Console.WriteLine("QuirkyBeacon");
            }
            Console.WriteLine();
        }
        
        static void resetObjs(dataFilterBeacon[] myObjs, int numObjs)
        {
            for (int i = 0; i < numObjs; i++)
                myObjs[i].reset();
        }

        static void switchModes(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Switching modes from LARGE to SMALL...");
            for (int i = 0; i < numObjs; i++)
                myObjs[i].switchMode();
        }

        static void testGetActive(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Status:");
            for (int i = 0; i < numObjs; i++)
                Console.WriteLine($"myObj{i+1}: " + (myObjs[i].getActiveStatus() ? "Active" : "Inactive"));
            Console.WriteLine();
        }

        static void testFilterSignals(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Filtering signals...\nmyObjs: Before | After");
            for (int i = 0; i < numObjs; i++)
            {
                int[] signals;
                signals = myObjs[i].filterSignal();
                Console.WriteLine(String.Format("myObj{0}:    {1, -3} |  {2, -3} ", i + 1, signals[0], signals[1]));
            }
            Console.WriteLine();
        }

        static void testScrambleSignals(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Scrambling signals...\nmyObjs: Before | After");
            for (int i = 0; i < numObjs; i++)
            {
                int[] signals;
                signals = myObjs[i].scrambleSignal();
                Console.WriteLine(String.Format("myObj{0}:    {1, -3} |  {2, -3} ", i + 1, signals[0], signals[1]));
            }
            Console.WriteLine();
        }

        static void testEmitSignals(dataFilterBeacon[] myObjs, int numObjs)
        {
            Console.WriteLine("Emitting signals...");
            for (int i = 0; i < numObjs; i++)
                Console.WriteLine($"myObjs{i + 1}: {myObjs[i].emitSignal()}");
            Console.WriteLine();
        }
    }
}
