/* Justin Thoreson
 * P1.cs
 * 17 September 2020
 *
 * PURPOSE:
 *   The purpose of the jumpPrime assignment is to demonstrate the potential
 *   invalidation of data over time, as well as the control of state and
 *   information.
 * 
 * PROCESSING:
 *   An array of jumpPrimes is declared, and each object is initialized to a
 *   random value at least four digits long. For the sake of this driver, the
 *   upper bound is 99999, which would strictly make each random value 
 *   generated either four or five digits long. The values are assigned to the
 *   jumpPrimes via a function called in main.
 *   The functionality of the jumpPrimes are tested through the second function
 *   called in main. Specifically, the up, down, revive, and reset functions 
 *   are called.
 *   
 *   
 * OUTPUT:
 *   1. The initial values assigned to each jumpPrime object are displayed.
 *   2. The lowest prime greater than the encapsulated value and the greatest
 *      prime less than the value are displayed with each up and down query
 *      respectfully.
 *   3. This driver will output when a reset or revive occurs.
 */

using System;

namespace P1
{
    class P1
    {
        public static void Main(string[] args)
        {
            const int NUM_OBJS = 3;
            jumpPrime[] myObjs = new jumpPrime[NUM_OBJS];
            int[] inputs = new int[NUM_OBJS];
            generateInput(ref myObjs, ref inputs, NUM_OBJS);
            testJumpPrimes(ref myObjs, ref inputs, NUM_OBJS);
        }

        public static void generateInput(ref jumpPrime[] myObjs, ref int[] inputs, int numObjs)
        {
            const int LOWER_BOUND = 1000;
            const int UPPER_BOUND = 99999;
            Random randVal = new Random();
            for (int i = 0; i < numObjs; i++)
            {
                inputs[i] = randVal.Next(LOWER_BOUND, UPPER_BOUND);
                Console.WriteLine($"jumpPrime {i + 1}: {inputs[i]}");
                myObjs[i] = new jumpPrime(inputs[i]);
            }
        }

        public static void testJumpPrimes(ref jumpPrime[] myObjs, ref int[] inputs, int numObjs)
        {
            for (int i = 0; i < numObjs; i++)
            {
                Console.WriteLine($"\njumpPrime {i + 1}:");
                runUpDownQuerries(ref myObjs[i]);

                Console.WriteLine("Reset");
                myObjs[i].reset(inputs[i]);
                runUpDownQuerries(ref myObjs[i]);

                Console.WriteLine("Revive");
                myObjs[i].revive();
                runUpDownQuerries(ref myObjs[i]);

            }
        }

        public static void runUpDownQuerries(ref jumpPrime myObj)
        {
            while (myObj.getActiveStatus())
            {
                Console.WriteLine($"Up:   {myObj.up()}");
                Console.WriteLine($"Down: {myObj.down()}");
            }
        }
    }
}
