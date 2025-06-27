============================================================
                          TetrisCPP
         Classic Tetris Game in Modern C++ with SDL2
============================================================


DESCRIPTION
-----------
TetrisCPP is a modern implementation of the classic Tetris game, 
written in C++ using the SDL2 graphics library. This project was 
developed as a learning exercise to deepen understanding of 
C++ object-oriented design SDL2, and game development 
fundamentals.

There is a lot of room for improvement but this project was
made as implementation of basic C++ knowledge.

FEATURES
--------
- Traditional Tetris gameplay with falling blocks
- Object-oriented architecture for modular development
- Randomized tetromino generation
- Collision detection and line-clearing logic
- SDL2-based rendering and input handling
- Cross-platform code (Windows, Linux)

TECHNOLOGIES USED
-----------------
- Language: C++17
- Graphics Library: SDL2

REQUIREMENTS
------------
To build and run the project, ensure the following are installed:

1. C++17 or newer
2. SDL2 library

LINUX/MAC SETUP
---------------
Install SDL2:
    sudo apt-get install libsdl2-dev

Compile and run:
    g++ -std=c++17 -o tetris main.cpp -lSDL2
    ./tetris

WINDOWS SETUP (MSYS2 + MinGW)
-----------------------------
Install SDL2:
    pacman -S mingw-w64-x86_64-SDL2

Compile and run:
    g++ -std=c++17 -IC:/msys64/mingw64/include/SDL2 ^
        -LC:/msys64/mingw64/lib -o tetris.exe main.cpp ^
        -lmingw32 -lSDL2main -lSDL2

    ./tetris.exe

(Adjust paths if SDL2 is installed elsewhere)


CONTROLS
--------
Arrow Keys  = Move left/right/down
Up Arrow    = Rotate piece
Space Bar   = Hard drop (if implemented)
'Z' Key     = Block Rotation
Esc         = Exit game

TO-DO / FUTURE IMPROVEMENTS
----------------------------
- Show Upcoming Block
- Pause/resume functionality
- UI enhancements
- Sound effects and background music
- High score saving

CREDITS & REFERENCES
--------------------
- SDL2 Documentation: https://wiki.libsdl.org/
- Tetris logic inspiration: https://www.gamedev.net/
- Special Thanks to Javier López
  Here is the complete manuel
(https://javilop.com/gamedev/tetris-tutorial-in-c-platform-independent-focused-in-game-logic-for-beginners/)

AUTHOR
------
Name: Soham Surve  
GitHub: https://github.com/SohamSurve22  
LinkedIn: https://www.linkedin.com/in/soham-surve/  



