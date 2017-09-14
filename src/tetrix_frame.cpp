#include <QtGui>
#include <iostream>

#include "tetrix_frame.h"

//Initialize the color table
const QRgb TetrixFrame::colorTable[8] = {
        0X000000, 0xFE0000, 0x00FF00, 0x0000FE,
        0xFFFF01, 0x07FBFF, 0xFF6632, 0xFF00FF
    };

TetrixFrame::TetrixFrame(QWidget *parent)
    : QFrame(parent)
{
    //Set the style and focus policy
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);

    //Set background image
    setStyleSheet("background-image: url(background.bmp);");

    //Initialize the game
    isStarted = false;
    clearFrame();

    //Initialize the next block
    nextBlock.setRandomShape();
}

QSize TetrixFrame::sizeHint() const
{
    //Calculate the size of main frame
    return QSize(FrameWidth * squareWidth + frameWidth() * 2,
                 FrameHeight * squareHeight + frameWidth() * 2);
}

void TetrixFrame::start()
{
    //Start the game
    isStarted = true;
    isWaiting = false;
    score = 0;
    level = 1;
    clearFrame();

    //Emit signals to initialize the score and level
    emit scoreChanged(score);
    emit levelChanged(level);

    //Generate new block and start the timer
    newBlock();
    timer.start(timeInterval(), this);
}

void TetrixFrame::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    //Define the painter
    QPainter painter(this);

    //Use the contents rectangle to calculate the coordinates 
    QRect rect = contentsRect();
    int frameTop = rect.bottom() - FrameHeight * squareHeight;

    //Paint the dropped tetrix block 
    for (int i = 0; i < FrameWidth; ++i) {
        for (int j = 0; j < FrameHeight; ++j) {
            TetrixShape shape = shapeAt(i, j);
            if (shape != NoShape)
                drawSquare(painter, rect.left() + i * squareWidth,
                           frameTop + j * squareHeight, shape);
        }
    }

    //Paint the current tetrix block
    if (curBlock.shape() != NoShape) {
        for (int i = 0; i < 4; ++i) {
            int x = curX + curBlock.x(i);
            int y = curY + curBlock.y(i);
            drawSquare(painter, rect.left() + x * squareWidth,
                       frameTop + y * squareHeight,
                       curBlock.shape());
        }
    }
}

void TetrixFrame::keyPressEvent(QKeyEvent *event)
{
	//Up for start(restart)
	if (event->key() == Qt::Key_Up) start();

	//If the game is end, do not response to the key press
	if (!isStarted) return;

    //Read the key pressed
    switch (event->key()) {
    //Left for moving left
    case Qt::Key_Left:
        tryMove(curBlock, curX - 1, curY);
        break;
    //Right for moving right
    case Qt::Key_Right:
        tryMove(curBlock, curX + 1, curY);
        break;
    //Z for rotating right
    case Qt::Key_Z:
        tryMove(curBlock.rotateRight(), curX, curY);
        break;
    //X for rotating left
    case Qt::Key_X:
        tryMove(curBlock.rotateLeft(), curX, curY);
        break;
    //Down for moving down
    case Qt::Key_Down:
        if (!tryMove(curBlock, curX, curY + 1))
            blockDropped();
        break;
    //default, pass it to QFrame
    default:
        QFrame::keyPressEvent(event);
    }
}

void TetrixFrame::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        //If waiting after clearing lines, then generate new block
        if (isWaiting) {
            isWaiting = false;
            newBlock();
            timer.start(timeInterval(), this);
        } 
        //Else, move down the current block
        else {
            if (!tryMove(curBlock, curX, curY + 1))
                 blockDropped();
        }
    } else {
        QFrame::timerEvent(event);
    }
}

void TetrixFrame::clearFrame()
{
    //Clear the frame
    for (int i = 0; i < FrameHeight * FrameWidth; ++i)
        frame[i] = NoShape;
}

void TetrixFrame::blockDropped()
{
    //Write the current block to the dropped
    for (int i = 0; i < 4; ++i) {
        int x = curX + curBlock.x(i);
        int y = curY + curBlock.y(i);
        shapeAt(x, y) = curBlock.shape();
    }

    //Try clearing full lines
    clearFullLines();

    //If no line cleared, just generate new block
    if (!isWaiting)
        newBlock();
}

void TetrixFrame::clearFullLines()
{
    //Count the number of lines cleared
    int numFullLines = 0;

    for (int j = FrameHeight - 1; j >= 0; --j) {

        //Flag for the full line
        bool lineIsFull = true;

        //Examine whether the line is full
        for (int i = 0; i < FrameWidth; ++i) {
            if (shapeAt(i, j) == NoShape) {
                lineIsFull = false;
                break;
            }
        }

        //If the line is full
        if (lineIsFull) {
            ++numFullLines;
            //Then move down the upper part of tbe frame to cover the bottom line
            for (int k = j; k > 0; --k) {
                for (int i = 0; i < FrameWidth; ++i)
                    shapeAt(i, k) = shapeAt(i, k - 1);
            }
            //And initialize the top line
            for (int i = 0; i < FrameWidth; ++i)
                shapeAt(i, 0) = NoShape;
        }
    }

    //If at least one line is full
    if (numFullLines > 0) {

        //Calculate new score and level
        //Emit signals to change the score and level
        score += 10 * numFullLines * numFullLines;
        emit scoreChanged(score);
        if (((score / 100) + 1) > level && level != 10) {
            if (((score / 100) + 1) > 10) level = 10;
            else level = (score / 100) + 1;
            emit levelChanged(level);
        }

        //Set the timer to wait after clearing lines
        //This is for the player to notice the result of clearing lines
        timer.start(500, this);
        isWaiting = true;

        //Initialize the current block
        curBlock.setShape(NoShape);

        //Update for repaint
        update();
    }
}

void TetrixFrame::newBlock()
{
    //Replace the current tetrix block by the new one and generate new random next tetrix block
    curBlock = nextBlock;
    nextBlock.setRandomShape();

    //Emit signal for showing the next block in the next frame
    emit showNextBlock(nextBlock);

    //Set the initial position of current block
    curX = FrameWidth / 2 - 1;
    curY = 2;


    //Flag for the empty line
    bool lineIsEmpty = true;


    //Examine whether the first two lines are full
    for (int j = 1; j >= 0; --j) {
        for (int i = 0; i < FrameWidth; ++i) {
            if (shapeAt(i, j) != NoShape) {
                lineIsEmpty = false;
                break;
            }
        }
    }

    //If the first two line is not empty or filed to place the new tetrix block in the initial position
    //Then the game ends
    if (!lineIsEmpty || !tryMove(curBlock, curX, curY)) {

        //If game ends, stop the timer
        curBlock.setShape(NoShape);
        timer.stop();
        isStarted = false;

        //Shoe a message box to remind the player
        QMessageBox gameoverReminder;
        gameoverReminder.setText("Game Over");
        gameoverReminder.exec();
    }
}

bool TetrixFrame::tryMove(const TetrixBlock &newBlock, int newX, int newY)
{
    //Examine the move
    for (int i = 0; i < 4; ++i) {

        //Calculate the new coordinates of each square
        int x = newX + newBlock.x(i);
        int y = newY + newBlock.y(i);

        //Check whether it is out of range and already occupied
        if (x < 0 || x >= FrameWidth || y < 0 || y >= FrameHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }

    //If the move is legitimate, set the new block and new position
    curBlock = newBlock;
    curX = newX;
    curY = newY;

    //Update for repaint
    update();

    return true;
}

void TetrixFrame::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
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