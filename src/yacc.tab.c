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
extern "C"{
	extern int yylex(void);
	extern int lex_init();
	extern int yyerror(char *s);
}
/*
  	functions
 */
int PrintSelectQuery();
int PrintAttrList();
int PrintCondList();
void PrintSpace(int n);
void PrintTree();

int SaveSelItem(char* tb_name, char* col_name);
int SaveFromItem(char* tb_name);
int SaveCondition(char* tb_name, char* col_name, char* value, TYPE value_type, OP op);
int SaveJoin(char* tb_name1, char* col_name1, char* tb_name2, char* col_name2, OP op);
int SaveOrderbyItem(char *col_name);
int SaveAttributeInfo(char* attr_name, TYPE type, int size);
int FillSelectCond();
int FillDeleteCond();
int FillUpdateCond();

static char errmsg[4096];
OP Operator(char* opstr);
TYPE GetType(char* type_str);
static char recordstr[4096];
//TableManagement* table_manager;

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


#line 142 "yacc.tab.c" /* yacc.c:339  */

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
    LOAD = 277,
    INSERT = 278,
    INTO = 279,
    VALUES = 280,
    DELETE = 281,
    UPDATE = 282,
    SET = 283,
    CHARACTER = 284,
    INTEGER = 285,
    DATE = 286,
    FLOAT = 287,
    VARCHAR = 288,
    SHOW = 289,
    TABLES = 290,
    EXIT = 291
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 77 "yacc.y" /* yacc.c:355  */

	int intval;
	char* strval;

#line 224 "yacc.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACC_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 241 "yacc.tab.c" /* yacc.c:358  */

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
#define YYFINAL  28
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   107

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  133

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   291

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
      42,    43,    10,     8,    44,     9,    45,    11,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
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
      39,    40
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   107,   107,   120,   126,   130,   131,   132,   133,   134,
     135,   136,   140,   150,   159,   167,   168,   171,   178,   184,
     189,   194,   200,   206,   214,   222,   231,   239,   247,   259,
     274,   286,   288,   291,   308,   326,   342,   347,   356,   361,
     368,   375,   379,   384,   389,   396,   397,   400,   405,   411,
     412,   415,   421,   425,   430,   432,   435,   436,   439,   443,
     447,   451,   455,   460,   462,   465,   469
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
  "CREATE", "TABLE", "DROP", "INDEX", "LOAD", "INSERT", "INTO", "VALUES",
  "DELETE", "UPDATE", "SET", "CHARACTER", "INTEGER", "DATE", "FLOAT",
  "VARCHAR", "SHOW", "TABLES", "EXIT", "';'", "'('", "')'", "','", "'.'",
  "$accept", "sql_start", "sql_func", "table_load", "table_def", "table",
  "table_attr_list", "column_def", "column", "data_type", "table_drop",
  "insert_stat", "insert_list", "update_stat", "set_cond", "set_expr",
  "delete_stat", "select_stat", "select_seg", "select_clause",
  "selectbegin", "unique", "sellist", "sel_column", "fromlist",
  "sel_table", "where_clause", "condition", "expr", "orderby_clause",
  "orderlist", YY_NULLPTR
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
     291,    59,    40,    41,    44,    46
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      -7,   -42,   -15,   -11,    10,   -10,    25,    49,   -42,   -42,
      53,   -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42,    13,
      42,    16,    54,    54,    28,    54,    54,    27,   -42,   -42,
      -3,   -42,   -42,   -42,     1,   -42,    18,    17,    58,    33,
      50,    60,   -42,    55,   -12,   -42,    20,   -42,    22,   -42,
      65,   -42,    29,    30,    66,    32,    68,    -1,   -42,    34,
      -3,    56,    72,    73,   -42,   -22,   -42,    -8,   -42,    26,
      -5,    71,   -42,   -42,    40,    60,    39,    76,   -42,    67,
     -42,   -42,   -42,    41,    65,    43,   -42,   -42,    45,    47,
     -42,   -42,   -42,     3,    44,    78,    66,   -42,   -42,   -42,
     -42,   -42,    81,   -42,   -42,    83,    85,    86,    51,    46,
     -42,   -42,    80,   -42,   -42,    52,    57,    59,    61,   -42,
     -42,   -42,    38,    90,   -42,   -42,   -42,    62,   -42,   -42,
     -42,    91,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    40,     0,     0,     0,     0,     0,     0,     3,     4,
       0,     2,     5,     6,     7,     8,     9,    10,    11,     0,
       0,    41,     0,     0,     0,     0,     0,     0,     1,    36,
       0,    42,    44,    43,     0,    14,     0,     0,     0,     0,
      54,     0,    51,     0,    54,    49,    47,    39,    38,    45,
       0,    24,     0,     0,     0,     0,     0,    54,    31,     0,
       0,    63,     0,     0,    18,     0,    15,     0,    12,     0,
       0,    55,    56,    35,     0,     0,     0,    52,    50,     0,
      37,    48,    46,     0,     0,     0,    20,    21,     0,     0,
      17,    27,    26,     0,     0,     0,     0,    33,    34,    32,
      30,    53,     0,    13,    16,     0,     0,     0,     0,     0,
      60,    59,     0,    57,    65,    64,     0,     0,     0,    25,
      29,    28,     0,     0,    19,    23,    22,     0,    62,    61,
      66,     0,    58
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,   -16,   -42,    11,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,    23,   -42,   -42,    63,   -42,
     -42,   -42,   -42,    36,   -42,    37,   -41,   -42,     5,   -42,
     -42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    10,    11,    12,    13,    36,    65,    66,    67,    90,
      14,    15,    93,    16,    57,    58,    17,    18,    19,    20,
      21,    34,    48,    49,    44,    45,    55,    71,    72,    80,
     115
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      42,    94,    54,    61,    46,     1,    75,    37,    22,    39,
      40,    47,    23,    54,    24,     2,    76,     3,    25,     4,
       5,    83,    84,     6,     7,    85,    86,    87,    88,    89,
      91,    92,    60,     8,     9,    31,    32,    33,    26,    43,
      95,   127,   128,   129,    97,    98,   108,   109,   110,   111,
     120,   121,    27,    28,    29,    30,    38,    35,    51,    41,
      50,    52,    53,    56,    54,    62,    63,     1,    64,    70,
      68,    79,    69,    73,    74,    81,    46,    77,    96,   101,
     100,   112,   103,   102,   114,   105,   122,   106,   116,   107,
     117,   118,   119,   130,   132,   104,   123,    78,    99,    82,
     124,   113,   125,     0,   126,     0,    59,   131
};

