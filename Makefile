CC = gcc
CFLAGS = -g -Wall

LEXER_SRC = lexer.l
PARSER_SRC = parser.y

LEXER_C = lexer.c
LEXER_H = lexer.h
PARSER_C = parser.c
PARSER_H = parser.h

FLEX = flex
FLEX_FLEXS = --header-file=$(LEXER_H)

BISON = bison
BISON_FLAGS = -d

CPP_SRC = main.c types.c list.c $(LEXER_C) $(PARSER_C)
OBJ = $(CPP_SRC:.c=.o)
EXE = zc

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

$(OBJ): $(LEXER_C) $(PARSER_C)
	$(CC) $(CFLAGS) -c $(CPP_SRC)

$(PARSER_C): $(PARSER_SRC)
	$(BISON) $(BISON_FLAGS) -o $(PARSER_C) $(PARSER_SRC)

$(LEXER_C): $(LEXER_SRC)
	$(FLEX) $(FLEX_FLEXS) -o $(LEXER_C) $(LEXER_SRC)

clean:
	rm $(LEXER_C) $(LEXER_H) $(PARSER_C) $(PARSER_H) $(OBJ) $(EXE)

clean-keepexe:
	rm $(LEXER_C) $(LEXER_H) $(PARSER_C) $(PARSER_H) $(OBJ)