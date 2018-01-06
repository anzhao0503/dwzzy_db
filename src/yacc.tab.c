/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yacc.y" /* yacc.c:339  */

#include <string.h>
#include "../include/parser.h"
#include "../include/BST.h"
extern "C"{
	extern int yylex(void);
	extern int lex_init();
	extern int yyerror(char *s);
}
/*
  	functions
 */
int Printdmy();
static char errmsg[4096];
OP Operator(char* opstr);
TYPE GetType(char* type_str);
static char recordstr[4096];
TableManagement* table_manager;


/*
	variables
 */

char* tb_name;
/*
	for update query.
 */
int update_col_count=0;
UpdateQuery* update_query;
/*
	for insert query.
 */
char* insert_record[MAX_TUPLE_SIZE];
int insert_count = 0;
/*
	for create query.
 */
int attr_count = 0;
AttrInfo attr_list[MAX_ATTR_NUM];

/*
	for conditions.
 */
int cond_count = 0;
Condition cond_list[MAX_COND_NUM];
/*
	for delete query.
 */
DeleteQuery* delete_query;
/*
	for select query.
 */
int join_count = 0;
int sel_count = 0;
int from_count = 0;
int orderby_count = 0;
SelectQuery* query;
int curPos = 0;
int funcRnt;


#line 129 "yacc.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yacc.tab.h".  */
#ifndef YY_YY_YACC_TAB_H_INCLUDED
# define YY_YY_YACC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NAME = 258,
    STRING = 259,
    NUMBER = 260,
    COMPARISION = 261,
    AND = 262,
    SELECT = 263,
    FROM = 264,
    WHERE = 265,
    ORDER = 266,
    BY = 267,
    ASC = 268,
    DESC = 269,
    ALL = 270,
    UNIQUE = 271,
    DISTINCT = 272,
    CREATE = 273,
    TABLE = 274,
    DROP = 275,
    INDEX = 276,
    INSERT = 277,
    INTO = 278,
    VALUES = 279,
    DELETE = 280,
    UPDATE = 281,
    SET = 282,
    CHARACTER = 283,
    INTEGER = 284,
    DATE = 285,
    FLOAT = 286,
    VARCHAR = 287,
    SHOW = 288,
    TABLES = 289,
    EXIT = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 64 "yacc.y" /* yacc.c:355  */

	int intval;
	char* strval;

#line 210 "yacc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 227 "yacc.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  25
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   104

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  30
/* YYNRULES -- Number of rules.  */
#define YYNRULES  64
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  127

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    10,     8,    43,     9,    44,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
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
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    94,    94,   107,   113,   117,   118,   119,   120,   121,
     122,   126,   136,   144,   145,   148,   155,   161,   166,   171,
     177,   183,   191,   201,   211,   219,   227,   239,   254,   267,
     269,   272,   289,   307,   324,   329,   346,   351,   358,   365,
     369,   374,   379,   386,   387,   390,   394,   400,   401,   404,
     410,   414,   419,   421,   424,   425,   428,   432,   436,   440,
     444,   449,   451,   454,   458
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "NAME", "STRING", "NUMBER",
  "COMPARISION", "AND", "'+'", "'-'", "'*'", "'/'", "SELECT", "FROM",
  "WHERE", "ORDER", "BY", "ASC", "DESC", "ALL", "UNIQUE", "DISTINCT",
  "CREATE", "TABLE", "DROP", "INDEX", "INSERT", "INTO", "VALUES", "DELETE",
  "UPDATE", "SET", "CHARACTER", "INTEGER", "DATE", "FLOAT", "VARCHAR",
  "SHOW", "TABLES", "EXIT", "';'", "'('", "')'", "','", "'.'", "$accept",
  "sql_start", "sql_func", "table_def", "table", "table_attr_list",
  "column_def", "column", "data_type", "table_drop", "insert_stat",
  "insert_list", "update_stat", "set_cond", "set_expr", "delete_stat",
  "select_stat", "select_seg", "select_clause", "selectbegin", "unique",
  "sellist", "sel_column", "fromlist", "sel_table", "where_clause",
  "condition", "expr", "orderby_clause", "orderlist", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,    43,    45,
      42,    47,   263,   264,   265,   266,   267,   268,   269,   270,
     271,   272,   273,   274,   275,   276,   277,   278,   279,   280,
     281,   282,   283,   284,   285,   286,   287,   288,   289,   290,
      59,    40,    41,    44,    46
};
# endif

