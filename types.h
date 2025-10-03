#ifndef __TYPES_HPP__
#define __TYPES_HPP__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

struct DataType
{
	char *typeName;
	struct List *typeParams;
};

enum MemMode
{
	MEMMODE_SHR = 0,
	MEMMODE_UNQ = 1,
	MEMMODE_WK = 2,
	MEMMODE_MNL = 3
};

enum PrivLvl
{
	PRIVLVL_DEFAULT = 0,
	PRIVLVL_PRIVATE = 1,
	PRIVLVL_PUBLIC = 2,
	PRIVLVL_PROTECTED = 3
};

struct VarDec
{
	struct DataType *dataType;
	char *varName;
	enum MemMode memMode;
	enum PrivLvl privLvl;
	bool isConst;			// applicable for both mnl and non-mnl
	bool isImmut;			// only applicable for non-mnl declarations
	struct List *lvlsConst; // only applicable for mnl declarations
};

struct FnDec
{
	struct VarDec *varDec;
	struct List *paramDecs;
};

// constructor functions

struct DataType *newDataType(char *typeName);
struct VarDec *newVarDec(char *varName, struct DataType *dataType);
struct VarDec *newMnlVarDec(char *varName, struct DataType *dataType,
							struct List *lvlsConst);
struct FnDec *newFnDec(struct VarDec *varDec, struct List *paramDecs);

// codegen functions

void codegenDataType(FILE *f, const struct DataType *dataType);

/* defined in types.h but doesn't need to be declared here */
// void codegenLvlsConst(FILE *f, const struct List *lvlsConst);

void codegenVarDec(FILE *f, const struct VarDec *varDec);
void codegenFnDec(FILE *f, const struct FnDec *fnDec);

// other functions

bool dataTypeIsPrimitive(struct DataType *dataType);

// cleanup functions

void freeDataType(struct DataType *dataType);
void freeVarDec(struct VarDec *varDec);
void freeFnDec(struct FnDec *fnDec);

#endif