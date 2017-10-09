#include "Piezas.h"
#include <vector>
#include <assert.h>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
    turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    board.clear();
    board.resize(BOARD_ROWS, std::vector<Piece>(BOARD_COLS, Blank));
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    //out of bounds
    if(column > BOARD_COLS-1 || column < 0) {
        if (turn == X) {
            turn = O;
        }
        else {
            turn = X;
        }
        return Invalid;
    }
    
    for(int i = 0; i < BOARD_ROWS; i++) {
        if(board[i][column] == Blank) {
            board[i][column] = turn; //set board spot to turn
            if(turn == X) {
                turn = O;
                return X;
            } else {
                turn = X;
                return O;
            }
        }
    }
    
    //column full
    if (turn == X) {
        turn = O;
    }
    else {
        turn = X; //lose turn
    }
    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    //invalid if out of bounds
    if(row > BOARD_ROWS-1 || row < 0 || column > BOARD_COLS-1 || column < 0 )
        return Invalid;

    return board[row][column];
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    //Game not over
    for(int i = 0; i < BOARD_ROWS; i++) {
        for(int j = 0; j < BOARD_COLS; j++) {
            if(board[i][j] == Blank)
                return Invalid;
        }
    }
    int xStreak = 0;
    int oStreak = 0;
    int curStreak = 0;
    Piece previous;
    //check columns
    for(int i = 0; i < BOARD_COLS; i++) {
        curStreak = 0;
        previous = board[0][i];

        for(int j = 0; j < BOARD_ROWS-1; j++) {
            assert(j+1 < 3 /*col first*/);
            if(previous == board[j+1][i]) {
                curStreak++; //add 1
                if(previous == X) {
                    if(curStreak > xStreak) {
                        xStreak = curStreak; //up x streak
                    }
                }
                else if(previous == O) {
                    if(curStreak > oStreak) {
                        oStreak = curStreak;
                    }
                }
            }
            else if(previous != board[j+1][i]) {
                curStreak = 0;
            }
            previous = board[j+1][i];    
        }
    }
    
    //check rows
    for(int i = 0; i < BOARD_ROWS; i++) {
        curStreak = 0;
        previous = board[i][0];

        for(int j = 0; j < BOARD_COLS-1; j++) {
            assert(j+1 < 4);
            if(previous == board[i][j+1]) {
                curStreak++; //add 1
                if(previous == X) {
                    if(curStreak > xStreak) {
                        xStreak = curStreak; //up x streak
                    }
                }
                else if(previous == O) {
                    if(curStreak > oStreak) {
                        oStreak = curStreak;
                    }
                }
            }
            else if(previous != board[i][j+1]) {
                curStreak = 0;
            }
            previous = board[i][j+1];    
        }
    }
    
    if(xStreak > oStreak) {
        return X;
    }
    else if(oStreak > xStreak) {
        return O;
    }
    else {
        return Blank;
    }
    return Blank;
}