#define YYPACT_NINF -37

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-37)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -7,   -37,    -9,    14,    22,     5,    47,   -37,   -37,    51,
     -37,   -37,   -37,   -37,   -37,   -37,   -37,    12,    40,    15,
      52,    52,    52,    52,    23,   -37,   -37,    -3,   -37,   -37,
     -37,     0,   -37,    17,    20,    28,    45,    54,   -37,    49,
     -12,   -37,    18,   -37,    21,   -37,    60,   -37,    24,    63,
      27,    62,    -1,   -37,    29,    -3,    55,    66,    69,   -37,
     -31,   -37,    -8,    16,    -5,    67,   -37,   -37,    25,    54,
      33,    72,   -37,    61,   -37,   -37,   -37,    36,    60,    37,
     -37,   -37,    38,    39,   -37,   -37,   -37,     1,    41,    78,
      63,   -37,   -37,   -37,   -37,   -37,    79,   -37,   -37,    80,
      81,    82,    44,    43,   -37,   -37,    77,   -37,   -37,    46,
      48,    50,    53,   -37,   -37,   -37,     4,    85,   -37,   -37,
     -37,    56,   -37,   -37,   -37,    88,   -37
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    38,     0,     0,     0,     0,     0,     3,     4,     0,
       2,     5,     6,     7,     8,     9,    10,     0,     0,    39,
       0,     0,     0,     0,     0,     1,    34,     0,    40,    42,
      41,     0,    12,     0,     0,     0,    52,     0,    49,     0,
      52,    47,    45,    37,    36,    43,     0,    22,     0,     0,
       0,     0,    52,    29,     0,     0,    61,     0,     0,    16,
       0,    13,     0,     0,     0,    53,    54,    33,     0,     0,
       0,    50,    48,     0,    35,    46,    44,     0,     0,     0,
      18,    19,     0,     0,    15,    25,    24,     0,     0,     0,
       0,    31,    32,    30,    28,    51,     0,    11,    14,     0,
       0,     0,     0,     0,    58,    57,     0,    55,    63,    62,
       0,     0,     0,    23,    27,    26,     0,     0,    17,    21,
      20,     0,    60,    59,    64,     0,    56
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -37,   -37,   -37,   -37,    19,   -37,    26,   -37,   -37,   -37,
     -37,   -37,   -37,   -37,    30,   -37,   -37,    57,   -37,   -37,
     -37,   -37,    35,   -37,    42,   -36,   -37,     8,   -37,   -37
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     9,    10,    11,    33,    60,    61,    62,    84,    12,
      13,    87,    14,    52,    53,    15,    16,    17,    18,    19,
      31,    44,    45,    40,    41,    50,    65,    66,    74,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      38,    88,    49,    42,    56,     1,    69,   121,   122,   123,
      43,    77,    78,    49,    20,     2,    70,     3,    23,     4,
      85,    86,     5,     6,    79,    80,    81,    82,    83,    91,
      92,    55,     7,     8,    28,    29,    30,    21,    39,    89,
      34,    35,    36,   102,   103,   104,   105,   114,   115,    22,
      24,    25,    26,    27,    37,    32,    48,    51,    46,    49,
      47,     1,    57,    59,    58,    63,    64,    67,    68,    75,
      73,    71,    42,    94,    90,    95,    97,    96,    99,   100,
     101,   106,   108,   116,   113,   110,   111,   112,   124,   117,
     118,   126,   119,    76,     0,   120,    54,    72,   107,    93,
     125,     0,     0,     0,    98
};

static const yytype_int8 yycheck[] =
{
       3,     6,    14,     3,    40,    12,     7,     3,     4,     5,
      10,    42,    43,    14,    23,    22,    52,    24,    13,    26,
       4,     5,    29,    30,    32,    33,    34,    35,    36,     4,
       5,    43,    39,    40,    19,    20,    21,    23,    41,    44,
      21,    22,    23,    42,    43,     4,     5,     4,     5,    27,
       3,     0,    40,    13,    31,     3,    28,     3,    41,    14,
      40,    12,    44,     3,    43,    41,     3,    40,     6,     3,
      15,    42,     3,    40,     7,     3,    40,    16,    41,    41,
      41,     3,     3,     6,    40,     5,     5,     5,     3,    43,
      42,     3,    42,    58,    -1,    42,    39,    55,    90,    69,
      44,    -1,    -1,    -1,    78
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    22,    24,    26,    29,    30,    39,    40,    46,
      47,    48,    54,    55,    57,    60,    61,    62,    63,    64,
      23,    23,    27,    13,     3,     0,    40,    13,    19,    20,
      21,    65,     3,    49,    49,    49,    49,    31,     3,    41,
      68,    69,     3,    10,    66,    67,    41,    40,    28,    14,
      70,     3,    58,    59,    62,    43,    70,    44,    43,     3,
      50,    51,    52,    41,     3,    71,    72,    40,     6,     7,
      70,    42,    69,    15,    73,     3,    67,    42,    43,    32,
      33,    34,    35,    36,    53,     4,     5,    56,     6,    44,
       7,     4,     5,    59,    40,     3,    16,    40,    51,    41,
      41,    41,    42,    43,     4,     5,     3,    72,     3,    74,
       5,     5,     5,    40,     4,     5,     6,    43,    42,    42,
      42,     3,     4,     5,     3,    44,     3
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    45,    46,    46,    47,    47,    47,    47,    47,    47,
      47,    48,    49,    50,    50,    51,    52,    53,    53,    53,
      53,    53,    54,    55,    56,    56,    56,    56,    57,    58,
      58,    59,    59,    60,    61,    62,    63,    63,    64,    65,
      65,    65,    65,    66,    66,    67,    67,    68,    68,    69,
      69,    69,    70,    70,    71,    71,    72,    72,    72,    72,
      72,    73,    73,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     7,     1,     1,     3,     2,     1,     4,     1,     1,
       4,     4,     4,     8,     1,     1,     3,     3,     6,     1,
       3,     3,     3,     5,     2,     5,     3,     3,     1,     0,
       1,     1,     1,     1,     3,     1,     3,     1,     3,     1,
       3,     4,     0,     2,     1,     3,     7,     3,     3,     5,
       5,     0,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 95 "yacc.y" /* yacc.c:1646  */
    {
			if(funcRnt == 0)
			{
				cout<<"should new query here."<<endl;
				cout << "Success" <<endl;
			}
			else if(funcRnt < 0)
			{
				cout << "Failure："<<funcRnt<<errmsg<<endl; 
			}
			return 0;
		}
#line 1399 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 108 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Should Flush Table Here.\n"<<endl;
		}
