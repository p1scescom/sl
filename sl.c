/*========================================
 *    sl.c: SL version 5.0
 *	Copyright 1993,1998,2013
 *                Toyoda Masashi
 *		  (mtoyoda@acm.org)
 *	Last Modified: 2013/ 5/ 5
 *========================================
 */
/* sl version 5.0e : erutasonize                                             */
/*                   delete -l -c options.                                   */
/*                                             by Taichi Sugiyama 2014/ 3/26 */
/* sl version 5.00 : add -c option                                           */
/*                                              by Toyoda Masashi 2013/ 5/ 5 */
/* sl version 4.00 : add C51, usleep(40000)                                  */
/*                                              by Toyoda Masashi 2002/12/31 */
/* sl version 3.03 : add usleep(20000)                                       */
/*                                              by Toyoda Masashi 1998/ 7/22 */
/* sl version 3.02 : D51 flies! Change options.                              */
/*                                              by Toyoda Masashi 1993/ 1/19 */
/* sl version 3.01 : Wheel turns smoother                                    */
/*                                              by Toyoda Masashi 1992/12/25 */
/* sl version 3.00 : Add d(D51) option                                       */
/*                                              by Toyoda Masashi 1992/12/24 */
/* sl version 2.02 : Bug fixed.(dust remains in screen)                      */
/*                                              by Toyoda Masashi 1992/12/17 */
/* sl version 2.01 : Smoke run and disappear.                                */
/*                   Change '-a' to accident option.			     */
/*                                              by Toyoda Masashi 1992/12/16 */
/* sl version 2.00 : Add a(all),l(long),F(Fly!) options.                     */
/* 						by Toyoda Masashi 1992/12/15 */
/* sl version 1.02 : Add turning wheel.                                      */
/*					        by Toyoda Masashi 1992/12/14 */
/* sl version 1.01 : Add more complex smoke.                                 */
/*                                              by Toyoda Masashi 1992/12/14 */
/* sl version 1.00 : SL runs vomitting out smoke.                            */
/*						by Toyoda Masashi 1992/12/11 */

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "sl.h"

int ACCIDENT  = 0;
int FLY       = 0;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
	if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x)
	if (mvaddch(y, x, *str) == ERR)  return ERR;
    return OK;
}

void option(char *str)
{
    extern int ACCIDENT, FLY;

    while (*str != '\0') {
	switch (*str++) {
	    case 'a': ACCIDENT = 1; break;
	    case 'F': FLY      = 1; break;
	    default:                break;
	}
    }
}

int main(int argc, char *argv[])
{
    int x, i;

    for (i = 1; i < argc; ++i) {
	if (*argv[i] == '-') {
	    option(argv[i] + 1);
	}
    }
    initscr();
    signal(SIGINT, SIG_IGN);
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);
    leaveok(stdscr, TRUE);
    scrollok(stdscr, FALSE);

    for (x = COLS - 1; ; --x) {
	if (add_erutaso(x) == ERR) break;
    getch();
	refresh();
	usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}


int add_erutaso(int x)
{
    static char *erutaso[ERUTASOPATTERNS][ERUTASOHIGHT + 1]
	= {{ERUTASO11, ERUTASO12, ERUTASO13, ERUTASO14, ERUTASO15, ERUTASO16, ERUTASO17, ERUTASO18, ERUTASO19, ERUTASO1DEL},
	   {ERUTASO21, ERUTASO22, ERUTASO23, ERUTASO24, ERUTASO25, ERUTASO26, ERUTASO27, ERUTASO28, ERUTASO29, ERUTASO2DEL},
	   {ERUTASO31, ERUTASO32, ERUTASO33, ERUTASO34, ERUTASO35, ERUTASO36, ERUTASO37, ERUTASO38, ERUTASO39, ERUTASO3DEL},
	   {ERUTASO41, ERUTASO42, ERUTASO43, ERUTASO44, ERUTASO45, ERUTASO46, ERUTASO47, ERUTASO48, ERUTASO49, ERUTASO4DEL},
	   {ERUTASO31, ERUTASO32, ERUTASO33, ERUTASO34, ERUTASO35, ERUTASO36, ERUTASO37, ERUTASO38, ERUTASO39, ERUTASO3DEL},
	   {ERUTASO21, ERUTASO22, ERUTASO23, ERUTASO24, ERUTASO25, ERUTASO26, ERUTASO27, ERUTASO28, ERUTASO29, ERUTASO2DEL}};

    int i, y;

    if (x < - ERUTASOLENGTH)  return ERR;
    y = LINES / 2 - 3;

    if (FLY == 1) {
	y = (x / 6) + LINES - (COLS / 6) - ERUTASOHIGHT;
    }
    for (i = 0; i <= ERUTASOHIGHT; ++i) {
	my_mvaddstr(y + i, x, erutaso[(ERUTASOLENGTH + x) / 3 % ERUTASOPATTERNS][i]);
    }
    if (ACCIDENT == 1) {
	add_kininarimasu(y , x + 16);
    }
    add_smoke(y - 1, x + ERUTASOFUNNEL);
    return OK;
}


int add_kininarimasu(int y, int x)
{
	static char *man[2] = {"", "< KININARIMASU! "};
	my_mvaddstr(y , x, man[(ERUTASOLENGTH + x) / 12 % 2]);
}


int add_smoke(int y, int x)
#define SMOKEPTNS	16
{
    static struct smokes {
	int y, x;
	int ptrn, kind;
    } S[1000];
    static int sum = 0;
    static char *Smoke[2][SMOKEPTNS]
	= {{"(   )", "(    )", "(    )", "(   )", "(  )",
	    "(  )" , "( )"   , "( )"   , "()"   , "()"  ,
	    "O"    , "O"     , "O"     , "O"    , "O"   ,
	    " "                                          },
	   {"(@@@)", "(@@@@)", "(@@@@)", "(@@@)", "(@@)",
	    "(@@)" , "(@)"   , "(@)"   , "@@"   , "@@"  ,
	    "@"    , "@"     , "@"     , "@"    , "@"   ,
	    " "                                          }};
    static char *Eraser[SMOKEPTNS]
	=  {"     ", "      ", "      ", "     ", "    ",
	    "    " , "   "   , "   "   , "  "   , "  "  ,
	    " "    , " "     , " "     , " "    , " "   ,
	    " "                                          };
    static int dy[SMOKEPTNS] = { 2,  1, 1, 1, 0, 0, 0, 0, 0, 0,
				 0,  0, 0, 0, 0, 0             };
    static int dx[SMOKEPTNS] = {-2, -1, 0, 1, 1, 1, 1, 1, 2, 2,
				 2,  2, 2, 3, 3, 3             };
    int i;

    if (x % 4 == 0) {
	for (i = 0; i < sum; ++i) {
	    my_mvaddstr(S[i].y, S[i].x, Eraser[S[i].ptrn]);
	    S[i].y    -= dy[S[i].ptrn];
	    S[i].x    += dx[S[i].ptrn];
	    S[i].ptrn += (S[i].ptrn < SMOKEPTNS - 1) ? 1 : 0;
	    my_mvaddstr(S[i].y, S[i].x, Smoke[S[i].kind][S[i].ptrn]);
	}
	my_mvaddstr(y, x, Smoke[sum % 2][0]);
	S[sum].y = y;    S[sum].x = x;
	S[sum].ptrn = 0; S[sum].kind = sum % 2;
	sum ++;
    }
}
