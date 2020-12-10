#define _CRT_SECURE_NO_WARNINGS
#include "Lexical Analysis.h"
#include <math.h>

namespace LT
{
	IT::IDDATATYPE previousDataType = IT::NONE;
	IT::IDTYPE previousType = IT::V;
	LT::OPERATIONTYPE optype;
	bool withinIf = false;
	bool withinElse = false;

	bool withinCall = false;

	bool mainDefined = false;
	bool typeDefined = false;

	int boolliteral = 0;
	int intliteral = 0;
	int pintliteral = 0;
	int strliteral = 0;
	int signliteral = 0;

	char function[10][10];
	int index = -1;

	char stdlib[5][8]{ "StrLen", "StrInt", "IntStr", "PintStr", "SignInt" };

	void LexEntryFill(LT::Entry &lex_entry, int line, char lexema, int idxTi, char operation, OPERATIONTYPE operationtype)
	{
		lex_entry.lexema = lexema;
		lex_entry.idxTI = idxTi;
		lex_entry.sn = line;
		lex_entry.operation = operation;
		lex_entry.operationtype = operationtype;
		return;
	}

	void LexEntryFill(LT::Entry &lex_entry, int line, char lexema, int idxTi)
	{
		lex_entry.lexema = lexema;
		lex_entry.idxTI = idxTi;
		lex_entry.sn = line;
		return;
	}


