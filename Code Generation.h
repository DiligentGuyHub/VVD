#include "IdTable.h"
#include "LexTable.h"
#include "Error.h"
#include <iomanip>
#include <fstream>
#include <time.h>

#define STANDARD_LIBRARY		*file << "from StandardLibrary import *\n\n"

#define OPERAND_NAME(n)			idt.table[lex.table[n].idxTI].id
#define OPERAND_DATATYPE(n)		idt.table[lex.table[n].idxTI].iddatatype
#define OPERAND_TYPE(n)			idt.table[lex.table[n].idxTI].idtype
#define OPERAND_VALUE(n)		switch (OPERAND_DATATYPE(n))	\
								{\
								case IT::INT:\
									*file << idt.table[lex.table[n].idxTI].value.vint << ""; \
									break; \
								case IT::PINT: \
									*file << idt.table[lex.table[n].idxTI].value.vpint << ""; \
									break; \
								case IT::BOOL: \
									*file << idt.table[lex.table[n].idxTI].value.vbool.value << ""; \
									break; \
								case IT::STR: \
									*file << "\"" << idt.table[lex.table[n].idxTI].value.vstr.str << "\""; \
									break; \
								case IT::SIGN: \
									*file << "\"" << idt.table[lex.table[n].idxTI].value.vsign << "\""; \
									break; \
								}
#define OPERATION(n)			switch (lex.table[n].operation)	\
								{\
								case '~': \
									*file << " ~"; \
									break; \
								case '&': \
									*file << " & "; \
									break; \
								case '\\': \
									*file << " | "; \
									break; \
								case '>': \
									*file << " > "; \
									break; \
								case '<': \
									*file << " < "; \
									break; \
								case '1': \
									*file << " >= "; \
									break; \
								case '2': \
									*file << " <= "; \
									break; \
								case '=': \
									*file << " == "; \
									break; \
								case '!': \
									*file << " != "; \
									break; \
								default: \
									*file << " " << lex.table[position].operation << " "; \
								}

#define TAB(n)					for(int i = 0; i < n; i++) *file << "\t";

namespace Python
{
	extern int intliteral;
	extern int pintliteral;
	extern int boolliteral;
	extern int strliteral;
	extern int signliteral;
	extern int tab;

	void General(LT::LexTable& lex, IT::IdTable& idt, char* filename);
	void Function(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file);
	void WithinFunction(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position);
	void Expression(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position);
	void Condition(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position);
	void Print(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position);
	void Return(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position);

}