#include "IdTable.h"
#include "LexTable.h"
#include "Error.h"
#include "FST.h"
#include "Regular Expressions.cpp"
#include "VVD.h"

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

	int LengthOfChar(
		char* buffer
	);

	char* DeleteFirstAndLast(
		char* buffer,
		int size
	);

	void LexicalAnalysisStatistics(
		uint start,
		uint finish
	);

	int ConvertToDecimal(
		char* buffer
	);

}