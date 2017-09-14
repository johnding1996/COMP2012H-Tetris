#ifndef TETRIX_NEXTFRAME
#define TETRIX_NEXTFRAME
#include <QFrame>

#include "tetrix_block.h"

class TetrixNextFrame : public QFrame
{
    Q_OBJECT

public:
    TetrixNextFrame(QWidget *parent = 0);

    //Fix the size of tetrix frame by sizeHint function
    //Accordingly, set fixed size in the tetrix window class
    QSize sizeHint() const;

public slots:
    //Slots for showing the next tetrix block
	void showNextBlock(TetrixBlock block);

protected:
	//Event for painting after updates
    void paintEvent(QPaintEvent *event);

private:
	//Initialize the size of next frame, unit in square
	enum { nextFrameWidth = 5, nextFrameHeight = 6 };

    //Color table for drawing eight types of blocks
	static const QRgb colorTable[8];

	//Draw a single square
    //Building block for all drawing processes
	void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

	//Private variable for storing the next block
	TetrixBlock nextBlock;
};

#endif
