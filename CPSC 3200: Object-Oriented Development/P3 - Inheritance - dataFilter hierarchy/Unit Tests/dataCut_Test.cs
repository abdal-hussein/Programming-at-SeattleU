// Justin Thoreson
// dataCut_Test.cs
// 11 October 2020

using Microsoft.VisualStudio.TestTools.UnitTesting;
using P3;

namespace P3_Test
{
    [TestClass]
    public class dataCut_Test
    {
        [TestMethod]
        public void Test_filter_dataCut()
        {
            // Arrange
            int[] seq = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int prime = 7;
            dataCut objLARGE = new dataCut(prime, seq);
            dataCut objSMALL = new dataCut(prime, seq);
            dataCut objNullLARGE = new dataCut(prime);
            dataCut objNullSMALL = new dataCut(prime);
            int[] expectedLARGE = new int[] { 8, 9 };
            int[] expectedSMALL = new int[] { 2, 3, 4, 5, 6 };
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

        [TestMethod]
        public void Test_scramble_dataCut()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataCut objLARGE = new dataCut(prime, seq);
            dataCut objSMALL = new dataCut(prime, seq);
            dataCut objNullLARGE = new dataCut(prime);
            dataCut objNullSMALL = new dataCut(prime);
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
        public void Test_scramble_removePreviousScramble_dataCut()
        {
            // Arrange
            int[] seq1 = new int[] { 7, 2, 5, 4, 3, 6, 1};
            int[] seq2 = new int[] { 11, 6, 9, 8, 7, 10, 5 };
            int prime = 7;
            dataCut objLARGE = new dataCut(prime, seq1);
            dataCut objSMALL = new dataCut(prime, seq1);
            dataCut objNullLARGE = new dataCut(prime);
            dataCut objNullSMALL = new dataCut(prime);
            int[] expectedLARGE1 = new int[] { 7, 6, 5, 4, 3, 2, 1 };
            int[] expectedSMALL1 = new int[] { 1, 2, 3, 4, 5, 6, 7 };
            int[] expectedNullLARGE1 = expectedLARGE1;
            int[] expectedNullSMALL1 = expectedSMALL1;
            int[] expectedLARGE2 = new int[] { 11, 9, 8, 10 };
            int[] expectedSMALL2 = new int[] { 10, 8, 9, 11 };
            int[] expectedNullLARGE2 = expectedLARGE2;
            int[] expectedNullSMALL2 = expectedSMALL2;
            // Act
            objSMALL.switchMode();
            objNullSMALL.switchMode();
            int[] resultLARGE1 = objLARGE.scramble();
            int[] resultSMALL1 = objSMALL.scramble();
            int[] resultNullLARGE1 = objNullLARGE.scramble(seq1);
            int[] resultNullSMALL1 = objNullSMALL.scramble(seq1);
            int[] resultLARGE2 = objLARGE.scramble(seq2);
            int[] resultSMALL2 = objSMALL.scramble(seq2);
            int[] resultNullLARGE2 = objNullLARGE.scramble(seq2);
            int[] resultNullSMALL2 = objNullSMALL.scramble(seq2);
            // Assert
            CollectionAssert.AreEqual(resultLARGE1, expectedLARGE1);
            CollectionAssert.AreEqual(resultSMALL1, expectedSMALL1);
            CollectionAssert.AreEqual(resultNullLARGE1, expectedNullLARGE1);
            CollectionAssert.AreEqual(resultNullSMALL1, resultNullSMALL1);
            CollectionAssert.AreEqual(resultLARGE2, expectedLARGE2);
            CollectionAssert.AreEqual(resultSMALL2, expectedSMALL2);
            CollectionAssert.AreEqual(resultNullLARGE2, expectedNullLARGE2);
            CollectionAssert.AreEqual(resultNullSMALL2, resultNullSMALL2);
        }

        [TestMethod]
        public void Test_switchMode_dataCut()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataCut obj = new dataCut(prime, seq);
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
        public void Test_isActive_dataCut()
        {
            // Arrange
            int[] seq = new int[] { 1, 9, 3, 7, 5, 6, 4, 8, 2, 10 };
            int prime = 7;
            dataCut obj = new dataCut(prime, seq);
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
        public void Test_findNextPrime_dataCut()
        {
            // Arrange
            int[] seq = new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
            int prime = 6;
            dataCut objLARGE = new dataCut(prime, seq);
            dataCut objSMALL = new dataCut(prime, seq);
            dataCut objNullLARGE = new dataCut(prime);
            dataCut objNullSMALL = new dataCut(prime);
            int[] expectedLARGE = new int[] { 8, 9 };
            int[] expectedSMALL = new int[] { 2, 3, 4, 5, 6 };
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
