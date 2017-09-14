# Tetris
Project 2 for COMP2012H, 2016 Fall, HKUST

A simple realization of classic tetris game

  
## How-to-compile-and-run
```
$ qmake
$ make
$ ./bin/tetris
```
  
## Technical Details
```
Source file tree:
    Tetris
    |
    |--include
    |  |--tetrix_block.h
    |  |--tetrix_frame.h
    |  |--tetrix_nextframe.h
    |  |--tetrix_window.h
    |
    |--src
    |  |--tetrix.cpp
    |  |--tetrix_block.cpp
    |  |--tetrix_frame.cpp
    |  |--tetris_nextframe.cpp
    |  |--tetris_window.cpp
    |
    |--tetris.pro
```

  
## Design of the project
This program is a simple tetris game with one main frame for game, one side frame for displying the next tetris block and two labels for displying the score and level seperately.

We first seperate the GUI with other parts of the program by defining a TetrixWindow class. Then the two frame are implemented as the TetrixFram and the TetrixNextFrame class. The TetrixFrame class handle the game logic, timing, painting and controling events. It needs another TetrixBlock class to help instantialize the single tetrix block. So there are four classes in total and one seperate main program.

The main program provides a entrance of the whole program, in which we define a instance of TetrixWindow and call the show() function. We also initialize the qrand generater by local time.

The TetrixWindow class handle the GUI and connects the signals in the TetrixFrame class with the corresponding slots in the two labels and the TetrixNextFrame class.

The TetrixFrame class handle the game logic, timing, painting and controling events. During the game, three important variables store the information about the dropped blocks, the current block and the next block seperately. The game logic and control focus on the current block by functions like trymove() and blockDropped(). They also process the dropped blocks and the next block by functions like newBlock() and clearFullLines. The timing events are simply calling to move down the blocks by one line. The keypressing events are handled carlefully by a switch-case statement. The painting events are handled by repeatly calling a drawSquare() function to draw a single square.

The TetrixNextFrame class paints the next tetris block. It uses nearly the same painting methods. The only thing that we concern is to paint the block at the center of the frame. This is done by some auxiliary functions in the TetrixBlock class to return the size and relatve coordinates information.

The TetrixBlock class store the shape of seven different types of tetris blocks. It also handle the tetrix block rotation by simple coordinates transform.
