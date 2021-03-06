/*   This a simple version of the arcade game tron
   Copyright (C) 2015  Aditya Karamchandani
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
   
*/

#include<stdio.h>
#include<stdlib.h>

#include"io.h"
#include"chess.h"
#include"gen.h"

char movestr[MAXMOV + 1];

char *getmove(char *src, char *trg){
	cerror = NOERR;
	*src = *trg = 0;

	//fetch commands and tests
	fgets(movestr, MAXMOV, stdin);
	if(feof(stdin)!=0) {
		cerror = ENDOF;
		return NULL;
	}

	//input analysis
	switch(movestr[0]) {
		//blank line
		case '\0':
			return NULL;
			break;
		//its a command
		case '\\':
			//returns a pointer to the beginning of the string commands
			return (movestr+1);
			break;
		default:
			//tests the limits of the source array
			if (movestr[0] < 'a' || movestr[0] > 'h' ||
					movestr[1] < '1' || movestr[1]> '8'){
				cerror = ILLEGAL;
				return NULL;
			}
			//calculation of the index fields for the specified source coordinate
			*src = movestr[0]-'a'+1 + (movestr[1]-'0'+1)*10;

			//tests the limits of the destination fields
			if (movestr[2] < 'a' || movestr[3] > 'h' || movestr[3] < '1' || movestr[3] > '8'){
				cerror = ILLEGAL;
				return NULL;
			}
			//index calculations for the entering the target coordinates
			*trg = movestr[2]-'a'+1 + (movestr[3]-'0'+1)*10;
			break;
	}

	return NULL;
}

void printbfp(cboard *board){
	
	int i = 0, j = 0, count = 0;

	cerror = NOERR;

	if(board == NULL){
		cerror = POINTERNULL;
		return;
	}

	//printing chessboard
	printf("\nCounter: %d\n", board->move);
	printf("    a    b    c    d    e    f    g    h\n");
	printf("-------------------------------------------\n");
	for(j = 90; j > 10; j -= 10){
		printf("%d|", (j/10) - 1);
		for(i = 1; i < 9; i++)
			if(board->board[j+i].fig != NULL){
				printf("%3d |", (int)board->board[j+i].fig->type);
				if((int)board->board[j + i].fig->type == 6 || (int)board->board[j + i].fig->type == -6)
					count++;
				}
			else{
				printf("    |");
			}
		printf("%d\n", (j/10) -1);
		printf("-------------------------------------------\n");
	}
	printf("    a    b    c    d    e    f    g    h\n");
	if(count != 2){
		printf("GAME OVER !!!!!!!!\n GO HOME !\n");
		exit(0);
	}
}

void printmoves(cboard* board){
	cmove *mve = NULL;

	if(board == NULL || board->node == NULL || board->node->first == NULL || board->node->data == NULL){
		cerror = POINTERNULL;
		return;
	}

	board->node->actual = board->node->first;
	while(board->node->actual != NULL){
		mve = (cmove*)(board->node->actual->data);
		printf("\nF%d,S%d,T%d,C%d,", board->board[(int)mve->src].fig->type, mve->src, mve->trg, mve->cost);
		if(mve->take != NULL){
			printf("take%d; ", mve->take->type);
		}
		else
			printf("take0; ");
		board->node->actual = board->node->actual->next;
	}
	putchar('\n');
	board->node->actual = board->node->first;
}

void printcentable(cboard *board){
	int i = 0, j = 0;

	cerror = NOERR;
	if(board == NULL){
		cerror = POINTERNULL;
		return;
	}

	putchar('\n');
	for(j = 90; j > 10; j -= 10){
		for(i = 1; i < 9; i++)
			printf("%2d", (int)board->board[j+i].value);
		putchar('\n');
	}
	putchar('\n');
}

void printfigval(cboard *board){
	int i = 0, j = 0;

	cerror = NOERR;
	if(board == NULL){
		cerror = POINTERNULL;
		return;
	}

	putchar('\n');
	for(j = 90; j > 10; j -= 10){
		for(i = 1; i < 9; i++)
			(board->board[j+i].fig != NULL) ?
				printf("%5d", (int)board->board[j+i].fig->value) :
				printf("     ");
		putchar('\n');
	}
	putchar('\n');
}

void figprint(cboard *board){
	int i=0;

	cerror = NOERR;
	if(board == NULL){
		cerror = POINTERNULL;
		return;
	}

	//listing of the figures in the game
	putchar('\n');
	for(i = 0; i < 16; i++) {
		printf("white: %d\n", (int)board->white[i].type);
		printf("black: %d\n", (int)board->black[i].type);
	}
	putchar('\n');	
}

void printerror(void){
	if(cerror == ENDOF) {
		cerror = NOERR;
		return;
	}

	printf("ERROR: ");
	switch(cerror) {
		case NOMEM:
			printf("can not allocate enough memmory\n");
			break;
		case POINTERNULL:
			printf("reference pointer is null\n");
			break;
		case ILLEGAL:
			printf("illegal move\n");
			break;
		default:
			printf("no errors\n");
			break;
	}
}