static const yytype_int8 yycheck[] =
{
       3,     6,    14,    44,     3,    12,     7,    23,    23,    25,
      26,    10,    23,    14,     4,    22,    57,    24,    28,    26,
      27,    43,    44,    30,    31,    33,    34,    35,    36,    37,
       4,     5,    44,    40,    41,    19,    20,    21,    13,    42,
      45,     3,     4,     5,     4,     5,    43,    44,     4,     5,
       4,     5,     3,     0,    41,    13,    28,     3,    41,    32,
      42,     3,    29,     3,    14,    45,    44,    12,     3,     3,
      41,    15,    42,    41,     6,     3,     3,    43,     7,     3,
      41,     3,    41,    16,     3,    42,     6,    42,     5,    42,
       5,     5,    41,     3,     3,    84,    44,    60,    75,    63,
      43,    96,    43,    -1,    43,    -1,    43,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    22,    24,    26,    27,    30,    31,    40,    41,
      47,    48,    49,    50,    56,    57,    59,    62,    63,    64,
      65,    66,    23,    23,     4,    28,    13,     3,     0,    41,
      13,    19,    20,    21,    67,     3,    51,    51,    28,    51,
      51,    32,     3,    42,    70,    71,     3,    10,    68,    69,
      42,    41,     3,    29,    14,    72,     3,    60,    61,    64,
      44,    72,    45,    44,     3,    52,    53,    54,    41,    42,
       3,    73,    74,    41,     6,     7,    72,    43,    71,    15,
      75,     3,    69,    43,    44,    33,    34,    35,    36,    37,
      55,     4,     5,    58,     6,    45,     7,     4,     5,    61,
      41,     3,    16,    41,    53,    42,    42,    42,    43,    44,
       4,     5,     3,    74,     3,    76,     5,     5,     5,    41,
       4,     5,     6,    44,    43,    43,    43,     3,     4,     5,
       3,    45,     3
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    48,    48,    48,    48,
      48,    48,    49,    50,    51,    52,    52,    53,    54,    55,
      55,    55,    55,    55,    56,    57,    58,    58,    58,    58,
      59,    60,    60,    61,    61,    62,    63,    64,    65,    65,
      66,    67,    67,    67,    67,    68,    68,    69,    69,    70,
      70,    71,    71,    71,    72,    72,    73,    73,    74,    74,
      74,    74,    74,    75,    75,    76,    76
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     5,     7,     1,     1,     3,     2,     1,     4,
       1,     1,     4,     4,     4,     8,     1,     1,     3,     3,
       6,     1,     3,     3,     3,     5,     2,     5,     3,     3,
       1,     0,     1,     1,     1,     1,     3,     1,     3,     1,
       3,     1,     3,     4,     0,     2,     1,     3,     7,     3,
       3,     5,     5,     0,     3,     1,     3
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
#line 108 "yacc.y" /* yacc.c:1646  */
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
#line 1419 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 121 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Should Flush Table Here.\n"<<endl;
		}
