//
// Created by soham on 25/06/2025.
//

#ifndef PIECES_H
#define PIECES_H

class Pieces {
public:

    static int GetBlockType(int pPieces, int pRot, int pX, int pY);
    static int GetXInit(int pPieces, int pRot);
    static int GetYInit(int pPieces, int pRot);
};

#endif // PIECES_H