#line 1407 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 114 "yacc.y" /* yacc.c:1646  */
    {
			funcRnt = 100;
		}
#line 1415 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 127 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Create Table "<< tb_name << endl;
			PrintAttrList();
			ExecCreate();
			parser_init();	
		}
#line 1426 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 137 "yacc.y" /* yacc.c:1646  */
    {
			tb_name = (yyvsp[0].strval);
			attr_list[attr_count].table_name = (yyvsp[0].strval);
			//printf("tb_name %s \n",tb_name);
		}
#line 1436 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 149 "yacc.y" /* yacc.c:1646  */
    {
			attr_count++;
			
		}
#line 1445 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 156 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].attr_name = (yyvsp[0].strval);
		}
#line 1453 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 162 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type = C;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1462 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 167 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= I;
			attr_list[attr_count].used_size = MAX_INT_ASCII_LENGTH;
		}
#line 1471 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 172 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= D;
			attr_list[attr_count].used_size = MAX_DATE_ASCII_LENGTH;
		}
#line 1480 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 178 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= V;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1489 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 184 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= F;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1498 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 192 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"DROP TABLE"<< tb_name << endl;
			cout<<"Call droptable("<<tb_name<<") func here."<<endl;
			table_manager->DropTable(tb_name);
			parser_init();	
		}
#line 1509 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 202 "yacc.y" /* yacc.c:1646  */
    {
			int tb_id = table_manager->GetTableId(tb_name);
			vector<int> cols;
			table_manager->Insert(tb_id, cols, insert_record);
			cout << "INSERT INTO " << tb_name << " " << recordstr <<endl;
			parser_init();	
		}
#line 1521 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 212 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_ASCII_LENGTH);
			insert_count++;
			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1533 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 220 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), 256);
			insert_count++;
			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1545 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 228 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_ASCII_LENGTH);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1561 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 240 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval),256);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1577 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 255 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Update";
			update_query->tb_name = (yyvsp[-4].strval);
			cout<<"tb_name:"<<update_query->tb_name<<endl;
			FillUpdateCond();
			cout<<"Update Cond:"<<endl;
			//PrintCondList();
			ExecUpdate();
		}
#line 1591 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 273 "yacc.y" /* yacc.c:1646  */
    {
			if(strcmp("=",(yyvsp[-1].strval))==0){
			cout << "string comp"<<endl;
			cout << "update_count"<<update_col_count<<endl;
			update_query->col_name[update_col_count] = (char*)malloc(20);
			memcpy(update_query->col_name[update_col_count],(yyvsp[-2].strval),20);
			update_query->col_value[update_col_count]=(char*)malloc(256);
			memcpy(update_query->col_value[update_col_count],(yyvsp[0].strval),256);
			cout<<update_query->col_name[update_col_count]<<" = "<<update_query->col_value[update_col_count]<<endl;
			update_col_count++;
			}
			else{
				cout<<"syntax error"<<endl;
			}
			
		}
#line 1612 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 290 "yacc.y" /* yacc.c:1646  */
    {
			if(strcmp("=",(yyvsp[-1].strval))==0){
			cout << "comp"<<endl;
			update_query->col_name[update_col_count] = (char*)malloc(20);
			memcpy(update_query->col_name[update_col_count],(yyvsp[-2].strval),20);
			update_query->col_value[update_col_count]=(char*)malloc(sizeof(int)*8);
			memcpy(update_query->col_value[update_col_count],(yyvsp[0].strval),sizeof(int)*8);
			cout<<update_query->col_name[update_col_count]<<" = "<<" number "<<update_query->col_value[update_col_count] << endl;
			update_col_count++;			
			}
			else{
				cout<<"syntax error"<<endl;
			}
		}
#line 1631 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 308 "yacc.y" /* yacc.c:1646  */
    {
			cout << "DELETE FROM\n"<<endl;
			delete_query->tb_name = tb_name;
			cout << delete_query->tb_name <<endl;
			FillDeleteCond();
			PrintCondList();
			cout << "Call delete() function here."<<endl;
			ExecDelete();
			parser_init();	
			
		}
#line 1647 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 325 "yacc.y" /* yacc.c:1646  */
    {
		}
#line 1654 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 330 "yacc.y" /* yacc.c:1646  */
    {
			//if(cond_count == 0) {
			  //cout << tb_name << endl;
			   //int tb_id = table_manager->GetTableId(tb_name);
			   //vector<int> cols;
                           //cout << tb_id << endl;
                           //table_manager->Project(tb_id, cols);
			//}
			FillSelectCond();
			//PrintSelectQuery();
			//Printdmy();
			parser_init();
			
		}
#line 1673 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 347 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 0;
			cout<<"all "<<query->all<<endl;
		}
#line 1682 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 352 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 1;
			cout<<"all "<<query->all<<endl;
		}
#line 1691 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 359 "yacc.y" /* yacc.c:1646  */
    {
			printf("-----one sub selection begin----\n");
		}
#line 1699 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 365 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1708 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 370 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 1;
			cout<<"all "<<query->distinct<<endl;
		}
