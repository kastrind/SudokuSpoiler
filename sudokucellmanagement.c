/*Kastrinakis Dimitrios
  Graduate of CSD University of Crete.
  June 2010*/

#include "sudokucellmanagement.h"

/*Checks whether row is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if row is not valid*/
int isValidRow(int row, cell_t *cells[NINE][NINE]){
	int y, num, counter=1;
	int invalid = 0, exist_zeros=0;
	
	while(counter<NINE) {
		num = cells[row][counter-1]->val;
		for(y=counter;y<NINE;y++) {
			if((num == cells[row][y]->val)&&(cells[row][y]->val!=0)) invalid = 1;
			if (cells[row][y]->val==0) exist_zeros = 1;
		}
		counter++;
	}
	if((!invalid)&&(!exist_zeros))	   return  1;
	else if((!invalid)&&(exist_zeros)) return -1;
	else if(invalid)		   return  0;
	assert(0);
}

/*Checks whether col is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if col is not valid*/
int isValidColumn(int col, cell_t *cells[NINE][NINE]){
	int y, num, counter=1;
	int invalid = 0, exist_zeros=0;
	
	while(counter<NINE) {
		num = cells[counter-1][col]->val;
		for(y=counter;y<NINE;y++) {
			if((num == cells[y][col]->val)&&(cells[y][col]->val!=0)) invalid = 1;
			if (cells[y][col]->val==0) exist_zeros = 1;
		}
		counter++;
	}
	if((!invalid)&&(!exist_zeros))	   return  1;
	else if((!invalid)&&(exist_zeros)) return -1;
	else if(invalid)		   return  0;
	assert(0);
}

/*Checks whether given region is valid
  returns 1 if its valid,
  returns-1 if it is valid but there is a zero (empty cell)
  returns 0 if region is not valid*/
