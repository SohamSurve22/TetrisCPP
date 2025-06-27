//
// Created by soham on 26/06/2025.
//

#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <cstdio>
#include "Game.h"

Game::Game(Board *pBoard, Pieces *pPieces, IO *pIO, int pScreenHeight)
{
    mBoard = pBoard;
    mPieces = pPieces;
    mIO = pIO;
    mScreenHeight = pScreenHeight;
    mScore = 0;
    mLinesCleared = 0;

    InitGame();
}

int Game::GetRand(int pA, int pB)
{
    return rand() % (pB - pA + 1) + pA;
}

void Game::InitGame()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // Current Piece
    mPiece = GetRand(0, 6);
    mRotation = GetRand(0, 3);
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInit(mPiece, mRotation);
    mPosY = mPieces->GetYInit(mPiece, mRotation);
}

void Game::CreateNewPiece()
{
    // Generate new random piece
    mPiece = GetRand(0, 6);
    mRotation = GetRand(0, 3);
    mPosX = (BOARD_WIDTH / 2) + mPieces->GetXInit(mPiece, mRotation);
    mPosY = mPieces->GetYInit(mPiece, mRotation);
}

void Game::DrawPiece(int pX, int pY, int pPiece, int pRotation)
{
    color mColor;

    int mPixelsX = mBoard->GetXPosInPixel(pX);
    int mPixelsY = mBoard->GetYPosInPixels(pY);

    // Different colors for different piece types
    color pieceColors[] = {CYAN, YELLOW, MAGENTA, GREEN, BLACK, BLUE, DARK_GRAY};

    for (int i = 0; i < PIECE_BLOCKS; i++)
    {
        for (int j = 0; j < PIECE_BLOCKS; j++)
        {
            int block = mPieces->GetBlockType(pPiece, pRotation, j, i);

            if (block == 1 || block == 2)
            {
                mColor = pieceColors[pPiece % 7]; // Use piece type to determine color

                // Draw the block without borders
                mIO->DrawRectangle(
                    mPixelsX + i * BLOCK_SIZE,
                    mPixelsY + j * BLOCK_SIZE,
                    mPixelsX + i * BLOCK_SIZE + BLOCK_SIZE - 1,
                    mPixelsY + j * BLOCK_SIZE + BLOCK_SIZE - 1,
                    mColor);
            }
        }
    }
}

void Game::DrawBoard()
{
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1;
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT);

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (!mBoard->IsFreeBlock(i, j))
            {
                mIO->DrawRectangle(
                    mX1 + i * BLOCK_SIZE,
                    mY + j * BLOCK_SIZE,
                    mX1 + i * BLOCK_SIZE + BLOCK_SIZE - 1,
                    mY + j * BLOCK_SIZE + BLOCK_SIZE - 1,
                    RED);
            }
        }
    }
}

void Game::DrawScene()
{
    DrawBorder();
    DrawBoard();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    DrawUI();
}

void Game::DrawBorder()
{
    int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 3;
    int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2)) + 2;
    int mY = mScreenHeight - (BLOCK_SIZE * BOARD_HEIGHT) - 3;
    int mY2 = mScreenHeight - 2;

    // Draw game board border
    mIO->DrawRectangle(mX1 - 2, mY - 2, mX1, mY2, BLACK);
    mIO->DrawRectangle(mX2, mY - 2, mX2 + 2, mY2, BLACK);
    mIO->DrawRectangle(mX1 - 2, mY2, mX2 + 2, mY2 + 2, BLACK);
}

void Game::DrawUI()
{
    // Print game status to console
    std::cout << "\r\x1b[K" << "TETRIS - Points: " << mScore << " | Lines: " << mLinesCleared << std::flush;

    // Position UI elements at bottom right of screen
    int bottomRightX = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2)) + 20;
    int bottomY = mScreenHeight - 180; // Start from bottom and work up

    // LINES section at bottom
    DrawRetroTextBox(bottomRightX, bottomY, 100, 50, "LINES", GREEN);
    DrawRetroNumber(bottomRightX + 10, bottomY + 25, mLinesCleared, WHITE);
    bottomY -= 60;

    // POINTS section above lines
    DrawRetroTextBox(bottomRightX, bottomY, 100, 50, "POINTS", YELLOW);
    DrawRetroNumber(bottomRightX + 10, bottomY + 25, mScore, WHITE);
}

void Game::DrawRetroTextBox(int x, int y, int width, int height, const char *label, color borderColor)
{
    // Draw retro-style text box with double border and background
    mIO->DrawRectangle(x, y, x + width, y + height, BLACK);                       // Outer border
    mIO->DrawRectangle(x + 1, y + 1, x + width - 1, y + height - 1, borderColor); // Border
    mIO->DrawRectangle(x + 2, y + 2, x + width - 2, y + height - 2, BLACK);       // Background for content

    // Draw label area at top
    mIO->DrawRectangle(x + 2, y + 2, x + width - 2, y + 12, borderColor);
}

void Game::DrawRetroNumber(int x, int y, int number, color digitColor)
{
    // Convert number to string and draw each digit as small rectangles
    char numStr[16];
    sprintf(numStr, "%d", number);

    int digitX = x;
    for (int i = 0; numStr[i] != '\0'; i++)
    {
        DrawRetroDigit(digitX, y, numStr[i] - '0', digitColor);
        digitX += 8; // Space between digits
    }
}

