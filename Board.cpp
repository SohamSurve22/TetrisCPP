//
// Created by soham on 26/06/2025.
//

#include "Board.h"

Board::Board(Pieces *pPieces, int pScreenHeight) {
    mPieces = pPieces;
    mScreenHeight = pScreenHeight;
    InitBoard();
}

void Board::InitBoard() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        for (int j = 0; j < BOARD_HEIGHT; j++) {
            mBoard[i][j] = POS_FREE;
        }
    }
}

void Board::StorePiece(int pX, int pY, int pPiece, int pRot) {
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {
            if (mPieces->GetBlockType(pPiece, pRot, j2, i2) != 0) {
                mBoard[i1][j1] = POS_FILLED;
            }
        }
    }
}

bool Board::IsGameOver() {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (mBoard[i][0] == POS_FILLED) {
            return true;
        }
    }
    return false;  // FIX: ensure return on all paths
}

void Board::DeleteLine(int pY) {
    for (int j = pY; j > 0; j--) {
        for (int i = 0; i < BOARD_WIDTH; i++) {
            mBoard[i][j] = mBoard[i][j - 1];
        }
    }

    // Clear top line after shift
    for (int i = 0; i < BOARD_WIDTH; i++) {
        mBoard[i][0] = POS_FREE;
    }
}

int Board::DeletePossibleLines() {
    int linesCleared = 0;
    
    for (int j = 0; j < BOARD_HEIGHT; j++) {
        int i = 0;
        while (i < BOARD_WIDTH && mBoard[i][j] == POS_FILLED) {
            i++;
        }

        if (i == BOARD_WIDTH) {
            DeleteLine(j);
            linesCleared++;
            j--; // Check same line again since we shifted down
        }
    }
    
    return linesCleared;
}

bool Board::IsFreeBlock(int pX, int pY) {
    return mBoard[pX][pY] == POS_FREE;
}

int Board::GetXPosInPixel(int pPos) {
    return ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::GetYPosInPixels(int pPos) {
    return ((mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT)) + (pPos * BLOCK_SIZE));
}

bool Board::IsPossibleMovement(int pX, int pY, int pPiece, int pRotation) {
    for (int i1 = pX, i2 = 0; i1 < pX + PIECE_BLOCKS; i1++, i2++) {
        for (int j1 = pY, j2 = 0; j1 < pY + PIECE_BLOCKS; j1++, j2++) {

            if (i1 < 0 || i1 >= BOARD_WIDTH || j1 >= BOARD_HEIGHT) {
                if (mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0)
                    return false;
            }

            if (j1 >= 0 && mPieces->GetBlockType(pPiece, pRotation, j2, i2) != 0) {
                if (!IsFreeBlock(i1, j1)) {
                    return false;
                }
            }
        }
    }

    return true;
}
