//
// Created by soham on 26/06/2025.
//

#include "Game.h"
#ifndef LINUX
#include <windows.h>
#endif
#include <cstdlib> // for exit

/*
==================
Main Entry Point
==================
*/

#define WAIT_TIME 500

// Platform-specific entry point
#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
    IO mIO;
    int mScreenHeight = mIO.GetScreenHeight();

    Pieces mPieces;
    Board mBoard(&mPieces, mScreenHeight);
    Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

    mGame.CreateNewPiece(); // <- Initialize the first piece
    unsigned long mTime1 = SDL_GetTicks();

    while (!mIO.IsKeyDown(SDLK_ESCAPE))
    {
        mIO.ClearScreen();
        mGame.DrawScene();
        mIO.UpdateScreen();

        int mKey = mIO.Pollkey();

        switch (mKey)
        {
        case SDLK_RIGHT:
            if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX++;
            break;

        case SDLK_LEFT:
            if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
                mGame.mPosX--;
            break;

        case SDLK_DOWN:
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
                mGame.mPosY++;
            break;

        case SDLK_SPACE:
            // Hard drop: keep falling until no longer possible
            while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
            {
                mGame.mPosY++;
            }

            // Store the piece exactly where it landed
            mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

            // Clear lines and update score/lines
            {
                int linesCleared = mBoard.DeletePossibleLines();
                mGame.AddScore(linesCleared);
            }

            // Check for game over
            if (mBoard.IsGameOver())
            {
                mGame.ShowGameOver();
                mIO.Getkey();
                exit(0);
            }

            // Create the next piece
            mGame.CreateNewPiece();
            break;

        case SDLK_z:
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
                mGame.mRotation = (mGame.mRotation + 1) % 4;
            break;
        }

        unsigned long mTime2 = SDL_GetTicks();
        if ((mTime2 - mTime1) > WAIT_TIME)
        {
            if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
            {
                mGame.mPosY++;
            }
            else
            {
                mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);
                // Clear lines and update score/lines
                {
                    int linesCleared = mBoard.DeletePossibleLines();
                    mGame.AddScore(linesCleared);
                }

                if (mBoard.IsGameOver())
                {
                    mGame.ShowGameOver();
                    mIO.Getkey();
                    exit(0);
                }

                mGame.CreateNewPiece();
            }
            mTime1 = SDL_GetTicks();
        }
    }

    return 0;
}
