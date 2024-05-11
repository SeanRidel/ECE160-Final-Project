#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void MazeSolver();
typedef struct Marker {
    int posX;
    int posY;
    char posVal;
} M;

struct Tile {
    int index;
    int posX;
    int posY;
    char val;
};

struct Maze {
    int rows;
    int cols;
    // stores memory address refrencing begging of Tiles array
    struct Tile *gridTiles;
    // marker for current position
    M marker;
};

// sudo random generator that produces a 0/1
char randos() {

    char val=' ';

    int seed = rand();
    //printf("%d\n",seed);

    if((seed%2)==0){
        return '1';
    }

    return '0';
}

void getSizeFromUser (struct Maze *mazePtr) {
    int rows,cols = 0;

    printf("Enter the number of rows\n");
    scanf("%d", &rows);

    printf("Enter the number of cols\n");
    scanf("%d", &cols);

    mazePtr->rows=rows;
    mazePtr->cols=cols;
}

void printMaze (struct Maze *mazePtr) {

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

void initMaze ( struct Maze *mazePtr ) {

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

void radomizeMaze ( struct Maze *mazePtr ) {

    struct Tile *gridTilesPtr = mazePtr->gridTiles;

    int i,j;
    for(i=1;i<=(mazePtr->rows);i++){
        for(j=1;j<=(mazePtr->cols);j++){
            if((i!=1 && i!=mazePtr->rows) && (j!=1 && j!=mazePtr->cols)){
                gridTilesPtr->val=randos();
            }
            gridTilesPtr++;
        }
    }
}

void getStartingPos(struct Maze *mazePtr){

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
    /////////////////////////////Select Starting/////////////////////////////////////////
}
