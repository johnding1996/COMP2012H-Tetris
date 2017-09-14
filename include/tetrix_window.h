#ifndef TETRIX_WINDOW
#define TETRIX_WINDOW

#include <QFrame>
#include <QWidget>

class QLabel;
class TetrixFrame;
class TetrixNextFrame;

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
	//Initialize the tetrix window
    TetrixWindow();

private:
	//Declare the frames and labels
    TetrixFrame *mainFrame;
    TetrixNextFrame *nextFrame;
    QLabel *score;
    QLabel *level;

    QLabel *scoreLabel;
    QLabel *levelLabel;
};

#endif