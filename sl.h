/*========================================
 *    sl.h: SL version 5.02
 *	Copyright 1993,2002,2014
 *                Toyoda Masashi
 *		  (mtoyoda@acm.org)
 *	Last Modified: 2014/06/03
 *========================================
 */

#define D51HIGHT	10
#define D51FUNNEL	 7
#define D51LENGTH	83
#define D51PATTERNS	 6

#define MESSAGE          "< OMATASESHIMASHITA."
#define MESSAGEACCIDENT1 "< A!                "
#define MESSAGEACCIDENT2 "< ...               "
#define MESSAGEDEL       "                    "

#define SPANGRIND 80
#define SPANHEAT 48
#define SPANEXTRACT 48
#define SPANSTIR 80
#define SPANPOUR 80
#define SPANFINISHED 32
#define SPANACCIDENT1 32
#define SPANACCIDENT2 32

#define STARTGRIND 0
#define STARTHEAT (STARTGRIND + SPANGRIND)
#define STARTEXTRACT (STARTHEAT + SPANHEAT)
#define STARTSTIR (STARTEXTRACT + SPANEXTRACT)
#define STARTPOUR (STARTSTIR + SPANSTIR)
#define STARTFINISHED (STARTPOUR + SPANPOUR)
#define STARTACCIDENT1 (STARTFINISHED + SPANFINISHED)
#define STARTACCIDENT2 (STARTACCIDENT1 + SPANACCIDENT1)

#define TIPPYPATTERNS 5
#define TIPPYHEIGHT 5
#define TIPPYLENGTH 12

#define TIPPYLEFT01A     "            "
#define TIPPYLEFT02A     "   A___A_   "
#define TIPPYLEFT03A     "  / . .  \\  "
#define TIPPYLEFT04A     " | \" ~ \"  | "
#define TIPPYLEFT05A     " ?\\______/? "

#define TIPPYLEFT01B     "   A___A_   "
#define TIPPYLEFT02B     "  / . .  \\  "
#define TIPPYLEFT03B     " | \" ~ \" |  "
#define TIPPYLEFT04B     " |       |  "
#define TIPPYLEFT05B     " ?\\_____/?? "

#define TIPPYLEFT01C     "   A___A_   "
#define TIPPYLEFT02C     "  / . .  \\  "
#define TIPPYLEFT03C     " | \" ~ \"  | "
#define TIPPYLEFT04C     "  \\______/  "
#define TIPPYLEFT05C     " ?????????? "

#define TIPPYFRONT01A    "            "
#define TIPPYFRONT02A    "   A___A    "
#define TIPPYFRONT03A    "  / . . \\   "
#define TIPPYFRONT04A    " | \" ~ \" |  "
#define TIPPYFRONT05A    " ?\\_____/?  "

#define TIPPYFRONT01B    "   A___A    "
#define TIPPYFRONT02B    "  / . . \\   "
#define TIPPYFRONT03B    " | \" ~ \" |  "
#define TIPPYFRONT04B    " |       |  "
#define TIPPYFRONT05B    " ?\\_____/?  "

#define TIPPYFRONT01C    "   A___A    "
#define TIPPYFRONT02C    "  / . . \\   "
#define TIPPYFRONT03C    " | \" ~ \" |  "
#define TIPPYFRONT04C    "  \\_____/   "
#define TIPPYFRONT05C    " ?????????? "

#define TIPPYRIGHT01A    "            "
#define TIPPYRIGHT02A    "   A___A_   "
#define TIPPYRIGHT03A    "  /  . . \\  "
#define TIPPYRIGHT04A    " |  \" ~ \" | "
#define TIPPYRIGHT05A    " ?\\______/? "

#define TIPPYRIGHT01B    "   A___A_   "
#define TIPPYRIGHT02B    "  /  . . \\  "
#define TIPPYRIGHT03B    "  | \" ~ \"|  "
#define TIPPYRIGHT04B    "  |      |  "
#define TIPPYRIGHT05B    " ?\\______/? "

#define TIPPYRIGHT01C    "   A___A_   "
#define TIPPYRIGHT02C    "  /  . . \\  "
#define TIPPYRIGHT03C    " |  \" ~ \" | "
#define TIPPYRIGHT04C    "  \\______/  "
#define TIPPYRIGHT05C    " ?????????? "

#define CHINOPATTERNS 1
#define CHINOHEIGHT 8
#define CHINOLENGTH  17

