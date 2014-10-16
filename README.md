sudoku-solution
===============
A simple C++ program to solve a sudoku problem.
* no exceptions handling, no input check right now
* no GUI, this is a command line demo

To run this:
* write a file about input data, 0 means the position is blank. The input file looks like this
```
000000081
000000000
040820006
500390000
008407900
000052003
700089020
924100008
050000000
```
* two command line parameters, the second is a directory path, where you put your input file in
* run the program and it will output solutions into the directory path you specified in the command line
