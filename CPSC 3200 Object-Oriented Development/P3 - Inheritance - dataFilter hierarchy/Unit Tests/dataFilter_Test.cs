// Justin Thoreson
// dataFilter_Test.cs
// 11 October 2020

using Microsoft.VisualStudio.TestTools.UnitTesting;
using P3;

namespace P3_Test
{
    [TestClass]
    public class dataFilter_Test
    {
        [TestMethod]
        public void Test_filter_dataFilter()
        {
            // Arrange
            int[] seq = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int prime = 7;
            dataFilter objLARGE = new dataFilter(prime, seq);
            dataFilter objSMALL = new dataFilter(prime, seq);
            dataFilter objNullLARGE = new dataFilter(prime);
            dataFilter objNullSMALL = new dataFilter(prime);
            int[] expectedLARGE = new int[] { 8, 9, 10 };
            int[] expectedSMALL = new int[] { 1, 2, 3, 4, 5, 6 };
            int[] expectedNullLARGE =  new int[] { 7 };
            int[] expectedNullSMALL = new int[] { 7 };
            // Act
            objSMALL.switchMode();
            objNullSMALL.switchMode();
            int[] resultLARGE = objLARGE.filter();
            int[] resultSMALL = objSMALL.filter();
            int[] resultNullLARGE = objNullLARGE.filter();
            int[] resultNullSMALL = objNullSMALL.filter();
            // Assert
            CollectionAssert.AreEqual(resultLARGE, expectedLARGE);
            CollectionAssert.AreEqual(resultSMALL, expectedSMALL);
            CollectionAssert.AreEqual(resultNullLARGE, expectedNullLARGE);
            CollectionAssert.AreEqual(resultNullSMALL, expectedNullSMALL);
        }

        [TestMethod]
        public void Test_scramble_dataFilter()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataFilter objLARGE = new dataFilter(prime, seq);
            dataFilter objSMALL = new dataFilter(prime, seq);
            dataFilter objNullLARGE = new dataFilter(prime);
            dataFilter objNullSMALL = new dataFilter(prime);
            int[] expectedLARGE = new int[] { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
            int[] expectedSMALL = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int[] expectedNullLARGE = expectedLARGE;
            int[] expectedNullSMALL = expectedSMALL;
            // Act
            objSMALL.switchMode();
            objNullSMALL.switchMode();
            int[] resultLARGE = objLARGE.scramble();
            int[] resultSMALL = objSMALL.scramble();
            int[] resultNullLARGE = objNullLARGE.scramble(seq);
            int[] resultNullSMALL = objNullSMALL.scramble(seq);
            // Assert
            CollectionAssert.AreEqual(resultLARGE, expectedLARGE);
            CollectionAssert.AreEqual(resultSMALL, expectedSMALL);
            CollectionAssert.AreEqual(resultNullLARGE, expectedNullLARGE);
            CollectionAssert.AreEqual(resultNullSMALL, resultNullSMALL);
        }

        [TestMethod]
        public void Test_switchMode_dataFilter()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataFilter obj = new dataFilter(prime, seq);
            int[] expectedLARGE = new int[] { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
            int[] expectedSMALL = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            // Act
            int[] resultLARGE = obj.scramble();
            obj.switchMode();
            int[] resultSMALL = obj.scramble();
            // Assert
            CollectionAssert.AreEqual(resultLARGE, expectedLARGE);
            CollectionAssert.AreEqual(resultSMALL, expectedSMALL);
        }

        [TestMethod]
        public void Test_isActive_dataFilter()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataFilter obj = new dataFilter(prime, seq);
            int[] expectedLARGE = new int[] { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
            int[] expectedSMALL = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int[] expectedInactiveSeq = null;
            bool expectedActive = false;
            // Act
            int[] resultLARGE = obj.scramble();
            obj.switchMode();
            int[] resultSMALL = obj.scramble();
            obj.switchMode();
            int[] resultInactive = obj.scramble();
            bool activeState = obj.getActiveStatus();
            // Assert
            CollectionAssert.AreEqual(resultLARGE, expectedLARGE);
            CollectionAssert.AreEqual(resultSMALL, expectedSMALL);
            CollectionAssert.AreEqual(resultInactive, expectedInactiveSeq);
            Assert.AreEqual(activeState, expectedActive);
        }

        [TestMethod]
        public void Test_findNextPrime_dataFilter()
        {
            // Arrange
            int[] seq = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int prime = 6;
            dataFilter objLARGE = new dataFilter(prime, seq);
            dataFilter objSMALL = new dataFilter(prime, seq);
            dataFilter objNullLARGE = new dataFilter(prime);
            dataFilter objNullSMALL = new dataFilter(prime);
            int[] expectedLARGE = new int[] { 8, 9, 10 };
            int[] expectedSMALL = new int[] { 1, 2, 3, 4, 5, 6 };
            int[] expectedNullLARGE = new int[] { 7 };
            int[] expectedNullSMALL = new int[] { 7 };
            // Act
            objSMALL.switchMode();
            objNullSMALL.switchMode();
            int[] resultLARGE = objLARGE.filter();
            int[] resultSMALL = objSMALL.filter();
            int[] resultNullLARGE = objNullLARGE.filter();
            int[] resultNullSMALL = objNullSMALL.filter();
            // Assert
            CollectionAssert.AreEqual(resultLARGE, expectedLARGE);
            CollectionAssert.AreEqual(resultSMALL, expectedSMALL);
            CollectionAssert.AreEqual(resultNullLARGE, expectedNullLARGE);
            CollectionAssert.AreEqual(resultNullSMALL, expectedNullSMALL);
        }
    }
}
