%{
#include <stdio.h>
#include <stdlib.h>
//#include "../include/parser.h"
#include "../include/yacc.tab.h"

int lineno = 1;
extern "C"{
	int yyerror(char *s);
	int yylex(void);
	int yywrap(void);
	int lex_init();
}
char *strdupxy(char *s);


%}
%%

	/* reserved keywords */
CREATE	|
create		return CREATE;
TABLE	|
table		return TABLE;
DROP	|
drop		return DROP;
INDEX	|
index		return INDEX;
SELECT	|
select		return SELECT;
FROM	|
from		return FROM;
WHERE	|
where		return WHERE;
ORDER	|
order		return ORDER;
BY	|
by		return BY;
ASC	|
asc		return ASC;
DESC	|
desc		return DESC;
UNIQUE	|
unique		return UNIQUE;
ALL	|
all		return ALL;
DISTINCT |
distinct	return DISTINCT;
INSERT	|
insert		return INSERT;
INTO	|
into		return INTO;
VALUES	|
values		return VALUES;
DELETE	|
delete		return DELETE;
AND	|
and		return AND;
INT(EGER)? |
int(eger)?	return INTEGER;
CHAR(ACTER)? |
char(acter)?	return CHARACTER;
varchar |
VARCHAR		return VARCHAR;
float	|
FLOAT		return FLOAT;
EXIT	|
exit	|
QUIT	|
quit		return EXIT;
DATE	|
date		return DATE;
SHOW	|
show		return SHOW;
TABLES	|
tables		return TABLES;
UPDATE	|
update		return UPDATE;
SET	|
set		return SET;

	/* punctation */
"="	|
"<>"	|
"<"	|
">"	|
"<="	|
">="			yylval.strval = strdupxy(yytext);	return COMPARISION;
[-+*/:(),.;]							return yytext[0];

'[^'\n]*'	yylval.strval = strdupxy(yytext); 	return STRING;
	/* names */
[a-zA-Z][a-zA-Z0-9_]*		yylval.strval = strdupxy(yytext);	return NAME;
	/* numbers */
[0-9]+		yylval.strval = strdupxy(yytext);	return NUMBER;



	/* whitespace */
\n	lineno++;
[ \t\r]+	;

	
	/* anything else */
.		yyerror("invalid character");
%%

int yyerror(char *s)
{
	printf("> %s at ==> %s\n", s, yytext);
	printf("SQL syntax error....\n");
	return 0;
}

int yywrap()
{
	extern int ctb;
	if (yyin == stdin) {
		return 1;
	} else {
		fclose(yyin);
		yyin = stdin;
		return 0;
	}
}
/* make a duplicate of s */
char *strdupxy(char *s)		
{
	char *p;
	p = (char *) malloc(strlen(s) + 1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}
int lex_init()
{
	lineno = 1;
	return 0;
}