#line 1427 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 127 "yacc.y" /* yacc.c:1646  */
    {
			funcRnt = 100;
		}
#line 1435 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 141 "yacc.y" /* yacc.c:1646  */
    {
			tb_name = (yyvsp[-1].strval);
			cout<<"LOAD " << (yyvsp[-3].strval) <<" INTO "<<(yyvsp[-1].strval)<<" "<<endl;
			string tmp_name(tb_name);
			load_data(tmp_name);
		}
#line 1446 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 151 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Create Table "<< tb_name << endl;
			PrintAttrList();
			exec_create_stmt();	
		}
#line 1456 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 160 "yacc.y" /* yacc.c:1646  */
    {
			tb_name = (yyvsp[0].strval);
			attr_list[attr_count].table_name = (yyvsp[0].strval);
			//printf("tb_name %s \n",tb_name);
		}
#line 1466 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 172 "yacc.y" /* yacc.c:1646  */
    {
			attr_count++;
			
		}
#line 1475 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 179 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].attr_name = (yyvsp[0].strval);
		}
#line 1483 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 185 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type = C;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1492 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 190 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= I;
			attr_list[attr_count].used_size = MAX_INT_ASCII_LENGTH;
		}
#line 1501 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 195 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= D;
			attr_list[attr_count].used_size = MAX_DATE_ASCII_LENGTH;
		}
#line 1510 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 201 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= V;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1519 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 207 "yacc.y" /* yacc.c:1646  */
    {
			attr_list[attr_count].type= F;
			attr_list[attr_count].used_size = (int)atoi((yyvsp[-1].strval));
		}
#line 1528 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 215 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"DROP TABLE"<< tb_name << endl;
			exec_drop_table_stmt();
		}
#line 1537 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 223 "yacc.y" /* yacc.c:1646  */
    {
			for(int i = 0; i<insert_count;i++){
				cout<<"insert_record: "<< insert_record[i]<<endl;
			}
			exec_insert_stmt();
		}
#line 1548 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 232 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_ASCII_LENGTH);
			insert_count++;
			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1560 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 240 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), 256);
			insert_count++;
			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos+=strlen((yyvsp[0].strval));
		}
#line 1572 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 248 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(sizeof(int)*MAX_INT_ASCII_LENGTH);
			memcpy(insert_record[insert_count],(yyvsp[0].strval), MAX_INT_ASCII_LENGTH);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1588 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 260 "yacc.y" /* yacc.c:1646  */
    {
			insert_record[insert_count] = (char*)malloc(256);
			memcpy(insert_record[insert_count],(yyvsp[0].strval),256);
			insert_count++;
			
			strcpy(recordstr+curPos, ",");
			curPos++;

			strcpy(recordstr+curPos, (yyvsp[0].strval));
			curPos += strlen((yyvsp[0].strval));
		}
#line 1604 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 275 "yacc.y" /* yacc.c:1646  */
    {
			cout<<"Update";
			update_query->tb_name = (yyvsp[-4].strval);
			cout<<"tb_name:"<<update_query->tb_name<<endl;
			FillUpdateCond();
			cout<<"Update Cond:"<<endl;
			exec_update_stmt();
		}
#line 1617 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 292 "yacc.y" /* yacc.c:1646  */
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
#line 1638 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 309 "yacc.y" /* yacc.c:1646  */
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
#line 1657 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 327 "yacc.y" /* yacc.c:1646  */
    {
			cout << "DELETE FROM\n"<<endl;
			delete_query->tb_name = tb_name;
			cout << delete_query->tb_name <<endl;
			FillDeleteCond();
			PrintCondList();
			cout << "Call delete() function here."<<endl;
			exec_delete_stmt();
			
		}
