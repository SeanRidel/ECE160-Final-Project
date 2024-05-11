#include <stdio.h>
#include <stdlib.h>

void GenerateMazeFunction();
void MazeSolver();
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
