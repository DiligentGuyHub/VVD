#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Error.h"

extern int truecounter;
extern int continuecounter;

#define MASM_HEAD				".586\n.model flat, stdcall\n"
#define MASM_LIBS				"includelib libucrt.lib\nincludelib kernel32.lib\nincludelib user32.lib\nincludelib \"..\\Debug\\StandardLibrary.lib\"\n"	
#define MASM_PROTO				"\nExitProcess proto : DWORD\nMessageBoxA proto	: DWORD, : DWORD, : DWORD, : DWORD\nGetStdHandle proto : DWORD\nWriteConsoleA proto : DWORD, : DWORD, : DWORD, : DWORD, : DWORD\n\n"
#define MASM_EXTERN				"extern StrLen : proc\nextern StrInt : proc\nextern IntStr : proc\nextern PintStr : proc\nextern SignInt : proc\nextern Concat : proc\nextern print_int : proc\nextern print_pint : proc\nextern print_bool : proc\n"

#define MASM_STACK				"\n.stack 4096\n"

#define MASM_CONST				"\n.const\nhandleOutput\tSDWORD\t-11\n"
#define MASM_LITERAL_INT(n)		"INT"	<< n << "\t\t\tSDWORD\t"
#define MASM_LITERAL_PINT(n)	"PINT"	<< n << "\t\t\tDWORD\t"
#define MASM_LITERAL_BOOL(n)	"BOOL"	<< n << "\t\t\tBYTE\t"
#define MASM_LITERAL_STR(n)		"STR"	<< n << "\t\t\tBYTE\t"
#define MASM_LITERAL_SIGN(n)	"SIGN"	<< n << "\t\t\tBYTE\t"

#define MASM_DATA				"\n.data\nconsoleHandle\tDWORD\t0h\n"
#define MASM_VARIABLE_INT(n)	n << "\t\t\tSDWORD\t"
#define MASM_VARIABLE_PINT(n)	n << "\t\t\tDWORD\t"
#define MASM_VARIABLE_BOOL(n)	n << "\t\t\tBYTE\t"
#define MASM_VARIABLE_STR(n)	n << "\t\t\tBYTE\t"
#define MASM_VARIABLE_SIGN(n)	n << "\t\t\tBYTE\t"

#define MASM_CODE				"\n\n.code\n"
#define MASM_MAIN				"main PROC\n\tinvoke GetStdHandle, handleOutput\n\tmov consoleHandle, eax\n"
#define MASM_PROC(n)			n << " PROC\t"
#define MASM_CALL(n)			"\tcall " << n << "\noush eax\n"
#define MASM_PUSH_OFFSET(n)		"\tpush offset\t" << n << "\n"
#define MASM_PUSH_OFFSET_		"\tpush offset\t"
#define MASM_PUSH(n)			"\tpush\t" << idt.table[lex.table[position].idxTI].function << "_" << n << "\n"
#define MASM_PUSH_				"\tpush\t"
#define MASM_MOV				"\tpop ebx\n\tmov\t" << idt.table[lex.table[sourceposition].idxTI].function << "_" << idt.table[lex.table[sourceposition].idxTI].id << ", ebx\n\n"
#define MASM_RETURN				"\tret"
#define MASM_END				"\tpush 0\n\tcall ExitProcess\nmain ENDP\nend main" 
#define MASM_END_PROC(n)		n << " ENDP\n"

#define MASM_VARIABLE(n)		idt.table[lex.table[n].idxTI].function << "_" << idt.table[lex.table[n].idxTI].id
#define MASM_LITERAL(n, c)		n << c

#define MASM_ADD				"\tpop ebx\n\tpop edx\n\tadd edx, ebx\n\tpush edx\n"
#define MASM_CONCAT				"\tcall Concat\n"
#define MASM_SUB				"\tpop ebx\n\tpop edx\n\tsub edx, ebx\n\tpush edx\n"
#define MASM_MUL				"\tpop ebx\n\tpop eax\n\tmov edx, 0\n\tmul ebx\n\tmov ebx, eax\n\tpush eax\n"
#define MASM_DIV				"\tpop ebx\n\tpop eax\n\tmov edx, 0\n\tdiv ebx\n\tmov ebx, eax\n\tpush eax\n"
#define MASM_AND				"\tpop ebx\n\tpop edx\n\tand edx, ebx\n\tpush edx\n"
#define MASM_OR					"\tpop ebx\n\tpop edx\n\tor edx, ebx\n\tpush edx\n"
#define MASM_JA(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tja TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"
#define MASM_JAE(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tjae TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"
#define MASM_JB(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tjb TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"
#define MASM_JBE(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tjbe TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"
#define MASM_JE(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tje TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"
#define MASM_JNE(n)				"\tmov " << MASM_VARIABLE(n) << ", 0\n\t\tpop ebx\n\tpop edx\n\tcmp dl, bl\n\tjne TRUE" << ++truecounter << "\n\tjmp CONTINUE" << ++continuecounter << "\nTRUE" << truecounter << ":\n\tmov " << MASM_VARIABLE(n) << ", 1\nCONTINUE" << continuecounter << ":\n"

#define MASM_PRINT_INT			"\tcall print_int\n\n"
#define MASM_PRINT_PINT			"\tcall print_pint\n\n"
#define MASM_PRINT_BOOL			"\tcall print_bool\n\n"
#define MASM_PRINT_STR(n)		"\tinvoke WriteConsoleA, consoleHandle, eax, sizeof " << n << ", 0, 0\n"
#define MASM_PRINT_SIGN(n)		"\tinvoke WriteConsoleA, consoleHandle, eax, sizeof " << n << ", 0, 0\n"



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

	void ExpressionGeneration(
		LT::LexTable& lex,
		IT::IdTable& idt,
		std::ofstream* file,
		int& position,
		int& sourceposition,
		int& boolliteral,
		int& intliteral,
		int& pintliteral,
		int& strliteral,
		int& signliteral
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