#line 1717 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 375 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1726 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 380 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1735 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 391 "yacc.y" /* yacc.c:1646  */
    {
			SaveSelItem(NULL,(yyvsp[0].strval));
		}
#line 1743 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 395 "yacc.y" /* yacc.c:1646  */
    {
			SaveSelItem((yyvsp[-2].strval),(yyvsp[0].strval));
		}
#line 1751 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 405 "yacc.y" /* yacc.c:1646  */
    {	
			SaveFromItem((yyvsp[0].strval));
			
		}
#line 1760 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 411 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1768 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 415 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1776 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 429 "yacc.y" /* yacc.c:1646  */
    {
			SaveJoin((yyvsp[-6].strval), (yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), Operator((yyvsp[-3].strval)));	
		}
#line 1784 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 433 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));	
		}
#line 1792 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 437 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), V, Operator((yyvsp[-1].strval)));
		}
#line 1800 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 441 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));
		}
#line 1808 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 445 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), V, Operator((yyvsp[-1].strval)));
		}
#line 1816 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 455 "yacc.y" /* yacc.c:1646  */
    {
			SaveOrderbyItem((yyvsp[0].strval));
		}
#line 1824 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 1828 "yacc.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 460 "yacc.y" /* yacc.c:1906  */


void parser_init()
{
	lex_init();
	// tb_name = NULL;
	funcRnt = 0;
	curPos = 0;
	cond_count = 0;
	join_count = 0;
	attr_count = 0;
	sel_count = 0;
	from_count = 0;
	update_col_count = 0;
	for(int i = 0; i<insert_count;i++)
		memset(insert_record[i],0,MAX_TUPLE_SIZE);
	insert_count = 0;
	memset(attr_list,0,sizeof(AttrInfo)*MAX_ATTR_NUM);
	memset(cond_list,0,sizeof(Condition)*MAX_COND_NUM);
	memset(query,0,sizeof(SelectQuery));
	memset(delete_query,0,sizeof(DeleteQuery));
	memset(update_query,0,sizeof(UpdateQuery));
	return;
}

