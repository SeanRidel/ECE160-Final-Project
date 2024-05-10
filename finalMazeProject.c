// HEHE //

// Maze Game //
// The Maze Solver requires the exterior walls to be all 1s //
// Starting points MUST be on an exterior wall and cannot interface with boundaries (need a place to go) //

//  The Maze Generator will only work for square mazes (n x n)  // 
// Take the second maze as the final output, may generate unsolvable mazes //

///////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
void GenerateMazeFunction(); 
void MazeSolver(); 

typedef struct Marker 
{
    int posX;
    int posY;
    char posVal;
} M;

struct Tile 
{
    int index;
    int posX;
    int posY;
    char val;  
};

struct Maze 
{
    int rows;
    int cols; // stores memory address refrencing begging of Tiles array
    struct Tile *gridTiles; // marker for current position
    M marker;   
};

// sudo random generator that produces a 0/1
char randos() 
{
    char val=' ';
    int seed = rand();
    //printf("%d\n",seed); //ignore, for testing //

    if((seed%2)==0)
    {
        return '1';
    }
    return '0';
}

void getSizeFromUser (struct Maze *mazePtr) 
{
    int rows,cols = 0;
    
    printf("Enter the number of rows\n");
    scanf("%d", &rows);
    
    printf("Enter the number of cols\n");
    scanf("%d", &cols);
    
    mazePtr->rows=rows;
    mazePtr->cols=cols;
}

void printMaze (struct Maze *mazePtr) 
{
    struct Tile *gridTilesPtr = mazePtr->gridTiles;

    int i;
    // print maze to screen
    for(i=0;i<(mazePtr->rows*mazePtr->cols);i++){
        printf("%c",gridTilesPtr->val);
        gridTilesPtr++;
        
        if((gridTilesPtr->index%mazePtr->rows)==0){
            printf("\n");
        }   
    }
}

void initMaze ( struct Maze *mazePtr ) 
{
    struct Tile *gridTilesPtr = mazePtr->gridTiles;

    int i,j,index=0;

    for(i=0;i<mazePtr->rows;i++){
        for(j=0;j<mazePtr->cols;j++) {
            gridTilesPtr->index=index;
            gridTilesPtr->posX=i;
            gridTilesPtr->posY=j;
            gridTilesPtr->val='1';
            gridTilesPtr++;
            index++;
        }
    }
}

void radomizeMaze ( struct Maze *mazePtr ) 
{
    struct Tile *gridTilesPtr = mazePtr->gridTiles;
    
    int i,j;
    for(i=1;i<=(mazePtr->rows);i++)
    {
        for(j=1;j<=(mazePtr->cols);j++)
        {
            if((i!=1 && i!=mazePtr->rows) && (j!=1 && j!=mazePtr->cols))
            {
                gridTilesPtr->val=randos();
            }
            gridTilesPtr++;
        }
    }
}

void getStartingPos(struct Maze *mazePtr)
{
    printf("Enter starting (x) coordinate position:\n");
    scanf("%d", &mazePtr->marker.posX);
    
    printf("Enter starting (y) coordinate position:\n");
    scanf("%d", &mazePtr->marker.posY);
}

void MazeSolver()
{
// init the random generator
time_t t;
srand((unsigned) time(&t));
// initialize maze structure
struct Maze gridMaze = { 0, 0, 0 , { 0 , 0 , '1'} };
// create a Maze struct pointer and assign it to address of gridMaze struct
struct Maze *gridMazePtr=&gridMaze;
// user grid size select
getSizeFromUser(gridMazePtr);
// create a pointer and malloc for size of tiles in maze
gridMaze.gridTiles = malloc((gridMaze.rows*gridMaze.cols)*sizeof(struct Tile));
// fill (init) grid Tiles array with 1's
initMaze(gridMazePtr);
// print maze
printMaze(gridMazePtr);
//////////////////////////random///////////////////////////////////////////
// spacer
printf("\n");
// randomize our gride tiles with '1' or '0'
radomizeMaze(gridMazePtr);
////////////////////////////////////////////////////////////////////////////////
// print maze
printMaze(gridMazePtr);
/////////////////////////////Select Starting////////////////////////////////////////////
}

