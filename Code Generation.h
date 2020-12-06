#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Error.h"
#define MASM_HEAD	".586\n.model flat, stdcall\n"
#define MASM_LIBS	"includelib libucrt.lib\nincludelib kernel32.lib\n" // добавить стандартную библиотеку
#define MASM_PROTO	"ExitProcess PROTO:DWORD" // добавить функции стандартной библиотеки
#define MASM_STACK	".stack 4096"
#define MASM_CONST	".const"
#define MASM_END	""

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
		char* outfile
	);
}