void Game::DrawRetroDigit(int x, int y, int digit, color digitColor)
{
    // Simple 7-segment style digit representation using rectangles
    // Each digit is 6x9 pixels
    bool segments[10][7] = {
        {1, 1, 1, 0, 1, 1, 1}, // 0
        {0, 0, 1, 0, 0, 1, 0}, // 1
        {1, 0, 1, 1, 1, 0, 1}, // 2
        {1, 0, 1, 1, 0, 1, 1}, // 3
        {0, 1, 1, 1, 0, 1, 0}, // 4
        {1, 1, 0, 1, 0, 1, 1}, // 5
        {1, 1, 0, 1, 1, 1, 1}, // 6
        {1, 0, 1, 0, 0, 1, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };

    if (digit < 0 || digit > 9)
        return;

    // Draw 7-segment display style
    if (segments[digit][0])
        mIO->DrawRectangle(x + 1, y, x + 5, y + 1, digitColor); // top
    if (segments[digit][1])
        mIO->DrawRectangle(x, y + 1, x + 1, y + 4, digitColor); // top-left
    if (segments[digit][2])
        mIO->DrawRectangle(x + 5, y + 1, x + 6, y + 4, digitColor); // top-right
    if (segments[digit][3])
        mIO->DrawRectangle(x + 1, y + 4, x + 5, y + 5, digitColor); // middle
    if (segments[digit][4])
        mIO->DrawRectangle(x, y + 5, x + 1, y + 8, digitColor); // bottom-left
    if (segments[digit][5])
        mIO->DrawRectangle(x + 5, y + 5, x + 6, y + 8, digitColor); // bottom-right
    if (segments[digit][6])
        mIO->DrawRectangle(x + 1, y + 8, x + 5, y + 9, digitColor); // bottom
}

void Game::AddScore(int pLinesCleared)
{
    // Tetris guideline scoring
    static const int baseScores[] = {0, 40, 100, 300, 1200};
    if (pLinesCleared >= 1 && pLinesCleared <= 4)
        mScore += baseScores[pLinesCleared];

    mLinesCleared += pLinesCleared;
}

void Game::ShowGameOver()
{
    // Print Game Over message to console
    std::cout << "\n\n=================================\n";
    std::cout << "           GAME OVER!           \n";
    std::cout << "=================================\n";
    std::cout << "Final Points: " << mScore << "\n";
    std::cout << "Lines Cleared: " << mLinesCleared << "\n";
    std::cout << "=================================\n";
    std::cout << "Press any key to exit...\n";
    std::cout.flush();

    mIO->ClearScreen();

    const int centerX = 320;
    const int centerY = 240;

    // Main Game Over window with retro border
    mIO->DrawRectangle(centerX - 200, centerY - 150, centerX + 200, centerY + 150, BLACK);
    mIO->DrawRectangle(centerX - 195, centerY - 145, centerX + 195, centerY + 145, WHITE);
    mIO->DrawRectangle(centerX - 190, centerY - 140, centerX + 190, centerY + 140, BLACK);

    // Draw "GAME OVER" text using pixel blocks
    DrawGameOverText(centerX - 120, centerY - 120);

    // Final stats with retro styling - simplified layout
    DrawRetroTextBox(centerX - 150, centerY - 40, 120, 35, "POINTS", YELLOW);
    DrawRetroNumber(centerX - 100, centerY - 20, mScore, YELLOW);

    DrawRetroTextBox(centerX - 150, centerY + 10, 120, 35, "LINES", GREEN);
    DrawRetroNumber(centerX - 100, centerY + 30, mLinesCleared, GREEN);

    // Exit instruction
    DrawRetroTextBox(centerX - 100, centerY + 70, 200, 25, "PRESS ANY KEY", WHITE);

    mIO->UpdateScreen();
}

void Game::DrawGameOverText(int x, int y)
{
    // Draw "GAME OVER" in retro pixel style
    // G
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x, y + 20, x + 20, y + 25, WHITE);
    mIO->DrawRectangle(x + 15, y + 10, x + 20, y + 20, WHITE);
    mIO->DrawRectangle(x + 10, y + 10, x + 20, y + 15, WHITE);

    // A
    x += 25;
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x + 15, y, x + 20, y + 25, WHITE);
    mIO->DrawRectangle(x, y + 10, x + 20, y + 15, WHITE);

    // M
    x += 25;
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x + 15, y, x + 20, y + 25, WHITE);
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x + 7, y + 5, x + 12, y + 15, WHITE);

    // E
    x += 25;
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x, y + 10, x + 15, y + 15, WHITE);
    mIO->DrawRectangle(x, y + 20, x + 20, y + 25, WHITE);

    // Space before OVER
    x += 35;

    // O
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x + 15, y, x + 20, y + 25, WHITE);
    mIO->DrawRectangle(x, y + 20, x + 20, y + 25, WHITE);

    // V
    x += 25;
    mIO->DrawRectangle(x, y, x + 5, y + 15, WHITE);
    mIO->DrawRectangle(x + 15, y, x + 20, y + 15, WHITE);
    mIO->DrawRectangle(x + 5, y + 15, x + 15, y + 25, WHITE);

    // E
    x += 25;
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x, y + 10, x + 15, y + 15, WHITE);
    mIO->DrawRectangle(x, y + 20, x + 20, y + 25, WHITE);

    // R
    x += 25;
    mIO->DrawRectangle(x, y, x + 5, y + 25, WHITE);
    mIO->DrawRectangle(x, y, x + 20, y + 5, WHITE);
    mIO->DrawRectangle(x + 15, y, x + 20, y + 15, WHITE);
    mIO->DrawRectangle(x, y + 10, x + 15, y + 15, WHITE);
    mIO->DrawRectangle(x + 10, y + 15, x + 20, y + 25, WHITE);
}

int Game::GetWaitTime() const
{
    // Fixed wait time since we removed level progression
    return BASE_WAIT_TIME;
}
