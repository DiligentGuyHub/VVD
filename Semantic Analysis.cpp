#include "Semantic Analysis.h"

namespace Semantic
{
	void DefineExpressions(LT::LEX& lex)
	{
		for (int i = 0, lineCounter = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].sn != lineCounter) // определение номера строки
			{
				lineCounter = lex.lextable.table->sn;
			}


		}
	}

	void CheckOutExpression(LT::LexTable& lex, IT::IdTable& idt, int line)
	{
		TYPEOFEXPRESSION firstMentioned = U, buffer;
		for (int i = 0; lex.table[i].sn == line; i++)
		{
			if (lex.table[i].idxTI != LT_TI_NULLIDX)
			{
				if (firstMentioned == U)
				{
					
				}
			}
			/*else if ()
			{

			}
			*/
		}
	}
}