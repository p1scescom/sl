/*========================================
 *    sl.c: SL version 5.0
 *	Copyright 1993,1998,2013
 *                Toyoda Masashi
 *		  (mtoyoda@acm.org)
 *	Last Modified: 2013/ 5/ 5
 *========================================
 */
/* sl version 5.0f : eromangasenseinize                                      */
/*                   add -y option to yukadon                                */
/*                                                   by p1scescom 2017/ 4/20 */
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
int YUKADON   = 0;


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
			case 'y': YUKADON  = 1; break;
			default:                break;
		}
    }
}


int add_eromangasensei_shiranai(int y, int x)
{
	static char *man[8] = {"", "< SHIRANAI ", "", "< NAMAENOHITO ", "", "< SONNNAHAZUKASHII ", "", "< EROMANGASENSEI? "};
	int count = EROMANGASENSEILENGTH + x;
	my_mvaddstr(y , x, man[count / 12 % 8]);
	my_mvaddstr(y + 6 , x - 8, "-");
}


int do_eromangasensei_yukadon(int y, int x)
{
    static char *eromangasensei_yukadon[EROMANGASENSEIYUKADONPATTERNS][EROMANGASENSEIHIGHT + 1]
	= {{EROMANGASENSEI41, EROMANGASENSEI42, EROMANGASENSEI43, EROMANGASENSEI44, EROMANGASENSEI45, EROMANGASENSEI46, EROMANGASENSEI47, EROMANGASENSEI48, EROMANGASENSEI49, EROMANGASENSEI4A, EROMANGASENSEI4B, EROMANGASENSEI4DEL},
	   {EROMANGASENSEI51, EROMANGASENSEI52, EROMANGASENSEI53, EROMANGASENSEI54, EROMANGASENSEI55, EROMANGASENSEI56, EROMANGASENSEI57, EROMANGASENSEI58, EROMANGASENSEI59, EROMANGASENSEI5A, EROMANGASENSEI5B, EROMANGASENSEI5DEL}};
	int i,l;
	for(i = 0; i < 30; i++) {
		for(l = 0; l <= EROMANGASENSEIHIGHT; l++) {
			my_mvaddstr(y + l, x, eromangasensei_yukadon[(EROMANGASENSEILENGTH + i) / 3 % EROMANGASENSEIYUKADONPATTERNS][l]);
			getch();
			refresh();
			usleep(5000);
		}
	}
	YUKADON = 0;
}


int add_eromangasensei(int x)
{
    static char *eromangasensei[EROMANGASENSEIPATTERNS][EROMANGASENSEIHIGHT + 1]
	= {{EROMANGASENSEI11, EROMANGASENSEI12, EROMANGASENSEI13, EROMANGASENSEI14, EROMANGASENSEI15, EROMANGASENSEI16, EROMANGASENSEI17, EROMANGASENSEI18, EROMANGASENSEI19, EROMANGASENSEI1A, EROMANGASENSEI1B, EROMANGASENSEI1DEL},
	   {EROMANGASENSEI21, EROMANGASENSEI22, EROMANGASENSEI23, EROMANGASENSEI24, EROMANGASENSEI25, EROMANGASENSEI26, EROMANGASENSEI27, EROMANGASENSEI28, EROMANGASENSEI29, EROMANGASENSEI2A, EROMANGASENSEI2B, EROMANGASENSEI2DEL},
	   {EROMANGASENSEI31, EROMANGASENSEI32, EROMANGASENSEI33, EROMANGASENSEI34, EROMANGASENSEI35, EROMANGASENSEI36, EROMANGASENSEI37, EROMANGASENSEI38, EROMANGASENSEI39, EROMANGASENSEI3A, EROMANGASENSEI3B, EROMANGASENSEI3DEL},
	   {EROMANGASENSEI21, EROMANGASENSEI22, EROMANGASENSEI23, EROMANGASENSEI24, EROMANGASENSEI25, EROMANGASENSEI26, EROMANGASENSEI27, EROMANGASENSEI28, EROMANGASENSEI29, EROMANGASENSEI2A, EROMANGASENSEI2B, EROMANGASENSEI2DEL}};

    int i, y;

    if (x < - EROMANGASENSEILENGTH) return ERR;

    y = LINES / 2 - 6;

    if (FLY == 1) {
		y = (x / 6) + LINES - (COLS / 6) - EROMANGASENSEIHIGHT;
    }
    for (i = 0; i <= EROMANGASENSEIHIGHT; ++i) {
		my_mvaddstr(y + i, x, eromangasensei[(EROMANGASENSEILENGTH + x) / 3 % EROMANGASENSEIPATTERNS][i]);
    }
    if (ACCIDENT == 1) {
		add_eromangasensei_shiranai(y , x + 16);
    }
	if (YUKADON == 1 && COLS / 2 > x + 11 ) {
		do_eromangasensei_yukadon(y, x);
	}
    return OK;
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
		if (add_eromangasensei(x) == ERR) break;
		getch();
		refresh();
		usleep(50000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}