#line 1672 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 343 "yacc.y" /* yacc.c:1646  */
    {
		}
#line 1679 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 348 "yacc.y" /* yacc.c:1646  */
    {
			FillSelectCond();
			//select_tree();
			//select_tree();
			exec_select_stmt();			
		}
#line 1690 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 357 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 0;
			cout<<"all "<<query->all<<endl;
		}
#line 1699 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 362 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 1;
			cout<<"all "<<query->all<<endl;
		}
#line 1708 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 369 "yacc.y" /* yacc.c:1646  */
    {
			printf("-----one sub selection begin----\n");
		}
#line 1716 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 375 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 0;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1725 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 380 "yacc.y" /* yacc.c:1646  */
    {
			query->all = 1;
			cout<<"all "<<query->distinct<<endl;
		}
#line 1734 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 385 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1743 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 390 "yacc.y" /* yacc.c:1646  */
    {
			query->distinct = 1;
			cout<<"distinct "<<query->distinct<<endl;
		}
#line 1752 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 401 "yacc.y" /* yacc.c:1646  */
    {
			cout << "$1"<<endl;
			SaveSelItem(NULL,(yyvsp[0].strval));
		}
#line 1761 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 406 "yacc.y" /* yacc.c:1646  */
    {
			SaveSelItem((yyvsp[-2].strval),(yyvsp[0].strval));
		}
#line 1769 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 416 "yacc.y" /* yacc.c:1646  */
    {	cout<<"from "<<(yyvsp[0].strval)<<endl;
			SaveFromItem((yyvsp[0].strval));
			
		}
#line 1778 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 422 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1786 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 426 "yacc.y" /* yacc.c:1646  */
    {	
			cout << "Sorry, Our DB Cannnot Support Nested Select Now."<<endl;
		}
#line 1794 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 440 "yacc.y" /* yacc.c:1646  */
    {
			SaveJoin((yyvsp[-6].strval), (yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), Operator((yyvsp[-3].strval)));	
		}
#line 1802 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 444 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));	
		}
#line 1810 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 448 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition("", (yyvsp[-2].strval), (yyvsp[0].strval), V, Operator((yyvsp[-1].strval)));
		}
#line 1818 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 452 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), I, Operator((yyvsp[-1].strval)));
		}
#line 1826 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 456 "yacc.y" /* yacc.c:1646  */
    {
			SaveCondition((yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval), V, Operator((yyvsp[-1].strval)));
		}
#line 1834 "yacc.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 466 "yacc.y" /* yacc.c:1646  */
    {
			SaveOrderbyItem((yyvsp[0].strval));
		}
#line 1842 "yacc.tab.c" /* yacc.c:1646  */
    break;


#line 1846 "yacc.tab.c" /* yacc.c:1646  */
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
#line 471 "yacc.y" /* yacc.c:1906  */


void parser_init()
{
	lex_init();
	tb_name = "";
	funcRnt = 0;
	curPos = 0;

	for(int i = 0; i<insert_count;i++)
		memset(insert_record[i],0,MAX_TUPLE_SIZE);
	insert_count = 0;

	attr_count = 0;
	memset(attr_list,0,sizeof(AttrInfo)*MAX_ATTR_NUM);

	cond_count = 0;
	memset(cond_list,0,sizeof(Condition)*MAX_COND_NUM);

	join_count = 0;	
	sel_count = 0;
	from_count = 0;
	memset(query,0,sizeof(SelectQuery));
	memset(delete_query,0,sizeof(DeleteQuery));

	update_col_count = 0;
	memset(update_query,0,sizeof(UpdateQuery));
	return;
}

void InitQuery(){
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
	query->cond_count = cond_count;
	query->from_count = from_count;
	query->sel_count = sel_count;
	query->join_count = join_count;
	memcpy(query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillDeleteCond(){
	delete_query->cond_count = cond_count;
	memcpy(delete_query->CondList,cond_list,cond_count * sizeof(Condition));
	return 0;
}
int FillUpdateCond(){
	update_query->cond_count = cond_count;
	update_query->col_count = update_col_count;
	memcpy(update_query->CondList,cond_list,cond_count * sizeof(Condition));

	return 0;
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
