#include "Semantic Analysis.h"
#include "IdTable.h"
#include "Error.h"
#include "PolishNotation.h"

namespace Semantic
{
	int begin = 0;
	int line = 1;
	IT::IDDATATYPE functiontype = IT::NONE;
	char stdlib[5][8]{ "StrLen", "StrInt", "IntStr", "PintStr", "SignInt" };

	void General(LT::LexTable& lex, IT::IdTable& idt)
	{
		unsigned int start = clock();
		Function(lex, idt);
		unsigned int end = clock();
		std::cout << "\nСемантический анализ завершен успешно\nВремя выполнения: ";
		if (end - start == 0)
		{
			std::cout << "< 1 мс\n";
		}
		else 
		{
			std::cout << end - start << " мс\n";
		}
		return;
	}
	void Function(LT::LexTable& lex, IT::IdTable& idt)
	{

		char* functionname;
		for (int position = 0; position < lex.size; position++)
		{
			if (lex.table[position].lexema)
			{
				if (lex.table[position].lexema == LEX_FUNCTION && lex.table[position + 1].lexema != LEX_MAIN)
				{
					functionname = idt.table[lex.table[++(++position)].idxTI].id;
					functiontype = OPERAND_DATATYPE(position);
					if (int(functionname[0]) > 90)
					{
						throw ERROR_THROW_IN(301, line, position - begin + 1);
					}
					for (++position; lex.table[position].lexema != LEX_LEFTBRACE; position++)
					{
					}
					WithinFunction(lex, idt, position);
					functiontype = IT::NONE;
				}
				else
				{
					WithinFunction(lex, idt, position);
					break;
				}
			}
		}
	}
	void WithinFunction(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		for (position; lex.table[position].lexema != LEX_BRACELET; position++)
		{
			if (lex.table[position].sn != line)
			{
				line = lex.table[position].sn;
				begin = position;
			}
			switch (lex.table[position].lexema)
			{
			case LEX_EQUAL:
				Expression(lex, idt, position);
				break;
			case LEX_IF:
				Condition(lex, idt, position);
				break;
			case LEX_PRINT:
				Print(lex, idt, position);
				break;
			case LEX_RETURN:
				Return(lex, idt, position);
				break;
			default:
				break;
			}
		}
	}

	void Call(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		IT::IDDATATYPE prev = IT::NONE;
		LT::OPERATIONTYPE op = LT::UNDEF;
		for (++position; lex.table[position].lexema != LEX_RIGHTHESIS; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					if (prev == IT::NONE)
					{
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
					Call(lex, idt, position);
				}
				else
				{
					if (prev == IT::NONE)
					{
						if (OPERAND_DATATYPE(position) == IT::NONE)
						{
							throw ERROR_THROW_IN(304, line, position - begin + 1);
						}
						prev = OPERAND_DATATYPE(position);
					}
				}
				break;
			case LEX_LITERAL:
				CHECK_DATATYPE(position);
				break;
			case LEX_LEFTHESIS:
				break;
			case LEX_OPERATION:
				CHECK_OPERATION(position);
				break;
			default:
				break;
			}

		}
		if (lex.table[position + 1].lexema == LEX_SEMICOLON)
		{
			return;
		}
		else if (lex.table[position + 1].lexema == LEX_COMMA)
		{
			return;
		}
	}

	void Expression(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		int sourceposition = 0;
		IT::IDDATATYPE prev = IT::NONE;
		LT::OPERATIONTYPE op = LT::UNDEF;
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_EQUAL:
				sourceposition = position - 1;
				prev = OPERAND_DATATYPE(sourceposition);
				break;
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::UNDEF || OPERAND_DATATYPE(position) == IT::NONE)
				{
					throw ERROR_THROW_IN(304, line, position - begin + 1);
				}
				if (OPERAND_TYPE(position) == IT::F)
				{
					CHECK_DATATYPE(position);
					Call(lex, idt, position);
				}
				else
				{
					CHECK_DATATYPE(position);
				}
				break;
			case LEX_LITERAL:
				CHECK_DATATYPE(position);
				break;
			case LEX_OPERATION:
				if (prev == IT::BOOL || prev == IT::STR || prev == IT::SIGN)
				{
					CHECK_OPERATION(position);
				}
				else {
					if (op == LT::UNDEF)
					{
						op = lex.table[position].operationtype;
					}
					else
					{
						CHECK_OPERATION(position);
					}
				}
				break;
			case LEX_SEMICOLON:
				begin = position + 1;
				return;
			default:
				break;
			}
		}
	}
	void Condition(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		IT::IDDATATYPE prev = IT::BOOL;
		LT::OPERATIONTYPE op = LT::L;
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					if (prev == IT::NONE)
					{
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
					Call(lex, idt, position);
				}
				else
				{
					if (prev == IT::NONE)
					{
						if (OPERAND_DATATYPE(position) == IT::NONE)
						{
							throw ERROR_THROW_IN(304, line, position - begin + 1);
						}
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
				}
				break;
			case LEX_OPERATION:
				CHECK_OPERATION(position);
				break;
			case LEX_LITERAL:
				CHECK_DATATYPE(position);
				break;
			case LEX_RIGHTHESIS:
				break;
			case LEX_LEFTBRACE:
				WithinFunction(lex, idt, position);
				if (lex.table[position + 1].lexema != LEX_ELIF && lex.table[position + 1].lexema != LEX_ELSE)
				{
					return;
				}
				break;
			default:
				break;
			}
		}
	}
	void Print(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		IT::IDDATATYPE prev = IT::NONE;
		LT::OPERATIONTYPE op = LT::UNDEF;
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					if (prev == IT::NONE)
					{
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
					Call(lex, idt, position);
				}
				else
				{
					if (prev == IT::NONE)
					{
						if (OPERAND_DATATYPE(position) == IT::NONE)
						{
							throw ERROR_THROW_IN(304, line, position - begin + 1);
						}
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
				}
				break;
			case LEX_OPERATION:
				if (op == LT::UNDEF)
				{
					op = lex.table[position].operationtype;
				}
				else
				{
					CHECK_OPERATION(position);
				}
				break;
			case LEX_LITERAL:
				if (prev == IT::NONE)
				{
					prev = OPERAND_DATATYPE(position);
				}
				else
				{
					CHECK_DATATYPE(position);
				}
				break;
			case LEX_SEMICOLON:
				begin = position + 1;
				return;
			default:
				break;
			}
		}
	}
	void Return(LT::LexTable& lex, IT::IdTable& idt, int& position)
	{
		IT::IDDATATYPE prev = functiontype;
		LT::OPERATIONTYPE op = LT::UNDEF;
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					if (prev == IT::NONE)
					{
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
					Call(lex, idt, position);
				}
				else
				{
					if (prev == IT::NONE)
					{
						if (OPERAND_DATATYPE(position) == IT::NONE)
						{
							throw ERROR_THROW_IN(304, line, position - begin + 1);
						}
						prev = OPERAND_DATATYPE(position);
					}
					else
					{
						CHECK_DATATYPE(position);
					}
				}
				break;
			case LEX_OPERATION:
				if (op == LT::UNDEF)
				{
					op = lex.table[position].operationtype;
				}
				else
				{
					CHECK_OPERATION(position);
				}
				break;
			case LEX_LITERAL:
				if (prev == IT::NONE)
				{
					prev = OPERAND_DATATYPE(position);
				}
				else
				{
					CHECK_DATATYPE(position);
				}
				break;
			case LEX_SEMICOLON:
				begin = position + 1;
				return;
			default:
				break;
			}
		}
	}
}