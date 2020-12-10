#pragma once
#include "Lexical Analysis.h"
#include "LexTable.h"
#include "VVD.h"

namespace Semantic
{
	void FindExpressions(
		LT::LexTable& lex,
		IT::IdTable& idt
	);

	void CheckoutIntegerExpression(
		LT::LexTable& lex,
		IT::IdTable& idt,
		int begin,
		int line,
		int& pos
	);

	void CheckoutBooleanExpression(
		LT::LexTable& lex,
		IT::IdTable& idt,
		int begin,
		int line,
		int &pos
	);

	void CheckoutStringExpression(
		LT::LexTable& lex,
		IT::IdTable& idt,
		int begin,
		int line,
		int& pos
	);

	void CheckoutSignExpression(
		LT::LexTable& lex,
		IT::IdTable& idt,
		int begin,
		int line,
		int& pos
	);

	void CheckoutPrint(
		LT::LexTable& lex,
		IT::IdTable& idt,
		int begin,
		int line,
		int& pos
	);
}