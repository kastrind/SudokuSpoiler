/*Kastrinakis Dimitrios
  Graduate of CSD University of Crete.
  June 2010*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudokucellmanagement.h"

#define MAX_IPAE 500 //maximum iterations per algorithm execution

#define FAILURE0 "Cannot open file.\n"
#define FAILURE1 "Invalid command. For help, type 'sudospoil help'.\n"
#define USAGE "To generate a sudoku puzzle, type 'sudospoil generate'.\nTo solve a given puzzle, type 'sudospoil solve filename',\nwhere filename stands for the file where a given sudoku puzzle is stored.\nTo save the results in a file, provide its filename at the end of your command.\n"
#define WAIT "Please wait...\n"

int readSudoku(cell_t *cells_p[][], char *filename);
int solveSudoku(cell_t *cells_p[][]);

int main(int argc, char *argv[]) {

	cell_t *cells_p[NINE][NINE];
	cell_t cells[NINE][NINE];

	/*system time as seed for rand()*/
	long ltime = time(NULL);
	int utime = (unsigned int)ltime/2;
	srand(utime);
	/*system time as seed for rand()*/

	time_t start, end;
	FILE *out_fp;

	if((argc>=2)&&(!strcmp(argv[1], "generate"))) {
	        printf(WAIT);
	        start = time(NULL);
		initCells(cells, cells_p);
		while(!solveSudoku(cells_p)) initCells(cells, cells_p);
		if((argv[2])&&((out_fp=fopen(argv[2], "a"))!=NULL)){printCells(cells_p, out_fp);fclose(out_fp);}
		else printCells(cells_p, stdout);
		end = time(NULL);
		printf("Sudoku generation required %d seconds.\n", difftime(end, start));
	}
	else if((argc>=3)&&(!strcmp(argv[1], "solve"))) {
                printf(WAIT);
                start = time(NULL);
		do {
		  initCells(cells, cells_p);
		  if(!readSudoku(cells_p, argv[2])) exit(0);
		}while(!solveSudoku(cells_p));
		if((argv[3])&&((out_fp=fopen(argv[3], "a"))!=NULL)){printCells(cells_p, out_fp);fclose(out_fp);}
		else printCells(cells_p, stdout);
		end = time(NULL);
		printf("Sudoku solution required %d seconds.\n", (int)difftime(end, start));
	}
	else if((argc==2)&&(!strcmp(argv[1], "help"))) printf(USAGE);
	else printf(FAILURE1);

	return 0;
}

/*Solves a given sudoku puzzle, or generates one from a given empty(initialized) grid.*/
int solveSudoku(cell_t *cells_p[NINE][NINE]) {
	int random;
	int row, col;
	int cnt_exit = 0;
	int breakloops=0;
	int tmp;
	int i;

	for(row=0; row<NINE;row++) {
	  for(col=0;col<NINE;col++) {
	    if(cells_p[row][col]->val==0) {
	      cnt_exit++;
	      if (cnt_exit>MAX_IPAE) return 0;
		while(1){
		  while(1){
		    random = rand()%9;
		    if(cells_p[row][col]->candidates[random]!='x') break;
		    if(!strcmp(cells_p[row][col]->candidates, "xxxxxxxxx")){
		      breakloops = 1;
		      break;
		    }
		  }
		  if(breakloops) {
		    if(col>=1){col=0;}else if((col==0)&&(row>0)){row--;col=0;}
		    for(i=0;i<NINE;i++) {
		      if((cells_p[row][i]->is_given==0)) {
		        tmp = deleteNum(cells_p, row, i);
			if (tmp>0) cells_p[row][i]->candidates[tmp-1] = 'x';
		      }
		    }
		    col--;
		    breakloops=0;
		    break;
		  }
		  insertNum(cells_p, row, col, random+1);
		  if ((isValidRow(row, cells_p)==0)||
		      (isValidColumn(col, cells_p)==0)||
		      (isValidRegion(row, col, cells_p)==0)) deleteNum(cells_p, row, col);
		  else {restrictCandidates(cells_p, row, col); break;}
		}
	    }
	  }
	}
	return 1;
}

/*Reads a sudoku puzzle from file*/
int readSudoku(cell_t *cells_p[NINE][NINE], char *filename){
	FILE *fp;
	char ch;
	if((fp = fopen(filename, "r"))==NULL){
		printf(FAILURE0);
		return 0;
	}
	int row=0, col=0, num;
	while((ch = fgetc(fp))!=EOF) {
		num = atoi(&ch);
		if(!isdigit(ch)&&(ch!='\n')){fclose(fp); return 0;}
		if(num!=0) {
			insertNum(cells_p, row, col, num);
			restrictCandidates(cells_p, row,col);
			markAsGiven(cells_p, row, col, 1);
		}
		col++;
		if(col==TEN){col=0;row++;}
		if((row==8)&&(col==NINE)){fclose(fp); return 1;}
	}

	fclose(fp);
	return -1;
}

