#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int startRow, startColumn, finishRow, finishColumn, currentRow, currentColumn, nextRow, nextColumn, direction, height, length, top, bottom, left, right, finished;

void GenerateMazeFunction();
void directionLeft(int top, int bottom, int left);
void directionRight(int top, int bottom, int right);
void directionUp(int top, int left, int right);
void directionDown(int bottom, int left, int right);
void dimensions();
void makeMazeAndCheckDimension(char maze[height][length]);
void checkWalls(char maze[height][length]);
void startAndEnd(char maze[height][length]);
void printMaze2(char maze[height][length]);
void startDirection(char maze[height][length]);
void solveMaze(char maze[height][length]);
void surroundings(char maze[height][length]);
void nextSpace();
void checkNextSpace(char maze[height][length]);

void dimensions()
{
    printf("How many rows is the maze?(3-150)"); //sets height to user input
    scanf("%i", &height);
    printf("How many columns is the maze?(3-150)"); //sets length to user input
    scanf("%i", &length);

    if (height < 3 || height > 150 || length < 3 || length > 150) //makes sure the height and length are valid
    {
        printf("Invalid maze dimensions. Please enter values between 3 and 150.\n");
        exit(0);
    }
}

void makeMazeAndCheckDimensions(char maze[height][length])
{
    printf("Now type out your maze using an array of characters. A 0 would be a path space and anything else is a wall space. Make sure all of your exterior walls aren't 0, you will input the start and finish space after. When finish typing your last line (the bottom exterior wall), press Enter.\n");
    char oneLine[22651];
    int c, i = 0, index = 0;

    while (1) //takes the user input into one long array until the expected number of characters are met
    {
        c = getchar();
        if (c == '\n' && i == 0)
        {
            continue;
        }
        if (index == height * (length + 1) - 1) {
            break;
        }
        oneLine[i++] = c;
        index++;
    }
    oneLine[i] = '\0';
    if (strlen(oneLine) != (length + 1) * height - 1) //checks to make sure the user didn't input too little characters by ending the file
    {
        printf("The number of inputs do not match the dimensions specified before.\n");
        exit(0);
    }

    int ll, nl;
    nl = ll = 0;
    index = 0;
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < length; column++)
        {
            if(oneLine[index] == '\n') //checks if the number of characters before each new line is the proper length
            {
                ++nl;
                if(ll != length)
                {
                    printf("Your maze does not match your parameters, please try again.");
                    exit(0);
                }
                ll = 0;
                ++index;
                --column;
            }
            else
            {
                if(oneLine[index] == '0') //if character is 0, its a blank space
                {
                    maze[row][column] = ' ';
                    ++ll;
                    ++index;
                }
                else
                {
                    maze[row][column] = 'X'; //if character is anything else, its a wall space
                    ++ll;
                    ++index;
                }
            }
        }
    }
    if (nl + 1 != height) //makes sure the number of lines matches the height
    {
        printf("Your maze does not match your parameters, please try again2.");
        exit(0);
    }
}

void checkWalls(char maze[height][length]) //checks to see if the all the exterior walls indeed all wall spaces
{
    for(int i = 0; i < length; i++)
    {
        if(maze[0][i] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again.");
            exit(0);
        }
    }
    for(int i = 0; i < length; i++)
    {
        if(maze[height - 1][i] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again.");
            exit(0);
        }
    }
    for(int i = 0; i < height; i++)
    {
        if(maze[i][0] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again.");
            exit(0);
        }
    }
    for(int i = 0; i < height; i++)
    {
        if(maze[i][length - 1] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again.");
            exit(0);
        }
    }
}

void startAndEnd(char maze[height][length])
{
    do
    {
        printf("Pick a starting row and column, it must to on an exterior wall.\n"); //makes starting space, makes sure it is on exterior wall
        scanf("%i %i", &startRow, &startColumn);
    } while (startRow != 1 && startRow != height && startColumn != 1 && startColumn != length);
    do
    {
        printf("Pick a finish row and column, it must be on an exterior wall and cannot be the same as the starting space.\n"); //males finish space, makes sure it is on exterior wall and isn't the same as the start
        scanf("%i %i", &finishRow, &finishColumn);
    } while ((finishRow != 1 && finishRow != height && finishColumn != 1 && finishColumn != length) || (finishRow == startRow && finishColumn == startColumn));
    --startRow;
    --finishRow;
    --startColumn;
    --finishColumn;
    maze[startRow][startColumn] = 'S';
    maze[finishRow][finishColumn] = 'F';
    currentRow = startRow;
    currentColumn = startColumn;
}

void printMaze2(char maze[height][length]) //prints the maze
{
    for (int k = 0; k < height; k++)
    {
        for (int j = 0; j < length; j++)
        {
            printf("%c ", maze[k][j]);
        }
        printf("\n");
    }
}

void startDirection(char maze[height][length]) //determines the start direction based on which exterior wall the staring point is at
{
    if(startRow == 0)
    {
        direction = 2;
        if(maze[startRow+1][startColumn] == 'X')
        {
            printf("This maze is impossible.\n");
            exit(0);
        }
    }
    if (startRow == height - 1)
    {
        direction = 0;
        if(maze[startRow-1][startColumn] == 'X')
        {
            printf("This maze is impossible.\n");
            exit(0);
        }

    }
    if (startColumn == 0)
    {
        direction = 1;
        if(maze[startRow][startColumn+1] == 'X')
        {
            printf("This maze is impossible.\n");
            exit(0);
        }

    }
    if (startColumn == length - 1)
    {
        direction = 3;
        if(maze[startRow][startColumn-1] == 'X')
        {
            printf("This maze is impossible.\n");
            exit(0);
        }
    }
}

