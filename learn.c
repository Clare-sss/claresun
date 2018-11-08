//Intro: Our program solves the sudoku puzzle by using recursive backtracking method.
//We used three functions to check columns, rows and 3*3 zones seperately and return to the is valid fucntion
//to solve the sudoku puzzle.

//partners: yanmiao2,jw22

#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
      for(int a=0; a<9; a++)
        {
          if(sudoku[i][a] == val)
          return 1;
          else
          return 0;
        }
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  for(int a=0; a<9; a++)
    {
      if(sudoku[a][j] == val)
      return 1;
      else
      return 0;
    }
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
int a,b;
    a = (i/3)*3;
    b = (j/3)*3;
    for(int c=0; c<3; c++)
    {
      for(int d =0; d<3; d++)
      {
        if(sudoku[a+c][b+d] == val)
        return 1;
        else
        return 0;
      }
    }
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
if(is_val_in_col(val, j, sudoku) == 0
&& is_val_in_row(val, i, sudoku) == 0
&& is_val_in_3x3_zone(val, i, j, sudoku) == 0)
return 1;
else
return 0;

  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  //BEG TODO.


  //base case
int i,j, flag = 0;
for(i=0; i<9; i++)
{
  for(j=0 ;j<9; j++)
  {
    if(sudoku[i][j] == 0)
    {
      flag = 1;
      break;
    }
  }
  if(flag == 1)
  break;
}


if(flag == 0)
{
  return 1;
}else
{
  int flag2 = 0;
  for(int a=0; a<9; a++)
  {
    for(int b=0 ;b<9; b++)
    {
        if(sudoku[a][b] == 0)
        {
          i = a;
          j = b;
          flag2 = 1;
          break;
        }

    }
    if(flag2 == 1)
    break;
  }
}





//recursive case
for(int num =1; num <10; num++)
{
    if(is_val_valid(num, i, j, sudoku) == 1)
    sudoku[i][j] = num;
    else
    return 0;
    if(solve_sudoku(sudoku) == 1)
    return 1;
    else
    {
      sudoku[i][j] = 0;
    }
}


return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
