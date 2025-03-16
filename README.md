## Introduction
"Maximise The Score" is a strategic game between two players, Scott and Rusty, who take turns picking number balls from a table. The players aim to maximise their scores. Scott picks any ball while Rusty focuses on selecting balls with the highest sum of digits. The game alternates between rounds, with each player taking up *k* turns per round. Both players should play optimally to achieve the highest possible score.

## Key Features
### Heap As Priority Queue
The priority queue concept is used to arrange the balls according to their priorities for each player. This is implemented using a heap data structure.
| Player | Heap Property |
| :---: | :---: |
| Scott | Max heap |
| Rusty | Heap with highest sum of digits as root node |

## Usage Guide
### How To Run Program
1. Compile the program with `gcc Maximiser_Le_Score.cpp`.
2. Execute the output file with `[Output Filename] InputLeScore.txt`.

### Input Format
The `InputLeScore.txt` file contains the test cases of the game. The format is shown as below:
> First line = The number of test cases<br>
> Starting from the second line, every three lines present the details of one test case, where:
> - First line contains two integers, representing the number of balls present and the maximum number of turns allowed.
> - Second line shows the score written on each ball.
> - Third line shows the result of coin toss, determining the player that starts the game. In this prohect, "HEADS" indicates Scott starts the game while "TAILS" indicates Rusty starts the game.

Example:
```
2 // Number of test cases
3 2 // First testcase, 3 balls on the table and 2 turns max per player
1000 99 98 // Scores on each ball
TAILS // Rusty starts the game
2 1 // Second test case
5 6
HEADS
```

### Output Format
For each testcase, print scores achieved by Scott and Rusty, if the both play optimally.

## Technology Used
Language: C++

## Developer
Loo<br>
loo.workspace@gmail.com