void surroundings(char maze[height][length]) //checks the sorrounding tiles to see if they are walls or not
{
    top = bottom = left = right = 0;
    if (direction != 0)
    {
        if (maze[currentRow + 1][currentColumn] == 'X')
        {
            bottom = 1;
        }
    }
    if (direction != 2)
    {
        if (maze[currentRow - 1][currentColumn] == 'X')
        {
            top = 1;
        }
    }
    if (direction != 1)
    {
        if (maze[currentRow][currentColumn - 1] == 'X')
        {
            left = 1;
        }
    }
    if (direction != 3)
    {
        if (maze[currentRow][currentColumn + 1] == 'X')
        {
            right = 1;
        }
    }
}

void nextSpace() //based on the surrounding walls, the next space is determined
{
    if(direction == 0)
    {
        nextColumn = currentColumn;
        nextRow = currentRow - 1;
    }
    if(direction == 1)
    {
        nextRow = currentRow;
        nextColumn = currentColumn + 1;
    }
    if(direction == 2)
    {
        nextColumn = currentColumn;
        nextRow = currentRow + 1;
    }
    if(direction == 3)
    {
        nextRow = currentRow;
        nextColumn = currentColumn - 1;
    }
}

void checkNextSpace(char maze[height][length]) //based on the next space, the code does different things
{
    if(maze[nextRow][nextColumn] == 'F') //If 'F', the maze has been solved
    {
        printf("The maze has been solved, here is the path.\n");
        finished = 0;
        for (int k = 0; k < height; k++)
        {
            for (int j = 0; j < length; j++)
            {
                printf("%c ", maze[k][j]);
            }
            printf("\n");
        }
        exit(0);
    }
    else
    {
        if(maze[nextRow][nextColumn] == '.') //If '.', the program is going backwards through the maze so it should delete the path it was just on
        {
            maze[currentRow][currentColumn] = ' ';
            currentRow = nextRow;
            currentColumn = nextColumn;
        }
        else
        {
            if(maze[nextRow][nextColumn] == 'S') //If 'S', the programs has looped through the entire maze without encountering 'F' so maze is impossible
            {
                printf("This maze is impossible.\n");
                exit(0);
            }
            else
            {
                currentColumn = nextColumn;
                currentRow = nextRow;
                maze[currentRow][currentColumn] = '.';
            }
        }
    }
}

void solveMaze(char maze[height][length]) //determines which function to run based on the surroundings
{
    int finished = 1;
    while (finished)
    {
        surroundings(maze);
        if(direction == 0)
        {
            directionUp(top, left, right);
        }
        else
        {
            if(direction == 1)
            {
                directionRight(top, bottom, right);
            }
            else
            {
                if(direction == 2)
                {
                    directionDown(bottom, left, right);
                }
                else
                {
                    directionLeft(top, bottom, left);
                }
            }
        }
        nextSpace();
        checkNextSpace(maze);
    }
}

void GenerateMazeFunction()
{
    dimensions();
    char maze[height][length];
    makeMazeAndCheckDimensions(maze);
    checkWalls(maze);
    startAndEnd(maze);
    printMaze2(maze);
    startDirection(maze);
    solveMaze(maze);
}

void directionUp(int top, int left, int right)
{
    if(!top && !left && right)
    {
        direction = 0;
    }
    if(!top && left && !right)
    {
        direction = 1;
    }
    if(!top && left && right)
    {
        direction = 0;
    }
    if(top && !left && !right)
    {
        direction = 1;
    }
    if(top && !left && right)
    {
        direction = 3;
    }
    if(top && left && !right)
    {
        direction = 1;
    }
    if(top && left && right)
    {
        direction = 2;
    }
}

void directionRight(int top, int bottom, int right)
{
    if(!top && !bottom && right)
    {
        direction = 2;
    }
    if(!top && bottom && !right)
    {
        direction = 1;
    }
    if(!top && bottom && right)
    {
        direction = 0;
    }
    if(top && !bottom && !right)
    {
        direction = 2;
    }
    if(top && !bottom && right)
    {
        direction = 2;
    }
    if(top && bottom && !right)
    {
        direction = 1;
    }
    if(top && bottom && right)
    {
        direction = 3;
    }
}

void directionDown(int bottom, int left, int right)
{
    if(!bottom && !left && right)
    {
        direction = 3;
    }
    if(!bottom && left && !right)
    {
        direction = 2;
    }
    if(!bottom && left && right)
    {
        direction = 2;
    }
    if(bottom && !left && !right)
    {
        direction = 3;
    }
    if(bottom && !left && right)
    {
        direction = 3;
    }
    if(bottom && left && !right)
    {
        direction = 1;
    }
    if(bottom && left && right)
    {
        direction = 0;
    }
}

void directionLeft(int top, int bottom, int left)
{
    if(!top && !bottom && left)
    {
        direction = 0;
    }
    if(!top && bottom && !left)
    {
        direction = 0;
    }
    if(!top && bottom && left)
    {
        direction = 0;
    }
    if(top && !bottom && !left)
    {
        direction = 3;
    }
    if(top && !bottom && left)
    {
        direction = 2;
    }
    if(top && bottom && !left)
    {
        direction = 3;
    }
    if(top && bottom && left)
    {
        direction = 1;
    }
}

