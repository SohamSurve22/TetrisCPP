//
// Created by soham on 26/06/2025.
//

#ifndef GAME_H
#define GAME_H

#include "Pieces.h"
#include "Board.h"
#include "IO.h"
#include <ctime>

#define BASE_WAIT_TIME 700

class Game {
public:
    Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight);

    void DrawScene();
    void CreateNewPiece();
    void ShowGameOver();
    void AddScore(int pLinesCleared);
    int GetScore() const { return mScore; }
    int GetLinesCleared() const { return mLinesCleared; }
    int GetWaitTime() const;

    int mPosX, mPosY;             // Position of current piece
    int mPiece, mRotation;        // Type and rotation of current piece

private:
    int mScreenHeight;
    int mScore;
    int mLinesCleared;

    // Next piece info
    int mNextPiece, mNextRotation;

    Board *mBoard;
    Pieces *mPieces;
    IO *mIO;

    int GetRand(int pA, int pB);
    void InitGame();
    void DrawPiece(int pX, int pY, int pPiece, int pRotation);
    void DrawBoard();
    void DrawUI();
    void DrawBorder();
    void DrawNextPieceBox();
    void DrawNextPiece();
    void DrawRetroTextBox(int x, int y, int width, int height, const char* label, color borderColor);
    void DrawRetroNumber(int x, int y, int number, color digitColor);
    void DrawRetroDigit(int x, int y, int digit, color digitColor);
    void DrawGameOverText(int x, int y);
};

#endif // GAME_H
