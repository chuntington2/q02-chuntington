/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, drop1) {
	Piezas pieza;
	pieza.dropPiece(1);
	ASSERT_EQ(pieza.pieceAt(0,1), X);
}

TEST(PiezasTest, drop0) {
	Piezas pieza;
	pieza.dropPiece(0);
	ASSERT_EQ(pieza.pieceAt(0,0), X);
}

TEST(PiezasTest, drop3) {
	Piezas pieza;
	pieza.dropPiece(3);
	ASSERT_EQ(pieza.pieceAt(0,3), X);
}

TEST(PiezasTest, dropTwo) {
	Piezas pieza;
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	ASSERT_EQ(pieza.pieceAt(1,3), O);
}

TEST(PiezasTest, dropThree) {
	Piezas pieza;
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	ASSERT_EQ(pieza.pieceAt(2,3), X);
}

TEST(PiezasTest, dropFour) {
	Piezas pieza;
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	ASSERT_EQ(pieza.dropPiece(3), Blank);
}

TEST(PiezasTest, dropLow) {
	Piezas pieza;
	ASSERT_TRUE(pieza.dropPiece(-1) == Invalid);
}

TEST(PiezasTest, dropHigh) {
	Piezas pieza;
	ASSERT_TRUE(pieza.dropPiece(4) == Invalid);
}

TEST(PiezasTest, pieceHigh) {
	Piezas pieza;
	ASSERT_EQ(pieza.pieceAt(3,0), Invalid);
}

TEST(PiezasTest, pieceLow) {
	Piezas pieza;
	ASSERT_EQ(pieza.pieceAt(-1,0), Invalid);
}

TEST(PiezasTest, pieceLeft) {
	Piezas pieza;
	ASSERT_EQ(pieza.pieceAt(0,-1), Invalid);
}

TEST(PiezasTest, pieceRight) {
	Piezas pieza;
	ASSERT_EQ(pieza.pieceAt(0,4), Invalid);
}

TEST(PiezasTest, pieceBlank) {
	Piezas pieza;
	ASSERT_EQ(pieza.pieceAt(0,0), Blank);
}

TEST(PiezasTest, reset) {
	Piezas pieza;
	pieza.dropPiece(3);
	pieza.dropPiece(2);
	pieza.reset();
	ASSERT_EQ(pieza.pieceAt(0,3), Blank);
	ASSERT_EQ(pieza.pieceAt(0,2), Blank);
}

TEST(PiezasTest, resetPrevious) {
	Piezas pieza;
	Piece test;
	pieza.dropPiece(3);
	test = pieza.pieceAt(0,3);
	pieza.reset();
	ASSERT_NE(test, Blank);
}

TEST(PiezasTest, boardTie) {
	Piezas pieza;
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	ASSERT_TRUE(pieza.gameState() == Invalid);
}

TEST(PiezasTest, boardEmpty) {
	Piezas pieza;
	ASSERT_TRUE(pieza.gameState() == Invalid);
}

TEST(PiezasTest, rowFourWin) {
	Piezas pieza;
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(0);
	pieza.dropPiece(2);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(2);
	pieza.dropPiece(1);
	pieza.dropPiece(1);
	ASSERT_TRUE(pieza.gameState() == X);
}

TEST(PiezasTest, rowFourTie) {
	Piezas pieza;
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	ASSERT_TRUE(pieza.gameState() == Blank);
}

TEST(PiezasTest, rowThreeWin) {
	Piezas pieza;
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(2);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	ASSERT_TRUE(pieza.gameState() == X);
}

TEST(PiezasTest, colRowTie) {
	Piezas pieza;
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(0);
	pieza.dropPiece(2);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(2);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	ASSERT_TRUE(pieza.gameState() == Blank);
}

TEST(PiezasTest, colThreeWin) {
	Piezas pieza;
	pieza.dropPiece(1);
	pieza.dropPiece(0);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(1);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(3);
	pieza.dropPiece(2);
	pieza.dropPiece(2);
	ASSERT_TRUE(pieza.gameState() == X);
}

TEST(PiezasTest, colThreeTie) {
	Piezas pieza;
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(1);
	pieza.dropPiece(2);
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(0);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	pieza.dropPiece(3);
	ASSERT_TRUE(pieza.gameState() == Blank);
}

