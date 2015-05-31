/*========================================
 *    sl.c: SL version 5.02
 *        Copyright 1993,1998,2014
 *                  Toyoda Masashi
 *                  (mtoyoda@acm.org)
 *        Last Modified: 2015/06/01
 *========================================
 */
/* sl version 5.03 : Ah^~ My heart will be hopping^~.                         */
/*                                              by Taichi Sugiyama 2015/06/01 */
/* sl version 5.02 : Fix compiler warnings.                                   */
/*                                              by Jeff Schwab     2014/06/03 */
/* sl version 5.01 : removed cursor and handling of IO                        */
/*                                              by Chris Seymour   2014/01/03 */
/* sl version 5.00 : add -c option                                            */
/*                                              by Toyoda Masashi  2013/05/05 */
/* sl version 4.00 : add C51, usleep(40000)                                   */
/*                                              by Toyoda Masashi  2002/12/31 */
/* sl version 3.03 : add usleep(20000)                                        */
/*                                              by Toyoda Masashi  1998/07/22 */
/* sl version 3.02 : D51 flies! Change options.                               */
/*                                              by Toyoda Masashi  1993/01/19 */
/* sl version 3.01 : Wheel turns smoother                                     */
/*                                              by Toyoda Masashi  1992/12/25 */
/* sl version 3.00 : Add d(D51) option                                       */
/*                                              by Toyoda Masashi  1992/12/24 */
/* sl version 2.02 : Bug fixed.(dust remains in screen)                       */
/*                                              by Toyoda Masashi  1992/12/17 */
/* sl version 2.01 : Smoke run and disappear.                                 */
/*                   Change '-a' to accident option.                          */
/*                                              by Toyoda Masashi  1992/12/16 */
/* sl version 2.00 : Add a(all),l(long),F(Fly!) options.                      */
/*                                              by Toyoda Masashi  1992/12/15 */
/* sl version 1.02 : Add turning wheel.                                      */
/*                                              by Toyoda Masashi  1992/12/14 */
/* sl version 1.01 : Add more complex smoke.                                  */
/*                                              by Toyoda Masashi  1992/12/14 */
/* sl version 1.00 : SL runs vomitting out smoke.                            */
/*                                              by Toyoda Masashi  1992/12/11 */

#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include "sl.h"

int make_coffee(int x);

int add_chino(int x);
int add_cocoa(int x);
int add_chino_making_coffee(int f, int p);
int add_cocoa_making_coffee(int f, int p);

void add_counter();
void add_smoke(int y, int x, int f);
void add_tippy(int y, int x, int d, int f);

void option(char *str);
int my_mvaddstr(int y, int x, char *str);

int ACCIDENT   = 0;
int LOST_TIPPY = 0;
int FLY        = 0;
int COCOA      = 0;

int my_mvaddstr(int y, int x, char *str)
{
    for ( ; x < 0; ++x, ++str)
        if (*str == '\0')  return ERR;
    for ( ; *str != '\0'; ++str, ++x) {
        if (*str == '?') continue;
        if (mvaddch(y, x, *str) == ERR)  return ERR;
    }
    return OK;
}

void option(char *str)
{
    extern int ACCIDENT, FLY, LOST_TIPPY, COCOA;

    while (*str != '\0') {
        switch (*str++) {
            case 'a': ACCIDENT   = 1; break;
            case 'F': FLY       = 1; break;
            case 
            //
            // ｳｻｷﾞｶﾞｲﾅｲ
            // ヘ(^o^)ヘ
            // 　　　|∧
            // 　　 /
             'l'
            // ｳｻｷﾞｶﾞｲﾅｲ?／
            // 　　　(^o^)／
            // 　　／( 　)
            // ／　／ ＞ 
             :
            // ｩﾌｧﾌｧﾌｪ
            // (^o^) 三
            // (＼＼ 三
            // ＜　＼ 三
             LOST_TIPPY = 1;
            // ＼ｳｻｷﾞｶﾞｲﾅｲ!!!
            // (／o^)
            // ( ／　
            // ／ く
            //　
             break;

            case 'c': COCOA      = 1; break;
            default:                break;
        }
    }
}

int main(int argc, char *argv[])
{
    int x, i, f, maxf;

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

    add_counter();
    for (x = COLS - 1, f = 0 ; ; --x) {
        if (x == (COLS - (COCOA == 1 ? COCOALENGTH : CHINOLENGTH)) / 2) {
            if (f < (ACCIDENT == 1 ? (STARTACCIDENT2 + SPANACCIDENT2) : (STARTFINISHED + SPANFINISHED))) {
                x++;
                make_coffee(f++);
            }
        } else if (COCOA == 1) {
            if (add_cocoa(x) == ERR) break;
        }
        else {
            if (add_chino(x) == ERR) break;
        }
        getch();
        refresh();
        usleep(40000);
    }
    mvcur(0, COLS - 1, LINES - 1, 0);
    endwin();
}

