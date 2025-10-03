%{
#include "parser.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

extern FILE *outfile;

%}

%option noinput nounput noyywrap

notword = [^A-Za-z0-9_]

%%
";" { return SEMICOLON; }
"+" { return PLUS; }
"-" { return MINUS; }
"*" { return ASTERISK; }

"class" { return CLASS; }
"struct" { return STRUCT; }

"const" { return CONST; }
"immut" { return IMMUT; }

"unq" { return UNQ; }
"shr" { return SHR; }
"wk" { return WK; }
"mnl" { return MNL; }

"quit" { return QUIT; }
"q" { return QUIT; }

[A-Za-z_][A-Za-z0-9_]* { 
	yylval.strval = strdup(yytext); 
	assert(yylval.strval); 
	return IDENT;
}
"//".* { fprintf(outfile, "%s", yytext); }
[ ]+ { /* ignore */ }
[\t\n]+ { fprintf(outfile, "%s", yytext); }
%%
