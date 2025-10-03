#include "lexer.h"
#include "parser.h"

#include <stdio.h>

FILE *outfile = NULL;

void yyerror(const char *s)
{
	fprintf(stderr, "Error at line %d in '%s': %s\n", yylineno, yytext, s);
}

int main(void)
{
	outfile = stdout;

	fprintf(outfile, "#include <memory>\n\n");

	yyparse();
}