void InitQuery(){
	char* tb_name_1 = "nation.tbl.data";
	char* tb_name_2 = "region.tbl.data";
	char* tb_name_3 = "supplier.tbl.data";

	vector<char*> tb_names;
	tb_names.push_back(tb_name_1);
	tb_names.push_back(tb_name_2);
	tb_names.push_back(tb_name_3);
	table_manager = new TableManagement(tb_names);
	for (int i = 0; i < tb_names.size(); i++) {
		table_manager->InitTable(tb_names[i], 0);
	}
	cout << "load ok" << endl;
	table_manager->CreateIndex(0, 0);
	table_manager->CreateIndex(1, 0);
	cout << "create index ok" << endl;
//	table_manager = new TableManagement();
	update_query = (UpdateQuery*)malloc(sizeof(UpdateQuery));
	delete_query = (DeleteQuery*)malloc(sizeof(DeleteQuery));
	query = (SelectQuery*)malloc(sizeof(SelectQuery));
	query->distinct = 0;
	query->all = 0;
}
void DestoryQuery(){
	free(delete_query);
	free(update_query);
	free(query);
}
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op){
	if(cond_count > MAX_COND_NUM){
		return -1;
	}
	cond_list[cond_count].col_name = col_name;
	
	cond_list[cond_count].tb_name = tb_name;
	cond_list[cond_count].value = value;
	
	cond_list[cond_count].value_type = value_type;
	
	cond_list[cond_count].op = op;
	
	cond_count++;
	
	return 0;
}
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op){
	if(join_count > MAX_JOIN_NUM){
			return -1;
		}
	query->JoinList[join_count].col_name1 = col_name1;
	query->JoinList[join_count].col_name2 = col_name2;
	query->JoinList[join_count].op = op;
	query->JoinList[join_count].tb_name1 = tb_name1;
	query->JoinList[join_count].tb_name2 = tb_name2;
	join_count++;
	return 0;

}
int SaveAttributeItem(char* table_name, char* attr_name, TYPE type, int size){
	if(attr_count > MAX_ATTR_NUM){
				return -1;
	}
	attr_list[attr_count].table_name = table_name;
	attr_list[attr_count].attr_name = attr_name;
	attr_list[attr_count].type = type;
	attr_list[attr_count].used_size = size;
	attr_count++;
	return 0;
}
int SaveSelItem(char* tb_name, char* col_name){
	query->SelList[sel_count].col_name = col_name;
	query->SelList[sel_count].table_name = tb_name;
	sel_count ++;
	return 0;
}
int SaveFromItem(char* tb_name){
	query->FromList[from_count].tb_name = tb_name;
	from_count++;
	return 0;
}
int SaveOrderbyItem(char *col_name){
	query->OrderbyList[orderby_count].col_name = col_name;
	orderby_count ++;
	return 0;
}
int FillSelectCond(){
	memcpy(query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillDeleteCond(){
	memcpy(delete_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillUpdateCond(){
	memcpy(update_query->CondList,cond_list,cond_count * sizeof(Condition));

	return 0;
}
bool ExecDelete(){
	int tb_id = table_manager->GetTableId(tb_name);
	vector<int> cols;
	vector<OP> operators;
	char* keys[cond_count];
	for(int i = 0; i < cond_count; i++){
		int col_id = table_manager->tables[tb_id]->GetAttrId(delete_query->CondList[i].col_name);
		cols.push_back(col_id);
		keys[i] = (char*)malloc(sizeof(char)*256);
		memcpy(keys[i], delete_query->CondList[i].value, sizeof(delete_query->CondList[i].value));
		operators.push_back(delete_query->CondList[i].op);
	}
	return table_manager->Delete(tb_id, cols, operators, keys);
	
}
int ExecProject() {
return 0;
}
bool ExecUpdate(){
	int tb_id = table_manager->GetTableId(update_query->tb_name);
	int col_id;
	vector<int> up_cols;
	vector<int> cols;
	char* keys[cond_count];
	vector<OP> operators;
	cout<<"cond_count "<<cond_count<<" update_col_count " << update_col_count<<endl;
	for(int i = 0; i < update_col_count; i++){
		col_id = table_manager->tables[tb_id]->GetAttrId(update_query->col_name[i]);
		up_cols.push_back(col_id);
		cout<<"col i "<< update_query->col_value[i]<<endl;
	}
	for(int i = 0; i < cond_count; i++){
		col_id = table_manager->tables[tb_id]->GetAttrId(update_query->CondList[i].col_name);
		cols.push_back(col_id);
		keys[i] = (char*)malloc(sizeof(char)*256);
		memcpy(keys[i], update_query->CondList[i].value, sizeof(update_query->CondList[i].value));
		operators.push_back(update_query->CondList[i].op);
		cout<<"cond i "<< keys[i]<<endl;
	}	
	return table_manager->Update(tb_id, up_cols, update_query->col_value, cols, operators, keys);
}
int ExecCreate(){
	char attr_names[16][MAX_ATTR_NAME_LENGTH];
	TYPE *types;
	int *attr_length;
	int attribute_num = attr_count;
	attr_length = (int*)malloc(sizeof(int)*attribute_num);
	types = (TYPE*)malloc(sizeof(TYPE)*attribute_num);
	for(int i = 0; i<attr_count;i++){
		strcpy(attr_names[i],attr_list[i].attr_name);
		types[i] = attr_list[i].type;
		attr_length[i] = attr_list[i].used_size;
	}
	table_manager->CreateTable(0, tb_name, MAX_TUPLE_SIZE, attr_names, types, attr_length,  attribute_num);
}
/*
 * attr_list: attributes iostreamfor a table
 */
int PrintAttrList(){
	int i;
	for(i=0;i<attr_count;i++){
			cout<<"attr "<<i<<": "<<attr_list[i].attr_name<<" type "<<attr_list[i].type<<" size "<<attr_list[i].used_size<<endl;
		}
		return 0;
}
int PrintCondList(){
	int i;
	for(i = 0; i < cond_count; i++){
		cout << "AND "<<endl;	
		if(cond_list[i].tb_name != "")
			cout<<"\t"<<cond_list[i].tb_name<<"."<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;
		else
			cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<cond_list[i].col_name<<" op "<<cond_list[i].op<<" "<< cond_list[i].value<<endl;		
	}
}
void print_select(char* tbl, vector<char*> cols, vector<OP> ops, char** keys){
  cout<<"σ "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  for(int i=0; i< 10;i++){
    if(keys[i] != NULL){
      cout<<keys[i]<<" ";
    }
    else
      break;
  }
  cout<<endl;
}
void print_project(char* tbl, vector<char*> cols){
  cout <<"π "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  cout<<endl;
}
void print_join(char* tb1, char* tb2, vector<char*> cols1, vector<char*> cols2, vector<OP> ops){
  cout <<"⋈ " << tb1 << " "<<tb2<<" ";
  for_each(cols1.begin(),cols1.end(),print_order);
  for_each(cols2.begin(),cols2.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  cout<<endl;
}
void print_kashi(char* tb1, char* tb2){
  cout << "x " << tb1<<" "<<tb2<<endl;
}

int PrintSelectQuery(){
	int i = 0;
	if(from_count!=0)
		cout << "SELECT "<< endl;
	if(query->all != 0)
		cout<< "*" << endl;
	if(sel_count!=0){
		cout << "SEL_LIST" <<endl;
		for(i=0; i < sel_count; i++){
			cout<<"\t"<<query->SelList[i].col_name<<endl;
		}
	}	
	cout << "FROMLIST" << endl;
	for(i = 0; i < from_count; i++){
		cout<<"\t"<<query->FromList[i].tb_name<<endl;
	}
	if(cond_count!=0){
		cout <<"WHERECLAUSE"<< endl;
	}
	PrintTree();
/*
	for(i = 0; i < cond_count; i++){
			
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[i].tb_name<<"."<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;
		else
			//cout << " op " << query->CondList[i].op << endl;
			cout<<"\t"<<query->CondList[i].col_name<<" op "<<query->CondList[i].op<<" "<< query->CondList[i].value<<endl;	
		cout << "AND "<<endl;	
	}
	for(i=0;i < join_count; i++){
		cout<<"\t"<<query->JoinList[i].tb_name1<<"."<<query->JoinList[i].col_name1<<" op "<<query->JoinList[i].op<<" "<<query->JoinList[i].tb_name2<<"."<<query->JoinList[i].col_name2<<endl;
		cout << "AND "<<endl;
	}*/	
	if(attr_count != 0)
		cout<<"CREATE TABLE "<<endl;
	for(i=0;i<attr_count;i++){
		cout<<attr_list[i].table_name<<"attr_name "<<attr_list[i].attr_name<<"type "<<attr_list[i].type<<"size "<<attr_list[i].used_size<<endl;
	}
	if(orderby_count!=0)
		cout<<"ORDER BY"<< endl;
	for(i=0;i<orderby_count;i++)
		cout<<query->OrderbyList[i].col_name<<endl;
	
	return 0;
}

void PrintTree(){
	int i;
	if(cond_count == 1 && join_count == 0){
		if(query->CondList[i].tb_name != "")
			cout<<"\t"<<query->CondList[0].tb_name<<"."<<query->CondList[0].col_name<<" op "<<query->CondList[0].op<<" "<< query->CondList[0].value<<endl;
		else
			cout<<"\t"<<query->CondList[0].col_name<<" op "<<query->CondList[0].op<<" "<< query->CondList[0].value<<endl;
		return;
	}//end if cond_count 1
	if(join_count == 1 && cond_count == 0){
		cout<<"\t"<<query->JoinList[0].tb_name1<<"."<<query->JoinList[0].col_name1<<" op "<<query->JoinList[0].op<<" "<<query->JoinList[0].tb_name2<<"."<<query->JoinList[0].col_name2<<endl;
		return;
	}//end if join_count 1
	else{
		cout<<"AND"<<endl;
		cout<<"| \t\t \\"<<endl;
		// for join_count + cond_count >= 3
		for(i=1;i<(join_count+cond_count)-1;i++){
			PrintSpace(i-1);
			PrintSpace(i-1);
			if(i<=cond_count){
				cout<<" op "<<query->CondList[i-1].op<<"\t\tAND"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<"|\t\\"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				if(query->CondList[i-1].tb_name != "")
					cout<<query->CondList[i-1].tb_name<<"."<<query->CondList[i-1].col_name<<" "<< query->CondList[i-1].value<<endl;
				else
				//cout << " op " << query->CondList[i].op << endl;
					cout<<query->CondList[i-1].col_name<<" "<< query->CondList[i-1].value<<endl;
			}
			if(i>cond_count){
				cout<<" op "<<query->JoinList[i-cond_count-1].op<<"\t\tAND"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<"|\t\\"<<endl;
				PrintSpace(i-1);
				PrintSpace(i-1);
				cout<<query->JoinList[i-cond_count-1].tb_name1<<"."<<query->JoinList[i-cond_count-1].col_name1<<" "<<query->JoinList[i-cond_count-1].tb_name2<<"."<<query->JoinList[i-cond_count-1].col_name2<<endl;
			}
			//cout<<"cond"<<i-1<<"\tAND"<<endl;
			PrintSpace(i);
			PrintSpace(i);
			cout<<"| \t\t \\"<<endl;
		}//end for
		PrintSpace(join_count+cond_count-2);
		PrintSpace(join_count+cond_count-2);
		if((join_count == 1)&(cond_count>=2)){
			cout<<" op "<<query->CondList[cond_count-1].op<<"\t\t\t"<<" op "<<query->JoinList[0].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			if(query->CondList[cond_count-1].tb_name != "")
				cout<<query->CondList[cond_count-1].tb_name<<"."<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<"\t\t\t";
			else
				cout<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<"\t\t\t";
			cout<<query->JoinList[join_count-1].tb_name1<<"."<<query->JoinList[join_count-1].col_name1<<" "<<query->JoinList[join_count-1].tb_name2<<"."<<query->JoinList[join_count-1].col_name2<<endl;
			return;			
		}
		if(join_count >=2 ){
			cout<<" op "<<query->JoinList[join_count-2].op<<"\t\t"<<" op "<<query->JoinList[join_count-1].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<query->JoinList[join_count-2].tb_name1<<"."<<query->JoinList[join_count-2].col_name1<<" "<<query->JoinList[join_count-2].tb_name2<<"."<<query->JoinList[join_count-2].col_name2<<"\t"<<query->JoinList[join_count-1].tb_name1<<"."<<query->JoinList[join_count-1].col_name1<<" "<<query->JoinList[join_count-1].tb_name2<<"."<<query->JoinList[join_count-1].col_name2<<endl;
			return;
		}//end if join_count >= 2
		if (join_count==0 & cond_count >= 2){
			cout<<" op "<<query->CondList[cond_count-2].op<<"\t\t\t"<<" op "<<query->CondList[cond_count-1].op<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			cout<<"| \\\t\t\t| \\"<<endl;
			PrintSpace(join_count+cond_count-2);
			PrintSpace(join_count+cond_count-2);
			if(query->CondList[cond_count-2].tb_name != "")
				cout<<query->CondList[cond_count-2].tb_name<<"."<<query->CondList[cond_count-2].col_name<<" "<< query->CondList[cond_count-2].value<<"\t";
			else
				cout<<query->CondList[cond_count-2].col_name<<" "<< query->CondList[cond_count-2].value<<"\t";
			if(query->CondList[cond_count-1].tb_name != "")
				cout<<query->CondList[cond_count-1].tb_name<<"."<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<endl;
			else
				cout<<query->CondList[cond_count-1].col_name<<" "<< query->CondList[cond_count-1].value<<endl;
			return;
		}//end if join = 0 & cond >= 2
	}//end else	
}
void PrintSpace(int n){
	int i;
	for(i=0;i<n;i++){
		cout<<"\t";	
	}
}

OP Operator(char* opstr)
{
	OP op;
	if (strcmp(opstr, "=") == 0){
		op = eq;
		return op;
	}
	else if (strcmp(opstr, ">=") == 0) {
		op = ge;
		return op;
	}	
	else if (strcmp(opstr, "<=") == 0){
		op = le;
		return op;
	}
	else if (strcmp(opstr, ">") == 0) {
		op = gt;
		return op;
	}
	else if (strcmp(opstr, "<") == 0) {
		op = lt;
		return op;
	}
	else if (strcmp(opstr, "<>") == 0) {
		op = nq;
		return op;
	}
	return eq;
}

TYPE GetType(char* type_str)
{
	TYPE type;
	if (strcmp(type_str, "INTEGER") == 0){
		type = I;
		return type;
	}
	else if (strcmp(type_str, "CHARACTER") == 0) {
		type = C;
		return type;
	}	
	else if (strcmp(type_str, "VARCHAR") == 0){
		type = V;
		return type;
	}
	else if (strcmp(type_str, "FLOAT") == 0) {
		type = F;
		return type;
	}
	else if (strcmp(type_str, "DATE") == 0) {
		type = D;
		return type;
	}
	return I;
}
int Printdmy(){
  int i, ilen;
  BSTree<char*>* tree=new BSTree<char*>();
//    for_each(attribute.begin(),attribute.end(),print);//用for_each进行遍历    
//    cout<<endl;
  if(from_count!=0)
    cout << "SELECT "<< endl;

  vector<char*> attribute1;
  if(query->all != 0){
    cout<< "*" << endl;
    attribute1.insert(attribute1.end(),"*");
  }
  if(sel_count!=0){
    cout << "SEL_LIST" <<endl;
    for(i=0; i < sel_count; i++){
      attribute1.insert(attribute1.end(),query->SelList[i].col_name);
    }
  }
  tree->insert_touying(NULL, attribute1);

  cout << "CONDITION" <<endl;
  for(i = 0; i < cond_count; i++){
    vector<char*> attribute2;
    attribute2.insert(attribute2.end(),cond_list[i].col_name);
    int b2[] = {1,2};
    vector<OP> op2;
    op2.insert(op2.end(),cond_list[i].op);
    vector<char*> value2;
    value2.insert(value2.end(),cond_list[i].value);
    tree->insert_xuanze(cond_list[i].tb_name, attribute2, op2, value2);
  }

  cout << "JOIN" <<endl;
  for(i = 0; i < join_count; i++){
    if (i==0)
      tree->insert_lianjie(query->JoinList[i].op, query->JoinList[i].tb_name1, query->JoinList[i].col_name1, query->JoinList[i].tb_name2, query->JoinList[i].col_name2, 0);
    else
      tree->insert_lianjie(query->JoinList[i].op, query->JoinList[i].tb_name1, query->JoinList[i].col_name1, query->JoinList[i].tb_name2, query->JoinList[i].col_name2, 1);
  }

  cout << "FROMLIST" << endl;
  vector<char*> tbl;
  for(i = 0; i < from_count; i++){
    tbl.insert(tbl.end(), query->FromList[i].tb_name);
  }  

  tree->insert_kashiji(tbl);



  Message message[100];
  memset(message,0,sizeof(struct Message)*100);
  tree->get(message);

  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    } 
    cout<<message[i].key<<"\t";  
    for_each(message[i].attribute.begin(),message[i].attribute.end(),print_order);
    cout<<"\t";
    for_each(message[i].value.begin(),message[i].value.end(),print_order);
    cout<<"\t";
    for_each(message[i].op.begin(),message[i].op.end(),print_order_int);
    cout<<"\t";
    if (message[i].tbl_name != NULL)
      cout <<message[i].tbl_name;
    cout <<endl;
  } 

  vector<Message> nodes;
  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    }
    nodes.insert(nodes.end(), message[i]);
  }

  cout<<endl<<"执行顺序"<<endl;
  vector<Message>::iterator it;
  int tmp_id =0;
  char *s = "tmptb";
  for(it=nodes.begin(); it!=nodes.end();it++){
    if (it != nodes.end() - 1) {
	    if ((*it).key == "⋈"){
	      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
	      
          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          vector<int> cols1;
          vector<int> cols2;
	      for (int i = 0; i < (*(it)).attribute.size(); i++) {
		  	int col = table_manager->tables[left_tb_id]->GetAttrId((*(it)).attribute[i]);
		  	cols1.push_back(col);
	      }
	      for (int i = 0; i < (*(it)).value.size(); i++) {
		  	int col = table_manager->tables[right_tb_id]->GetAttrId((*(it)).value[i]);
		  	cols2.push_back(col);
	      }
          tmp_id = table_manager->NestedLoopJoinTmp(left_tb_id, right_tb_id, cols1, cols2, (*(it)).op, false); 


          it=nodes.erase(it-2, it);
	      
          string str = table_manager->GetTableName(tmp_id);
	      char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
	      (*(it)).tbl_name = s;

	      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
	    }
	    if ((*it).key == "x"){
	      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);

          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          tmp_id = table_manager->NestedLoopCartesianProductTmp(left_tb_id, right_tb_id, false); 
	      it=nodes.erase(it-2, it);

          string str = table_manager->GetTableName(tmp_id);
	      char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
	      (*(it)).tbl_name = s;

	      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
	    }
	    if ((*it).key == "π"){
	      
	      print_project((*(it-1)).tbl_name, (*(it)).attribute);
	      int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
	      vector<int> cols;
          if (strcmp((*(it)).attribute[0], "*") != 0) {
		      for (int i = 0; i < (*(it)).attribute.size(); i++) {
			    int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
			  	cols.push_back(col);
		      }
          }
          for_each(cols.begin(),cols.end(),print_order_int);

	      tmp_id = table_manager->ProjectTmp(tb_id, cols);
	      
          it=nodes.erase(it-1, it);
	      

          string str = table_manager->GetTableName(tmp_id);
	      char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
	      (*(it)).tbl_name = s;
	      
	      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
	    }
	    if ((*it).key == "σ"){
	      //cout<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      char* keys[10];
	      memset(keys,0,sizeof(char* )*10);
	      for(i = 0;i<(*(it)).value.size();i++){
		       keys[i] = (*(it)).value[i];
	      }
	      print_select((*(it-1)).tbl_name, (*(it)).attribute, (*(it)).op, keys);
	      
          int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
	      vector<int> cols;
	      for (int i = 0; i < (*(it)).attribute.size(); i++) {
		  	int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
		  	cols.push_back(col);
	      }
	      tmp_id = table_manager->SelectTmp(tb_id, cols, (*(it)).op, keys);
	      
          it=nodes.erase(it-1, it);
          string str = table_manager->GetTableName(tmp_id);
          cout <<str <<endl;
	      char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
	      (*(it)).tbl_name = s;
	      (*(it)).key = s;
	      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
	    }
     } else {
	    if ((*it).key == "⋈"){
	      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
	      
          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          vector<int> cols1;
          vector<int> cols2;
	      for (int i = 0; i < (*(it)).attribute.size(); i++) {
		  	int col = table_manager->tables[left_tb_id]->GetAttrId((*(it)).attribute[i]);
		  	cols1.push_back(col);
	      }
	      for (int i = 0; i < (*(it)).value.size(); i++) {
		  	int col = table_manager->tables[right_tb_id]->GetAttrId((*(it)).value[i]);
		  	cols2.push_back(col);
	      }
          table_manager->NestedLoopJoin(left_tb_id, right_tb_id, cols1, cols2, (*(it)).op, false); 


          it=nodes.erase(it-2, it);
	    }
	    if ((*it).key == "x"){
	      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);

          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          table_manager->NestedLoopCartesianProduct(left_tb_id, right_tb_id, false); 

	      it=nodes.erase(it-2, it);
	    }
	    if ((*it).key == "π"){
	      
	      print_project((*(it-1)).tbl_name, (*(it)).attribute);
	      int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
	      vector<int> cols;
          if (strcmp((*(it)).attribute[0], "*") != 0) {
		      for (int i = 0; i < (*(it)).attribute.size(); i++) {
			    int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
			  	cols.push_back(col);
		      }
          }
          for_each(cols.begin(),cols.end(),print_order_int);

	      table_manager->Project(tb_id, cols);
	      
          it=nodes.erase(it-1, it);
	    }
	    if ((*it).key == "σ"){
	      //cout<<(*(it-1)).key<<(*(it-0)).key<<" ";
	      char* keys[10];
	      memset(keys,0,sizeof(char* )*10);
	      for(i = 0;i<(*(it)).value.size();i++){
		       keys[i] = (*(it)).value[i];
	      }
	      print_select((*(it-1)).tbl_name, (*(it)).attribute, (*(it)).op, keys);
	      
          int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
	      vector<int> cols;
	      for (int i = 0; i < (*(it)).attribute.size(); i++) {
		  	int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
		  	cols.push_back(col);
	      }
	      table_manager->Select(tb_id, cols, (*(it)).op, keys);
	      
          it=nodes.erase(it-1, it);
	    }
     }
  }


  tree->destroy();
  return 0;