int make_coffee(int f)
{
    // 参考：ご注文はうさぎですか？ 第一羽「ひと目で、尋常でないもふもふだと見抜いたよ」4:13頃〜
    // http://www.nicovideo.jp/watch/1397552685
    int x, y, p, top, middle, bottom, left, center, right, i;
    int stir;
    char drop;

    x = (COLS - CHINOLENGTH) / 2;
    y = (LINES - (COCOA == 1 ? COCOAHEIGHT : CHINOHEIGHT) + TIPPYHEIGHT) / 2;
    top = y;
    bottom = y + (COCOA == 1 ? COCOAHEIGHT : CHINOHEIGHT);
    middle = (top + bottom) / 2;
    left = x;
    right = x + (COCOA == 1 ? COCOALENGTH : CHINOLENGTH);
    center = (left + right) / 2;
    
    static char *grinder[GRINDERHEIGHT] = {GRINDER01, GRINDER02};
    static char *handle[HANDLEPATTERNS] = {HANDLEA, HANDLEB, HANDLEC, HANDLED, HANDLEE, HANDLED, HANDLEF, HANDLEB};
    static char *siphon[SIPHONHEIGHT] = {SIPHON01, SIPHON02, SIPHON03, SIPHON04};
    static char *fire[FIREPATTERNS] = {FIRE01, FIRE02};
    static char *lowersiphon[LOWERSIPHONPATTERNS] = {LOWERSIPHON01, LOWERSIPHON02};
    static char *uppersiphon[UPPERSIPHONPATTERNS] = {UPPERSIPHON01, UPPERSIPHON02, UPPERSIPHON03};
    static char *pour[POURPATTERNS] = {POUR01, POUR01, POUR01, POUR01, POUR02, POUR03, POUR03, POUR03};

    add_counter();

    p = (f <= STARTGRIND + SPANGRIND - 1|| STARTPOUR < f) ? 0 : 1;
    if (COCOA == 1) {
        add_cocoa_making_coffee(f, p);
    } else {
        add_chino_making_coffee(f, p);
    }
    // ｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘｺﾞﾘ
    if (f <= STARTGRIND + SPANGRIND - 1) {
        for (i = 0; i < GRINDERHEIGHT ; i++) {
            my_mvaddstr(bottom - GRINDERHEIGHT + 1 + i, center - GRINDERLENGTH / 2, grinder[i]);
        }
        my_mvaddstr(bottom - GRINDERHEIGHT, center - HANDLELENGTH / 2, handle[(f / 3) % HANDLEPATTERNS]);
    }

    // Co+2Fe→Coffee
    if (STARTHEAT <= f && f <= STARTPOUR) {
        for (i = 0; i < SIPHONHEIGHT ; i++) {
            my_mvaddstr(bottom - SIPHONHEIGHT + 1 + i, right - SIPHONLENGTH, siphon[i]);
        }
        my_mvaddstr(bottom - 3, right - SIPHONLENGTH + 1, uppersiphon[f < STARTEXTRACT ? 0 : (f < STARTEXTRACT + 4 ? 1 : 2)]);
        my_mvaddstr(bottom - 2, right - SIPHONLENGTH + 1, lowersiphon[(f / 3) % LOWERSIPHONPATTERNS]);
        my_mvaddstr(bottom - 1, right - SIPHONLENGTH + 1, fire[(f / 3) % FIREPATTERNS]);

        if (STARTSTIR <= f && f < STARTSTIR + SPANSTIR) {
            stir = (f / 6) % STIRPATTERNS;
            if (stir > (STIRPATTERNS + 1) / 2) stir = STIRPATTERNS - stir;
            mvaddch(bottom - 4, right - SIPHONLENGTH + 1 + stir , 'Q');
            mvaddch(bottom - 3, right - SIPHONLENGTH + 1 + stir , '|');
        }
    }

    // しげってんなぁー
    if (STARTPOUR <= f && f < STARTPOUR + SPANPOUR) {
        my_mvaddstr(bottom - 2, center - POURLENGTH / 2 , pour[(f - STARTPOUR) * POURPATTERNS / SPANPOUR]);
        if (f < STARTPOUR + SPANPOUR * 5 / POURPATTERNS) {
            drop = (f / 3) % 2 == 0 ? ':' : '|';
        } else if (f < STARTPOUR + SPANPOUR * 6 / POURPATTERNS) {
            drop = '.';
        } else {
            drop = ' ';
        }
        mvaddch(bottom - 1, center + POURLENGTH / 2 - 1, drop);
        my_mvaddstr(bottom, center, TEACUP);
    }

    // お待たせしました。
    if (STARTFINISHED <= f) {
        if (f < STARTFINISHED + SPANFINISHED - 1) {
            my_mvaddstr(middle, right, MESSAGE);
        } else if (ACCIDENT == 1 && f < STARTACCIDENT1 + SPANACCIDENT1) {
            my_mvaddstr(middle, right, MESSAGEACCIDENT1);
        } else if (ACCIDENT == 1 && f < STARTACCIDENT2 + SPANACCIDENT2 - 1) {
            my_mvaddstr(middle, right, MESSAGEACCIDENT2);
        } else {
            my_mvaddstr(middle, right, MESSAGEDEL);
        }
        if (f > STARTFINISHED + SPANFINISHED) {
            my_mvaddstr(bottom, center - TEACUPLENGTH / 2, TEACUPACCIDENT);
            my_mvaddstr(bottom + 1, center - TEACUPLENGTH / 2 + 3, "@@");
            my_mvaddstr(bottom + 2, center - TEACUPLENGTH / 2 + 4, "@@@");

        } else {
            my_mvaddstr(bottom, center - TEACUPLENGTH / 2, TEACUP);
        }
    }
    return OK;
}

