#include <QtGui>

#include "tetrix_nextframe.h"

//Initialize the color table
const QRgb TetrixNextFrame::colorTable[8] = {
        0X000000, 0xFE0000, 0x00FF00, 0x0000FE,
        0xFFFF01, 0x07FBFF, 0xFF6632, 0xFF00FF
    };

TetrixNextFrame::TetrixNextFrame(QWidget *parent)
    : QFrame(parent)
{   
    //Set the style and focus policy
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setFocusPolicy(Qt::NoFocus);

    //Initialize the next block
    nextBlock.setShape(NoShape);
}

QSize TetrixNextFrame::sizeHint() const
{
    //Calculate the size of next frame
    return QSize(nextFrameWidth * squareWidth + frameWidth() * 2,
                 nextFrameHeight * squareHeight + frameWidth() * 2);
}

void TetrixNextFrame::showNextBlock(TetrixBlock block)
{
    //Update and repaint
	nextBlock = block;
	update();
}

void TetrixNextFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    //Define the painter
    QPainter painter(this);

    //Use the contents rectangle to calculate the coordinates 
    QRect rect = contentsRect();
    int frameTop = rect.bottom() - nextFrameHeight * squareHeight;

    //Paint the next tetrix block
    //Calculate the coordinates to place the next block at the center of the next frame
    if (nextBlock.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
        	drawSquare(painter, rect.left() + (nextFrameWidth - nextBlock.width() + 2 * nextBlock.relativeX(i)) * squareWidth / 2,
        	          frameTop + (nextFrameHeight - nextBlock.height() + 2 * nextBlock.relativeY(i)) * squareHeight / 2, nextBlock.shape());
    	}
    }
}

void TetrixNextFrame::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    //Draw the squares by fillRect function
    if (shape == NoShape) return;
    QColor color = colorTable[shape];
    painter.fillRect(x + 1, y + 1, squareWidth - 2, squareHeight - 2,
                     color);

    //Draw the boundary lines to have better pictures
    painter.setPen(color.light());
    painter.drawLine(x, y + squareHeight - 1, x, y);
    painter.drawLine(x, y, x + squareWidth - 1, y);

    painter.setPen(color.dark());
    painter.drawLine(x + 1, y + squareHeight - 1,
                     x + squareWidth - 1, y + squareHeight - 1);
    painter.drawLine(x + squareWidth - 1, y + squareHeight - 1,
                     x + squareWidth - 1, y + 1);
}