
/*  A Bison parser, made from lev_comp.y with Bison version GNU Bison version 1.24
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	CHAR	258
#define	INTEGER	259
#define	BOOLEAN	260
#define	PERCENT	261
#define	MESSAGE_ID	262
#define	MAZE_ID	263
#define	LEVEL_ID	264
#define	LEV_INIT_ID	265
#define	GEOMETRY_ID	266
#define	NOMAP_ID	267
#define	OBJECT_ID	268
#define	COBJECT_ID	269
#define	MONSTER_ID	270
#define	TRAP_ID	271
#define	DOOR_ID	272
#define	DRAWBRIDGE_ID	273
#define	MAZEWALK_ID	274
#define	WALLIFY_ID	275
#define	REGION_ID	276
#define	FILLING	277
#define	RANDOM_OBJECTS_ID	278
#define	RANDOM_MONSTERS_ID	279
#define	RANDOM_PLACES_ID	280
#define	ALTAR_ID	281
#define	LADDER_ID	282
#define	STAIR_ID	283
#define	NON_DIGGABLE_ID	284
#define	NON_PASSWALL_ID	285
#define	ROOM_ID	286
#define	PORTAL_ID	287
#define	TELEPRT_ID	288
#define	BRANCH_ID	289
#define	LEV	290
#define	CHANCE_ID	291
#define	CORRIDOR_ID	292
#define	GOLD_ID	293
#define	ENGRAVING_ID	294
#define	FOUNTAIN_ID	295
#define	POOL_ID	296
#define	SINK_ID	297
#define	NONE	298
#define	RAND_CORRIDOR_ID	299
#define	DOOR_STATE	300
#define	LIGHT_STATE	301
#define	CURSE_TYPE	302
#define	ENGRAVING_TYPE	303
#define	MATERIAL_TYPE	304
#define	DIRECTION	305
#define	RANDOM_TYPE	306
#define	O_REGISTER	307
#define	M_REGISTER	308
#define	P_REGISTER	309
#define	A_REGISTER	310
#define	ALIGNMENT	311
#define	LEFT_OR_RIGHT	312
#define	CENTER	313
#define	TOP_OR_BOT	314
#define	ALTAR_TYPE	315
#define	UP_OR_DOWN	316
#define	SUBROOM_ID	317
#define	NAME_ID	318
#define	FLAGS_ID	319
#define	FLAG_TYPE	320
#define	MON_ATTITUDE	321
#define	MON_ALERTNESS	322
#define	MON_APPEARANCE	323
#define	CONTAINED	324
#define	STRING	325
#define	MAP_ID	326

#line 1 "lev_comp.y"

/*	SCCS Id: @(#)lev_yacc.c	3.4	2000/01/17	*/
/*	Copyright (c) 1989 by Jean-Christophe Collet */
/* NetHack may be freely redistributed.  See license for details. */

/*
 * This file contains the Level Compiler code
 * It may handle special mazes & special room-levels
 */

/* In case we're using bison in AIX.  This definition must be
 * placed before any other C-language construct in the file
 * excluding comments and preprocessor directives (thanks IBM
 * for this wonderful feature...).
 *
 * Note: some cpps barf on this 'undefined control' (#pragma).
 * Addition of the leading space seems to prevent barfage for now,
 * and AIX will still see the directive.
 */
#ifdef _AIX
 #pragma alloca		/* keep leading space! */
#endif

#include "hack.h"
#include "sp_lev.h"

#define MAX_REGISTERS	10
#define ERR		(-1)
/* many types of things are put in chars for transference to NetHack.
 * since some systems will use signed chars, limit everybody to the
 * same number for portability.
 */
#define MAX_OF_TYPE	128

#define New(type)		\
	(type *) memset((genericptr_t)alloc(sizeof(type)), 0, sizeof(type))
#define NewTab(type, size)	(type **) alloc(sizeof(type *) * size)
#define Free(ptr)		free((genericptr_t)ptr)

extern void FDECL(yyerror, (const char *));
extern void FDECL(yywarning, (const char *));
extern int NDECL(yylex);
int NDECL(yyparse);

extern int FDECL(get_floor_type, (CHAR_P));
extern int FDECL(get_room_type, (char *));
extern int FDECL(get_trap_type, (char *));
extern int FDECL(get_monster_id, (char *,CHAR_P));
extern int FDECL(get_object_id, (char *,CHAR_P));
extern boolean FDECL(check_monster_char, (CHAR_P));
extern boolean FDECL(check_object_char, (CHAR_P));
extern char FDECL(what_map_char, (CHAR_P));
extern void FDECL(scan_map, (char *));
extern void NDECL(wallify_map);
extern boolean NDECL(check_subrooms);
extern void FDECL(check_coord, (int,int,const char *));
extern void NDECL(store_part);
extern void NDECL(store_room);
extern boolean FDECL(write_level_file, (char *,splev *,specialmaze *));
extern void FDECL(free_rooms, (splev *));

static struct reg {
	int x1, y1;
	int x2, y2;
}		current_region;

static struct coord {
	int x;
	int y;
}		current_coord, current_align;

static struct size {
	int height;
	int width;
}		current_size;

char tmpmessage[256];
digpos *tmppass[32];
char *tmpmap[ROWNO];

digpos *tmpdig[MAX_OF_TYPE];
region *tmpreg[MAX_OF_TYPE];
lev_region *tmplreg[MAX_OF_TYPE];
door *tmpdoor[MAX_OF_TYPE];
drawbridge *tmpdb[MAX_OF_TYPE];
walk *tmpwalk[MAX_OF_TYPE];

room_door *tmprdoor[MAX_OF_TYPE];
trap *tmptrap[MAX_OF_TYPE];
monster *tmpmonst[MAX_OF_TYPE];
object *tmpobj[MAX_OF_TYPE];
altar *tmpaltar[MAX_OF_TYPE];
lad *tmplad[MAX_OF_TYPE];
stair *tmpstair[MAX_OF_TYPE];
gold *tmpgold[MAX_OF_TYPE];
engraving *tmpengraving[MAX_OF_TYPE];
fountain *tmpfountain[MAX_OF_TYPE];
sink *tmpsink[MAX_OF_TYPE];
pool *tmppool[MAX_OF_TYPE];

mazepart *tmppart[10];
room *tmproom[MAXNROFROOMS*2];
corridor *tmpcor[MAX_OF_TYPE];

static specialmaze maze;
static splev special_lev;
static lev_init init_lev;

static char olist[MAX_REGISTERS], mlist[MAX_REGISTERS];
static struct coord plist[MAX_REGISTERS];

int n_olist = 0, n_mlist = 0, n_plist = 0;

unsigned int nlreg = 0, nreg = 0, ndoor = 0, ntrap = 0, nmons = 0, nobj = 0;
unsigned int ndb = 0, nwalk = 0, npart = 0, ndig = 0, nlad = 0, nstair = 0;
unsigned int naltar = 0, ncorridor = 0, nrooms = 0, ngold = 0, nengraving = 0;
unsigned int nfountain = 0, npool = 0, nsink = 0, npass = 0;

static int lev_flags = 0;

unsigned int max_x_map, max_y_map;

static xchar in_room;

extern int fatal_error;
extern int want_warnings;
extern const char *fname;


#line 131 "lev_comp.y"
typedef union
{
	int	i;
	char*	map;
	struct {
		xchar room;
		xchar wall;
		xchar door;
	} corpos;
} YYSTYPE;

#ifndef YYLTYPE
typedef
  struct yyltype
    {
      int timestamp;
      int first_line;
      int first_column;
      int last_line;
      int last_column;
      char *text;
   }
  yyltype;

#define YYLTYPE yyltype
#endif

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		488
#define	YYFLAG		-32768
#define	YYNTBASE	78

#define YYTRANSLATE(x) ((unsigned)(x) <= 326 ? yytranslate[x] : 197)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,    72,
    73,     2,     2,    70,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,    71,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
    74,     2,    75,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
    26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
    36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
    46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
    56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
    66,    67,    68,    69,    76,    77
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     3,     5,     8,    10,    12,    18,    26,    30,
    31,    45,    57,    59,    61,    62,    66,    70,    72,    73,
    76,    80,    81,    84,    88,    92,    93,    95,    97,   100,
   102,   104,   106,   107,   110,   116,   122,   130,   133,   136,
   149,   162,   163,   166,   172,   174,   180,   182,   188,   190,
   196,   198,   199,   202,   204,   206,   208,   210,   212,   214,
   216,   218,   220,   222,   224,   226,   228,   232,   236,   246,
   248,   250,   252,   254,   256,   258,   264,   266,   268,   270,
   273,   277,   279,   282,   288,   290,   292,   294,   296,   297,
   300,   304,   308,   312,   314,   318,   320,   324,   326,   327,
   332,   333,   336,   338,   340,   342,   344,   346,   348,   350,
   352,   354,   356,   358,   360,   362,   364,   366,   368,   370,
   372,   374,   376,   377,   388,   389,   392,   395,   398,   401,
   404,   408,   411,   414,   415,   425,   427,   429,   430,   439,
   446,   453,   455,   457,   459,   461,   463,   464,   467,   470,
   473,   474,   477,   480,   486,   493,   501,   507,   509,   515,
   521,   522,   531,   532,   541,   542,   543,   552,   553,   560,
   561,   564,   566,   577,   581,   585,   589,   593,   597,   606,
   614,   620,   628,   630,   632,   634,   636,   638,   640,   642,
   644,   646,   648,   650,   652,   654,   656,   657,   660,   665,
   667,   669,   671,   673,   675,   677,   679,   681,   683,   685,
   687,   689,   694,   699,   704,   709,   711,   713,   715,   717,
   719,   721,   722,   724,   726,   728,   734
};

