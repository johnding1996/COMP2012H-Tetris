#include <QtGui>

#include "tetrix_frame.h"
#include "tetrix_nextframe.h"
#include "tetrix_window.h"

TetrixWindow::TetrixWindow()
{
    //Initialize the frames and labels
    mainFrame = new TetrixFrame;
    nextFrame = new TetrixNextFrame;

    scoreLabel = new QLabel("Score:");
    levelLabel = new QLabel("Level:");
    score = new QLabel("0");
    level = new QLabel("0");

    //Set the style of labels
    scoreLabel->setStyleSheet("font-weight: bold");
    levelLabel->setStyleSheet("font-weight: bold");
    score->setStyleSheet("font-weight: bold");
    level->setStyleSheet("font-weight: bold");

    //Fix the size of frames
    mainFrame->setFixedSize(mainFrame->sizeHint());
    nextFrame->setFixedSize(nextFrame->sizeHint());

    //Connect the signals and slots
    connect(mainFrame, SIGNAL(scoreChanged(int)), score, SLOT(setNum(int)));
    connect(mainFrame, SIGNAL(levelChanged(int)), level, SLOT(setNum(int)));
    connect(mainFrame, SIGNAL(showNextBlock(TetrixBlock)), nextFrame, SLOT(showNextBlock(TetrixBlock)));

    //Set the layout
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mainFrame, 0, 0, 5, 1);
    layout->addWidget(nextFrame, 0, 1, 3, 2);
    layout->addWidget(levelLabel, 3, 1);
    layout->addWidget(scoreLabel, 4, 1);
    layout->addWidget(level, 3, 2);
    layout->addWidget(score, 4, 2);
    setLayout(layout);

    //Set the title and size
    setWindowTitle(tr("Tetrix"));
    resize(340, 420);
}