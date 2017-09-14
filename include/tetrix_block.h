#ifndef TETRIX_BLOCK
#define TETRIX_BLOCK

//Enumerate type of tetrix shape, NoShape represemts the empty space
enum TetrixShape { NoShape, Type1, Type2, Type3, Type4, Type5, Type6, Type7 };

//Initialize the size constants of a single square, unit in pixel
enum { squareWidth = 20, squareHeight = 20 };

class TetrixBlock
{
public:
    TetrixBlock();

    //Set the shape of this tetrix block
    void setRandomShape();
    void setShape(TetrixShape shape);

    //Inline functions for returning the properties of this tetrix block
    TetrixShape shape() const { return pieceShape; }
    int x(int index) const { return coords[index][0]; }
    int y(int index) const { return coords[index][1]; }
    int width() const { return (maxX - minX + 1); }
    int height() const { return (maxY - minY + 1); }
    int relativeX(int index) const { return (coords[index][0] - minX); }
    int relativeY(int index) const { return (coords[index][1] - minY); }

    //Rotation by return another tetrix block instance
    TetrixBlock rotateLeft() const;
    TetrixBlock rotateRight() const;

private:
    //Coordinates table of eight types of blocks
    static const int blockCoords[8][4][2];

    //Set functions for the convience of rotation processes
    void setX(int index, int x) { coords[index][0] = x; }
    void setY(int index, int y) { coords[index][1] = y; }

    //Find min and max coordinates among all squares in this tetrix block
    //Usefull for drawing in the next frame
    int minX, maxX, minY, maxY;
    void findMinMax();

    //Private variable to store the shape and coordinate table of this tetrix block
    TetrixShape pieceShape;
    int coords[4][2];
};

#endif