static const short yyrhs[] = {    -1,
    79,     0,    80,     0,    80,    79,     0,    81,     0,    82,
     0,   115,    86,    84,    88,   117,     0,    83,    86,    84,
    88,    90,    92,    94,     0,     9,    71,   191,     0,     0,
    10,    71,     3,    70,     3,    70,     5,    70,     5,    70,
   181,    70,    85,     0,    10,    71,     3,    70,     3,    70,
     4,    70,     4,    70,   181,     0,     5,     0,    51,     0,
     0,    64,    71,    87,     0,    65,    70,    87,     0,    65,
     0,     0,    89,    88,     0,     7,    71,    76,     0,     0,
    90,    91,     0,    23,    71,   125,     0,    24,    71,   126,
     0,     0,    93,     0,    99,     0,    99,    93,     0,    95,
     0,    96,     0,    44,     0,     0,    96,    97,     0,    37,
    71,    98,    70,    98,     0,    37,    71,    98,    70,     4,
     0,    72,     4,    70,    50,    70,   114,    73,     0,   101,
   107,     0,   100,   107,     0,    62,    71,   177,    70,   181,
    70,   104,    70,   106,    70,   191,   102,     0,    31,    71,
   177,    70,   181,    70,   103,    70,   105,    70,   106,   102,
     0,     0,    70,     5,     0,    72,     4,    70,     4,    73,
     0,    51,     0,    72,     4,    70,     4,    73,     0,    51,
     0,    72,   121,    70,   122,    73,     0,    51,     0,    72,
     4,    70,     4,    73,     0,    51,     0,     0,   107,   108,
     0,   109,     0,   110,     0,   111,     0,   131,     0,   135,
     0,   146,     0,   169,     0,   163,     0,   164,     0,   165,
     0,   170,     0,   171,     0,   151,     0,    63,    71,   191,
     0,    36,    71,     4,     0,    17,    71,   112,    70,   180,
    70,   113,    70,   114,     0,     5,     0,    51,     0,    50,
     0,    51,     0,     4,     0,    51,     0,     8,    71,   191,
    70,   116,     0,     3,     0,    51,     0,   118,     0,   118,
   117,     0,   119,   123,   129,     0,    12,     0,   120,    77,
     0,    11,    71,   121,    70,   122,     0,    57,     0,    58,
     0,    59,     0,    58,     0,     0,   123,   124,     0,    23,
    71,   125,     0,    25,    71,   127,     0,    24,    71,   126,
     0,   190,     0,   190,    70,   125,     0,   189,     0,   189,
    70,   126,     0,   188,     0,     0,   188,   128,    70,   127,
     0,     0,   129,   130,     0,   131,     0,   135,     0,   145,
     0,   146,     0,   147,     0,   168,     0,   152,     0,   154,
     0,   156,     0,   159,     0,   169,     0,   163,     0,   148,
     0,   149,     0,   150,     0,   151,     0,   170,     0,   171,
     0,   166,     0,   167,     0,     0,    15,   193,    71,   172,
    70,   174,    70,   179,   132,   133,     0,     0,   133,   134,
     0,    70,   191,     0,    70,    66,     0,    70,    67,     0,
    70,   182,     0,    70,    68,   191,     0,    13,   136,     0,
    14,   136,     0,     0,   193,    71,   173,    70,   175,   137,
    70,   138,   139,     0,   179,     0,    69,     0,     0,    70,
   140,    70,   141,    70,   142,   143,   144,     0,    70,   140,
    70,   142,   143,   144,     0,    70,   141,    70,   142,   143,
   144,     0,    51,     0,    47,     0,    76,     0,    51,     0,
     4,     0,     0,    70,    43,     0,    70,    51,     0,    70,
    49,     0,     0,    70,    43,     0,    70,    76,     0,    17,
    71,   180,    70,   179,     0,    16,   193,    71,   176,    70,
   179,     0,    18,    71,   179,    70,    50,    70,   180,     0,
    19,    71,   179,    70,    50,     0,    20,     0,    27,    71,
   179,    70,    61,     0,    28,    71,   179,    70,    61,     0,
     0,    28,    71,   162,   153,    70,   162,    70,    61,     0,
     0,    32,    71,   162,   155,    70,   162,    70,   191,     0,
     0,     0,    33,    71,   162,   157,    70,   162,   158,   161,
     0,     0,    34,    71,   162,   160,    70,   162,     0,     0,
    70,    61,     0,   196,     0,    35,    72,     4,    70,     4,
    70,     4,    70,     4,    73,     0,    40,    71,   179,     0,
    42,    71,   179,     0,    41,    71,   179,     0,    29,    71,
   196,     0,    30,    71,   196,     0,    21,    71,   196,    70,
   181,    70,   177,   178,     0,    26,    71,   179,    70,   182,
    70,   183,     0,    38,    71,   192,    70,   179,     0,    39,
    71,   179,    70,   194,    70,   191,     0,   189,     0,    51,
     0,   186,     0,   190,     0,    51,     0,   185,     0,   191,
     0,    51,     0,   191,     0,    51,     0,   191,     0,    51,
     0,   191,     0,    51,     0,     0,    70,    22,     0,    70,
    22,    70,     5,     0,   195,     0,   184,     0,    51,     0,
    45,     0,    51,     0,    46,     0,    51,     0,    56,     0,
   187,     0,    51,     0,    60,     0,    51,     0,    54,    74,
     4,    75,     0,    52,    74,     4,    75,     0,    53,    74,
     4,    75,     0,    55,    74,     4,    75,     0,   195,     0,
     3,     0,     3,     0,    76,     0,     4,     0,    51,     0,
     0,     6,     0,    48,     0,    51,     0,    72,     4,    70,
     4,    73,     0,    72,     4,    70,     4,    70,     4,    70,
     4,    73,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
   170,   171,   174,   175,   178,   179,   182,   209,   246,   258,
   267,   285,   303,   304,   307,   311,   318,   322,   328,   329,
   332,   349,   350,   353,   364,   377,   392,   395,   396,   399,
   400,   403,   411,   412,   415,   430,   446,   456,   460,   466,
   484,   502,   506,   512,   522,   528,   537,   543,   548,   554,
   559,   565,   566,   569,   570,   571,   572,   573,   574,   575,
   576,   577,   578,   579,   580,   581,   584,   593,   606,   626,
   627,   630,   631,   634,   635,   638,   651,   655,   661,   662,
   665,   671,   687,   700,   706,   707,   710,   711,   714,   715,
   718,   729,   744,   757,   764,   773,   780,   789,   796,   803,
   806,   807,   810,   811,   812,   813,   814,   815,   816,   817,
   818,   819,   820,   821,   822,   823,   824,   825,   826,   827,
   828,   829,   832,   860,   868,   869,   872,   876,   880,   884,
   888,   895,   898,   907,   927,   936,   945,   954,   964,   967,
   970,   975,   979,   985,   996,  1000,  1006,  1007,  1010,  1014,
  1020,  1021,  1024,  1030,  1048,  1065,  1107,  1121,  1127,  1144,
  1161,  1170,  1190,  1199,  1216,  1225,  1234,  1249,  1258,  1275,
  1279,  1285,  1289,  1309,  1325,  1338,  1351,  1366,  1381,  1447,
  1465,  1482,  1500,  1501,  1505,  1508,  1509,  1513,  1516,  1517,
  1523,  1524,  1530,  1538,  1541,  1551,  1554,  1558,  1562,  1568,
  1569,  1570,  1576,  1577,  1580,  1581,  1584,  1585,  1586,  1592,
  1593,  1596,  1605,  1614,  1623,  1632,  1635,  1646,  1658,  1661,
  1662,  1665,  1669,  1677,  1678,  1681,  1692
};

static const char * const yytname[] = {   "$","error","$undefined.","CHAR","INTEGER",
"BOOLEAN","PERCENT","MESSAGE_ID","MAZE_ID","LEVEL_ID","LEV_INIT_ID","GEOMETRY_ID",
"NOMAP_ID","OBJECT_ID","COBJECT_ID","MONSTER_ID","TRAP_ID","DOOR_ID","DRAWBRIDGE_ID",
"MAZEWALK_ID","WALLIFY_ID","REGION_ID","FILLING","RANDOM_OBJECTS_ID","RANDOM_MONSTERS_ID",
"RANDOM_PLACES_ID","ALTAR_ID","LADDER_ID","STAIR_ID","NON_DIGGABLE_ID","NON_PASSWALL_ID",
"ROOM_ID","PORTAL_ID","TELEPRT_ID","BRANCH_ID","LEV","CHANCE_ID","CORRIDOR_ID",
"GOLD_ID","ENGRAVING_ID","FOUNTAIN_ID","POOL_ID","SINK_ID","NONE","RAND_CORRIDOR_ID",
"DOOR_STATE","LIGHT_STATE","CURSE_TYPE","ENGRAVING_TYPE","MATERIAL_TYPE","DIRECTION",
"RANDOM_TYPE","O_REGISTER","M_REGISTER","P_REGISTER","A_REGISTER","ALIGNMENT",
"LEFT_OR_RIGHT","CENTER","TOP_OR_BOT","ALTAR_TYPE","UP_OR_DOWN","SUBROOM_ID",
"NAME_ID","FLAGS_ID","FLAG_TYPE","MON_ATTITUDE","MON_ALERTNESS","MON_APPEARANCE",
"CONTAINED","','","':'","'('","')'","'['","']'","STRING","MAP_ID","file","levels",
"level","maze_level","room_level","level_def","lev_init","walled","flags","flag_list",
"messages","message","rreg_init","init_rreg","rooms","roomlist","corridors_def",
"random_corridors","corridors","corridor","corr_spec","aroom","subroom_def",
"room_def","roomfill","room_pos","subroom_pos","room_align","room_size","room_details",
"room_detail","room_name","room_chance","room_door","secret","door_wall","door_pos",
"maze_def","filling","regions","aregion","map_definition","map_geometry","h_justif",
"v_justif","reg_init","init_reg","object_list","monster_list","place_list","@1",
"map_details","map_detail","monster_detail","@2","monster_infos","monster_info",
"object_detail","object_desc","@3","object_where","object_infos","curse_state",
"monster_id","enchantment","material_id","optional_name","door_detail","trap_detail",
"drawbridge_detail","mazewalk_detail","wallify_detail","ladder_detail","stair_detail",
"stair_region","@4","portal_region","@5","teleprt_region","@6","@7","branch_region",
"@8","teleprt_detail","lev_region","fountain_detail","sink_detail","pool_detail",
"diggable_detail","passwall_detail","region_detail","altar_detail","gold_detail",
"engraving_detail","monster_c","object_c","m_name","o_name","trap_name","room_type",
"prefilled","coordinate","door_state","light_state","alignment","altar_type",
"p_register","o_register","m_register","a_register","place","monster","object",
"string","amount","chance","engraving_type","coord","region",""
};
#endif

static const short yyr1[] = {     0,
    78,    78,    79,    79,    80,    80,    81,    82,    83,    84,
    84,    84,    85,    85,    86,    86,    87,    87,    88,    88,
    89,    90,    90,    91,    91,    92,    92,    93,    93,    94,
    94,    95,    96,    96,    97,    97,    98,    99,    99,   100,
   101,   102,   102,   103,   103,   104,   104,   105,   105,   106,
   106,   107,   107,   108,   108,   108,   108,   108,   108,   108,
   108,   108,   108,   108,   108,   108,   109,   110,   111,   112,
   112,   113,   113,   114,   114,   115,   116,   116,   117,   117,
   118,   119,   119,   120,   121,   121,   122,   122,   123,   123,
   124,   124,   124,   125,   125,   126,   126,   127,   128,   127,
   129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
   130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
   130,   130,   132,   131,   133,   133,   134,   134,   134,   134,
   134,   135,   135,   137,   136,   138,   138,   139,   139,   139,
   139,   140,   140,   141,   142,   142,   143,   143,   143,   143,
   144,   144,   144,   145,   146,   147,   148,   149,   150,   151,
   153,   152,   155,   154,   157,   158,   156,   160,   159,   161,
   161,   162,   162,   163,   164,   165,   166,   167,   168,   169,
   170,   171,   172,   172,   172,   173,   173,   173,   174,   174,
   175,   175,   176,   176,   177,   177,   178,   178,   178,   179,
   179,   179,   180,   180,   181,   181,   182,   182,   182,   183,
   183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
   192,   193,   193,   194,   194,   195,   196
};

