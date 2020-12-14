#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"
#include "VVD.h"

namespace Semantic
{

#define OPERAND_TYPE(n)				idt.table[lex.table[n].idxTI].idtype
#define OPERAND_DATATYPE(n)			idt.table[lex.table[n].idxTI].iddatatype
#define OPERAND_VALUE(n)			switch (OPERAND_DATATYPE(n))	\
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
#define CHECK_DATATYPE(position)	switch (prev) \
									{ \
										case IT::INT:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT){throw ERROR_THROW_IN(313, line, position - begin + 1);}\
											break;\
										case IT::PINT:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT){throw ERROR_THROW_IN(313, line, position - begin + 1);}\
											break;\
										case IT::BOOL:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT && OPERAND_DATATYPE(position) != IT::BOOL){throw ERROR_THROW_IN(313, line, position - begin + 1);}\
											break;\
										case IT::STR:\
											if (OPERAND_DATATYPE(position) != IT::STR && OPERAND_DATATYPE(position) != IT::SIGN){throw ERROR_THROW_IN(313, line, position - begin + 1);}\
											break;\
										case IT::SIGN:\
											if (OPERAND_DATATYPE(position) != IT::SIGN){throw ERROR_THROW_IN(313, line, position - begin + 1);}\
											break;\
										default:\
											if(OPERAND_TYPE(position) != IT::L){throw ERROR_THROW_IN(304, line, position - begin + 1);}\
											break; \
									}\

#define CHECK_PARM_DATATYPE(position)	switch (idt.table[parmid].iddatatype) \
									{ \
										case IT::INT:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT){throw ERROR_THROW_IN(302, line,-1);}\
											break;\
										case IT::PINT:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT){throw ERROR_THROW_IN(302, line,-1);}\
											break;\
										case IT::BOOL:\
											if (OPERAND_DATATYPE(position) != IT::INT && OPERAND_DATATYPE(position) != IT::PINT && OPERAND_DATATYPE(position) != IT::BOOL){throw ERROR_THROW_IN(302, line,-1);}\
											break;\
										case IT::STR:\
											if (OPERAND_DATATYPE(position) != IT::STR && OPERAND_DATATYPE(position) != IT::SIGN){throw ERROR_THROW_IN(302, line,-1);}\
											break;\
										case IT::SIGN:\
											if (OPERAND_DATATYPE(position) != IT::SIGN) {throw ERROR_THROW_IN(302, line,-1);}\
											break;\
									}\

#define CHECK_OPERATION(position)	switch (prev) \
									{\
										case IT::INT:\
											if(op != LT::UNDEF && op != lex.table[position].operationtype){throw ERROR_THROW_IN(314, line, position - begin + 1);}\
											break; \
										case IT::PINT:\
											if(op != LT::UNDEF && op != lex.table[position].operationtype){throw ERROR_THROW_IN(314, line, position - begin + 1);}\
											break; \
										case IT::BOOL:\
											if (lex.table[position].operationtype != LT::L){throw ERROR_THROW_IN(314, line, position - begin + 1);}\
											break; \
										case IT::STR:\
											if (lex.table[position].operation != '+'){throw ERROR_THROW_IN(314, line, position - begin + 1);}\
											break; \
										case IT::SIGN:\
											throw ERROR_THROW_IN(314, line, position - begin + 1); \
											break; \
									}\

	extern char stdlib[5][8];
	extern int begin;
	extern int line;
	extern IT::IDDATATYPE functiontype;
	void General(LT::LexTable& lex, IT::IdTable& idt);
	void Function(LT::LexTable& lex, IT::IdTable& idt);
	void WithinFunction(LT::LexTable& lex, IT::IdTable& idt, int& position);
	void Call(LT::LexTable& lex, IT::IdTable& idt, int& position);
	void Expression(LT::LexTable& lex, IT::IdTable& idt, int& position);
	void Condition(LT::LexTable& lex, IT::IdTable& idt, int& position);
	void Print(LT::LexTable& lex, IT::IdTable& idt, int& position);
	void Return(LT::LexTable& lex, IT::IdTable& idt, int& position);
}