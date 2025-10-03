#include "types.h"
#include <string.h>

// =====================
// constructor functions
// =====================

struct DataType *newDataType(char *typeName)
{
	struct DataType *dt = (struct DataType *)malloc(sizeof(struct DataType));
	dt->typeName = strdup(typeName);
	dt->typeParams = NULL;
	return dt;
}

struct VarDec *newVarDec(char *varName, struct DataType *dataType)
{
	struct VarDec *varDec = (struct VarDec *)malloc(sizeof(struct VarDec));
	varDec->varName = strdup(varName);
	varDec->dataType = dataType;

	// set defaults
	varDec->memMode = dataTypeIsPrimitive(dataType) ? MEMMODE_MNL : MEMMODE_SHR;
	varDec->privLvl = PRIVLVL_DEFAULT;
	varDec->isConst = false;
	varDec->isImmut = false;
	varDec->lvlsConst = NULL;

	return varDec;
}

struct VarDec *newMnlVarDec(char *varName, struct DataType *dataType,
							struct List *lvlsConst)
{
	struct VarDec *varDec = newVarDec(varName, dataType);

	varDec->memMode = MEMMODE_MNL;
	varDec->lvlsConst = lvlsConst;

	return varDec;
}

struct FnDec *newFnDec(struct VarDec *varDec, struct List *paramDecs)
{
	struct FnDec *fn = (struct FnDec *)malloc(sizeof(struct FnDec));
	fn->varDec = varDec;
	fn->paramDecs = paramDecs;
	return fn;
}

// =================
// codegen functions
// =================

void codegenDataType(FILE *f, const struct DataType *dataType)
{
	fprintf(f, "%s", dataType->typeName);
}

void codegenLvlsConst(FILE *f, const struct List *lvlsConst)
{
	if (!lvlsConst->head)
	{
		return;
	}

	fprintf(f, " ");
	for (struct ListNode *node = lvlsConst->head;
		 node != NULL;
		 node = node->next)
	{
		bool *isConst = (bool *)node->data;
		if (*isConst)
		{
			fprintf(f, "*const ");
		}
		else
		{
			fprintf(f, "*");
		}
	}
}

void codegenVarDec(FILE *f, const struct VarDec *varDec)
{
	// privacy modifiers
	switch (varDec->privLvl)
	{
	case PRIVLVL_PRIVATE:
		fprintf(f, "private: ");
		break;
	case PRIVLVL_PUBLIC:
		fprintf(f, "public: ");
		break;
	case PRIVLVL_PROTECTED:
		fprintf(f, "protected: ");
		break;
	default:
		break;
	}

	// const keyword for const smart pointers
	if (varDec->isConst)
	{
		fprintf(f, "const ");
	}

	// smart pointers
	switch (varDec->memMode)
	{
	case MEMMODE_SHR:
		fprintf(f, "std::shared_ptr<");
		break;
	case MEMMODE_UNQ:
		fprintf(f, "std::unique_ptr<");
		break;
	case MEMMODE_WK:
		fprintf(f, "std::weak_ptr<");
		break;
	case MEMMODE_MNL:
		break;
	default:
		break;
	}

	// const again if immut (smart pointers only)
	if (varDec->isImmut)
	{
		fprintf(f, "const ");
	}

	// data type
	codegenDataType(f, varDec->dataType);

	if (varDec->memMode != MEMMODE_MNL)
	{
		// end smart pointer
		fprintf(f, ">");
	}
	else
	{
		// manual pointer declaration
		if (varDec->lvlsConst)
			codegenLvlsConst(f, varDec->lvlsConst);
	}

	fprintf(f, " %s", varDec->varName);
}

void codegenFnDec(FILE *f, const struct FnDec *fnDec)
{
	codegenVarDec(f, fnDec->varDec);
	fprintf(f, "(");
	for (struct ListNode *ln = fnDec->paramDecs->head;
		 ln != NULL;
		 ln = ln->next)
	{
		struct VarDec *paramDec = (struct VarDec *)ln->data;
		codegenVarDec(f, paramDec);
		if (ln->next)
		{
			fprintf(f, ", ");
		}
	}
	fprintf(f, ")");
}

// ===============
// other functions
// ===============

bool dataTypeIsPrimitive(struct DataType *dataType)
{
	if (dataType == NULL || dataType->typeName == NULL)
		return false;

	const char *primitiveTypes[] = {
		"bool", "char", "wchar_t", "char8_t", "char16_t", "char32_t",
		"short", "int", "long", "long long",
		"float", "double", "long double",
		"void"};

	const size_t numPrimitives =
		sizeof(primitiveTypes) / sizeof(*primitiveTypes);

	for (size_t i = 0; i < numPrimitives; ++i)
	{
		if (strcmp(dataType->typeName, primitiveTypes[i]) == 0)
			return true;
	}

	return false;
}

// =================
// cleanup functions
// =================

void freeDataType(struct DataType *dataType)
{
	free(dataType->typeName);
	free(dataType);
}

void freeVarDec(struct VarDec *varDec)
{
	if (varDec->lvlsConst)
		freeList(varDec->lvlsConst, free);
	free(varDec->varName);
	freeDataType(varDec->dataType);
	free(varDec);
}

void freeVarDecFromVoidPtr(void *ptr)
{
	freeVarDec((struct VarDec *)ptr);
}

void freeFnDec(struct FnDec *fnDec)
{
	freeVarDec(fnDec->varDec);
	freeList(fnDec->paramDecs, freeVarDecFromVoidPtr);
	free(fnDec);
}