static const short yyr2[] = {     0,
     0,     1,     1,     2,     1,     1,     5,     7,     3,     0,
    13,    11,     1,     1,     0,     3,     3,     1,     0,     2,
     3,     0,     2,     3,     3,     0,     1,     1,     2,     1,
     1,     1,     0,     2,     5,     5,     7,     2,     2,    12,
    12,     0,     2,     5,     1,     5,     1,     5,     1,     5,
     1,     0,     2,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     3,     3,     9,     1,
     1,     1,     1,     1,     1,     5,     1,     1,     1,     2,
     3,     1,     2,     5,     1,     1,     1,     1,     0,     2,
     3,     3,     3,     1,     3,     1,     3,     1,     0,     4,
     0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     0,    10,     0,     2,     2,     2,     2,     2,
     3,     2,     2,     0,     9,     1,     1,     0,     8,     6,
     6,     1,     1,     1,     1,     1,     0,     2,     2,     2,
     0,     2,     2,     5,     6,     7,     5,     1,     5,     5,
     0,     8,     0,     8,     0,     0,     8,     0,     6,     0,
     2,     1,    10,     3,     3,     3,     3,     3,     8,     7,
     5,     7,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     0,     2,     4,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     4,     4,     4,     4,     1,     1,     1,     1,     1,
     1,     0,     1,     1,     1,     5,     9
};

static const short yydefact[] = {     1,
     0,     0,     2,     3,     5,     6,    15,    15,     0,     0,
     4,     0,    10,    10,   219,     0,     9,     0,     0,    19,
    19,     0,    18,    16,     0,     0,    22,    19,     0,    77,
    78,    76,     0,     0,     0,    26,    20,     0,    82,     7,
    79,    89,     0,    17,     0,    21,     0,     0,     0,     0,
    23,    33,    27,    28,    52,    52,     0,    80,   101,    83,
     0,     0,     0,     0,     0,    32,     8,    30,    31,    29,
    39,    38,    85,    86,     0,     0,     0,     0,    90,    81,
     0,   218,    24,    94,   217,    25,    96,   196,     0,   195,
     0,     0,    34,   222,   222,   222,   222,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    53,    54,    55,
    56,    57,    58,    59,    66,    61,    62,    63,    60,    64,
    65,     0,     0,     0,     0,     0,     0,     0,   158,     0,
     0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
   105,   106,   107,   115,   116,   117,   118,   109,   110,   111,
   112,   114,   121,   122,   108,   113,   119,   120,     0,     0,
     0,     0,     0,     0,     0,   223,   132,     0,   133,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    88,    87,    84,    91,    93,     0,    92,    98,   216,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    95,    97,   205,   206,     0,     0,     0,
     0,     0,     0,     0,    70,    71,     0,   202,     0,     0,
   201,   200,     0,    68,   220,   221,     0,     0,   174,   176,
   175,    67,     0,     0,   203,   204,     0,     0,     0,     0,
     0,     0,     0,     0,   161,   172,   177,   178,   163,   165,
   168,     0,     0,     0,     0,     0,     0,   187,     0,     0,
   188,   186,   184,     0,     0,   185,   183,   194,     0,   193,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    45,     0,     0,    47,     0,     0,     0,    36,
    35,     0,     0,     0,     0,     0,     0,     0,   209,     0,
   207,     0,   208,   160,   181,   224,   225,     0,     0,   100,
   154,     0,   157,     0,     0,   159,     0,     0,     0,     0,
     0,     0,    12,     0,     0,     0,     0,     0,     0,     0,
   192,   134,   191,     0,   190,     0,   189,   155,     0,   212,
     0,     0,     0,   226,     0,     0,     0,     0,     0,     0,
     0,   166,   169,     0,     0,    49,     0,     0,     0,    51,
     0,     0,     0,   213,     0,   214,     0,    72,    73,     0,
     0,   211,   210,   180,   182,   156,     0,   197,     0,     0,
     0,   170,    13,    14,    11,     0,     0,     0,     0,     0,
     0,    74,    75,     0,     0,   123,     0,   215,     0,     0,
   179,     0,   162,   164,     0,   167,    44,     0,    42,    46,
     0,    42,    37,   137,   138,   136,   125,    69,     0,   198,
     0,   171,     0,     0,    41,     0,    40,     0,   135,   124,
     0,     0,     0,    48,    43,    50,   143,   142,   144,     0,
     0,     0,   126,   227,   199,     0,     0,     0,   128,   129,
     0,   130,   127,   173,   146,   145,     0,   147,   147,   131,
     0,     0,   151,   151,   147,   148,   150,   149,     0,   140,
   141,   151,   152,   153,   139,     0,     0,     0
};

static const short yydefgoto[] = {   486,
     3,     4,     5,     6,     7,    20,   395,    13,    24,    27,
    28,    36,    51,    52,    53,    67,    68,    69,    93,   211,
    54,    55,    56,   435,   295,   298,   368,   372,    71,   108,
   109,   110,   111,   217,   380,   404,     8,    32,    40,    41,
    42,    43,    75,   184,    59,    79,    83,    86,   188,   234,
    80,   138,   112,   427,   440,   453,   113,   167,   375,   425,
   439,   450,   451,   468,   473,   480,   141,   114,   143,   144,
   145,   146,   115,   148,   287,   149,   288,   150,   289,   392,
   151,   290,   416,   245,   116,   117,   118,   153,   154,   155,
   119,   120,   121,   265,   260,   346,   342,   269,    89,   411,
   223,   237,   208,   312,   384,   221,   261,   266,   313,   189,
    87,    84,    90,   227,   168,   318,   222,   246
};

static const short yypact[] = {   137,
   -16,    38,-32768,   137,-32768,-32768,   -11,   -11,   -12,   -12,
-32768,    46,    81,    81,-32768,    56,-32768,    82,    89,   170,
   170,    25,   122,-32768,   190,   123,-32768,   170,   147,-32768,
-32768,-32768,    82,   126,   119,    27,-32768,   127,-32768,-32768,
   147,-32768,   120,-32768,   196,-32768,   129,   130,   131,   132,
-32768,   160,-32768,     6,-32768,-32768,   125,-32768,   113,-32768,
   139,   204,   205,   -13,   -13,-32768,-32768,-32768,   173,-32768,
     3,     3,-32768,-32768,   141,   142,   143,   144,-32768,   135,
   180,-32768,-32768,   146,-32768,-32768,   148,-32768,   149,-32768,
   150,   151,-32768,   206,   206,   206,   206,   152,   153,   154,
   155,   156,   157,   158,   159,   161,   162,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   128,   204,   205,   145,   164,   165,   166,-32768,   167,
   168,   169,   171,   172,   174,   175,   176,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   178,   179,
   204,   205,    93,    93,   181,-32768,-32768,   183,-32768,   184,
   185,    29,    47,    47,   217,    21,    47,    47,    47,    47,
   -12,-32768,-32768,-32768,-32768,-32768,   227,-32768,   182,-32768,
    80,    47,    47,   186,    47,    -2,   186,   186,    12,    12,
    12,   237,   239,-32768,-32768,-32768,-32768,   187,   189,   246,
   191,    23,    20,    16,-32768,-32768,   192,-32768,   177,   193,
-32768,-32768,   194,-32768,-32768,-32768,   195,   197,-32768,-32768,
-32768,-32768,   198,   199,-32768,-32768,   200,   201,   202,   256,
   203,   207,   208,   262,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   209,   211,    31,    48,   212,    11,-32768,   210,   213,
-32768,-32768,-32768,   214,   215,-32768,-32768,-32768,   216,-32768,
    80,   270,   115,   226,    47,    79,   271,   145,    47,   228,
   240,   219,    93,   230,   272,   222,   223,   229,   231,   232,
    93,    93,-32768,   293,   233,-32768,   294,   234,   250,-32768,
-32768,   301,    36,   302,    37,    47,   238,   235,-32768,   241,
-32768,   242,-32768,-32768,-32768,-32768,-32768,   243,   236,-32768,
-32768,   244,-32768,   303,   247,-32768,   248,   307,    12,    12,
    12,    12,-32768,   249,   251,    49,   252,    51,   253,   245,
-32768,-32768,-32768,   254,-32768,   255,-32768,-32768,   138,-32768,
   312,    -3,   -12,-32768,    80,   257,   -13,   320,   108,   258,
   260,-32768,-32768,    30,   322,-32768,   125,   261,   328,-32768,
   329,   264,    26,-32768,   265,-32768,    47,-32768,-32768,   266,
   263,-32768,-32768,-32768,-32768,-32768,   333,   269,   273,   279,
   -12,   275,-32768,-32768,-32768,   268,   276,    51,   274,   278,
   -12,-32768,-32768,   277,    42,-32768,    26,-32768,   281,   327,
-32768,   338,-32768,-32768,   291,-32768,-32768,   128,   283,-32768,
   350,   283,-32768,-32768,   285,-32768,-32768,-32768,   352,   287,
   288,-32768,   286,   355,-32768,   289,-32768,     9,-32768,   295,
   290,   356,   360,-32768,-32768,-32768,-32768,-32768,-32768,   296,
   297,    39,-32768,-32768,-32768,   298,    10,    28,-32768,-32768,
   -12,-32768,-32768,-32768,-32768,-32768,   299,   300,   300,-32768,
    28,    67,   304,   304,   300,-32768,-32768,-32768,    -7,-32768,
-32768,   304,-32768,-32768,-32768,   368,   372,-32768
};

static const short yypgoto[] = {-32768,
   369,-32768,-32768,-32768,-32768,   361,-32768,   370,   343,   101,
-32768,-32768,-32768,-32768,   323,-32768,-32768,-32768,-32768,   124,
-32768,-32768,-32768,   -43,-32768,-32768,-32768,   -15,   324,-32768,
-32768,-32768,-32768,-32768,-32768,   -23,-32768,-32768,   344,-32768,
-32768,-32768,    19,   -31,-32768,-32768,   -96,   -84,   110,-32768,
-32768,-32768,   309,-32768,-32768,-32768,   310,   305,-32768,-32768,
-32768,-32768,   -66,  -412,  -341,  -420,-32768,   313,-32768,-32768,
-32768,-32768,   314,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,  -189,   315,-32768,-32768,-32768,-32768,-32768,
   316,   317,   318,-32768,-32768,-32768,-32768,-32768,   -62,-32768,
  -171,  -258,  -159,   -53,-32768,-32768,-32768,-32768,-32768,-32768,
   188,   218,    -9,-32768,    94,-32768,  -121,   -18
};


#define	YYLAST		452


