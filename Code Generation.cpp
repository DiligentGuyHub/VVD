#include "Code Generation.h"
#include <Windows.h>
#include <locale>
#include <codecvt>
using namespace std;

namespace Python
{
	int tab = 0;

	void General(LT::LexTable& lex, IT::IdTable& idt, char* filename)
	{
		unsigned int start = clock();
		setlocale(0, "");
		std::wofstream* file = new std::wofstream();
		file->open(filename);
		if (!file->is_open())
		{
			throw ERROR_THROW(8);
		}
		STANDARD_LIBRARY;
		Function(lex, idt, file);
		unsigned int end = clock();
		std::cout << "\nГенерация кода завершена успешно\nВремя выполнения: " << end - start << " мс\n";
		file->close();
		return;
	}

	void Function(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file)
	{
		char* functionname;
		for (int position = 0; position < lex.size; position++)
		{
			if(lex.table[position].lexema)
			{
				if (lex.table[position].lexema == LEX_FUNCTION && lex.table[position + 1].lexema != LEX_MAIN)
				{
					functionname = idt.table[lex.table[++(++position)].idxTI].id;
					*file << "def " << functionname << "(";
					for (++position; lex.table[position].lexema != LEX_LEFTBRACE; position++)
					{
						if (lex.table[position].lexema == LEX_ID)
						{
							*file << idt.table[lex.table[position].idxTI].id;
							if (lex.table[position + 3].lexema == LEX_ID)
							{
								*file << ", ";
							}
						}
					}
					*file << "):\n";
					tab += 1;
					WithinFunction(lex, idt, file, position);
					tab -= 1;
					*file << "\n";
				}
				else
				{
					*file << "def main():\n";
					tab += 1;
					WithinFunction(lex, idt, file, position);
					tab -= 1;
					*file << "\nmain()\n";
					break;
				}
			}
		}
	}

	void WithinFunction(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		for (position; lex.table[position].lexema != LEX_BRACELET; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_EQUAL:
				Expression(lex, idt, file, position);
				break;
			case LEX_IF:
				Condition(lex, idt, file, position);
				break;
			case LEX_PRINT:
				Print(lex, idt, file, position);
				break;
			case LEX_RETURN:
				Return(lex, idt, file, position);
				break;
			default:
				break;
			}
		}
	}

	void Call(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		*file << OPERAND_NAME(position);
		for (++position; lex.table[position].lexema != LEX_RIGHTHESIS; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					Call(lex, idt, file, position);
				}
				else
				{
					*file << OPERAND_NAME(position);
				}
				break;
			case LEX_LITERAL:
				OPERAND_VALUE(position);
				break;
			case LEX_OPERATION:
				OPERATION(position);
				break;
			default:
				*file << lex.table[position].lexema;
				break;
			}

		}
		*file << ")";
		if (lex.table[position + 1].lexema == LEX_SEMICOLON)
		{
			*file << "\n";
			return;
		}
		else if (lex.table[position + 1].lexema == LEX_COMMA)
		{
			return;
		}
	}

	void Expression(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		int sourceposition = 0;
		//PolishNotation::PolishNotation(++position, lex, idt);
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_EQUAL:
				sourceposition = position - 1;
				TAB(tab);
				*file << OPERAND_NAME(sourceposition) << " = ";
				break;
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					Call(lex, idt, file, position);
				}
				else
				{
					if (lex.table[position + 1].lexema == LEX_EQUAL)
					{
						TAB(tab);
						*file << OPERAND_NAME(position) << " = ";
						position += 1;
					}
					else
					{
						*file << OPERAND_NAME(position) << " ";
					}
				}
				break;
			case LEX_LITERAL:
				OPERAND_VALUE(position);
				break;
			case LEX_OPERATION:
				OPERATION(position);
				break;
			case LEX_SEMICOLON:
				*file << "\n";
				return;
			}
		}
	}

	void Condition(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_IF:
				TAB(tab);
				*file << "if";
				break;
			case LEX_ELIF:
				TAB(tab);
				*file << "elif";
				break;
			case LEX_ELSE:
				TAB(tab);
				*file << "else";
				break;
			case LEX_LEFTHESIS:
				*file << " ";
				break;
			case LEX_ID:
				*file << OPERAND_NAME(position);
				break;
			case LEX_OPERATION:
				OPERATION(position);
				break;
			case LEX_LITERAL:
				OPERAND_VALUE(position);
				break;
			case LEX_RIGHTHESIS:
				break;
			case LEX_LEFTBRACE:
				*file << ":\n";
				tab++;
				WithinFunction(lex, idt, file, position);
				tab--;
				if (lex.table[position + 1].lexema != LEX_ELIF && lex.table[position + 1].lexema != LEX_ELSE)
				{
					return;
				}
				break;
			}
		}
	}

	void Print(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_PRINT:
				TAB(tab)
				*file << "print ";
				break;
			case LEX_LEFTHESIS:
				*file << LEX_LEFTHESIS;
				break;
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					Call(lex, idt, file, position);
				}
				else
				{
					*file << OPERAND_NAME(position);
				}
				break;
			case LEX_OPERATION:
				OPERATION(position);
				break;
			case LEX_LITERAL:
				OPERAND_VALUE(position);
				break;
			case LEX_RIGHTHESIS:
				*file << LEX_RIGHTHESIS;
				break;
			case LEX_SEMICOLON:
				*file << "\n";
				position--;
				return;
			}
		}
	}

	void Return(LT::LexTable& lex, IT::IdTable& idt, std::wofstream* file, int& position)
	{
		for (position; ; position++)
		{
			switch (lex.table[position].lexema)
			{
			case LEX_RETURN:
				TAB(tab)
				*file << "return ";
				break;
			case LEX_LEFTHESIS:
				*file << LEX_LEFTHESIS;
				break;
			case LEX_ID:
				if (OPERAND_TYPE(position) == IT::F)
				{
					Call(lex, idt, file, position);
				}
				else
				{
					*file << OPERAND_NAME(position);
				}
				break;
			case LEX_OPERATION:
				OPERATION(position);
				break;
			case LEX_LITERAL:
				OPERAND_VALUE(position);
				break;
			case LEX_RIGHTHESIS:
				*file << LEX_RIGHTHESIS;
				break;
			case LEX_SEMICOLON:
				*file << "\n";
				position--;
				return;
			}
		}
	}

}