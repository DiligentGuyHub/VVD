#include "VVD.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Error.h"
#include "Lexical Analysis.h"

namespace PolishNotation
{
	enum CurrentPriority { 
		HIGH = 3,
		MIDDLE = 2, 
		LOW = 1,
		NONE = 0
	};

	struct Lexema
	{
		LT::Entry entry;
		CurrentPriority priority;
	};

	void Checkout(
		LT::LexTable& lextable,
		IT::IdTable& idtable
	);

	bool PolishNotation(
		int	lextable_position,
		LT::LexTable& lextable,
		IT::IdTable& idtable
	);

	bool PolishNotationBoolean(
		int	lextable_position,
		LT::LexTable& lex,
		IT::IdTable& idt
	);


}
