#include "VVD.h"
#include "LexTable.h"
#include "FST.h"
#include "Error.h"
#include "Log.h"
#include "IdTable.h"
#include "Regular Expressions.cpp"
#include "Lexical Analysis.h"


namespace LT {

	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE) throw ERROR_THROW(114);
		LexTable lex;
		lex.maxsize = size;
		lex.size = 0;
		lex.expressionsAmount = 0;
		lex.table = new Entry[size];
		return lex;
	}

	void Add(LexTable& lex, Entry entry)
	{
		if (lex.size == lex.maxsize) throw ERROR_THROW(115);
		lex.table[lex.size++] = entry;
		return;
	}

	Entry GetEntry(LexTable& lex, int n)
	{
		for (int i = 0; i < lex.size; i++)
		{
			if (lex.table[i].idxTI == n) return lex.table[i];
		}
		throw ERROR_THROW(117);
	}

	void Delete(LexTable& lex)
	{
		if (lex.table == nullptr) throw ERROR_THROW(118);
		lex.maxsize = 0;
		lex.size = 0;
		delete[] lex.table;
		return;
	}

}