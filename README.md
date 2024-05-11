# ECE160-Final-Project

// Maze Game in C //

Welcome to the Maze Game! This program will determine whether a user-inputted maze is solvable or not. If solvable, the program will trace out the quickest path from a given start to a given finish point. 

Input: 
The user will provide the dimensions of the maze (length and width = rows x columns), a description of the maze's interior using a grid of characters (0 for path space, anything else for wall space), and a start Point (S) and finish points (F) on the exterior walls (row x column).

Output:
If solvable, the program will output a printed maze with the path traced out (using a dot).
If unsolvable, the program will output a message indicating that the maze is impossible to solve and to enter another maze.

Upon compiling, the program will prompt the user to enter a (1) to solve a maze or (2) to generate a random maze.
After hitting 1, you the user will be prompted to enter the maze dimensions. The maze must be at least 3x3.
e.g. (15 rows x 15 columns)
15
15

Next, the user will be asked to input their own maze. This part can be quite tedious, so we've **attached a separate README.md** file called **MAZEINPUT.MD** in this repository with premade mazes for you to copy and paste to try out yourself.

Lastly, the solver will prompt you to enter a starting point (S) and a finish point (F). Make sure they are on the exterior of the maze and are in the format "2 1" for row 2, column 1.

If you select (2), you will be prompted to enter the dimensions of a maze and be given an output of two mazes. The second maze is the one you're interested in!

An external tool that inspired this project: 
https://keesiemeijer.github.io/maze-generator/#generate

**CONSTRAINTS**
This program includes two main components: maze solving and maze generation

Maze Solver:
  - The exterior walls of the maze must all be 1s.
  - Starting points must be on an exterior wall and have a boundary to enter.

Maze Generator
  - The generator only works for square mazes (n x n)
  - The generator will output two mazes, the first being an array of all 1s (n x n) and the second being the random maze that the **user is interested in**
  - The maze generator may generate impossible mazes. The generator tends to generate more solvable mazes with larger parameters (8x8+)

  **  Compilation Steps:**
gcc -o maze main.c mazeGenerator.c mazeSolver.c
./maze


