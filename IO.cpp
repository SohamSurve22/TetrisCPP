//
// Created by soham on 26/06/2025.
//

#include "IO.h"
#include <cstdlib>
#include <cstdio>

// Constructor
IO::IO()
{
    mScreen = nullptr;
    InitializeColors();
    InitGraph();
}

// Initialize the SDL video subsystem and graphics mode
int IO::InitGraph()
{
    const SDL_VideoInfo *info;
    Uint8 video_bpp;
    Uint32 videoFlags;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
        return 1;
    }

    atexit(SDL_Quit);

    info = SDL_GetVideoInfo();
    video_bpp = (info->vfmt->BitsPerPixel > 8) ? info->vfmt->BitsPerPixel : 16;
    videoFlags = SDL_SWSURFACE | SDL_DOUBLEBUF;

    mScreen = SDL_SetVideoMode(650 , 650, video_bpp, videoFlags);
    if (mScreen == nullptr)
    {
        fprintf(stderr, "Couldn't set 640x480 video mode: %s\n", SDL_GetError());
        return 2;
    }

    return 0;
}

// Fill color mapping
void IO::InitializeColors()
{
    mColors[BLACK] = 0x000000FF;
    mColors[RED] = 0xFF0000FF;
    mColors[GREEN] = 0x00FF00FF;
    mColors[BLUE] = 0x0000FFFF;
    mColors[CYAN] = 0x00FFFFFF;
    mColors[MAGENTA] = 0xFF00FFFF;
    mColors[YELLOW] = 0xFFFF00FF;
    mColors[WHITE] = 0xFFFFFFFF;
    mColors[DARK_GRAY]= 0xFFA9A9A9;
}

// Clears the entire screen with white
void IO::ClearScreen()
{
    boxColor(mScreen, 0, 0, mScreen->w - 1, mScreen->h - 1, mColors[WHITE]);
}

// Draw rectangle using SDL_gfx
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC)
{
    boxColor(mScreen, pX1, pY1, pX2, pY2, mColors[pC]);
}

// Updates the visible screen (flips buffer)
void IO::UpdateScreen()
{
    SDL_Flip(mScreen);
}

// Returns height of the screen
int IO::GetScreenHeight()
{
    return mScreen->h;
}

// Polls for key events (non-blocking)
int IO::Pollkey()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            return event.key.keysym.sym;
        }
        else if (event.type == SDL_QUIT)
        {
            exit(0);
        }
    }
    return -1; // No key
}

// Waits for key press (blocking)
int IO::Getkey()
{
    SDL_Event event;
    while (true)
    {
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN)
            return event.key.keysym.sym;
        else if (event.type == SDL_QUIT)
            exit(0);
    }
}

// Check if specific key is currently down
int IO::IsKeyDown(int pKey)
{
    SDL_PumpEvents();
    Uint8 *keyState = SDL_GetKeyState(nullptr);
    return keyState[pKey];
}
