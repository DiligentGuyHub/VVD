#include "IdTable.h"
#include "LexTable.h"
#include "Error.h"
#include "FST.h"
#include "Regular Expressions.cpp"

namespace LT 
{
	LexTable& CreateEntry
	(
		LexTable& lex,
		IT::IdTable& idt,
		char* buffer,
		int line,
		int id
	);

	void LexTableFill
	(
		LexTable& lex,
		LexTable& lexcopy,
		In::IN,
		IT::IdTable& idt
	);

	void LexTableOut
	(
		LexTable lex
	);

	char* ClearChar(
		char* buffer
	);

	int ConvertToDecimal(
		char* buffer
	);

}