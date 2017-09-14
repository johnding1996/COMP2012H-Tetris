#include <QtCore>

#include "tetrix_block.h"

//Initialize the tetrix block coordinate table
const int TetrixBlock::blockCoords[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, 1 },  { 0, 0 },   { 0, -1 },   { 0, -2 } },
        { { -1, 1 },  { -1, 0 },   { 0, 1 },  { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, 1 },  { 0, 0 },   { 1, 0 },   { 1, -1 } },
        { { 0, -1 },   { 0, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, 1 }, { 0, 1 },  { 0, 0 },   { 0, -1 } },
        { { -1, 0 },  { 0, 0 },  { 0, -1 },   { 1, 0 } }
    };

TetrixBlock::TetrixBlock() 
{
    //Initialize the shape and size information
    setShape(NoShape);
    findMinMax();
}

void TetrixBlock::setRandomShape()
{
    //Set random shape by qrand and mod 7
    setShape(TetrixShape(qrand() % 7 + 1));
}

void TetrixBlock::setShape(TetrixShape shape)
{
    //Set the shape by copying the coordinate table
    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = blockCoords[shape][i][j];
    }
    pieceShape = shape;

    //Update the size information
    findMinMax();
}

void TetrixBlock::findMinMax()
{
    //Calculate minX, minY, maxX, maxY
    minX = coords[0][0];
    maxX = coords[0][0];
    for (int i = 1; i < 4; ++i)
        if (minX > coords[i][0]) minX = coords[i][0];
    for (int i = 1; i < 4; ++i)
        if (maxX < coords[i][0]) maxX = coords[i][0];

    minY = coords[0][1];
    maxY = coords[0][1];
    for (int i = 1; i < 4; ++i)
        if (minY > coords[i][1]) minY = coords[i][1];
    for (int i = 1; i < 4; ++i)
        if (maxY < coords[i][1]) maxY = coords[i][1];

}

TetrixBlock TetrixBlock::rotateLeft() const
{
    //Rotate by returning a new instance of tetrix block
    //Note that for the same class, we can call the private member
    TetrixBlock newBlock;
    newBlock.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        newBlock.setX(i, y(i));
        newBlock.setY(i, -x(i));
    }

    //Update the size information
    newBlock.findMinMax();
    return newBlock;
}

TetrixBlock TetrixBlock::rotateRight() const
{
    //Rotate by returning a new instance of tetrix block
    //Note that for the same class, we can call the private member
    TetrixBlock newBlock;
    newBlock.pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        newBlock.setX(i, -y(i));
        newBlock.setY(i, x(i));
    }

    //Update the size information
    newBlock.findMinMax();
    return newBlock;
}