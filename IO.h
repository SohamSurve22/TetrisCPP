//
// Created by soham on 26/06/2025.
//

#ifndef _IO_
#define _IO_

#ifdef _WIN32
#include "SDL/include/SDL.h"
#include "SDL/SDL_GfxPrimitives/SDL_gfxPrimitives.h"
#else
#include <SDL/SDL.h>
#include "SDL/SDL_gfxPrimitives.h"
#endif

// Color enumeration used for drawing
enum color
{
    BLACK,
    RED,
    GREEN,
    BLUE,
    CYAN,
    MAGENTA,
    YELLOW,
    WHITE,
    DARK_GRAY,
    COLOR_MAX
};

class IO
{
public:
    IO();

    void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC);
    void ClearScreen();
    void UpdateScreen();

    int InitGraph();
    int GetScreenHeight();

    int Pollkey();
    int Getkey();
    int IsKeyDown(int pKey);

private:
    SDL_Surface *mScreen;      // SDL rendering surface
    Uint32 mColors[COLOR_MAX]; // Color lookup table

    void InitializeColors(); // Helper to initialize color mapping
};

#endif // _IO_