static const short yytable[] = {    16,
    17,   220,    91,   190,   209,   228,   229,   230,   231,   249,
   250,   251,   307,   465,   300,    94,    95,    96,    97,    98,
   238,   239,    85,   242,   225,    82,   185,    30,    99,   402,
   100,   465,   243,   215,   393,   483,    49,    88,   101,   186,
   102,   103,   104,   105,   106,   469,   243,   382,   218,    47,
    48,   219,    12,   481,     9,   447,   383,    49,   475,   448,
   466,   485,    15,    15,   204,   107,   268,    50,   484,   244,
   263,   226,   264,   258,   259,    31,   403,   205,   466,   216,
   394,   293,   210,   240,   449,   449,   341,   345,    50,   309,
    19,    15,   218,   310,   311,   219,   386,   218,   296,   366,
   219,   370,   294,   315,   459,   460,   461,   321,    10,   476,
   424,    15,    15,   187,    15,   477,    18,   478,   187,   297,
   367,    29,   371,   325,   235,    22,   316,   474,    37,   317,
   236,   333,   334,   482,   348,    76,    77,    78,   206,   360,
   361,   362,   363,   207,     1,     2,    23,    94,    95,    96,
    97,   126,   127,   128,   129,   130,   190,    38,    39,    25,
    99,   131,   132,   133,   134,   309,   135,   136,   137,   310,
   311,   232,   102,   103,   104,   241,    26,   387,   247,   248,
   354,    73,    74,   159,   160,   182,   183,   378,   379,   170,
   171,    33,    34,    35,    46,    45,    60,    57,    61,    62,
    63,    64,    65,    66,   270,   406,    82,    85,    81,    92,
   122,   166,   123,   124,   125,   161,   187,   162,   163,   164,
   224,   165,   172,   173,   174,   175,   176,   177,   178,   179,
   233,   180,   181,   426,   191,   192,   193,   194,   195,   196,
   252,   197,   198,   253,   199,   200,   201,   202,   203,   256,
   272,   -99,   210,   212,   213,   214,   254,   240,   255,   282,
   257,   271,   273,   274,   275,   286,   276,   277,   278,   279,
   280,   281,   283,   308,   319,   327,   284,   322,   291,   285,
   292,   299,   303,   302,   305,   306,   314,   304,   324,   323,
   326,   328,   329,   343,   388,   347,   335,   337,   330,   339,
   331,   332,   336,   338,   340,   344,   356,   349,   354,   350,
   359,   352,   353,   355,   351,   381,   357,   358,   364,   374,
   365,   369,   373,   389,   377,   396,   387,   390,   376,   391,
   398,   399,   400,   401,   405,   407,   409,   408,   410,   413,
   417,   431,   412,   385,   415,   418,   420,   421,   430,   423,
   429,   432,   434,   436,   438,   441,   442,   443,   444,   445,
   455,   446,   454,   456,   452,   457,   458,   487,   471,   472,
   464,   488,    11,   479,    21,    44,    70,    14,   437,    72,
   301,   414,   419,   428,    58,   397,   433,   320,   139,   140,
   467,   422,   142,   147,   152,   156,   157,   158,   462,   169,
   267,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   262,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   463,     0,     0,     0,     0,     0,     0,     0,
     0,   470
};

