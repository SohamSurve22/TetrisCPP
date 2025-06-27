//
// Created by soham on 25/06/2025.
//

#ifndef BOARD_H
#define BOARD_H

#include "Pieces.h"

#define BOARD_LINE_WIDTH 6
#define BLOCK_SIZE 16
#define BOARD_POSITION 200
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define MIN_VERTICAL_MARGIN 20
#define MIN_HORIZONTAL_MARGIN 20
#define PIECE_BLOCKS 5

class Board
{
public:
    Board(Pieces *pPieces, int pScreenHeight);

    int GetXPosInPixel(int pPos);
    int GetYPosInPixels(int pPos);
    bool IsFreeBlock(int pX, int pY);
    bool IsPossibleMovement(int pX, int pY, int pPiece, int pRot);
    void StorePiece(int pX, int pY, int pPiece, int pRot);
    int DeletePossibleLines();
    bool IsGameOver();

private:
    enum
    {
        POS_FREE,
        POS_FILLED
    };

    int mBoard[BOARD_WIDTH][BOARD_HEIGHT];
    Pieces *mPieces;
    int mScreenHeight;

    void InitBoard();
    void DeleteLine(int pY);
};

#endif // BOARD_H