int add_chino_making_coffee(int f, int p)
{
    static char *chino[2][CHINOHEIGHT]
        = {{CHINOFRONT01, CHINOFRONT02, CHINOFRONT03, CHINOFRONT04, CHINOFRONT05, CHINOFRONT06, CHINOFRONT07, CHINOFRONT08},
           {CHINORIGHT01, CHINORIGHT02, CHINORIGHT03, CHINORIGHT04, CHINORIGHT05, CHINORIGHT06, CHINORIGHT07, CHINORIGHT08}};

    int x, y, i;

    x = (COLS - CHINOLENGTH) / 2;
    y = (LINES - CHINOHEIGHT + TIPPYHEIGHT) / 2;

    for (i = 0; i < CHINOHEIGHT; ++i) {
        my_mvaddstr(y + i, x, chino[p][i]);
    }
    if (LOST_TIPPY != 1) {
        add_tippy(y - TIPPYHEIGHT + 1, x + 3, p + 1, f);
    }
    add_smoke(y - (LOST_TIPPY != 1 ? TIPPYHEIGHT - 1 : 0) - 1, x + 5, f);
    return OK;
}

int add_cocoa_making_coffee(int f, int p)
{
    static char *chino[2][CHINOHEIGHT]
        = {{COCOAFRONT01, COCOAFRONT02, COCOAFRONT03, COCOAFRONT04, COCOAFRONT05, COCOAFRONT06, COCOAFRONT07, COCOAFRONT08},
           {COCOARIGHT01, COCOARIGHT02, COCOARIGHT03, COCOARIGHT04, COCOARIGHT05, COCOARIGHT06, COCOARIGHT07, COCOARIGHT08}};

    int x, y, i;

    x = (COLS - CHINOLENGTH) / 2;
    y = (LINES - CHINOHEIGHT + TIPPYHEIGHT) / 2;

    for (i = 0; i < CHINOHEIGHT; ++i) {
        my_mvaddstr(y + i, x, chino[p][i]);
    }
    if (LOST_TIPPY != 1) {
        add_tippy(y - TIPPYHEIGHT + 1, x + 3, p + 1, f);
    }
    add_smoke(y - (LOST_TIPPY != 1 ? TIPPYHEIGHT - 1 : 0) - 1, x + 5, f);
    return OK;
}

void add_counter(){
    int x;
    for (x = 0 ; x  < COLS ; x++) {
        mvaddch((LINES + CHINOHEIGHT + TIPPYHEIGHT) / 2, x, '-');
    }
}

int add_chino(int x)
{
    static char *chino[CHINOPATTERNS][CHINOHEIGHT]
        = {{CHINOLEFT01, CHINOLEFT02, CHINOLEFT03, CHINOLEFT04, CHINOLEFT05, CHINOLEFT06, CHINOLEFT07, CHINOLEFT08}};

    int y, i;

    if (x < - CHINOLENGTH)  return ERR;
    y = (LINES - CHINOHEIGHT + TIPPYHEIGHT) / 2;

    for (i = 0; i < CHINOHEIGHT; ++i) {
        my_mvaddstr(y + i, x, chino[(CHINOLENGTH + x) / 3 % CHINOPATTERNS][i]);
    }
    if (LOST_TIPPY != 1) {
        add_tippy(y - TIPPYHEIGHT + 1, x + 2, 0, x + (COCOA == 1 ? COCOALENGTH : CHINOLENGTH));
    }
    add_smoke(y - (LOST_TIPPY != 1 ? TIPPYHEIGHT - 1 : 0) - 1, x + CHINOLENGTH / 2, 0);
    return OK;
}