int isValidRegion(int row, int col, cell_t *cells[NINE][NINE]){
	int temp[NINE];
	int x,y,i=0;
	if((row<=2)&&(row>=0)&&(col<=2)&&(col>=0)) {
		for(x=0; x<3; x++) {
			for(y=0; y<3; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=2)&&(col>=0)) {
		for(x=3; x<6; x++) {
			for(y=0; y<3; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=2)&&(col>=0)) {
		for(x=6; x<9; x++) {
			for(y=0; y<3; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=5)&&(col>=3)) {
		for(x=0; x<3; x++) {
			for(y=3; y<6; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=8)&&(col>=6)) {
		for(x=0; x<3; x++) {
			for(y=6; y<9; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=5)&&(col>=3)) {
		for(x=3; x<6; x++) {
			for(y=3; y<6; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=8)&&(col>=6)) {
		for(x=3; x<6; x++) {
			for(y=6; y<9; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=5)&&(col>=3)) {
		for(x=6; x<9; x++) {
			for(y=3; y<6; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=8)&&(col>=6)) {
		for(x=6; x<9; x++) {
			for(y=6; y<9; y++){temp[i++] = cells[x][y]->val;}
		}
	}
	else{assert(0);}

	int travel, num, counter=1;
	int invalid = 0, exist_zeros=0;
	
	while(counter<NINE) {
		num = temp[counter-1];
		for(travel=counter;travel<NINE;travel++) {
			if((num==temp[travel])&&(temp[travel]!=0)) invalid = 1;
			if(temp[travel]==0) exist_zeros = 1;
		}
		counter++;
	}
	if((!invalid)&&(!exist_zeros))	   return  1;
	else if((!invalid)&&(exist_zeros)) return -1;
	else if(invalid)		   return  0;
	assert(0);
}

/*Initializes the cells by assigning 0 to each cell, as well as a list
  of candidate numbers from 1 to 9 for each cell */
void initCells(cell_t cells[NINE][NINE], cell_t *cells_p[NINE][NINE]) {
	char str[TEN] = "123456789\0";
	char *str_p;
	str_p=str;
	int row, col;
	char *cand_p;

	for(row=0; row<NINE;row++) {
		for(col=0;col<NINE;col++) {
			cells_p[row][col] = &cells[row][col];
			cells_p[row][col]->val = 0;
			cells_p[row][col]->is_given=0;
			cand_p = cells_p[row][col]->candidates;
			while(*str_p) *cand_p++ = *str_p++;
			*cand_p = '\0';
			str_p = str;
		}
	}
}

/*Prints all cells to standard output*/
void printCells(cell_t *cells[NINE][NINE], FILE *fp){
	int row, col;
	for(row=0; row<NINE;row++) {
		if((row==0)||(row==3)||(row==6)) fprintf(fp, "----------------------\n");
		for(col=0;col<NINE;col++) {
			if((col==0)||(col==3)||(col==6)) fprintf(fp, "|");
			fprintf(fp, "%d ",cells[row][col]->val);
			if(col==8) fprintf(fp, "|\n");
		}
	}
	fprintf(fp, "----------------------\n");
	/*
	for(row=0; row<NINE;row++) {
		for(col=0;col<NINE;col++) {
			printf("[%s] ",cells[row][col]->candidates);
		}
		printf("\n");
	}
	for(row=0; row<NINE;row++) {
		for(col=0;col<NINE;col++) {
			printf("[%d] ",cells[row][col]->is_given);
		}
		printf("\n");
	}
	*/
	
}

/*Inserts specified number to a specified cell*/
void insertNum(cell_t *cells[NINE][NINE], int row, int col, int num) {
	if(cells[row][col]->is_given==0) cells[row][col]->val = num;
}

/*Deletes number from specified cell and updates the candidate
  numbers for the respective row, column and region.
  Returns the deleted number.*/
int deleteNum(cell_t *cells[NINE][NINE], int row, int col){
	int deleted_num, tmp_deleted_num;
	deleted_num = tmp_deleted_num = cells[row][col]->val;

	if(deleted_num==0) {return 0;}

	cells[row][col]->val = 0;

	char deleted_num_char;
	sprintf(&deleted_num_char, "%d", tmp_deleted_num);
////////////PHASE 1: RESET THE CANDIDATES
/////////////////////////////////////////
	int x, y;
	for(x=0; x<NINE; x++){
		if(cells[x][col]->is_given==0) resetCandidates(cells, x, col);
		if(cells[row][x]->is_given==0) resetCandidates(cells, row, x);
	}

	if((row<=2)&&(row>=0)&&(col<=2)&&(col>=0)) {
		for(x=0; x<3; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=2)&&(col>=0)) {
		for(x=3; x<6; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=2)&&(col>=0)) {
		for(x=6; x<9; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=5)&&(col>=3)) {
		for(x=0; x<3; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=8)&&(col>=6)) {
		for(x=0; x<3; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=5)&&(col>=3)) {
		for(x=3; x<6; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=8)&&(col>=6)) {
		for(x=3; x<6; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=5)&&(col>=3)) {
		for(x=6; x<9; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=8)&&(col>=6)) {
		for(x=6; x<9; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0) resetCandidates(cells, x, y);}
		}
	}
	else{assert(0);}
/////////PHASE 2: RECALCULATE THE CANDIDATES
////////////////////////////////////////////
	for(x=0; x<NINE; x++){
		if(cells[x][col]->is_given==0) recalculateCandidates(cells, row,col);
		if(cells[row][x]->is_given==0) recalculateCandidates(cells, row,col);
	}

	if((row<=2)&&(row>=0)&&(col<=2)&&(col>=0)) {
		for(x=0; x<3; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0) recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=2)&&(col>=0)) {
		for(x=3; x<6; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0) recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=2)&&(col>=0)) {
		for(x=6; x<9; x++) {
			for(y=0; y<3; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=5)&&(col>=3)) {
		for(x=0; x<3; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=8)&&(col>=6)) {
		for(x=0; x<3; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=5)&&(col>=3)) {
		for(x=3; x<6; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0) recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=8)&&(col>=6)) {
		for(x=3; x<6; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=5)&&(col>=3)) {
		for(x=6; x<9; x++) {
			for(y=3; y<6; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=8)&&(col>=6)) {
		for(x=6; x<9; x++) {
			for(y=6; y<9; y++){
			if(cells[x][y]->is_given==0)  recalculateCandidates(cells, row,col);}
		}
	}
	else{assert(0);}

	return deleted_num;
}

/*Marks a cell as given (as a fact)*/
void markAsGiven(cell_t *cells[NINE][NINE], int row, int col, int value){
	cells[row][col]->is_given = value;
}

/*Restricts the candidate numbers of cells in the same row, column and region.
  Used after a valid insertion of a number.*/
void restrictCandidates(cell_t *cells[NINE][NINE], int row, int col){
	int num = cells[row][col]->val;
	if (num==0) return;
	cells[row][col]->candidates[num-1] = 'x';
	int x, y;

	for(x=0; x<NINE;x++){
		cells[x][col]->candidates[num-1] = 'x';
		cells[row][x]->candidates[num-1] = 'x';
	}
	if((row<=2)&&(row>=0)&&(col<=2)&&(col>=0)) {
		for(x=0; x<3; x++) {
			for(y=0; y<3; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=2)&&(col>=0)) {
		for(x=3; x<6; x++) {
			for(y=0; y<3; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=2)&&(col>=0)) {
		for(x=6; x<9; x++) {
			for(y=0; y<3; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=5)&&(col>=3)) {
		for(x=0; x<3; x++) {
			for(y=3; y<6; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=8)&&(col>=6)) {
		for(x=0; x<3; x++) {
			for(y=6; y<9; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=5)&&(col>=3)) {
		for(x=3; x<6; x++) {
			for(y=3; y<6; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=8)&&(col>=6)) {
		for(x=3; x<6; x++) {
			for(y=6; y<9; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=5)&&(col>=3)) {
		for(x=6; x<9; x++) {
			for(y=3; y<6; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=8)&&(col>=6)) {
		for(x=6; x<9; x++) {
			for(y=6; y<9; y++){cells[x][y]->candidates[num-1] = 'x';}
		}
	}
	else{assert(0);}
}

/*Recalculates the candidates for cells in the same row, column and region.
  Called at a deletion of a number, to restore consistency of candidate numbers.*/
static void recalculateCandidates(cell_t *cells[NINE][NINE], int row, int col){
	int x, y;
	int curr_num;

	for(x=0; x<NINE; x++) {
		curr_num = cells[row][x]->val;
		if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
		curr_num = cells[x][col]->val;
		if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
	}

	if((row<=2)&&(row>=0)&&(col<=2)&&(col>=0)) {
		for(x=0; x<3; x++) {
			for(y=0; y<3; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=2)&&(col>=0)) {
		for(x=3; x<6; x++) {
			for(y=0; y<3; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=2)&&(col>=0)) {
		for(x=6; x<9; x++) {
			for(y=0; y<3; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=5)&&(col>=3)) {
		for(x=0; x<3; x++) {
			for(y=3; y<6; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=2)&&(row>=0)&&(col<=8)&&(col>=6)) {
		for(x=0; x<3; x++) {
			for(y=6; y<9; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=5)&&(col>=3)) {
		for(x=3; x<6; x++) {
			for(y=3; y<6; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=5)&&(row>=3)&&(col<=8)&&(col>=6)) {
		for(x=3; x<6; x++) {
			for(y=6; y<9; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=5)&&(col>=3)) {
		for(x=6; x<9; x++) {
			for(y=3; y<6; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else if((row<=8)&&(row>=6)&&(col<=8)&&(col>=6)) {
		for(x=6; x<9; x++) {
			for(y=6; y<9; y++){
				curr_num = cells[x][y]->val;
				if(curr_num>0) cells[row][col]->candidates[curr_num-1] = 'x';
			}
		}
	}
	else{assert(0);}
}

/*Resets the candidates of given cell to initial values (all digits become candidates)*/
static void resetCandidates(cell_t *cells[NINE][NINE], int row, int col){
	cells[row][col]->candidates[0] = '1';
	cells[row][col]->candidates[1] = '2';
	cells[row][col]->candidates[2] = '3';
	cells[row][col]->candidates[3] = '4';
	cells[row][col]->candidates[4] = '5';
	cells[row][col]->candidates[5] = '6';
	cells[row][col]->candidates[6] = '7';
	cells[row][col]->candidates[7] = '8';
	cells[row][col]->candidates[8] = '9';
}

