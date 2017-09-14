#ifndef TETRIX_FRAME
#define TETRIX_FRAME

#include <QBasicTimer>
#include <QFrame>

#include "tetrix_block.h"

class TetrixFrame : public QFrame
{
    Q_OBJECT

public:
    TetrixFrame(QWidget *parent = 0);

    //Fix the size of tetrix frame by sizeHint function
    //Accordingly, set fixed size in the tetrix window class
    QSize sizeHint() const;

    //Start(restart) the game
    void start();

signals:
    //Signals for the score and level label and the next block frame
    //Connected to the corresponding slots in the tetrix window class
    void scoreChanged(int score);
    void levelChanged(int level);
    void showNextBlock(TetrixBlock block);

protected:
    //Events for painting, keypressing and timer ticking
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

private:
    //Initialize the size of main frame, unit in square
    enum { FrameWidth = 10, FrameHeight = 20 };

    //Color table for drawing eight types of blocks
    static const QRgb colorTable[8];

    //Read the tetrix shape at certain places in the frame
    TetrixShape &shapeAt(int x, int y) { return frame[(y * FrameWidth) + x]; }

    //Calculate the time interval of the timer by level
    int timeInterval() { return (1000 - (level - 1) * 100); }

    //Clear the tetrix frame for restart
    void clearFrame();

    //Write the current block to the frame when the block is droped
    //Also call the clearFullLines function to try clearing full lines
    void blockDropped();

    //Clear the full lines and calculate the new score and level
    //Emit signals for changing the score and level
    void clearFullLines();

    //Replace the current tetrix block by the new one and generate new random next tetrix block
    //Emit signal for showing the next block in the next frame
    //Try placing the new tetrix block in the initial position, decide whether the game ends
    void newBlock();

    //Try moving the current block, if doable then move it and update, if not then return false
    bool tryMove(const TetrixBlock &newBlock, int newX, int newY);

    //Draw a single square
    //Building block for all drawing processes
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

    //Private variables
    QBasicTimer timer;
    bool isStarted;
    bool isWaiting;
    TetrixBlock curBlock;
    TetrixBlock nextBlock;
    int curX;
    int curY;
    int score;
    int level;
    TetrixShape frame[FrameWidth * FrameHeight];
};

#endif