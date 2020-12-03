#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"

namespace Semantic
{
	enum TYPEOFEXPRESSION {C = 1, L = 2, B = 3, U};

	// c - arithmetic
	// l - logic
	// b - byte
	// uknown - causes an error

	struct Expressions
	{
		int line;
		TYPEOFEXPRESSION type;
	};

	void DefineExpressions(LT::LexTable& lex);
}