#define CHINOLEFT01      "   __________    "
#define CHINOLEFT02      "  /          \\   "
#define CHINOLEFT03      " /\\/     \\/   \\  "
#define CHINOLEFT04      " |/\\v\\/v\\/\\    | "
#define CHINOLEFT05      " || O   O  | ) l "
#define CHINOLEFT06      " |\\ \" _ \"  //  | "
#define CHINOLEFT07      " |v|o---o_/||  | "
#define CHINOLEFT08      "  \\l| :   |~l~/  "

#define CHINOFRONT01     "    _________    "
#define CHINOFRONT02     "   /         \\   "
#define CHINOFRONT03     "  / \\/      \\/\\  "
#define CHINOFRONT04     "  | /\\Vv\\/vV/\\|  "
#define CHINOFRONT05     "  | | O   O | |  "
#define CHINOFRONT06     "  | \\ \" _ \" / |  "
#define CHINOFRONT07     "  |V||o---o||V|  "
#define CHINOFRONT08     "   \\~|  :  |~/   "

#define CHINORIGHT01     "    __________   "
#define CHINORIGHT02     "   /          \\  "
#define CHINORIGHT03     "  /   \\/     \\/\\ "
#define CHINORIGHT04     " |    /\\/v\\/v/\\| "
#define CHINORIGHT05     " l ( |  O   O || "
#define CHINORIGHT06     " |   \\\\ \" _ \" /| "
#define CHINORIGHT07     " |  ||\\_o---o|v| "
#define CHINORIGHT08     "  \\~l~|   : ||/  "

#define COCOAPATTERNS 1
#define COCOAHEIGHT 8
#define COCOALENGTH  17

#define COCOALEFT01      "   _________     "
#define COCOALEFT02      "  /         \\    "
#define COCOALEFT03      " /         =*\\   "
#define COCOALEFT04      " (/Vv\\ /vV\\   )  "
#define COCOALEFT05      " || O   O |   |  "
#define COCOALEFT06      " |\\ \" _ \" / / }  "
#define COCOALEFT07      "  (|o---o_/|v)   "
#define COCOALEFT08      "   l|  :  ||    "

#define COCOAFRONT01     "    _________    "
#define COCOAFRONT02     "   /         \\   "
#define COCOAFRONT03     "  /         =*\\  "
#define COCOAFRONT04     "  ( /Vv\\ /vV\\ )  "
#define COCOAFRONT05     "  | | O   O | |  "
#define COCOAFRONT06     "  |\\\\ \" _ \" //|  "
#define COCOAFRONT07     "   (v|o---o|v)   "
#define COCOAFRONT08     "     |  :  |     "

#define COCOARIGHT01     "     _________   "
#define COCOARIGHT02     "    /         \\  "
#define COCOARIGHT03     "   /          =\\ "
#define COCOARIGHT04     "  (   /Vv\\ /vV\\) "
#define COCOARIGHT05     "  |   | O   O || "
#define COCOARIGHT06     "  { \\ \\ \" _ \" /| "
#define COCOARIGHT07     "   (v|\\_o---o|)  "
#define COCOARIGHT08     "     ||   : |l   "

#define HANDLEPATTERNS  8
#define HANDLELENGTH  5
#define HANDLEA          "q=i  "
#define HANDLEB          " qi  "
#define HANDLEC          "  i  "
#define HANDLED          "  iq "
#define HANDLEE          "  i=q"
#define HANDLEF          "  q  "

#define GRINDERHEIGHT 2
#define GRINDERLENGTH 5
#define GRINDER01        " ( )c"
#define GRINDER02        "[|_|]"


#define SIPHONHEIGHT 4
#define SIPHONLENGTH 5
#define SIPHON01         "(   )"
#define SIPHON02         "(   )"
#define SIPHON03         " \\ / "
#define SIPHON04         "-[ ]-"

#define UPPERSIPHONPATTERNS  3
#define UPPERSIPHONLENGTH  3
#define UPPERSIPHON01    "   "
#define UPPERSIPHON02    "___"
#define UPPERSIPHON03    "==="

#define LOWERSIPHONPATTERNS  2
#define LOWERSIPHONLENGTH  3
#define LOWERSIPHON01    "~-~"
#define LOWERSIPHON02    "-~-"

#define FIREPATTERNS  2
#define FIRELENGTH  3
#define FIRE01           "VvV"
#define FIRE02           "vVv"

#define STIRPATTERNS 4

#define POURPATTERNS 8
#define POURLENGTH 6
#define POUR01           "G(===)"
#define POUR02           "G(___)"
#define POUR03           "G(   )"

#define DROPPATTERNS 4
#define DROP01           ':'
#define DROP02           '|'
#define DROP03           '.'
#define DROP04           ' '

#define TEACUPLENGTH 4
#define TEACUP           "c[_]"
#define TEACUPACCIDENT   "=(@)"

#define DELLN "                     "
