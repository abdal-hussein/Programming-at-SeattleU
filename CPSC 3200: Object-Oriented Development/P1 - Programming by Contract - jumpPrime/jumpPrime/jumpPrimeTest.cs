// Justin Thoreson
// jumpPrimeTest.cs
// 17 September 2020

using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using P1;

namespace P1Test
{
    [TestClass]
    public class jumpPrimeTest
    {
        [TestMethod]
        public void Test_Initialization_jumpPrime()
        {
            // Arrange
            int testVal = 999;
            jumpPrime obj;
            bool expectedActive = true;
            // Act
            obj = new jumpPrime(testVal);
            // Assert
            Assert.AreEqual(expectedActive, obj.getActiveStatus());
        }

        [TestMethod]
        public void Test_UpperPrime_jumpPrime()
        {
            // Arrange
            int testVal = 2020;
            jumpPrime obj;
            int expectedUpperPrime = 2027;
            // Act
            obj = new jumpPrime(testVal);
            int upperPrime = obj.up();
            // Assert
            Assert.AreEqual(expectedUpperPrime, upperPrime);
        }

        [TestMethod]
        public void Test_LowerPrime_jumpPrime()
        {
            // Arrange
            int testVal = 2020;
            jumpPrime obj;
            int expectedLowerPrime = 2017;
            // Act
            obj = new jumpPrime(testVal);
            int lowerPrime = obj.down();
            // Assert
            Assert.AreEqual(expectedLowerPrime, lowerPrime);
        }

        [TestMethod]
        public void Test_Primes_InputLessThat1000_jumpPrime()
        {
            // Arange
            int testVal = 50;
            jumpPrime obj;
            int expectedUpperPrime = 1009;
            int expectedLowerPrime = 997;
            // Act
            obj = new jumpPrime(testVal);
            int upperPrime = obj.up();
            int lowerPrime = obj.down();
            // Assert
            Assert.AreEqual(expectedUpperPrime, upperPrime);
            Assert.AreEqual(expectedLowerPrime, lowerPrime);
        }

        [TestMethod]
        public void Test_Reset_jumpPrime()
        {
            // Arrange
            int testVal = 1000;
            jumpPrime obj;
            bool expectedInitialIsActive = false;
            bool expectedFinalIsActive = true;
            int expectedOrigUpperPrime = 1009;
            int expectedOrigLowerPrime = 997;
            int expectedJumpUpperPrime = 1019;
            int expectedJumpLowerPrime = 1013;
            // Act
            obj = new jumpPrime(testVal);
            while (obj.getActiveStatus())
                obj.up();
            bool initialIsActive = obj.getActiveStatus();
            int jumpUpperPrime = obj.up();
            int jumpLowerPrime = obj.down();
            obj.reset(testVal);
            // Assert
            Assert.AreEqual(expectedInitialIsActive, initialIsActive);
            Assert.AreEqual(expectedFinalIsActive, obj.getActiveStatus());
            Assert.AreEqual(expectedOrigUpperPrime, obj.up());
            Assert.AreEqual(expectedOrigLowerPrime, obj.down());
            Assert.AreEqual(expectedJumpUpperPrime, jumpUpperPrime);
            Assert.AreEqual(expectedJumpLowerPrime, jumpLowerPrime);
        }

        [TestMethod]
        public void Test_Revive_jumpPrime()
        {
            // Arrange
            int testVal = 4002;
            jumpPrime obj;
            bool expectedInitialIsActive = false;
            bool expectedFinalIsActive = true;
            int originalLowerPrime = 4001;
            // Act
            obj = new jumpPrime(testVal);
            while (obj.getActiveStatus())
                obj.down();
            bool initialIsActive = obj.getActiveStatus();
            obj.revive();
            // Assert
            Assert.AreEqual(expectedInitialIsActive, initialIsActive);
            Assert.AreEqual(expectedFinalIsActive, obj.getActiveStatus());
            Assert.AreNotEqual(originalLowerPrime, obj.down());
        }

        [TestMethod]
        public void Test_ReviveWhileActive_PermanentDeactivation_jumpPrime()
        {
            // Arrange
            int testVal = 10000;
            jumpPrime obj;
            bool expectedInitialIsActive = false;
            bool expectedSecondIsActive = false;
            bool expectedFinalIsActive = false;
            // Act
            obj = new jumpPrime(testVal);
            obj.revive();
            bool initialIsActive = obj.getActiveStatus();
            obj.revive();
            bool secondIsActive = obj.getActiveStatus();
            obj.reset(testVal);
            bool finalIsActive = obj.getActiveStatus();
            // Assert
            Assert.AreEqual(expectedInitialIsActive, initialIsActive);
            Assert.AreEqual(expectedSecondIsActive, secondIsActive);
            Assert.AreEqual(expectedFinalIsActive, finalIsActive);
        }
    }
}
