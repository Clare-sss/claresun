#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
    // Your code here. Make sure to replace following line with your own code.
    int width, height,a;
    FILE * unsolvedmaze;
    unsolvedmaze = fopen(fileName, "r");
    maze_t * maze = malloc(sizeof(maze_t));

    fscanf(unsolvedmaze,"%d %d", &(maze->width), &(maze->height));
    width = maze->width;
    height = maze->height;
    maze->cells = malloc(sizeof(char*)*height);
    for(a = 0; a < height; a++)
    {
        maze->cells[a] = malloc(sizeof(char)*width);
    }


        char ch;
        int i,j;
      for(i = 0; i < height; i++)
      {
          for(j = 0; j < width; j++)
          {
                ch = fgetc(unsolvedmaze);
                if(ch == '\n')
                    ch = fgetc(unsolvedmaze);
                if(ch == WALL)
                    maze->cells[i][j] = WALL;
                if(ch == EMPTY)
                    maze->cells[i][j] = EMPTY;
                if(ch == START)
                    maze->cells[i][j] = START;
                    maze->startColumn = i;
                    maze->startRow = j;
                if(ch == END)
                    maze->cells[i][j] = END;
                    maze->endColumn = i;
                    maze->endRow = j;
                if(ch == PATH)
                    maze->cells[i][j] = PATH;
                if(ch == VISITED)
                    maze->cells[i][j] = VISITED;
          }
      }
        fclose(unsolvedmaze);
    return NULL;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
    // Your code here.
    int a;
    for(a = 0; a < maze->height; a++)
    {
        free(maze->cells[a]);
    }
        free(maze->cells);
        free(maze);


}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
    // Your code here.
    int i,j;
    for(i=0; i<maze->height; i++)
    {
      for(j =0; j<maze->width; j++)
      {
        fprintf( stdout, "%c" , maze->cells[i][j]);
        if(j == maze->width-1)
        fprintf(stdout, "\n");
      }
        fprintf(stdout, "\n");
    }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */
int solveMazeDFS(maze_t * maze, int col, int row)
{
    // Your code here. Make sure to replace following line with your own code.


      //base case

      //if current place is the wall or outside the wall, return false
    if(col < 0 || col >= maze->width || row < 0 || row >= maze->height)
    return 0;

    //if the current place is not an empty place, return false
    if(maze->cells[row][col] != EMPTY && maze->cells[row][col] != END && maze->cells[row][col] != START)
    return 0;

    //if we have reached the end, return true
    if(maze->cells[row][col] == END)
    return 1;


    //recursive case

    //mark this place as part of the solution path
    maze->cells[row][col] = PATH;

    if(solveMazeDFS(maze, col+1, row) == 1)   //checking the right
    return 1;
    if(solveMazeDFS(maze, col-1, row) == 1)   //checking the left
    return 1;
    if(solveMazeDFS(maze, col, row-1) == 1)   //checking down
    return 1;
    if(solveMazeDFS(maze, col, row+1) == 1)   //checking up
    return 1;


    //if none of the future path is valid, mark current place as visited and return false
    maze->cells[row][col] = VISITED;
    return 0;
}
