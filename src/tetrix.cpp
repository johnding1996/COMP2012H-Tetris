#include <QtGui>
#include <stdlib.h>

#include "tetrix_window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //Main window as an instance of tetirx window class
    TetrixWindow window;
    window.show();

    //Initialize the random number generator
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    
    return app.exec();
}