/* Justin Thoreson
 * dataFilterBeacon_test.cs
 * 9 November 2020
 */

using Microsoft.VisualStudio.TestTools.UnitTesting;
using P5;

namespace P5_Test
{
    [TestClass]
    public class dataFilterBeacon_test
    {
        [TestMethod]
        public void Test_filterSignal_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            int[] expectedSignals1 = { 5, 5 };
            int[] expectedSignals2 = { 5, 6 };
            int[] expectedSignals3 = { 5, 4 };
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(1, 0, prime, seq);
            obj3 = new dataFilterBeacon(2, 0, prime, seq);
            obj1.switchOnOff();
            obj2.switchOnOff();
            obj3.switchOnOff();
            int[] signals1 = obj1.filterSignal();
            int[] signals2 = obj2.filterSignal();
            int[] signals3 = obj3.filterSignal();
            // Assert
            CollectionAssert.AreEqual(expectedSignals1, signals1);
            CollectionAssert.AreEqual(expectedSignals2, signals2);
            CollectionAssert.AreEqual(expectedSignals3, signals3);
        }

        [TestMethod]
        public void Test_scrambleSignal_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            int[] expectedSignals1 = { 5, 1 };
            int[] expectedSignals2 = { 5, 1 };
            int[] expectedSignals3 = { 5, 1 };
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(1, 0, prime, seq);
            obj3 = new dataFilterBeacon(2, 0, prime, seq);
            obj1.switchOnOff();
            obj2.switchOnOff();
            obj3.switchOnOff();
            int[] signals1 = obj1.scrambleSignal();
            int[] signals2 = obj2.scrambleSignal();
            int[] signals3 = obj3.scrambleSignal();
            // Assert
            CollectionAssert.AreEqual(expectedSignals1, signals1);
            CollectionAssert.AreEqual(expectedSignals2, signals2);
            CollectionAssert.AreEqual(expectedSignals3, signals3);
        }

        [TestMethod]
        public void Test_switchMode_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            int[] expectedSignals1 = new int[] { 5, 2 };
            int[] expectedSignals2 = new int[] { 5, 1 };
            int[] expectedSignals3 = new int[] { 5, 2 };
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(1, 0, prime, seq);
            obj3 = new dataFilterBeacon(2, 0, prime, seq);
            obj1.switchOnOff();
            obj2.switchOnOff();
            obj3.switchOnOff();
            obj1.switchMode();
            obj2.switchMode();
            obj3.switchMode();
            int[] signals1  = obj1.filterSignal();
            int[] signals2 = obj2.filterSignal();
            int[] signals3 = obj3.filterSignal();
            // Assert
            CollectionAssert.AreEqual(expectedSignals1, signals1);
            CollectionAssert.AreEqual(expectedSignals2, signals2);
            CollectionAssert.AreEqual(expectedSignals3, signals3);
        }

        [TestMethod]
        public void Test_switchOnOff_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            bool expectedActive1 = true;
            bool expectedActive2 = true;
            bool expectedActive3 = false;
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(0, 1, prime, seq);
            obj3 = new dataFilterBeacon(0, 2, prime, seq);
            obj1.switchOnOff(); 
            obj2.switchOnOff();
            obj3.switchOnOff();
            obj3.switchOnOff();
            obj3.switchOnOff();
            obj3.switchOnOff();
            obj3.switchOnOff();
            bool active1 = obj1.getActiveStatus();
            bool active2 = obj2.getActiveStatus();
            bool active3 = obj3.getActiveStatus();
            // Assert
            Assert.AreEqual(expectedActive1, active1);
            Assert.AreEqual(expectedActive2, active2);
            Assert.AreEqual(expectedActive3, active3);
        }

        [TestMethod]
        public void Test_emitSignal_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            int expectedSignal1 = 5;
            int expectedSignal2_SecondObj2Emit = -4;
            int expectedSignal3 = 15;
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(0, 1, prime, seq);
            obj3 = new dataFilterBeacon(0, 2, prime, seq);
            obj1.switchOnOff();
            obj2.switchOnOff();
            obj3.switchOnOff();
            int signal1 = obj1.emitSignal();
            obj2.emitSignal();
            int signal2 = obj2.emitSignal();
            int signal3 = obj3.emitSignal();
            // Assert
            Assert.AreEqual(expectedSignal1, signal1);
            Assert.AreEqual(expectedSignal2_SecondObj2Emit, signal2);
            Assert.AreEqual(expectedSignal3, signal3);
        }

        [TestMethod]
        public void Test_reset_dataFilterBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            uint prime = 3;
            dataFilterBeacon obj1, obj2, obj3;
            int[] expectedSignals1 = { 5, 5 };
            int[] expectedSignals2 = { 5, 6 };
            int[] expectedSignals3 = { 5, 4 };
            // Act
            obj1 = new dataFilterBeacon(0, 0, prime, seq);
            obj2 = new dataFilterBeacon(1, 0, prime, seq);
            obj3 = new dataFilterBeacon(2, 0, prime, seq);
            obj1.switchOnOff();
            obj2.switchOnOff();
            obj3.switchOnOff();
            int[] signals1 = obj1.filterSignal();
            int[] signals2 = obj2.filterSignal();
            int[] signals3 = obj3.filterSignal();
            obj1.reset();
            obj2.reset();
            obj3.reset();
            int[] signals4 = obj1.filterSignal();
            int[] signals5 = obj2.filterSignal();
            int[] signals6 = obj3.filterSignal();
            // Assert
            CollectionAssert.AreEqual(expectedSignals1, signals1);
            CollectionAssert.AreEqual(expectedSignals2, signals2);
            CollectionAssert.AreEqual(expectedSignals3, signals3);
            CollectionAssert.AreEqual(expectedSignals1, signals4);
            CollectionAssert.AreEqual(expectedSignals2, signals5);
            CollectionAssert.AreEqual(expectedSignals3, signals6);
        }
    }
}