int main() 
{
    int choice;
    printf("Would you like to solve a maze (1) or generate a random maze? (2) \n");
    scanf("%d", &choice);

    if (choice == 1)
    {
         GenerateMazeFunction(); // Sean Solver
    }
    else 
    {
         MazeSolver(); // AJ generator
    }
    
    return 0;
}

/* -----------------------------------------------------------------  */

int startRow, startColumn, finishRow, finishColumn, currentRow, currentColumn, nextRow, nextColumn, direction, height, length, top, bottom, left, right, finished;

void directionLeft(int top, int bottom, int left);
void directionRight(int top, int bottom, int right);
void directionUp(int top, int left, int right);
void directionDown(int bottom, int left, int right);
void dimensions();
void makeMazeAndCheckDimension(char maze[height][length]);
void checkWalls(char maze[height][length]);
void startAndEnd(char maze[height][length]);
void printMaze2(char maze[height][length]);
void startDirection();
void solveMaze(char maze[height][length]);
void surroundings(char maze[height][length]);
void nextSpace();
void checkNextSpace(char maze[height][length]);

void dimensions()
{
    printf("How many rows is the maze?(3-150)");
    scanf("%i", &height);
    printf("How many columns is the maze?(3-150)");
    scanf("%i", &length);

    if (height < 3 || height > 150 || length < 3 || length > 150) {
        printf("Invalid maze dimensions. Please enter values between 3 and 150.\n");
        exit(0);
    }
}

void makeMazeAndCheckDimensions(char maze[height][length])
{
    printf("Now type out your maze using an array of characters. A 0 would be a path space and anything else is a wall space. Make sure all of your exterior walls aren't 0, you will input the start and finish space after. When finish typing your last line (the bottom exterior wall), press Enter.\n");
    char oneLine[22651];
    int c, i = 0, index = 0;

    while (1) {
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
    if (strlen(oneLine) != (length + 1) * height - 1)
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
            if(oneLine[index] == '\n')
            {
                ++nl;
                if(ll != length)
                {
                    printf("Your maze does not match your parameters, please try again1.");
                    exit(0);
                }
                ll = 0;
                ++index;
                --column;
            }
            else
            {
                if(oneLine[index] == '0')
                {
                    maze[row][column] = ' ';
                    ++ll;
                    ++index;
                }
                else
                {
                    maze[row][column] = 'X';
                    ++ll;
                    ++index;
                }
            }
        }
    }
    if (nl + 1 != height)
    {
        printf("Your maze does not match your parameters, please try again2.");
        exit(0);
    }
}

void checkWalls(char maze[height][length])
{
    for(int i = 0; i < length; i++)
    {
        if(maze[0][i] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again1.");
            exit(0);
        }
    }
    for(int i = 0; i < length; i++)
    {
        if(maze[height - 1][i] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again2.");
            exit(0);
        }
    }
    for(int i = 0; i < height; i++)
    {
        if(maze[i][0] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again3.");
            exit(0);
        }
    }
    for(int i = 0; i < height; i++)
    {
        if(maze[i][length - 1] != 'X')
        {
            printf("One of your exterior walls isn't a wall space, try again4.");
            exit(0);
        }
    }
}

void startAndEnd(char maze[height][length])
{
    do
    {
        printf("Pick a starting row and column, it must to on an exterior wall.\n");
        scanf("%i %i", &startRow, &startColumn);
    } while (startRow != 1 && startRow != height && startColumn != 1 && startColumn != length);
    do
    {
        printf("Pick a finish row and column, it must be on an exterior wall and cannot be the same as the starting space.\n");
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

void printMaze2(char maze[height][length])
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

void startDirection()
{
    if(startRow == 0)
    {
        direction = 2;
    }
    if (startRow == height - 1)
    {
        direction = 0;
    }
    if (startColumn == 0)
    {
        direction = 1;
    }
    if (startColumn == length - 1)
    {
        direction = 3;
    }
}

void surroundings(char maze[height][length])
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

void nextSpace()
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

void checkNextSpace(char maze[height][length])
{
    if(maze[nextRow][nextColumn] == 'F')
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
        if(maze[nextRow][nextColumn] == '.')
        {
            maze[currentRow][currentColumn] = ' ';
            currentRow = nextRow;
            currentColumn = nextColumn;
        }
        else
        {
            if(maze[nextRow][nextColumn] == 'S')
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

void solveMaze(char maze[height][length])
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
    startDirection();
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

