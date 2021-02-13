/* Justin Thoreson
 * quirkyBeacon_test.cs
 * 9 November 2020
 */

using Microsoft.VisualStudio.TestTools.UnitTesting;
using P5;

namespace P5_Test
{
    [TestClass]
    public class quirkyBeacon_test
    {
        [TestMethod]
        public void Test_switchOnOff_quirkyBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            quirkyBeacon obj;
            int expectedSignalOff = 0;
            int expectedSignalOn1 = 15;
            int expectedSignalOn2 = 12;
            // Act
            obj = new quirkyBeacon(seq);
            int signalOff1 = obj.emitSignal();
            obj.switchOnOff();
            int signalOn1 = obj.emitSignal();
            obj.switchOnOff();
            int signalOff2 = obj.emitSignal();
            obj.switchOnOff();
            int signalOn2 = obj.emitSignal();
            obj.switchOnOff();
            int signalOff3 = obj.emitSignal();
            obj.switchOnOff();
            int signalOff4 = obj.emitSignal();
            // Assert
            Assert.AreEqual(expectedSignalOff, signalOff1);
            Assert.AreEqual(expectedSignalOn1, signalOn1);
            Assert.AreEqual(expectedSignalOff, signalOff2);
            Assert.AreEqual(expectedSignalOn2, signalOn2);
            Assert.AreEqual(expectedSignalOff, signalOff3);
            Assert.AreEqual(expectedSignalOff, signalOff4);
        }

        [TestMethod]
        public void Test_emitSignal_quirkyBeacon()
        {
            // Arrange
            uint[] seq = new uint[] { 1, 4, 3, 2, 5 };
            quirkyBeacon obj;
            int expectedSignalOff = 0;
            int expectedSignal1 = 15;
            int expectedSignal2 = 12;
            int expectedSignal3 = 1;
            int expectedSignal4 = 6;
            int expectedSignal5 = 3;
            int expectedSignalNotCharged = 0;
            // Act
            obj = new quirkyBeacon(seq);
            int signalOff = obj.emitSignal();
            obj.switchOnOff();
            int signal1 = obj.emitSignal();
            int signal2 = obj.emitSignal();
            int signal3 = obj.emitSignal();
            int signal4 = obj.emitSignal();
            int signal5 = obj.emitSignal();
            int signalNotCharged = obj.emitSignal();
            // Assert
            Assert.AreEqual(expectedSignalOff, signalOff);
            Assert.AreEqual(expectedSignal1, signal1);
            Assert.AreEqual(expectedSignal2, signal2);
            Assert.AreEqual(expectedSignal3, signal3);
            Assert.AreEqual(expectedSignal4, signal4);
            Assert.AreEqual(expectedSignal5, signal5);
            Assert.AreEqual(expectedSignal1, signal1);
            Assert.AreEqual(expectedSignalNotCharged, signalNotCharged);
        }

        [TestMethod]
        public void Test_newSeq_quirkyBeacon()
        {
            // Arrange
            uint[] origSeq = new uint[] { 1, 2, 3, 4, 5, };
            uint[] newSeq = new uint[] { 6, 7, 8, 9 };
            int expectedSignal1 = 15;
            int expectedSignal2 = 3;
            quirkyBeacon obj;
            // Act
            obj = new quirkyBeacon(origSeq);
            obj.switchOnOff();
            int signal1 = obj.emitSignal();
            obj.newSeq(newSeq);
            int signal2 = obj.emitSignal();
            // Assert
            Assert.AreEqual(expectedSignal1, signal1);
            Assert.AreEqual(expectedSignal2, signal2);
        }

        [TestMethod]
        public void Test_whoAmI_quirkyBeacon()
        {
            // Arrange 
            uint[] seq = new uint[] { 1, 2, 3, 4, 5 };
            quirkyBeacon obj;
            uint expectedWhoAmI = 2;
            // Act
            obj = new quirkyBeacon(seq);
            uint whoAmI = obj.whoAmI();
            // Assert
            Assert.AreEqual(expectedWhoAmI, whoAmI);
        }

        [TestMethod]
        public void Test_resetToOrigSeq_quirkyBeacon()
        {
            // Arrange
            uint[] seq1 = new uint[] { 1, 2, 3, 4, 5 };
            uint[] seq2 = new uint[] { 6, 7, 8, 9 };
            quirkyBeacon obj;
            int expectedSignal1 = 15;
            int expectedSignal2 = 3;
            int expectedSignal3 = 15;
            // Act
            obj = new quirkyBeacon(seq1);
            obj.switchOnOff();
            int signal1 = obj.emitSignal();
            obj.newSeq(seq2);
            int signal2 = obj.emitSignal();
            obj.resetToOrigSeq();
            int signal3 = obj.emitSignal();
            // Assert
            Assert.AreEqual(expectedSignal1, signal1);
            Assert.AreEqual(expectedSignal2, signal2);
            Assert.AreEqual(expectedSignal3, signal3);
        }
    }
}