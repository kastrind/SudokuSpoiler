/*Kastrinakis Dimitrios
  Graduate of CSD University of Crete.
  June 2010*/

#include <assert.h>
#include <stdio.h>

#define NINE 9
#define TEN 10

struct cell {
	int val;
	int is_given;
	char candidates[TEN];
};

typedef struct cell cell_t;

/*Checks whether row is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if row is not valid*/
int isValidRow(int row, cell_t *cells[][]);

/*Checks whether col is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if col is not valid*/
int isValidColumn(int col, cell_t *cells[][]);

/*Checks whether given region is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if region is not valid*/
int isValidRegion(int row, int col, cell_t *cells[][]);

/*Initializes the cells by assigning 0 to each cell, as well as a list
  of candidate numbers from 1 to 9 for each cell */
void initCells(cell_t cells[][],  cell_t *cells_p[][]);

/*Prints all cells to standard output*/
void printCells(cell_t *cells[][], FILE *fp);

/*Inserts specified number to a specified cell*/
void insertNum(cell_t *cells[][], int row, int col, int num);

/*Deletes number from specified cell and recalculates the candidate
  numbers for the respective row, column and region.
  Returns the deleted number.*/
int deleteNum(cell_t *cells[][], int row, int col);

/*Marks a cell as given (as a fact)*/
void markAsGiven(cell_t *cells[][], int row, int col, int value);

/*Restricts the candidate numbers of cells in the same row, column and region.
  Used after a valid insertion of a number.*/
void restrictCandidates(cell_t *cells[][], int row, int col);

/*Recalculates the candidates for cells in the same row, column and region.
  Called at a deletion of a number, to restore consistency of candidate numbers.*/
static void recalculateCandidates(cell_t *cells[][], int row, int col);

/*Resets the candidates of given cell to initial values (all digits become candidates)*/
static void resetCandidates(cell_t *cells[][], int row, int col);