static const short yycheck[] = {     9,
    10,   173,    65,   125,   164,   177,   178,   179,   180,   199,
   200,   201,   271,     4,     4,    13,    14,    15,    16,    17,
   192,   193,     3,   195,     4,     3,   123,     3,    26,     4,
    28,     4,    35,     5,     5,    43,    31,    51,    36,   124,
    38,    39,    40,    41,    42,   458,    35,    51,    51,    23,
    24,    54,    64,   474,    71,    47,    60,    31,   471,    51,
    51,   482,    76,    76,   161,    63,    51,    62,    76,    72,
    51,    51,    53,    51,    52,    51,    51,   162,    51,    51,
    51,    51,    72,    72,    76,    76,    51,    51,    62,    51,
    10,    76,    51,    55,    56,    54,   355,    51,    51,    51,
    54,    51,    72,   275,    66,    67,    68,   279,    71,    43,
    69,    76,    76,    72,    76,    49,    71,    51,    72,    72,
    72,    21,    72,   283,    45,    70,    48,   469,    28,    51,
    51,   291,   292,   475,   306,    23,    24,    25,    46,   329,
   330,   331,   332,    51,     8,     9,    65,    13,    14,    15,
    16,    17,    18,    19,    20,    21,   278,    11,    12,    71,
    26,    27,    28,    29,    30,    51,    32,    33,    34,    55,
    56,   181,    38,    39,    40,   194,     7,    70,   197,   198,
    73,    57,    58,     4,     5,    58,    59,    50,    51,    96,
    97,    70,     3,    71,    76,    70,    77,    71,     3,    71,
    71,    71,    71,    44,   214,   377,     3,     3,    70,    37,
    70,     6,    71,    71,    71,    70,    72,    70,    70,    70,
     4,    71,    71,    71,    71,    71,    71,    71,    71,    71,
     4,    71,    71,   405,    71,    71,    71,    71,    71,    71,
     4,    71,    71,     5,    71,    71,    71,    70,    70,     4,
    74,    70,    72,    71,    71,    71,    70,    72,    70,     4,
    70,    70,    70,    70,    70,     4,    70,    70,    70,    70,
    70,    70,    70,     4,     4,     4,    70,    50,    70,    72,
    70,    70,    70,    74,    70,    70,    61,    74,    70,    50,
    61,    70,    70,   303,   357,   305,     4,     4,    70,    50,
    70,    70,    70,    70,     4,     4,     4,    70,    73,    75,
     4,    70,    70,    70,    74,     4,    70,    70,    70,    75,
    70,    70,    70,     4,    70,     4,    70,    70,    75,    70,
    70,     4,     4,    70,    70,    70,     4,    75,    70,    61,
    73,     4,    70,   353,    70,    70,    73,    70,    22,    73,
    70,    61,    70,     4,    70,     4,    70,    70,    73,     5,
     5,    73,    73,     4,    70,    70,    70,     0,    70,    70,
    73,     0,     4,    70,    14,    33,    54,     8,   422,    56,
   257,   391,   398,   407,    41,   367,   418,   278,    80,    80,
   457,   401,    80,    80,    80,    80,    80,    80,   452,    95,
   213,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   212,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   452,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   461
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(FROM,TO,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (from, to, count)
     char *from;
     char *to;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *from, char *to, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 192 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#else
#define YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#endif

int
yyparse(YYPARSE_PARAM)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss1, (char *)yyss, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs1, (char *)yyvs, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls1, (char *)yyls, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 7:
#line 183 "lev_comp.y"
{
			unsigned i;

			if (fatal_error > 0) {
				(void) fprintf(stderr,
				"%s : %d errors detected. No output created!\n",
					fname, fatal_error);
			} else {
				maze.flags = yyvsp[-3].i;
				(void) memcpy((genericptr_t)&(maze.init_lev),
						(genericptr_t)&(init_lev),
						sizeof(lev_init));
				maze.numpart = npart;
				maze.parts = NewTab(mazepart, npart);
				for(i=0;i<npart;i++)
				    maze.parts[i] = tmppart[i];
				if (!write_level_file(yyvsp[-4].map, (splev *)0, &maze)) {
					yyerror("Can't write output file!!");
					exit(EXIT_FAILURE);
				}
				npart = 0;
			}
			Free(yyvsp[-4].map);
		  ;
    break;}
case 8:
#line 210 "lev_comp.y"
{
			unsigned i;

			if (fatal_error > 0) {
			    (void) fprintf(stderr,
			      "%s : %d errors detected. No output created!\n",
					fname, fatal_error);
			} else {
				special_lev.flags = (long) yyvsp[-5].i;
				(void) memcpy(
					(genericptr_t)&(special_lev.init_lev),
					(genericptr_t)&(init_lev),
					sizeof(lev_init));
				special_lev.nroom = nrooms;
				special_lev.rooms = NewTab(room, nrooms);
				for(i=0; i<nrooms; i++)
				    special_lev.rooms[i] = tmproom[i];
				special_lev.ncorr = ncorridor;
				special_lev.corrs = NewTab(corridor, ncorridor);
				for(i=0; i<ncorridor; i++)
				    special_lev.corrs[i] = tmpcor[i];
				if (check_subrooms()) {
				    if (!write_level_file(yyvsp[-6].map, &special_lev,
							  (specialmaze *)0)) {
					yyerror("Can't write output file!!");
					exit(EXIT_FAILURE);
				    }
				}
				free_rooms(&special_lev);
				nrooms = 0;
				ncorridor = 0;
			}
			Free(yyvsp[-6].map);
		  ;
    break;}
case 9:
#line 247 "lev_comp.y"
{
			if (index(yyvsp[0].map, '.'))
			    yyerror("Invalid dot ('.') in level name.");
			if ((int) strlen(yyvsp[0].map) > 8)
			    yyerror("Level names limited to 8 characters.");
			yyval.map = yyvsp[0].map;
			special_lev.nrmonst = special_lev.nrobjects = 0;
			n_mlist = n_olist = 0;
		  ;
    break;}
case 10:
#line 259 "lev_comp.y"
{
			/* in case we're processing multiple files,
			   explicitly clear any stale settings */
			(void) memset((genericptr_t) &init_lev, 0,
					sizeof init_lev);
			init_lev.init_present = FALSE;
			yyval.i = 0;
		  ;
    break;}
case 11:
#line 268 "lev_comp.y"
{
			init_lev.init_present = 1;
			init_lev.fg = what_map_char((char) yyvsp[-10].i);
			if (init_lev.fg == INVALID_TYPE)
			    yyerror("Invalid foreground type.");
			init_lev.bg = what_map_char((char) yyvsp[-8].i);
			if (init_lev.bg == INVALID_TYPE)
			    yyerror("Invalid background type.");
			init_lev.smoothed = yyvsp[-6].i;
			init_lev.joined = yyvsp[-4].i;
			if (init_lev.joined &&
			    init_lev.fg != CORR && init_lev.fg != ROOM)
			    yyerror("Invalid foreground type for joined map.");
			init_lev.lit = yyvsp[-2].i;
			init_lev.walled = yyvsp[0].i;
			yyval.i = 1;
		  ;
    break;}
case 12:
#line 286 "lev_comp.y"
{
			init_lev.init_present = yyvsp[-4].i;
			init_lev.arg = yyvsp[-2].i;
			init_lev.fg = what_map_char((char) yyvsp[-8].i);
			if (init_lev.fg == INVALID_TYPE)
			    yyerror("Invalid foreground type.");
			init_lev.bg = what_map_char((char) yyvsp[-6].i);
			if (init_lev.bg == INVALID_TYPE)
			    yyerror("Invalid background type.");
			init_lev.lit = yyvsp[0].i;
			init_lev.smoothed = 0;
			init_lev.joined = 0;
			init_lev.walled = 0;
			yyval.i = 1;
		  ;
    break;}
case 15:
#line 308 "lev_comp.y"
{
			yyval.i = 0;
		  ;
    break;}
case 16:
#line 312 "lev_comp.y"
{
			yyval.i = lev_flags;
			lev_flags = 0;	/* clear for next user */
		  ;
    break;}
case 17:
#line 319 "lev_comp.y"
{
			lev_flags |= yyvsp[-2].i;
		  ;
    break;}
case 18:
#line 323 "lev_comp.y"
{
			lev_flags |= yyvsp[0].i;
		  ;
    break;}
case 21:
#line 333 "lev_comp.y"
{
			int i, j;

			i = (int) strlen(yyvsp[0].map) + 1;
			j = (int) strlen(tmpmessage);
			if (i + j > 255) {
			   yyerror("Message string too long (>256 characters)");
			} else {
			    if (j) tmpmessage[j++] = '\n';
			    (void) strncpy(tmpmessage+j, yyvsp[0].map, i - 1);
			    tmpmessage[j + i - 1] = 0;
			}
			Free(yyvsp[0].map);
		  ;
    break;}
case 24:
#line 354 "lev_comp.y"
{
			if(special_lev.nrobjects) {
			    yyerror("Object registers already initialized!");
			} else {
			    special_lev.nrobjects = n_olist;
			    special_lev.robjects = (char *) alloc(n_olist);
			    (void) memcpy((genericptr_t)special_lev.robjects,
					  (genericptr_t)olist, n_olist);
			}
		  ;
    break;}
case 25:
#line 365 "lev_comp.y"
{
			if(special_lev.nrmonst) {
			    yyerror("Monster registers already initialized!");
			} else {
			    special_lev.nrmonst = n_mlist;
			    special_lev.rmonst = (char *) alloc(n_mlist);
			    (void) memcpy((genericptr_t)special_lev.rmonst,
					  (genericptr_t)mlist, n_mlist);
			  }
		  ;
    break;}
case 26:
#line 378 "lev_comp.y"
{
			tmproom[nrooms] = New(room);
			tmproom[nrooms]->name = (char *) 0;
			tmproom[nrooms]->parent = (char *) 0;
			tmproom[nrooms]->rtype = 0;
			tmproom[nrooms]->rlit = 0;
			tmproom[nrooms]->xalign = ERR;
			tmproom[nrooms]->yalign = ERR;
			tmproom[nrooms]->x = 0;
			tmproom[nrooms]->y = 0;
			tmproom[nrooms]->w = 2;
			tmproom[nrooms]->h = 2;
			in_room = 1;
		  ;
    break;}
case 32:
#line 404 "lev_comp.y"
{
			tmpcor[0] = New(corridor);
			tmpcor[0]->src.room = -1;
			ncorridor = 1;
		  ;
    break;}
case 35:
#line 416 "lev_comp.y"
{
			tmpcor[ncorridor] = New(corridor);
			tmpcor[ncorridor]->src.room = yyvsp[-2].corpos.room;
			tmpcor[ncorridor]->src.wall = yyvsp[-2].corpos.wall;
			tmpcor[ncorridor]->src.door = yyvsp[-2].corpos.door;
			tmpcor[ncorridor]->dest.room = yyvsp[0].corpos.room;
			tmpcor[ncorridor]->dest.wall = yyvsp[0].corpos.wall;
			tmpcor[ncorridor]->dest.door = yyvsp[0].corpos.door;
			ncorridor++;
			if (ncorridor >= MAX_OF_TYPE) {
				yyerror("Too many corridors in level!");
				ncorridor--;
			}
		  ;
    break;}
case 36:
#line 431 "lev_comp.y"
{
			tmpcor[ncorridor] = New(corridor);
			tmpcor[ncorridor]->src.room = yyvsp[-2].corpos.room;
			tmpcor[ncorridor]->src.wall = yyvsp[-2].corpos.wall;
			tmpcor[ncorridor]->src.door = yyvsp[-2].corpos.door;
			tmpcor[ncorridor]->dest.room = -1;
			tmpcor[ncorridor]->dest.wall = yyvsp[0].i;
			ncorridor++;
			if (ncorridor >= MAX_OF_TYPE) {
				yyerror("Too many corridors in level!");
				ncorridor--;
			}
		  ;
    break;}
case 37:
#line 447 "lev_comp.y"
{
			if ((unsigned) yyvsp[-5].i >= nrooms)
			    yyerror("Wrong room number!");
			yyval.corpos.room = yyvsp[-5].i;
			yyval.corpos.wall = yyvsp[-3].i;
			yyval.corpos.door = yyvsp[-1].i;
		  ;
    break;}
case 38:
#line 457 "lev_comp.y"
{
			store_room();
		  ;
    break;}
case 39:
#line 461 "lev_comp.y"
{
			store_room();
		  ;
    break;}
case 40:
#line 467 "lev_comp.y"
{
			tmproom[nrooms] = New(room);
			tmproom[nrooms]->parent = yyvsp[-1].map;
			tmproom[nrooms]->name = (char *) 0;
			tmproom[nrooms]->rtype = yyvsp[-9].i;
			tmproom[nrooms]->rlit = yyvsp[-7].i;
			tmproom[nrooms]->filled = yyvsp[0].i;
			tmproom[nrooms]->xalign = ERR;
			tmproom[nrooms]->yalign = ERR;
			tmproom[nrooms]->x = current_coord.x;
			tmproom[nrooms]->y = current_coord.y;
			tmproom[nrooms]->w = current_size.width;
			tmproom[nrooms]->h = current_size.height;
			in_room = 1;
		  ;
    break;}
case 41:
#line 485 "lev_comp.y"
{
			tmproom[nrooms] = New(room);
			tmproom[nrooms]->name = (char *) 0;
			tmproom[nrooms]->parent = (char *) 0;
			tmproom[nrooms]->rtype = yyvsp[-9].i;
			tmproom[nrooms]->rlit = yyvsp[-7].i;
			tmproom[nrooms]->filled = yyvsp[0].i;
			tmproom[nrooms]->xalign = current_align.x;
			tmproom[nrooms]->yalign = current_align.y;
			tmproom[nrooms]->x = current_coord.x;
			tmproom[nrooms]->y = current_coord.y;
			tmproom[nrooms]->w = current_size.width;
			tmproom[nrooms]->h = current_size.height;
			in_room = 1;
		  ;
    break;}
case 42:
#line 503 "lev_comp.y"
{
			yyval.i = 1;
		  ;
    break;}
case 43:
#line 507 "lev_comp.y"
{
			yyval.i = yyvsp[0].i;
		  ;
    break;}
case 44:
#line 513 "lev_comp.y"
{
			if ( yyvsp[-3].i < 1 || yyvsp[-3].i > 5 ||
			    yyvsp[-1].i < 1 || yyvsp[-1].i > 5 ) {
			    yyerror("Room position should be between 1 & 5!");
			} else {
			    current_coord.x = yyvsp[-3].i;
			    current_coord.y = yyvsp[-1].i;
			}
		  ;
    break;}
case 45:
#line 523 "lev_comp.y"
{
			current_coord.x = current_coord.y = ERR;
		  ;
    break;}
case 46:
#line 529 "lev_comp.y"
{
			if ( yyvsp[-3].i < 0 || yyvsp[-1].i < 0) {
			    yyerror("Invalid subroom position !");
			} else {
			    current_coord.x = yyvsp[-3].i;
			    current_coord.y = yyvsp[-1].i;
			}
		  ;
    break;}
case 47:
#line 538 "lev_comp.y"
{
			current_coord.x = current_coord.y = ERR;
		  ;
    break;}
case 48:
#line 544 "lev_comp.y"
{
			current_align.x = yyvsp[-3].i;
			current_align.y = yyvsp[-1].i;
		  ;
    break;}
case 49:
#line 549 "lev_comp.y"
{
			current_align.x = current_align.y = ERR;
		  ;
    break;}
case 50:
#line 555 "lev_comp.y"
{
			current_size.width = yyvsp[-3].i;
			current_size.height = yyvsp[-1].i;
		  ;
    break;}
case 51:
#line 560 "lev_comp.y"
{
			current_size.height = current_size.width = ERR;
		  ;
    break;}
case 67:
#line 585 "lev_comp.y"
{
			if (tmproom[nrooms]->name)
			    yyerror("This room already has a name!");
			else
			    tmproom[nrooms]->name = yyvsp[0].map;
		  ;
    break;}
case 68:
#line 594 "lev_comp.y"
{
			if (tmproom[nrooms]->chance)
			    yyerror("This room already assigned a chance!");
			else if (tmproom[nrooms]->rtype == OROOM)
			    yyerror("Only typed rooms can have a chance!");
			else if (yyvsp[0].i < 1 || yyvsp[0].i > 99)
			    yyerror("The chance is supposed to be percentile.");
			else
			    tmproom[nrooms]->chance = yyvsp[0].i;
		   ;
    break;}
case 69:
#line 607 "lev_comp.y"
{
			/* ERR means random here */
			if (yyvsp[-2].i == ERR && yyvsp[0].i != ERR) {
		     yyerror("If the door wall is random, so must be its pos!");
			} else {
			    tmprdoor[ndoor] = New(room_door);
			    tmprdoor[ndoor]->secret = yyvsp[-6].i;
			    tmprdoor[ndoor]->mask = yyvsp[-4].i;
			    tmprdoor[ndoor]->wall = yyvsp[-2].i;
			    tmprdoor[ndoor]->pos = yyvsp[0].i;
			    ndoor++;
			    if (ndoor >= MAX_OF_TYPE) {
				    yyerror("Too many doors in room!");
				    ndoor--;
			    }
			}
		  ;
    break;}
case 76:
#line 639 "lev_comp.y"
{
			maze.filling = (schar) yyvsp[0].i;
			if (index(yyvsp[-2].map, '.'))
			    yyerror("Invalid dot ('.') in level name.");
			if ((int) strlen(yyvsp[-2].map) > 8)
			    yyerror("Level names limited to 8 characters.");
			yyval.map = yyvsp[-2].map;
			in_room = 0;
			n_plist = n_mlist = n_olist = 0;
		  ;
    break;}
case 77:
#line 652 "lev_comp.y"
{
			yyval.i = get_floor_type((char)yyvsp[0].i);
		  ;
    break;}
case 78:
#line 656 "lev_comp.y"
{
			yyval.i = -1;
		  ;
    break;}
case 81:
#line 666 "lev_comp.y"
{
			store_part();
		  ;
    break;}
case 82:
#line 672 "lev_comp.y"
{
			tmppart[npart] = New(mazepart);
			tmppart[npart]->halign = 1;
			tmppart[npart]->valign = 1;
			tmppart[npart]->nrobjects = 0;
			tmppart[npart]->nloc = 0;
			tmppart[npart]->nrmonst = 0;
			tmppart[npart]->xsize = 1;
			tmppart[npart]->ysize = 1;
			tmppart[npart]->map = (char **) alloc(sizeof(char *));
			tmppart[npart]->map[0] = (char *) alloc(1);
			tmppart[npart]->map[0][0] = STONE;
			max_x_map = COLNO-1;
			max_y_map = ROWNO;
		  ;
    break;}
case 83:
#line 688 "lev_comp.y"
{
			tmppart[npart] = New(mazepart);
			tmppart[npart]->halign = yyvsp[-1].i % 10;
			tmppart[npart]->valign = yyvsp[-1].i / 10;
			tmppart[npart]->nrobjects = 0;
			tmppart[npart]->nloc = 0;
			tmppart[npart]->nrmonst = 0;
			scan_map(yyvsp[0].map);
			Free(yyvsp[0].map);
		  ;
    break;}
case 84:
#line 701 "lev_comp.y"
{
			yyval.i = yyvsp[-2].i + (yyvsp[0].i * 10);
		  ;
    break;}
case 91:
#line 719 "lev_comp.y"
{
			if (tmppart[npart]->nrobjects) {
			    yyerror("Object registers already initialized!");
			} else {
			    tmppart[npart]->robjects = (char *)alloc(n_olist);
			    (void) memcpy((genericptr_t)tmppart[npart]->robjects,
					  (genericptr_t)olist, n_olist);
			    tmppart[npart]->nrobjects = n_olist;
			}
		  ;
    break;}
case 92:
#line 730 "lev_comp.y"
{
			if (tmppart[npart]->nloc) {
			    yyerror("Location registers already initialized!");
			} else {
			    register int i;
			    tmppart[npart]->rloc_x = (char *) alloc(n_plist);
			    tmppart[npart]->rloc_y = (char *) alloc(n_plist);
			    for(i=0;i<n_plist;i++) {
				tmppart[npart]->rloc_x[i] = plist[i].x;
				tmppart[npart]->rloc_y[i] = plist[i].y;
			    }
			    tmppart[npart]->nloc = n_plist;
			}
		  ;
    break;}
case 93:
#line 745 "lev_comp.y"
{
			if (tmppart[npart]->nrmonst) {
			    yyerror("Monster registers already initialized!");
			} else {
			    tmppart[npart]->rmonst = (char *) alloc(n_mlist);
			    (void) memcpy((genericptr_t)tmppart[npart]->rmonst,
					  (genericptr_t)mlist, n_mlist);
			    tmppart[npart]->nrmonst = n_mlist;
			}
		  ;
    break;}
case 94:
#line 758 "lev_comp.y"
{
			if (n_olist < MAX_REGISTERS)
			    olist[n_olist++] = yyvsp[0].i;
			else
			    yyerror("Object list too long!");
		  ;
    break;}
case 95:
#line 765 "lev_comp.y"
{
			if (n_olist < MAX_REGISTERS)
			    olist[n_olist++] = yyvsp[-2].i;
			else
			    yyerror("Object list too long!");
		  ;
    break;}
case 96:
#line 774 "lev_comp.y"
{
			if (n_mlist < MAX_REGISTERS)
			    mlist[n_mlist++] = yyvsp[0].i;
			else
			    yyerror("Monster list too long!");
		  ;
    break;}
case 97:
#line 781 "lev_comp.y"
{
			if (n_mlist < MAX_REGISTERS)
			    mlist[n_mlist++] = yyvsp[-2].i;
			else
			    yyerror("Monster list too long!");
		  ;
    break;}
case 98:
#line 790 "lev_comp.y"
{
			if (n_plist < MAX_REGISTERS)
			    plist[n_plist++] = current_coord;
			else
			    yyerror("Location list too long!");
		  ;
    break;}
case 99:
#line 797 "lev_comp.y"
{
			if (n_plist < MAX_REGISTERS)
			    plist[n_plist++] = current_coord;
			else
			    yyerror("Location list too long!");
		  ;
    break;}
case 123:
#line 833 "lev_comp.y"
{
			tmpmonst[nmons] = New(monster);
			tmpmonst[nmons]->x = current_coord.x;
			tmpmonst[nmons]->y = current_coord.y;
			tmpmonst[nmons]->class = yyvsp[-4].i;
			tmpmonst[nmons]->peaceful = -1; /* no override */
			tmpmonst[nmons]->asleep = -1;
			tmpmonst[nmons]->align = - MAX_REGISTERS - 2;
			tmpmonst[nmons]->name.str = 0;
			tmpmonst[nmons]->appear = 0;
			tmpmonst[nmons]->appear_as.str = 0;
			tmpmonst[nmons]->chance = yyvsp[-6].i;
			tmpmonst[nmons]->id = NON_PM;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Monster");
			if (yyvsp[-2].map) {
			    int token = get_monster_id(yyvsp[-2].map, (char) yyvsp[-4].i);
			    if (token == ERR)
				yywarning(
			      "Invalid monster name!  Making random monster.");
			    else
				tmpmonst[nmons]->id = token;
			    Free(yyvsp[-2].map);
			}
		  ;
    break;}
case 124:
#line 860 "lev_comp.y"
{
			if (++nmons >= MAX_OF_TYPE) {
			    yyerror("Too many monsters in room or mazepart!");
			    nmons--;
			}
		  ;
    break;}
case 127:
#line 873 "lev_comp.y"
{
			tmpmonst[nmons]->name.str = yyvsp[0].map;
		  ;
    break;}
case 128:
#line 877 "lev_comp.y"
{
			tmpmonst[nmons]->peaceful = yyvsp[0].i;
		  ;
    break;}
case 129:
#line 881 "lev_comp.y"
{
			tmpmonst[nmons]->asleep = yyvsp[0].i;
		  ;
    break;}
case 130:
#line 885 "lev_comp.y"
{
			tmpmonst[nmons]->align = yyvsp[0].i;
		  ;
    break;}
case 131:
#line 889 "lev_comp.y"
{
			tmpmonst[nmons]->appear = yyvsp[-1].i;
			tmpmonst[nmons]->appear_as.str = yyvsp[0].map;
		  ;
    break;}
case 132:
#line 896 "lev_comp.y"
{
		  ;
    break;}
case 133:
#line 899 "lev_comp.y"
{
			/* 1: is contents of preceeding object with 2 */
			/* 2: is a container */
			/* 0: neither */
			tmpobj[nobj-1]->containment = 2;
		  ;
    break;}
case 134:
#line 908 "lev_comp.y"
{
			tmpobj[nobj] = New(object);
			tmpobj[nobj]->class = yyvsp[-2].i;
			tmpobj[nobj]->corpsenm = NON_PM;
			tmpobj[nobj]->curse_state = -1;
			tmpobj[nobj]->name.str = 0;
			tmpobj[nobj]->chance = yyvsp[-4].i;
			tmpobj[nobj]->material = -127;
			tmpobj[nobj]->id = -1;
			if (yyvsp[0].map) {
			    int token = get_object_id(yyvsp[0].map, yyvsp[-2].i);
			    if (token == ERR)
				yywarning(
				"Illegal object name!  Making random object.");
			     else
				tmpobj[nobj]->id = token;
			    Free(yyvsp[0].map);
			}
		  ;
    break;}
case 135:
#line 928 "lev_comp.y"
{
			if (++nobj >= MAX_OF_TYPE) {
			    yyerror("Too many objects in room or mazepart!");
			    nobj--;
			}
		  ;
    break;}
case 136:
#line 937 "lev_comp.y"
{
			tmpobj[nobj]->containment = 0;
			tmpobj[nobj]->x = current_coord.x;
			tmpobj[nobj]->y = current_coord.y;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Object");
		  ;
    break;}
case 137:
#line 946 "lev_comp.y"
{
			tmpobj[nobj]->containment = 1;
			/* random coordinate, will be overridden anyway */
			tmpobj[nobj]->x = -MAX_REGISTERS-1;
			tmpobj[nobj]->y = -MAX_REGISTERS-1;
		  ;
    break;}
case 138:
#line 955 "lev_comp.y"
{
			tmpobj[nobj]->spe = -127;
	/* Note below: we're trying to make as many of these optional as
	 * possible.  We clearly can't make curse_state, enchantment, and
	 * monster_id _all_ optional, since ",random" would be ambiguous.
	 * We can't even just make enchantment mandatory, since if we do that
	 * alone, ",random" requires too much lookahead to parse.
	 */
		  ;
    break;}
case 139:
#line 965 "lev_comp.y"
{
		  ;
    break;}
case 140:
#line 968 "lev_comp.y"
{
		  ;
    break;}
case 141:
#line 971 "lev_comp.y"
{
		  ;
    break;}
case 142:
#line 976 "lev_comp.y"
{
			tmpobj[nobj]->curse_state = -1;
		  ;
    break;}
case 143:
#line 980 "lev_comp.y"
{
			tmpobj[nobj]->curse_state = yyvsp[0].i;
		  ;
    break;}
case 144:
#line 986 "lev_comp.y"
{
			int token = get_monster_id(yyvsp[0].map, (char)0);
			if (token == ERR)	/* "random" */
			    tmpobj[nobj]->corpsenm = NON_PM - 1;
			else
			    tmpobj[nobj]->corpsenm = token;
			Free(yyvsp[0].map);
		  ;
    break;}
case 145:
#line 997 "lev_comp.y"
{
			tmpobj[nobj]->spe = -127;
		  ;
    break;}
case 146:
#line 1001 "lev_comp.y"
{
			tmpobj[nobj]->spe = yyvsp[0].i;
		  ;
    break;}
case 148:
#line 1008 "lev_comp.y"
{
		  ;
    break;}
case 149:
#line 1011 "lev_comp.y"
{
			tmpobj[nobj]->material = -127;
		  ;
    break;}
case 150:
#line 1015 "lev_comp.y"
{
			tmpobj[nobj]->material = yyvsp[0].i;
		  ;
    break;}
case 152:
#line 1022 "lev_comp.y"
{
		  ;
    break;}
case 153:
#line 1025 "lev_comp.y"
{
			tmpobj[nobj]->name.str = yyvsp[0].map;
		  ;
    break;}
case 154:
#line 1031 "lev_comp.y"
{
			tmpdoor[ndoor] = New(door);
			tmpdoor[ndoor]->x = current_coord.x;
			tmpdoor[ndoor]->y = current_coord.y;
			tmpdoor[ndoor]->mask = yyvsp[-2].i;
			if(current_coord.x >= 0 && current_coord.y >= 0 &&
			   tmpmap[current_coord.y][current_coord.x] != DOOR &&
			   tmpmap[current_coord.y][current_coord.x] != SDOOR)
			    yyerror("Door decl doesn't match the map");
			ndoor++;
			if (ndoor >= MAX_OF_TYPE) {
				yyerror("Too many doors in mazepart!");
				ndoor--;
			}
		  ;
    break;}
case 155:
#line 1049 "lev_comp.y"
{
			tmptrap[ntrap] = New(trap);
			tmptrap[ntrap]->x = current_coord.x;
			tmptrap[ntrap]->y = current_coord.y;
			tmptrap[ntrap]->type = yyvsp[-2].i;
			tmptrap[ntrap]->chance = yyvsp[-4].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Trap");
			if (++ntrap >= MAX_OF_TYPE) {
				yyerror("Too many traps in room or mazepart!");
				ntrap--;
			}
		  ;
    break;}
case 156:
#line 1066 "lev_comp.y"
{
		        int x, y, dir;

			tmpdb[ndb] = New(drawbridge);
			x = tmpdb[ndb]->x = current_coord.x;
			y = tmpdb[ndb]->y = current_coord.y;
			/* convert dir from a DIRECTION to a DB_DIR */
			dir = yyvsp[-2].i;
			switch(dir) {
			case W_NORTH: dir = DB_NORTH; y--; break;
			case W_SOUTH: dir = DB_SOUTH; y++; break;
			case W_EAST:  dir = DB_EAST;  x++; break;
			case W_WEST:  dir = DB_WEST;  x--; break;
			default:
			    yyerror("Invalid drawbridge direction");
			    break;
			}
			tmpdb[ndb]->dir = dir;
			if (current_coord.x >= 0 && current_coord.y >= 0 &&
			    !IS_WALL(tmpmap[y][x])) {
			    char ebuf[60];
			    Sprintf(ebuf,
				    "Wall needed for drawbridge (%02d, %02d)",
				    current_coord.x, current_coord.y);
			    yyerror(ebuf);
			}

			if ( yyvsp[0].i == D_ISOPEN )
			    tmpdb[ndb]->db_open = 1;
			else if ( yyvsp[0].i == D_CLOSED )
			    tmpdb[ndb]->db_open = 0;
			else
			    yyerror("A drawbridge can only be open or closed!");
			ndb++;
			if (ndb >= MAX_OF_TYPE) {
				yyerror("Too many drawbridges in mazepart!");
				ndb--;
			}
		   ;
    break;}
case 157:
#line 1108 "lev_comp.y"
{
			tmpwalk[nwalk] = New(walk);
			tmpwalk[nwalk]->x = current_coord.x;
			tmpwalk[nwalk]->y = current_coord.y;
			tmpwalk[nwalk]->dir = yyvsp[0].i;
			nwalk++;
			if (nwalk >= MAX_OF_TYPE) {
				yyerror("Too many mazewalks in mazepart!");
				nwalk--;
			}
		  ;
    break;}
case 158:
#line 1122 "lev_comp.y"
{
			wallify_map();
		  ;
    break;}
case 159:
#line 1128 "lev_comp.y"
{
			tmplad[nlad] = New(lad);
			tmplad[nlad]->x = current_coord.x;
			tmplad[nlad]->y = current_coord.y;
			tmplad[nlad]->up = yyvsp[0].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Ladder");
			nlad++;
			if (nlad >= MAX_OF_TYPE) {
				yyerror("Too many ladders in mazepart!");
				nlad--;
			}
		  ;
    break;}
case 160:
#line 1145 "lev_comp.y"
{
			tmpstair[nstair] = New(stair);
			tmpstair[nstair]->x = current_coord.x;
			tmpstair[nstair]->y = current_coord.y;
			tmpstair[nstair]->up = yyvsp[0].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Stairway");
			nstair++;
			if (nstair >= MAX_OF_TYPE) {
				yyerror("Too many stairs in room or mazepart!");
				nstair--;
			}
		  ;
    break;}
case 161:
#line 1162 "lev_comp.y"
{
			tmplreg[nlreg] = New(lev_region);
			tmplreg[nlreg]->in_islev = yyvsp[0].i;
			tmplreg[nlreg]->inarea.x1 = current_region.x1;
			tmplreg[nlreg]->inarea.y1 = current_region.y1;
			tmplreg[nlreg]->inarea.x2 = current_region.x2;
			tmplreg[nlreg]->inarea.y2 = current_region.y2;
		  ;
    break;}
case 162:
#line 1171 "lev_comp.y"
{
			tmplreg[nlreg]->del_islev = yyvsp[-2].i;
			tmplreg[nlreg]->delarea.x1 = current_region.x1;
			tmplreg[nlreg]->delarea.y1 = current_region.y1;
			tmplreg[nlreg]->delarea.x2 = current_region.x2;
			tmplreg[nlreg]->delarea.y2 = current_region.y2;
			if(yyvsp[0].i)
			    tmplreg[nlreg]->rtype = LR_UPSTAIR;
			else
			    tmplreg[nlreg]->rtype = LR_DOWNSTAIR;
			tmplreg[nlreg]->rname.str = 0;
			nlreg++;
			if (nlreg >= MAX_OF_TYPE) {
				yyerror("Too many levregions in mazepart!");
				nlreg--;
			}
		  ;
    break;}
case 163:
#line 1191 "lev_comp.y"
{
			tmplreg[nlreg] = New(lev_region);
			tmplreg[nlreg]->in_islev = yyvsp[0].i;
			tmplreg[nlreg]->inarea.x1 = current_region.x1;
			tmplreg[nlreg]->inarea.y1 = current_region.y1;
			tmplreg[nlreg]->inarea.x2 = current_region.x2;
			tmplreg[nlreg]->inarea.y2 = current_region.y2;
		  ;
    break;}
case 164:
#line 1200 "lev_comp.y"
{
			tmplreg[nlreg]->del_islev = yyvsp[-2].i;
			tmplreg[nlreg]->delarea.x1 = current_region.x1;
			tmplreg[nlreg]->delarea.y1 = current_region.y1;
			tmplreg[nlreg]->delarea.x2 = current_region.x2;
			tmplreg[nlreg]->delarea.y2 = current_region.y2;
			tmplreg[nlreg]->rtype = LR_PORTAL;
			tmplreg[nlreg]->rname.str = yyvsp[0].map;
			nlreg++;
			if (nlreg >= MAX_OF_TYPE) {
				yyerror("Too many levregions in mazepart!");
				nlreg--;
			}
		  ;
    break;}
case 165:
#line 1217 "lev_comp.y"
{
			tmplreg[nlreg] = New(lev_region);
			tmplreg[nlreg]->in_islev = yyvsp[0].i;
			tmplreg[nlreg]->inarea.x1 = current_region.x1;
			tmplreg[nlreg]->inarea.y1 = current_region.y1;
			tmplreg[nlreg]->inarea.x2 = current_region.x2;
			tmplreg[nlreg]->inarea.y2 = current_region.y2;
		  ;
    break;}
case 166:
#line 1226 "lev_comp.y"
{
			tmplreg[nlreg]->del_islev = yyvsp[0].i;
			tmplreg[nlreg]->delarea.x1 = current_region.x1;
			tmplreg[nlreg]->delarea.y1 = current_region.y1;
			tmplreg[nlreg]->delarea.x2 = current_region.x2;
			tmplreg[nlreg]->delarea.y2 = current_region.y2;
		  ;
    break;}
case 167:
#line 1234 "lev_comp.y"
{
			switch(yyvsp[0].i) {
			case -1: tmplreg[nlreg]->rtype = LR_TELE; break;
			case 0: tmplreg[nlreg]->rtype = LR_DOWNTELE; break;
			case 1: tmplreg[nlreg]->rtype = LR_UPTELE; break;
			}
			tmplreg[nlreg]->rname.str = 0;
			nlreg++;
			if (nlreg >= MAX_OF_TYPE) {
				yyerror("Too many levregions in mazepart!");
				nlreg--;
			}
		  ;
    break;}
case 168:
#line 1250 "lev_comp.y"
{
			tmplreg[nlreg] = New(lev_region);
			tmplreg[nlreg]->in_islev = yyvsp[0].i;
			tmplreg[nlreg]->inarea.x1 = current_region.x1;
			tmplreg[nlreg]->inarea.y1 = current_region.y1;
			tmplreg[nlreg]->inarea.x2 = current_region.x2;
			tmplreg[nlreg]->inarea.y2 = current_region.y2;
		  ;
    break;}
case 169:
#line 1259 "lev_comp.y"
{
			tmplreg[nlreg]->del_islev = yyvsp[0].i;
			tmplreg[nlreg]->delarea.x1 = current_region.x1;
			tmplreg[nlreg]->delarea.y1 = current_region.y1;
			tmplreg[nlreg]->delarea.x2 = current_region.x2;
			tmplreg[nlreg]->delarea.y2 = current_region.y2;
			tmplreg[nlreg]->rtype = LR_BRANCH;
			tmplreg[nlreg]->rname.str = 0;
			nlreg++;
			if (nlreg >= MAX_OF_TYPE) {
				yyerror("Too many levregions in mazepart!");
				nlreg--;
			}
		  ;
    break;}
case 170:
#line 1276 "lev_comp.y"
{
			yyval.i = -1;
		  ;
    break;}
case 171:
#line 1280 "lev_comp.y"
{
			yyval.i = yyvsp[0].i;
		  ;
    break;}
case 172:
#line 1286 "lev_comp.y"
{
			yyval.i = 0;
		  ;
    break;}
case 173:
#line 1290 "lev_comp.y"
{
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if (yyvsp[-7].i <= 0 || yyvsp[-7].i >= COLNO)
				yyerror("Region out of level range!");
			else if (yyvsp[-5].i < 0 || yyvsp[-5].i >= ROWNO)
				yyerror("Region out of level range!");
			else if (yyvsp[-3].i <= 0 || yyvsp[-3].i >= COLNO)
				yyerror("Region out of level range!");
			else if (yyvsp[-1].i < 0 || yyvsp[-1].i >= ROWNO)
				yyerror("Region out of level range!");
			current_region.x1 = yyvsp[-7].i;
			current_region.y1 = yyvsp[-5].i;
			current_region.x2 = yyvsp[-3].i;
			current_region.y2 = yyvsp[-1].i;
			yyval.i = 1;
		  ;
    break;}
case 174:
#line 1310 "lev_comp.y"
{
			tmpfountain[nfountain] = New(fountain);
			tmpfountain[nfountain]->x = current_coord.x;
			tmpfountain[nfountain]->y = current_coord.y;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Fountain");
			nfountain++;
			if (nfountain >= MAX_OF_TYPE) {
			    yyerror("Too many fountains in room or mazepart!");
			    nfountain--;
			}
		  ;
    break;}
case 175:
#line 1326 "lev_comp.y"
{
			tmpsink[nsink] = New(sink);
			tmpsink[nsink]->x = current_coord.x;
			tmpsink[nsink]->y = current_coord.y;
			nsink++;
			if (nsink >= MAX_OF_TYPE) {
				yyerror("Too many sinks in room!");
				nsink--;
			}
		  ;
    break;}
case 176:
#line 1339 "lev_comp.y"
{
			tmppool[npool] = New(pool);
			tmppool[npool]->x = current_coord.x;
			tmppool[npool]->y = current_coord.y;
			npool++;
			if (npool >= MAX_OF_TYPE) {
				yyerror("Too many pools in room!");
				npool--;
			}
		  ;
    break;}
case 177:
#line 1352 "lev_comp.y"
{
			tmpdig[ndig] = New(digpos);
			tmpdig[ndig]->x1 = current_region.x1;
			tmpdig[ndig]->y1 = current_region.y1;
			tmpdig[ndig]->x2 = current_region.x2;
			tmpdig[ndig]->y2 = current_region.y2;
			ndig++;
			if (ndig >= MAX_OF_TYPE) {
				yyerror("Too many diggables in mazepart!");
				ndig--;
			}
		  ;
    break;}
case 178:
#line 1367 "lev_comp.y"
{
			tmppass[npass] = New(digpos);
			tmppass[npass]->x1 = current_region.x1;
			tmppass[npass]->y1 = current_region.y1;
			tmppass[npass]->x2 = current_region.x2;
			tmppass[npass]->y2 = current_region.y2;
			npass++;
			if (npass >= 32) {
				yyerror("Too many passwalls in mazepart!");
				npass--;
			}
		  ;
    break;}
case 179:
#line 1382 "lev_comp.y"
{
			tmpreg[nreg] = New(region);
			tmpreg[nreg]->x1 = current_region.x1;
			tmpreg[nreg]->y1 = current_region.y1;
			tmpreg[nreg]->x2 = current_region.x2;
			tmpreg[nreg]->y2 = current_region.y2;
			tmpreg[nreg]->rlit = yyvsp[-3].i;
			tmpreg[nreg]->rtype = yyvsp[-1].i;
			if(yyvsp[0].i & 1) tmpreg[nreg]->rtype += MAXRTYPE+1;
			tmpreg[nreg]->rirreg = ((yyvsp[0].i & 2) != 0);
			if(current_region.x1 > current_region.x2 ||
			   current_region.y1 > current_region.y2)
			   yyerror("Region start > end!");
			if(tmpreg[nreg]->rtype == VAULT &&
			   (tmpreg[nreg]->rirreg ||
			    (tmpreg[nreg]->x2 - tmpreg[nreg]->x1 != 1) ||
			    (tmpreg[nreg]->y2 - tmpreg[nreg]->y1 != 1)))
				yyerror("Vaults must be exactly 2x2!");
			if(want_warnings && !tmpreg[nreg]->rirreg &&
			   current_region.x1 > 0 && current_region.y1 > 0 &&
			   current_region.x2 < (int)max_x_map &&
			   current_region.y2 < (int)max_y_map) {
			    /* check for walls in the room */
			    char ebuf[60];
			    register int x, y, nrock = 0;

			    for(y=current_region.y1; y<=current_region.y2; y++)
				for(x=current_region.x1;
				    x<=current_region.x2; x++)
				    if(IS_ROCK(tmpmap[y][x]) ||
				       IS_DOOR(tmpmap[y][x])) nrock++;
			    if(nrock) {
				Sprintf(ebuf,
					"Rock in room (%02d,%02d,%02d,%02d)?!",
					current_region.x1, current_region.y1,
					current_region.x2, current_region.y2);
				yywarning(ebuf);
			    }
			    if (
		!IS_ROCK(tmpmap[current_region.y1-1][current_region.x1-1]) ||
		!IS_ROCK(tmpmap[current_region.y2+1][current_region.x1-1]) ||
		!IS_ROCK(tmpmap[current_region.y1-1][current_region.x2+1]) ||
		!IS_ROCK(tmpmap[current_region.y2+1][current_region.x2+1])) {
				Sprintf(ebuf,
				"NonRock edge in room (%02d,%02d,%02d,%02d)?!",
					current_region.x1, current_region.y1,
					current_region.x2, current_region.y2);
				yywarning(ebuf);
			    }
			} else if(tmpreg[nreg]->rirreg &&
		!IS_ROOM(tmpmap[current_region.y1][current_region.x1])) {
			    char ebuf[60];
			    Sprintf(ebuf,
				    "Rock in irregular room (%02d,%02d)?!",
				    current_region.x1, current_region.y1);
			    yyerror(ebuf);
			}
			nreg++;
			if (nreg >= MAX_OF_TYPE) {
				yyerror("Too many regions in mazepart!");
				nreg--;
			}
		  ;
    break;}
case 180:
#line 1448 "lev_comp.y"
{
			tmpaltar[naltar] = New(altar);
			tmpaltar[naltar]->x = current_coord.x;
			tmpaltar[naltar]->y = current_coord.y;
			tmpaltar[naltar]->align = yyvsp[-2].i;
			tmpaltar[naltar]->shrine = yyvsp[0].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Altar");
			naltar++;
			if (naltar >= MAX_OF_TYPE) {
				yyerror("Too many altars in room or mazepart!");
				naltar--;
			}
		  ;
    break;}
case 181:
#line 1466 "lev_comp.y"
{
			tmpgold[ngold] = New(gold);
			tmpgold[ngold]->x = current_coord.x;
			tmpgold[ngold]->y = current_coord.y;
			tmpgold[ngold]->amount = yyvsp[-2].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Gold");
			ngold++;
			if (ngold >= MAX_OF_TYPE) {
				yyerror("Too many golds in room or mazepart!");
				ngold--;
			}
		  ;
    break;}
case 182:
#line 1483 "lev_comp.y"
{
			tmpengraving[nengraving] = New(engraving);
			tmpengraving[nengraving]->x = current_coord.x;
			tmpengraving[nengraving]->y = current_coord.y;
			tmpengraving[nengraving]->engr.str = yyvsp[0].map;
			tmpengraving[nengraving]->etype = yyvsp[-2].i;
			if (!in_room)
			    check_coord(current_coord.x, current_coord.y,
					"Engraving");
			nengraving++;
			if (nengraving >= MAX_OF_TYPE) {
			    yyerror("Too many engravings in room or mazepart!");
			    nengraving--;
			}
		  ;
    break;}
case 184:
#line 1502 "lev_comp.y"
{
			yyval.i = - MAX_REGISTERS - 1;
		  ;
    break;}
case 187:
#line 1510 "lev_comp.y"
{
			yyval.i = - MAX_REGISTERS - 1;
		  ;
    break;}
case 190:
#line 1518 "lev_comp.y"
{
			yyval.map = (char *) 0;
		  ;
    break;}
case 192:
#line 1525 "lev_comp.y"
{
			yyval.map = (char *) 0;
		  ;
    break;}
case 193:
#line 1531 "lev_comp.y"
{
			int token = get_trap_type(yyvsp[0].map);
			if (token == ERR)
				yyerror("Unknown trap type!");
			yyval.i = token;
			Free(yyvsp[0].map);
		  ;
    break;}
case 195:
#line 1542 "lev_comp.y"
{
			int token = get_room_type(yyvsp[0].map);
			if (token == ERR) {
				yywarning("Unknown room type!  Making ordinary room...");
				yyval.i = OROOM;
			} else
				yyval.i = token;
			Free(yyvsp[0].map);
		  ;
    break;}
case 197:
#line 1555 "lev_comp.y"
{
			yyval.i = 0;
		  ;
    break;}
case 198:
#line 1559 "lev_comp.y"
{
			yyval.i = yyvsp[0].i;
		  ;
    break;}
case 199:
#line 1563 "lev_comp.y"
{
			yyval.i = yyvsp[-2].i + (yyvsp[0].i << 1);
		  ;
    break;}
case 202:
#line 1571 "lev_comp.y"
{
			current_coord.x = current_coord.y = -MAX_REGISTERS-1;
		  ;
    break;}
case 209:
#line 1587 "lev_comp.y"
{
			yyval.i = - MAX_REGISTERS - 1;
		  ;
    break;}
case 212:
#line 1597 "lev_comp.y"
{
			if ( yyvsp[-1].i >= MAX_REGISTERS )
				yyerror("Register Index overflow!");
			else
				current_coord.x = current_coord.y = - yyvsp[-1].i - 1;
		  ;
    break;}
case 213:
#line 1606 "lev_comp.y"
{
			if ( yyvsp[-1].i >= MAX_REGISTERS )
				yyerror("Register Index overflow!");
			else
				yyval.i = - yyvsp[-1].i - 1;
		  ;
    break;}
case 214:
#line 1615 "lev_comp.y"
{
			if ( yyvsp[-1].i >= MAX_REGISTERS )
				yyerror("Register Index overflow!");
			else
				yyval.i = - yyvsp[-1].i - 1;
		  ;
    break;}
case 215:
#line 1624 "lev_comp.y"
{
			if ( yyvsp[-1].i >= 3 )
				yyerror("Register Index overflow!");
			else
				yyval.i = - yyvsp[-1].i - 1;
		  ;
    break;}
case 217:
#line 1636 "lev_comp.y"
{
			if (check_monster_char((char) yyvsp[0].i))
				yyval.i = yyvsp[0].i ;
			else {
				yyerror("Unknown monster class!");
				yyval.i = ERR;
			}
		  ;
    break;}
case 218:
#line 1647 "lev_comp.y"
{
			char c = yyvsp[0].i;
			if (check_object_char(c))
				yyval.i = c;
			else {
				yyerror("Unknown char class!");
				yyval.i = ERR;
			}
		  ;
    break;}
case 222:
#line 1666 "lev_comp.y"
{
			yyval.i = 100;	/* default is 100% */
		  ;
    break;}
case 223:
#line 1670 "lev_comp.y"
{
			if (yyvsp[0].i <= 0 || yyvsp[0].i > 100)
			    yyerror("Expected percentile chance.");
			yyval.i = yyvsp[0].i;
		  ;
    break;}
case 226:
#line 1682 "lev_comp.y"
{
			if (!in_room && !init_lev.init_present &&
			    (yyvsp[-3].i < 0 || yyvsp[-3].i > (int)max_x_map ||
			     yyvsp[-1].i < 0 || yyvsp[-1].i > (int)max_y_map))
			    yyerror("Coordinates out of map range!");
			current_coord.x = yyvsp[-3].i;
			current_coord.y = yyvsp[-1].i;
		  ;
    break;}
case 227:
#line 1693 "lev_comp.y"
{
/* This series of if statements is a hack for MSC 5.1.  It seems that its
   tiny little brain cannot compile if these are all one big if statement. */
			if (yyvsp[-7].i < 0 || yyvsp[-7].i > (int)max_x_map)
				yyerror("Region out of map range!");
			else if (yyvsp[-5].i < 0 || yyvsp[-5].i > (int)max_y_map)
				yyerror("Region out of map range!");
			else if (yyvsp[-3].i < 0 || yyvsp[-3].i > (int)max_x_map)
				yyerror("Region out of map range!");
			else if (yyvsp[-1].i < 0 || yyvsp[-1].i > (int)max_y_map)
				yyerror("Region out of map range!");
			current_region.x1 = yyvsp[-7].i;
			current_region.y1 = yyvsp[-5].i;
			current_region.x2 = yyvsp[-3].i;
			current_region.y2 = yyvsp[-1].i;
		  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 487 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 1711 "lev_comp.y"


/*lev_comp.y*/