int add_cocoa(int x)
{
    static char *cocoa[COCOAPATTERNS][COCOAHEIGHT]
        = {{COCOALEFT01, COCOALEFT02, COCOALEFT03, COCOALEFT04, COCOALEFT05, COCOALEFT06, COCOALEFT07, COCOALEFT08}};

    int y, i;

    if (x < - COCOALENGTH)  return ERR;
    y = (LINES - CHINOHEIGHT + TIPPYHEIGHT) / 2;

    for (i = 0; i < COCOAHEIGHT; ++i) {
        my_mvaddstr(y + i, x, cocoa[(COCOALENGTH + x) / 3 % COCOAPATTERNS][i]);
    }
    if (LOST_TIPPY != 1) {
        add_tippy(y - TIPPYHEIGHT + 1, x + 2, 0, x + (COCOA == 1 ? COCOALENGTH : CHINOLENGTH));
    }
    add_smoke(y - (LOST_TIPPY != 1 ? TIPPYHEIGHT - 1 : 0) - 1, x + COCOALENGTH / 2, 0);
    return OK;
}

void add_tippy(int y, int x, int d, int f)
{
    int i;
    static char *tippy[3][TIPPYPATTERNS][TIPPYHEIGHT] = {
        {{TIPPYLEFT01A, TIPPYLEFT02A, TIPPYLEFT03A, TIPPYLEFT04A, TIPPYLEFT05A},
         {TIPPYLEFT01A, TIPPYLEFT02A, TIPPYLEFT03A, TIPPYLEFT04A, TIPPYLEFT05A},
         {TIPPYLEFT01B, TIPPYLEFT02B, TIPPYLEFT03B, TIPPYLEFT04B, TIPPYLEFT05B},
         {TIPPYLEFT01C, TIPPYLEFT02C, TIPPYLEFT03C, TIPPYLEFT04C, TIPPYLEFT05C},
         {TIPPYLEFT01C, TIPPYLEFT02C, TIPPYLEFT03C, TIPPYLEFT04C, TIPPYLEFT05C}},
        {{TIPPYFRONT01A, TIPPYFRONT02A, TIPPYFRONT03A, TIPPYFRONT04A, TIPPYFRONT05A},
         {TIPPYFRONT01A, TIPPYFRONT02A, TIPPYFRONT03A, TIPPYFRONT04A, TIPPYFRONT05A},
         {TIPPYFRONT01B, TIPPYFRONT02B, TIPPYFRONT03B, TIPPYFRONT04B, TIPPYFRONT05B},
         {TIPPYFRONT01C, TIPPYFRONT02C, TIPPYFRONT03C, TIPPYFRONT04C, TIPPYFRONT05C},
         {TIPPYFRONT01C, TIPPYFRONT02C, TIPPYFRONT03C, TIPPYFRONT04C, TIPPYFRONT05C}},
        {{TIPPYRIGHT01A, TIPPYRIGHT02A, TIPPYRIGHT03A, TIPPYRIGHT04A, TIPPYRIGHT05A},
         {TIPPYRIGHT01A, TIPPYRIGHT02A, TIPPYRIGHT03A, TIPPYRIGHT04A, TIPPYRIGHT05A},
         {TIPPYRIGHT01B, TIPPYRIGHT02B, TIPPYRIGHT03B, TIPPYRIGHT04B, TIPPYRIGHT05B},
         {TIPPYRIGHT01C, TIPPYRIGHT02C, TIPPYRIGHT03C, TIPPYRIGHT04C, TIPPYRIGHT05C},
         {TIPPYRIGHT01C, TIPPYRIGHT02C, TIPPYRIGHT03C, TIPPYRIGHT04C, TIPPYRIGHT05C}}
        };
    for (i = 0; i < TIPPYHEIGHT; ++i) {
        my_mvaddstr(y + i, x, tippy[d][FLY == 1 ? (f / 3 % TIPPYPATTERNS) : 0][i]);
    }
}

void add_smoke(int y, int x, int f)
#define SMOKEPTNS        16
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

    if ((x + f) % 4 == 0) {
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