/*  int i;
  if(from_count!=0)
    cout << "SELECT "<< endl;
  if(query->all != 0)
    cout<< "*" << endl;
  if(sel_count!=0){
    cout << "SEL_LIST" <<endl;
    for(i=0; i < sel_count; i++){
      //cout<<" "<<query->SelList[i].col_name<<endl;
      if (NULL ==query->SelList[i].table_name)
        cout<<" "<<query->SelList[i].col_name<<endl;
      else
        cout<< query->SelList[i].table_name << " "<<query->SelList[i].col_name<<endl;
    }
  }

  cout << "FROMLIST" << endl;
  for(i = 0; i < from_count; i++){
    cout<<"\t"<<query->FromList[i].tb_name<<endl;
  }  
  cout << "CONDITION" <<endl;
  for(i = 0; i < cond_count; i++){
    cout << cond_list[i].op <<" "<< cond_list[i].tb_name <<" "<< cond_list[i].tb_id <<" "<< cond_list[i].col_name <<" "<< cond_list[i].value <<" "<< cond_list[i].value_type << endl;
  }
  cout << "JOIN" <<endl;
  for(i = 0; i < join_count; i++){
    cout << query->JoinList[i].op <<" "<< query->JoinList[i].tb_name1 <<" "<< query->JoinList[i].col_name1 << query->JoinList[i].tb_name2 <<" "<< query->JoinList[i].col_name2 << endl;
  }*/
}
