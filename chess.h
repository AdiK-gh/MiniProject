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

#ifndef __CH_CHESS_H__
#define __CH_CHESS_H__

#include"tree.h"

//Macros for initializing of figures
#define fig_init(fig, typ, val, pos, mov, multi) \
	(fig).type = (char)(typ); \
	(fig).value = (int)(val); \
	(fig).position = (char)(pos); \
	(fig).cmove = (char)(mov); \
	(fig).multiply = (char)(multi)

#define figset(b, f) ((b)[(int)(f)->position].fig != NULL || \
	(b)[(int)(f)->position].value == CBORDER || \
	(f)->position < 0 || (f)->position > 119) ? \
	(b)[(int)(f)->position].fig : \
	((b)[(int)(f)->position].fig = f)

#define errprint() if (cerror!=NOERR) printerror()

typedef int player;

//structure describing the piece
typedef struct cfig{
	char type;	//the type of the figure
	int value;	//its value
	char position;	//current or latest position
	char cmove;
	char multiply;	//if multiple steps are taken
}cfig;

typedef struct cfield{
	cfig *fig;
	char value;
	int danger; //whether the field is safe or not
}cfield;

typedef struct cboard{
	cfig white[16]; //for white pieces
	cfig black[16]; //for black pieces
	cfield board[120]; //chessboard
	char cmove;
	int move;
	int check;
	
	player wp;
	player bp;
	player pl;
	
	int cost;
	int wcost;
	int bcost;
	
	tree *node;
}cboard;

typedef enum{
	NOERR, NOMEM, POINTERNULL, ILLEGAL, ENDOF
}enumerror;

extern enumerror cerror;

extern cboard *initboard(cboard *board);

extern void doneboard(cboard *board);

extern void startgame(cboard *board);

extern inline cfig *cfigmove(cfield board[], char src, char target, int flag);

extern void undomove(cboard *board);

#endif
