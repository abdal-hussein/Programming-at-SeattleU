/* Justin Thoreson
 * P3.cs
 * 11 October 2020
 * 
 * SUMMARY:
 *   1. This assignment is meant to demonstrate the practice of inheritance as
 *      well as dependency injection and heterogenous containers.
 *   2. Dependency injection is implemented through constructor injection.
 *   3. Multiple dataFilter, dataMod, and dataCut objects are processed.
 *   
 * SOURCES:
 *   stackoverflow.com, geeksforgeeks.org, & docs.microsoft.com/en-us/dotnet/
 *     - C# sytnax
 */

using System;

namespace P3
{
    class P3
    {
        static void Main(string[] args)
        {
            const int NUM_OBJS = 9;
            dataFilter[] myObjs= new dataFilter[NUM_OBJS];
            setObjects(myObjs, NUM_OBJS);

            Console.WriteLine("LARGE Mode:");
            testScramble(myObjs);
            testFilter(myObjs);
            testSwitchMode(myObjs);
            testResetObject(myObjs);

            Console.WriteLine("\nSMALL Mode:");
            testScramble(myObjs);
            testFilter(myObjs);
            testSwitchMode(myObjs);
            testResetObject(myObjs);           

            Console.WriteLine("\nInactive:");
            testScramble(myObjs);
            testFilter(myObjs);
        }

        static void setObjects(dataFilter[] myObjs, int numObjs)
        {
            int[] seq1 = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int[] seq2 = new int[] { 11, 19, 13, 17, 15, 16, 14, 18, 12, 20 };
            int[] seq3 = new int[] { 21, 37, 25, 33, 29, 31, 27, 35, 23, 39 };
            int[] primes = new int[] { 3, 13, 23, 5, 17, 29, 7, 19, 37};

            for (int i = 0; i < numObjs; i++)
            {
                if (i % 3 == 0)
                    myObjs[i] = getObj(primes[i], seq1, i, numObjs);
                else if (i % 3 == 1)
                    myObjs[i] = getObj(primes[i], seq2, i, numObjs);
                else
                    myObjs[i] = getObj(primes[i], seq3, i, numObjs);
            }
        }

        static dataFilter getObj(int prime, int[] seq, int index, int numObjs)
        {
            if (index < numObjs/3) 
                return new dataFilter(prime, seq);
            if (index >= numObjs/3 && index < numObjs*2/3) 
                return new dataMod(prime, seq);
            return new dataCut(prime, seq);
        }

        static void testScramble(dataFilter[] myObjs)
        {
            for (int i = 0; i < myObjs.Length; i++)
            {
                Console.Write($"{myObjs[i].GetType()} " 
                    + $"{(i % (myObjs.Length / 3)) + 1} scramble: ");

                if (!myObjs[i].getActiveStatus())
                    Console.WriteLine("Object is inactive");

                else
                {
                    int[] result = myObjs[i].scramble();

                    if (myObjs[i].GetType() == typeof(dataCut))
                    {
                        int[] newCutSeq = new int[] 
                            { 1, 2, 3, 11, 12, 13, 27, 29, 33 };
                        result = myObjs[i].scramble(newCutSeq);
                    }

                    if (result != null)
                        for (int j = 0; j < result.Length; j++)
                            Console.Write(result[j] + " ");
                    else Console.Write("Sequence is empty");
                    Console.WriteLine();
                }
            }
        }

        static void testFilter(dataFilter[] myObjs)
        {
            for (int i = 0; i < myObjs.Length; i++)
            {
                Console.Write($"{myObjs[i].GetType()} "
                    + $"{(i % (myObjs.Length/3)) + 1} filter: ");

                if (!myObjs[i].getActiveStatus())
                    Console.WriteLine("Object is inactive");
                else
                {
                    int[] result = myObjs[i].filter();
                    if (result != null)
                        for (int j = 0; j < result.Length; j++)
                            Console.Write(result[j] + " ");
                    else Console.Write("Sequence is empty");
                    Console.WriteLine();
                }
            }
        }

        static void testSwitchMode(dataFilter[] myObjs)
        {
            for (int i = 0; i < myObjs.Length; i++)
                myObjs[i].switchMode();
        }

        static void testResetObject(dataFilter[] myObjs)
        {
            for (int i = 0; i < myObjs.Length; i++)
                myObjs[i].resetToOrigSeq();
        }
    }
}