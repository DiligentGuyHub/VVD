#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Error.h"

#define MASM_HEAD				".586\n.model flat, stdcall\n"
#define MASM_LIBS				"includelib libucrt.lib\nincludelib kernel32.lib\nincludelib user32.lib\nincludelib \"..\\Debug\\StandardLibrary.lib\"\n"	
#define MASM_PROTO				"\nExitProcess proto : DWORD\nMessageBoxA PROTO	: DWORD, : DWORD, : DWORD, : DWORD\n"
#define MASM_EXTERN				"extern StrLen : proc\nextern StrInt : proc\nextern IntStr : proc\nextern PintStr : proc\nextern SignInt : proc\nextern print_int : proc\nextern print_pint : proc\nextern print_bool : proc\nextern print_str : proc\nextern print_sign : proc\n"

#define MASM_STACK				"\n.stack 4096\n"

#define MASM_CONST				"\n.const\n"
#define MASM_LITERAL_INT(n)		"INT"	<< n << "\t\t\tSDWORD\t"
#define MASM_LITERAL_PINT(n)	"PINT"	<< n << "\t\t\tDWORD\t"
#define MASM_LITERAL_BOOL(n)	"BOOL"	<< n << "\t\t\tBYTE\t"
#define MASM_LITERAL_STR(n)		"STR"	<< n << "\t\t\tBYTE\t"
#define MASM_LITERAL_SIGN(n)	"SIGN"	<< n << "\t\t\tBYTE\t"

#define MASM_DATA				"\n.data\n"
#define MASM_VARIABLE_INT(n)	n << "\t\t\tSDWORD\t"
#define MASM_VARIABLE_PINT(n)	n << "\t\t\tDWORD\t"
#define MASM_VARIABLE_BOOL(n)	n << "\t\t\tBYTE\t"
#define MASM_VARIABLE_STR(n)	n << "\t\t\tBYTE\t"
#define MASM_VARIABLE_SIGN(n)	n << "\t\t\tBYTE\t"

#define MASM_CODE				"\n.code\n"
#define MASM_MAIN				"main PROC\n"
#define MASM_END				"\tpush 0\n\tcall ExitProcess\nmain ENDP\nend main" 
#define MASM_PROC(n)			n << " PROC\t"
#define MASM_
#define MASM_
#define MASM_CALL(n)			"\tcall " << n << "\noush eax\n"
#define MASM_PUSH_OFFSET(n)		"\tpush offset\t" << n << "\n"
#define MASM_PUSH_OFFSET_		"\tpush offset\t"
#define MASM_PUSH(n)			"\tpush\t" << idt.table[lex.table[position].idxTI].function << "_" << n << "\n"
#define MASM_PUSH_				"\tpush\t"
#define MASM_MOV				"\tpop ebx\n\tmov\t" << idt.table[lex.table[sourceposition].idxTI].function << "_" << idt.table[lex.table[sourceposition].idxTI].id << ", ebx\n\n"
#define MASM_RETURN				"\tret"
#define MASM_END_PROC(n)		n << " ENDP\n"

#define MASM_VARIABLE(n)		idt.table[lex.table[n].idxTI].function << "_" << idt.table[lex.table[n].idxTI].id
#define MASM_LITERAL(n, c)		n << c

#define MASM_ADD				"\tpop ebx\n\tpop edx\n\tadd edx, ebx\n\tpush edx\n"
#define MASM_SUB				"\tpop ebx\n\tpop edx\n\tsub edx, ebx\n\tpush edx\n"
#define MASM_MUL				"\tpop ebx\n\tpop eax\n\tmov edx, 0\n\tmul ebx\n\tmov ebx, eax\n\tpush eax\n"
#define MASM_DIV				"\tpop ebx\n\tpop eax\n\tmov edx, 0\n\tdiv ebx\n\tmov ebx, eax\n\tpush eax\n"
#define MASM_AND				"\tpop ebx\n\tpop edx\n\tand edx, ebx\n\tpush edx\n"
#define MASM_OR					"\tpop ebx\n\tpop edx\n\tor edx, ebx\n\tpush edx\n"

#define MASM_PRINT_INT			"\tcall print_int"
#define MASM_PRINT_PINT			"\tcall print_pint"
#define MASM_PRINT_BOOL			"\tcall print_bool"
#define MASM_PRINT_STR			"\tcall print_str"
#define MASM_PRINT_SIGN			"\tcall print_sign"

namespace Generation
{
	void CodeGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		char* outfile
	);

	void LiteralGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		std::ofstream* file
	);

	void VariableGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		std::ofstream* file
	);

	void FunctionGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		std::ofstream* file
	);

	void WithinFunctionGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		std::ofstream* file,
		int& position, 
		int&,
		int&,
		int&,
		int&,
		int&
	);

	void ValuePush(
		LT::LexTable& lex, 
		IT::IdTable& idt,
		std::ofstream* file,
		int& pos, 
		int&,
		int&,
		int&,
		int&,
		int&
	);

	void ValuePush(
		LT::LexTable& lex,
		IT::IdTable& idt, 
		std::ofstream* file,
		int& position
	);
}