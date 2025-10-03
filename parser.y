%{
#include "types.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

extern int yylex();
extern int yyparse();
extern void yyerror(const char *s);
extern FILE *yyin;
extern FILE *outfile;
extern int yylineno;
extern char *yytext;

void appendBoolToList(struct List *ls, bool b) {
  
  bool *ptr = malloc(sizeof(bool));
  assert(ptr);
  *ptr = b;

  appendToList(ls, ptr);
}
%}

%union {
  int intval;
  double decval;
  char *strval;
  struct DataType *dataType;
  struct VarDec *vardec;
  struct FnDec *fndec;
  struct List *list;
}

// =========
// operators
// =========

// numerical operators
%token PLUS
%token MINUS
%token ASTERISK // for multiplication operation and manual pointers
%token FORWARDSLASH // for division operation
%token PERCENT // for modulo operation
%token HASHTAG // for protected privacy modifier

// comparison operators
%token LT // less than
%token LTE // less then or equal to
%token GT
%token GTE

// other operators
%token COMMA
%token INSERTION
%token EXTRACTION
%token DOT

// brackets and things
%token OPAREN CPAREN // ()
%token OBRACE CBRACE // {}
%token OSQUBR CSQUBR // []
%token OANGBR CANGBR // <>

// end of statement
%token SEMICOLON

// ========
// keywords
// ========

// data type keywords
%token CLASS
%token STRUCT

// mutability keywords
%token CONST
%token IMMUT
%token NOMUT

// memory management keywords
%token UNQ
%token SHR
%token WK
%token MNL

// other keywords
%token VOID
%token QUIT

// ========================
// identifiers and literals
// ========================

// identifiers
%token <strval>IDENT

// literals
%token <intval>INT_LIT;
%token <decval>DEC_LIT; // decimal literal (float or double)
%token <strval>STR_LIT;

// ============================
// data types of language parts
// ============================

%type <dataType>data_type

%type <list>mnl_ptr_dec

%type <vardec>var_typing
%type <vardec>var_memory
%type <vardec>var_immut
%type <vardec>var_constant
%type <vardec>var_dec

%type <list>var_dec_list
%type <fndec>fn_dec

%%
input:
  stmt_list
  ;

stmt_list:
  | stmt_list stmt SEMICOLON;

stmt:
  var_dec { codegenVarDec(outfile, $1); fprintf(outfile, "; "); freeVarDec($1); }
  | fn_dec { codegenFnDec(outfile, $1); fprintf(outfile, "; "); freeFnDec($1); }
  | class_dec { /* todo */ }
  | QUIT { printf("Exiting gracefully.\n"); exit(EXIT_SUCCESS); }
  ;

class_dec: CLASS IDENT { fprintf(outfile, "class %s;", $2); }
  ;

fn_dec: var_dec OPAREN CPAREN { $$ = newFnDec($1, NULL); }
  | var_dec OPAREN var_dec_list CPAREN { $$ = newFnDec($1, $3); }
  ;

var_dec_list: var_dec { $$ = newList(); appendToList($$, $1); }
  | var_dec_list COMMA var_dec { $$ = $1; appendToList($$, $3); }
  ;

var_dec: var_constant { $$ = $1; }
  ;

var_constant: var_immut { $$ = $1; }
  | CONST var_immut { $$ = $2; $$->isConst = true; }
  ;

var_immut: var_memory { $$ = $1; }
  | IMMUT var_memory { 
    $$ = $2;
    if($$->memMode == MEMMODE_MNL) {
      yyerror("Can't use 'immut' with 'mnl'.");
    }
    $$->isImmut = true; 
  }
  ;

var_memory: var_typing
  | UNQ var_typing { $$ = $2; $$->memMode = MEMMODE_UNQ; }
  | SHR var_typing { $$ = $2; $$->memMode = MEMMODE_SHR; }
  | WK var_typing { $$ = $2; $$->memMode = MEMMODE_WK; }
  | MNL var_typing { $$ = $2;  $$->memMode = MEMMODE_MNL; }
  ;

var_typing: data_type IDENT { $$ = newVarDec($2, $1); }
  | data_type mnl_ptr_dec IDENT { $$ = newMnlVarDec($3, $1, $2); }
  ;

data_type: IDENT { $$ = newDataType($1); }
  ;

mnl_ptr_dec: ASTERISK { $$ = newList(); appendBoolToList($$, false); }
  | ASTERISK CONST { $$ = newList(); appendBoolToList($$, true); }
  | mnl_ptr_dec ASTERISK { $$ = $1; appendBoolToList($$, false); }
  | mnl_ptr_dec ASTERISK CONST { $$ = $1; appendBoolToList($$, true); }
  ;

%%