	LexTable& CreateEntry(LexTable& lex, IT::IdTable& idt, char* buffer, int line, int id)
	{
		

		LT::Entry lex_entry;
		IT::Entry id_entry;
		switch (buffer[0])
		{

		case 'i':
		{
			FST::FST fst(INT(buffer));
			if (FST::execute(fst, line))
			{
				previousDataType = IT::INT;
				typeDefined = !typeDefined;
				LexEntryFill(lex_entry, line, LEX_INT, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(IF(buffer));
			if (FST::execute(fst1, line))
			{
				withinIf = true;
				LexEntryFill(lex_entry, line, LEX_IF, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 's':
		{
			FST::FST fst(SIGN(buffer));
			if (FST::execute(fst, line))
			{
				previousDataType = IT::SIGN;
				typeDefined = !typeDefined;
				LexEntryFill(lex_entry, line, LEX_SIGN, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(STRING(buffer));
			if (FST::execute(fst1, line))
			{
				previousDataType = IT::STR;
				typeDefined = !typeDefined;
				LexEntryFill(lex_entry, line, LEX_STRING, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 'p':
		{
			FST::FST fst(PINT(buffer));
			if (FST::execute(fst, line))
			{
				previousDataType = IT::PINT;
				typeDefined = !typeDefined;
				LexEntryFill(lex_entry, line, LEX_PINT, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(PRINT(buffer));
			if (FST::execute(fst1, line))
			{
				LexEntryFill(lex_entry, line, LEX_PRINT, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 'b':
		{
			FST::FST fst(BOOL(buffer));
			if (FST::execute(fst, line))
			{
				previousDataType = IT::BOOL;
				typeDefined = !typeDefined;
				LexEntryFill(lex_entry, line, LEX_BOOL, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case 'e':
		{
			FST::FST fst(ELIF(buffer));
			if (FST::execute(fst, line))
			{
				withinIf = true;
				LexEntryFill(lex_entry, line, LEX_ELIF, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(ELSE(buffer));
			if (FST::execute(fst1, line))
			{
				withinElse = true;
				LexEntryFill(lex_entry, line, LEX_ELSE, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 'd':
		{
			FST::FST fst(DEF(buffer));
			if (FST::execute(fst, line))
			{
				previousType = IT::V;
				LexEntryFill(lex_entry, line, LEX_DEF, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 'f':
		{
			FST::FST fst(FUNCTION(buffer));
			if (FST::execute(fst, line))
			{
				//withinFunction = true;
				previousType = IT::F;
				index += 1;
				LexEntryFill(lex_entry, line, LEX_FUNCTION, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case 'm':
		{
			FST::FST fst(MAIN(buffer));
			if (FST::execute(fst, line))
			{
				if (mainDefined == false)
				{
					previousType = IT::F;
					index += 1;
					strcpy_s(function[index], "main");
					LexEntryFill(lex_entry, line, LEX_MAIN, LT_TI_NULLIDX);
					Add(lex, lex_entry);
					mainDefined = true;
					return lex;
				}
				else
				{
					throw ERROR_THROW(104);
				}
			}
			break;
		}
		case 'r':
		{
			FST::FST fst(RETURN(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_RETURN, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '>':
		{
			FST::FST fst(MORE(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_MORE, LT_TI_NULLIDX, '>', LT::L);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(EQMORE(buffer));
			if (FST::execute(fst1, line))
			{
				LexEntryFill(lex_entry, line, LEX_EQMORE, LT_TI_NULLIDX, '1', LT::L);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '<':
		{
			FST::FST fst(LESS(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_LESS, LT_TI_NULLIDX, '<', LT::L);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(EQLESS(buffer));
			if (FST::execute(fst1, line))
			{
				LexEntryFill(lex_entry, line, LEX_EQLESS, LT_TI_NULLIDX, '2', LT::L);
				Add(lex, lex_entry);
				return lex;
			}
			break;

			break;
		}
		case '(':
		{
			FST::FST fst(LEFTHESIS(buffer));
			if (FST::execute(fst, line))
			{
				if (previousType == IT::F) previousType = IT::P;
				typeDefined = false;
				LexEntryFill(lex_entry, line, LEX_LEFTHESIS, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case ')':
		{
			FST::FST fst(RIGHTHESIS(buffer));
			if (FST::execute(fst, line))
			{
				typeDefined = false;
				if (previousType == IT::P) previousType = IT::V;
				else if (previousType == IT::F)
				{
					*function[index] = *(ClearChar(function[index]));
					index -= 1;
					previousType = IT::V;
				}
				LexEntryFill(lex_entry, line, LEX_RIGHTHESIS, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '{':
		{
			FST::FST fst(LEFTBRACE(buffer));
			if (FST::execute(fst, line))
			{
				typeDefined = false;
				LexEntryFill(lex_entry, line, LEX_LEFTBRACE, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '}':
		{
			FST::FST fst(BRACELET(buffer));
			if (FST::execute(fst, line))
			{
				if (!withinIf && !withinElse)
				{
					*function[index] = *(ClearChar(function[index]));
					index -= 1;
				}
				typeDefined = false;
				LexEntryFill(lex_entry, line, LEX_BRACELET, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case ';':
		{
			FST::FST fst(SEMICOLON(buffer));
			if (FST::execute(fst, line))
			{
				// если это был вызов функции, то он завершается
				if (withinCall)
				{
					withinCall = !withinCall;
				}
				typeDefined = false;
				previousDataType = IT::NONE;
				LexEntryFill(lex_entry, line, LEX_SEMICOLON, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case ',':
		{
			FST::FST fst(COMMA(buffer));
			if (FST::execute(fst, line))
			{
				typeDefined = false;
				LexEntryFill(lex_entry, line, LEX_COMMA, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;

			}
			break;
		}
		case 'T':
		{
			FST::FST fst(TRUE(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::BOOL;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				strcpy_s(id_entry.value.vbool.str, buffer);
				id_entry.value.vbool.value = 1;
				strcpy_s(id_entry.id, "BOOL");
				strcat(id_entry.id, IntegerToString(++boolliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;

			}
			break;
		}
		case 'F':
		{
			FST::FST fst(FALSE(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::BOOL;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				strcpy_s(id_entry.value.vbool.str, buffer);
				id_entry.value.vbool.value = 0;
				strcpy_s(id_entry.id, "BOOL");
				strcat(id_entry.id, IntegerToString(++boolliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;

			}
			break;
		}
		case '"':
		{
			FST::FST fst1(SIGN_LITERAL(buffer));
			if (FST::execute(fst1, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::SIGN;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vsign = buffer[1];
				strcpy_s(id_entry.id, "SIGN");
				strcat(id_entry.id, IntegerToString(++signliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;

			}
			FST::FST fst2(STR_LITERAL(buffer));
			if (FST::execute(fst2, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::STR;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vstr.len = strlen(buffer) - 2;
				strcpy_s(id_entry.value.vstr.str, DeleteFirstAndLast(buffer, id_entry.value.vstr.len + 2));
				strcpy_s(id_entry.id, "STR");
				strcat(id_entry.id, IntegerToString(++strliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;

			}
			break;
		}
		case '+':
		{
			FST::FST fst(OP(buffer));
			if (FST::execute(fst, line)) 
			{
				LexEntryFill(lex_entry, line, LEX_PLUS, LT_TI_NULLIDX, '+', LT::A);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '-':
		{
			FST::FST fst(OP(buffer));
			if (FST::execute(fst, line)) 
			{
				LexEntryFill(lex_entry, line, LEX_MINUS, LT_TI_NULLIDX, '-', LT::A);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST nfst(NEG_NUMBER10(buffer));
			if (FST::execute(nfst, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = atoi(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst2(NEG_NUMBER2(buffer));
			if (FST::execute(fst2, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = ConvertToDecimal(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst8(NEG_NUMBER8(buffer));
			if (FST::execute(fst8, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = ConvertToDecimal(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '*':
		{
			FST::FST fst(OP(buffer));
			if (FST::execute(fst, line)) 
			{
				LexEntryFill(lex_entry, line, LEX_STAR, LT_TI_NULLIDX, '*', LT::A);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '/':
		{
			FST::FST fst(OP(buffer));
			if (FST::execute(fst, line)) 
			{
				LexEntryFill(lex_entry, line, LEX_DIRSLASH, LT_TI_NULLIDX, '/', LT::A);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '=':
		{
			FST::FST fst(EQ(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_EQUAL, LT_TI_NULLIDX);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst1(EQUALS(buffer));
			if (FST::execute(fst1, line))
			{
				LexEntryFill(lex_entry, line, LEX_EQUALS, LT_TI_NULLIDX, '=', LT::L);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '!':
		{
			FST::FST fst(NEQUALS(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_NEQUALS, LT_TI_NULLIDX, '!', LT::L);
				Add(lex, lex_entry);
				return lex;
			}
			break;
		}
		case '~':
		{
			FST::FST fst(INVERSION(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_INVERSION, LT_TI_NULLIDX, '~', LT::B);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '&':
		{
			FST::FST fst(CONJUCTION(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_CONJUCTION, LT_TI_NULLIDX, '&', LT::B);
				Add(lex, lex_entry);
				return lex;
			}
		}
		case '\\':
		{
			FST::FST fst(DISJUNCTION(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_DISJUNCTION, LT_TI_NULLIDX, '\\', LT::B);
				Add(lex, lex_entry);
				return lex;
			}
		}
		default:
		{
			FST::FST fst(NUMBER10(buffer));
			if (FST::execute(fst, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = atoi(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}

			FST::FST fst2(NUMBER2(buffer));
			if (FST::execute(fst2, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = ConvertToDecimal(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}
			FST::FST fst8(NUMBER8(buffer));
			if (FST::execute(fst8, line))
			{
				LexEntryFill(lex_entry, line, LEX_LITERAL, idt.size);
				strcpy_s(id_entry.function, function[index]);
				id_entry.index = index;
				id_entry.iddatatype = IT::INT;
				id_entry.idtype = IT::L;
				id_entry.idxfirstLE = lex.size - 1;
				id_entry.value.vint = ConvertToDecimal(buffer);
				strcpy_s(id_entry.id, "INT");
				strcat(id_entry.id, IntegerToString(++intliteral));
				Add(lex, idt, id_entry, line, id);
				Add(lex, lex_entry);
				return lex;
			}

		}
		}

		FST::FST fst(ID(buffer));
		if (FST::execute(fst, line))
		{
			for (int i = 0; i < 5; i++)
			{
				if (!strcmp(buffer, stdlib[i]))
				{
					LexEntryFill(lex_entry, line, LEX_ID, idt.size);
					strcpy_s(id_entry.id, buffer);
					strcpy_s(id_entry.function, "stdlib");
					id_entry.idxfirstLE = lex.size - 1;
					id_entry.index = index;
					if (i == 0 || i == 1 || i == 4)
					{
						id_entry.iddatatype = IT::INT;
					}
					else {
						id_entry.iddatatype = IT::STR;
					}
					id_entry.idtype = IT::F;
					idt.table[idt.size++] = id_entry;
					Add(lex, lex_entry);
					return lex;
				}
			}
			LexEntryFill(lex_entry, line, LEX_ID, idt.size);

			strcpy_s(id_entry.id, buffer);
			strcpy_s(id_entry.function, "global");
			id_entry.idxfirstLE = lex.size - 1;
			id_entry.index = index;
			id_entry.iddatatype = previousDataType;

			switch (previousType)
			{
			case IT::V:
				id_entry.idtype = IT::V;
				if (id_entry.iddatatype == IT::INT)
				{
					id_entry.value.vint = 0;
				}
				else if (id_entry.iddatatype == IT::PINT)
				{
					id_entry.value.vpint = 0;
				}
				else if (id_entry.iddatatype == IT::STR) {
					strcpy_s(id_entry.value.vstr.str, "\0");
				}
				else if (id_entry.iddatatype == IT::SIGN)
				{
					id_entry.value.vsign = '\0';
				}
				else if (id_entry.iddatatype == IT::BOOL)
				{
					strcpy_s(id_entry.value.vbool.str, "False");
					id_entry.value.vbool.value = 0;
				}
				strcpy_s(id_entry.function, function[index]);
				break;
			case IT::F:
				strcpy_s(function[index], buffer);
				id_entry.idtype = IT::F;
				break;
			case IT::P:
				id_entry.idtype = IT::P;
				if (id_entry.iddatatype == IT::INT) id_entry.value.vint = 0;
				else if (id_entry.iddatatype == IT::STR) strcpy_s(id_entry.value.vstr.str, "\0");
				strcpy_s(id_entry.function, function[index]);
				break;
			}
			previousDataType = IT::NONE;
			Add(lex, idt, id_entry, line, id, withinCall);

			if (IT::IsId(idt, buffer, function[index]) != 0xffffffff)
				lex_entry.idxTI = IT::IsId(idt, buffer, function[index]);
			else
				lex_entry.idxTI = idt.size - 1;

			Add(lex, lex_entry);
			return lex;
		}

		if (buffer[0] != '\0') {
			std::cout << "\n----------------------------------------------------------\n";
			std::cout << "\nОшибка разбора цепочки ";
			for (int i = 0; buffer[i] != '\0'; i++) std::cout << buffer[i];
			std::cout << " зафиксирована:\nСтрока: " << line << " Позиция: " << id << std::endl;
		}
		return lex;
	}

	void LexTableFill(LexTable& lex, LexTable& lexcopy, In::IN input, IT::IdTable& idt)
	{
		char* buffer = new char[LEXEMA_MAXSIZE] {};
		bool readExtraSimbols = false;
		LT::Entry en;
		for (int i = 0, bufferIndex = 0, lexCounter = 0, lineCounter = 1; input.text[i - 1] != '\0'; i++)
		{
			if (input.text[i] == '"')
			{
				readExtraSimbols = !readExtraSimbols;
				buffer[bufferIndex] = input.text[i];
				bufferIndex++;
			}
			else if (input.text[i] == '\0')
			{
				bufferIndex = 0;
				*buffer = *(ClearChar(buffer));
				break;
			}
			else if (input.text[i] == '-' && buffer[0] == '\0' &&(\
				lex.table[lex.size - 1].lexema == 'r' || lex.table[lex.size - 1].lexema == '='	||\
				lex.table[lex.size - 1].lexema == ':' || lex.table[lex.size - 1].lexema == '('	||\
				lex.table[lex.size - 1].lexema == '?' || lex.table[lex.size - 1].lexema == 'z'	  \
				))
			{
				buffer[bufferIndex] = input.text[i++];
				bufferIndex++;
				// после унарного минуса помещаем в буфер все цифры числа
				while (48 <= int(input.text[i]) && int(input.text[i]) <= 57 || input.text[i] == '.')
				{
					buffer[bufferIndex] = input.text[i++];
					bufferIndex++;
				}
				// отправляем отрицательное число на проверку регулярного выражения
				lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
				*buffer = *(ClearChar(buffer));
				lexCounter++;
				bufferIndex = 0;
				// передадим в буфер следующий за числом символ, ; + - * / и т.д.
				buffer[bufferIndex] = input.text[i];
				lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
				*buffer = *(ClearChar(buffer));
				lexCounter++;
				bufferIndex = 0;

			}
			else if (input.text[i] != ' ' && input.text[i] != '|')
			{

				if ((input.text[i] == '(' || input.text[i] == ')' || \
					input.text[i] == '{' || input.text[i] == '}' || \
					input.text[i] == ',' || input.text[i] == ';' || \
					input.text[i] == '=' || input.text[i] == '+' || \
					input.text[i] == '-' || input.text[i] == '*' || \
					input.text[i] == '/' || input.text[i] == '!' || \
					input.text[i] == '>' || input.text[i] == '<' || \
					input.text[i] == '&' || input.text[i] == '\\' ||\
					input.text[i] == '~') && !readExtraSimbols) \
				{
					// сначала проверим то, что уже было занесено в буфер
					bufferIndex = 0;
					lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
					*buffer = *(ClearChar(buffer));
					lexCounter++;
					// затем передадим в чистый буфер символ и отправим на проверку

					if ((input.text[i] == '=' || input.text[i] == '!' || input.text[i] == '>' || input.text[i] == '<') && input.text[i + 1] == '=')
					{
						buffer[bufferIndex++] = input.text[i++];
					}

					buffer[bufferIndex] = input.text[i];
					bufferIndex = 0;
					lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
					lexCounter++;
					*buffer = *(ClearChar(buffer));
				}
				else
				{
					buffer[bufferIndex] = input.text[i];
					bufferIndex++;
				}
			}
			else if (input.text[i] == '|')
			{
				bufferIndex = 0;
				lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
				lexCounter++;
				*buffer = *(ClearChar(buffer));

				lineCounter++;
			}
			else
			{
				if (readExtraSimbols == false)
				{
					bufferIndex = 0;
					lex = LT::CreateEntry(lex, idt, buffer, lineCounter, lexCounter);
					lexCounter++;
					*buffer = *(ClearChar(buffer));
				}
				else
				{
					buffer[bufferIndex] = input.text[i];
					bufferIndex++;
				}
			}
		}
		if (!mainDefined) throw ERROR_THROW(105);
		lexcopy = lex;
		return;
	}
	
	void LexTableOut(LexTable lex)
	{
#ifdef LEX_TABLE_OUT
		std::cout << "\n00" << lex.table[0].sn << ' ';
		int previousLine = 1;
		for (int i = 0; i < lex.size; i++)
		{
			if (previousLine != lex.table[i].sn)
			{
				std::cout << std::endl;
				std::cout << std::setw(3) << std::right << std::setfill('0');
				std::cout << lex.table[i].sn << ' ';
			}
			if (lex.table[i].lexema == 'v')
				std::cout << lex.table[i].operation;
			else
				std::cout << lex.table[i].lexema;
			/*if (lex.table[i].idxTI >= 0 && lex.table[i].idxTI < 100)
				cout << "[" << lex.table[i].idxTI << "]";*/
			if (lex.table[i].lexema == '@')
				std::cout << "[" << lex.table[i].idxTI << "]";
			previousLine = lex.table[i].sn;
		}
#endif
		return;
	}

	void LexicalAnalysisStatistics(uint start, uint finish)
	{
		std::cout << "\nЛексический анализ завершен успешно";
		std::cout << "\nВремя выполнения: " << finish - start << " мс\n";
	}

	char* ClearChar(char* buffer)
	{
		for (int i = 0; buffer[i] != '\0'; i++)
		{
			buffer[i] = '\0';
		}
		return buffer;
	}

	int LengthOfChar(char* buffer)
	{
		int i = 0;
		while (buffer[i] != '\0')
		{
			i++;
		}
		// кавычки не входят в длину строки
		return i - 2;
	}

	char* DeleteFirstAndLast(char* buffer, int size)
	{
		char* result = new char[size]{};
		int i, j;
		for (i = 0, j = 0; buffer[i + 1] != '\0'; i++)
		{
			if(i != 0)
			{
				result[j++] = buffer[i];
			}
			
		}
		return result;
	}

	char* IntegerToString(int num)
	{
		char result[255] = "";
		_itoa_s(num, result, 10);
		return result;
	}

	int ConvertToDecimal(char* buffer)
	{	
		// ... + int(buffer[0] == '-' на случай, если число отрицательное
		// тогда логическое выражение вернет единицу и она добавится ко всем индексам
		int radix = buffer[0 + int(buffer[0] == '-')] - '0';
		int counter = 0;
		int result = 0;
		for (int i = 2 + int(buffer[0] == '-'); buffer[i] != '\0'; i++)
		{
			counter++;
		}
		for (int i = 2 + int(buffer[0] == '-'); buffer[i] != '\0'; i++)
		{
			result += (buffer[i] - '0') * pow(radix, --counter);
		}
		
		return (buffer[0] == '-') ? -result : result;
	}
}