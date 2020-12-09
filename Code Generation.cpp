#include "Code Generation.h"
#include "PolishNotation.h"


namespace Generation
{
	int truecounter = 0;
	int continuecounter = 0;

	void CodeGeneration(LT::LexTable& lex, IT::IdTable& idt, char* filename)
	{
		std::ofstream* file = new std::ofstream();
		file->open(filename);
		if (!file->is_open())
		{
			throw ERROR_THROW(8);
		}
		*file << MASM_HEAD;
		*file << MASM_LIBS;
		*file << MASM_PROTO;
		*file << MASM_EXTERN;
		*file << MASM_STACK;
		LiteralGeneration(lex, idt, file);
		VariableGeneration(lex, idt, file);
		FunctionGeneration(lex, idt, file);
	}

	void LiteralGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream *file)
	{
		*file << MASM_CONST;

		// каждый литерал в секции констант будет иметь свой номер
		int boolliteral = 0;
		int intliteral = 0;
		int pintliteral = 0;
		int strliteral = 0;
		int signliteral = 0;

		for (int i = 0; i < idt.size; i++)
		{
			if (idt.table[i].idtype == IT::L)
			{
				switch (idt.table[i].iddatatype)
				{
					case IT::INT:
						*file << MASM_LITERAL_INT(++intliteral) << idt.table[i].value.vint << "\n";
						break;
					case IT::PINT:
						*file << MASM_LITERAL_PINT(++pintliteral) << idt.table[i].value.vpint << "\n";
						break;
					case IT::BOOL:
						*file << MASM_LITERAL_BOOL(++boolliteral) << idt.table[i].value.vbool.value << "\n";
						break;
					case IT::STR:
						*file << MASM_LITERAL_STR(++strliteral) << "\"" << idt.table[i].value.vstr.str << "\", 0\n";
						break;
					case IT::SIGN:
						*file << MASM_LITERAL_SIGN(++signliteral) << "\"" << idt.table[i].value.vsign << "\", 0\n";
						break;
					default:
						throw ERROR_THROW(9);
						break;
				}
			}
		}
	}

	void VariableGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file)
	{
		*file << MASM_DATA;
		for (int i = 0; i < idt.size; i++)
		{
			if (idt.table[i].idtype == IT::V)
			{
				*file << idt.table[i].function << "_";
				switch (idt.table[i].iddatatype)
				{
					case IT::INT:
						*file << MASM_VARIABLE_INT(idt.table[i].id) << idt.table[i].value.vint << "\n";
						break; 
					case IT::PINT:
						*file << MASM_VARIABLE_PINT(idt.table[i].id) << idt.table[i].value.vpint << "\n";
						break;
					case IT::BOOL:
						*file << MASM_VARIABLE_BOOL(idt.table[i].id) << idt.table[i].value.vbool.value << "\n";
						break;
					case IT::STR:
						*file << MASM_VARIABLE_STR(idt.table[i].id) << "?\n";
						break;
					case IT::SIGN:
						*file << MASM_VARIABLE_SIGN(idt.table[i].id) <<"\"" << idt.table[i].value.vsign << "\", 0\n";
						break;
					default:
						throw ERROR_THROW(9);
						break;	
				}
			}
		}
	}

	void FunctionGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file)
	{
		*file << MASM_CODE;
		char* buffer;
		int boolliteral = 1;
		int intliteral = 1;
		int pintliteral = 1;
		int strliteral = 1;
		int signliteral = 1;
		for (int i = 0; i < lex.size; i++)
		{
			switch (lex.table[i].lexema)
			{
				case LEX_MAIN:
					*file << MASM_MAIN;
					WithinFunctionGeneration(lex, idt, file, i, boolliteral, intliteral, pintliteral, strliteral, signliteral);
					*file << MASM_END;
					break;
				case LEX_FUNCTION:
					if (lex.table[i + 2].idxTI == LT_TI_NULLIDX)
					{
						break;
					}
					buffer = idt.table[lex.table[++(++i)].idxTI].id;
					*file << MASM_PROC(buffer);
					for (++i; lex.table[i].lexema != LEX_LEFTBRACE; i++)
					{
 						switch (lex.table[i].lexema)
						{
							case LEX_COMMA:
								*file << LEX_COMMA << " ";
								break;
							case LEX_ID:
								*file << " " << idt.table[lex.table[i].idxTI].function << "_" << idt.table[lex.table[i].idxTI].id << " : ";
								switch (idt.table[i].iddatatype)
								{
									case IT::INT:
										*file << "SDWORD";
										break;
									case IT::PINT:
										*file << "DWORD";
										break;
									case IT::BOOL:
										*file << "BYTE";
										break;
									case IT::STR:
										*file << "BYTE";
									case IT::SIGN:
										*file << "BYTE";
									default:
										break;
								}
								break;
							default:
								break;
						}
					}
					*file << "\n";
					WithinFunctionGeneration(lex, idt, file, i, boolliteral, intliteral, pintliteral, strliteral, signliteral);
					*file << MASM_RETURN;
					*file << MASM_END_PROC(buffer);
					break;
				default:
					break;
			}
		}
	}

	void ValuePush(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& pos, int& boolliteral, int& intliteral, int& pintliteral, int& strliteral, int& signliteral)
	{
		switch (idt.table[lex.table[pos].idxTI].iddatatype)
		{
		case IT::INT:
			*file << MASM_PUSH_ << "INT" << intliteral++ << "\n";
			break;
		case IT::PINT:
			*file << MASM_PUSH_ << "PINT" << pintliteral++ << "\n";
			break;
		case IT::BOOL:
			*file << "\tmov\tbl, BOOL" << boolliteral++ << "\n\tpush ebx\n";
			break;
		case IT::STR:
			*file << MASM_PUSH_OFFSET_ << "STR" << strliteral++ << "\n";
			break;
		case IT::SIGN:
			*file << MASM_PUSH_OFFSET_ << "SIGN" << signliteral++ << "\n";
			break;
		default:
			break;
		}
		return;
	}

	void ValuePush(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& position)
	{
		if (idt.table[lex.table[position].idxTI].iddatatype == IT::INT || idt.table[lex.table[position].idxTI].iddatatype == IT::PINT)
		{
			*file << MASM_PUSH(idt.table[lex.table[position].idxTI].id);
		}
		else if (idt.table[lex.table[position].idxTI].iddatatype == IT::BOOL)
		{
			*file << "\tmov bl, " << MASM_VARIABLE(position) << "\n";
			*file << "\tpush ebx\n";
		}
		else if (idt.table[lex.table[position].idxTI].iddatatype == IT::STR)
		{

		}
		return;
	}

	void WithinFunctionGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& position, int& boolliteral, int& intliteral, int& pintliteral, int& strliteral, int& signliteral)
	{
		for (position; lex.table[position].lexema != LEX_BRACELET; position++)
		{
			int sourceposition = 0;
			switch (lex.table[position].lexema)
			{
			// для присваивания значений выражений
			case LEX_EQUAL:
				ExpressionGeneration(lex, idt, file, position, sourceposition, boolliteral, intliteral, pintliteral, strliteral, signliteral);
				break;
			case LEX_IF:

				break;
			case LEX_PRINT:
				if (lex.table[position + 1].lexema == LEX_LEFTHESIS)
				{
					PolishNotation::PolishNotation(++position, lex, idt);
					LT::LexTableOut(lex);
					IT::IDDATATYPE prev = IT::NONE;
					for (position; lex.table[position].lexema != LEX_SEMICOLON; position++)
					{
						// преверяем каждую лексему
						switch (lex.table[position].lexema)
						{
						// идентификатор помещает в стек для дальнейших действий
						case LEX_ID:
							prev = idt.table[lex.table[position].idxTI].iddatatype;
							ValuePush(lex, idt, file, position);
							break;
						// литерал помещаем в стек для дальнейших действий
						case LEX_LITERAL:
							prev = idt.table[lex.table[position].idxTI].iddatatype;
							ValuePush(lex, idt, file, position, boolliteral, intliteral, pintliteral, strliteral, signliteral);
							break;
						case LEX_OPERATION:
							switch (lex.table[position].operation)
							{
							case '+':
								// для целочисленных операндов
								if (prev == IT::INT || prev == IT::PINT)
								{
									*file << MASM_ADD;
								}
								// для строковых и символьных операндов
								else
								{
									*file << MASM_CONCAT;
								}
								break;
							case '-':
								*file << MASM_SUB;
								break;
							case '*':
								*file << MASM_MUL;
								break;
							case '/':
								*file << MASM_SUB;
								break;
							case '&':
								*file << MASM_AND;
								break;
							case '\\':
								*file << MASM_OR;
								break;
							case '>':
								*file << MASM_JA(sourceposition);
								break;
							case '<':
								*file << MASM_JB(sourceposition);
								break;
							case '1':
								*file << MASM_JAE(sourceposition);
								break;
							case '2':
								*file << MASM_JBE(sourceposition);
								break;
							case '=':
								*file << MASM_JE(sourceposition);
								break;
							case '!':
								*file << MASM_JNE(sourceposition);
								break;
							}
						default:
							break;
						}
					}
					switch (prev)
					{
					case IT::INT:
						*file << MASM_PRINT_INT;
						break;
					case IT::PINT:
						*file << MASM_PRINT_PINT;
						break;
					case IT::BOOL:
						*file << "\n\tmov bl, " << MASM_VARIABLE(position) << "\n\tpush ebx\n";
						*file << MASM_PRINT_BOOL;
						break;
					case IT::STR:
						*file << "\tpush eax\n\tinvoke WriteConsoleA, consoleHandle, eax, sizeof eax, 0, 0\n";
						break;
					case IT::SIGN:
						*file << "\tpush eax\n\tinvoke WriteConsoleA, consoleHandle, eax, sizeof eax, 1, 0\n";
						break;
					}
				}
				// одиночное значение
				else
				{
					if (lex.table[++position].lexema == LEX_LITERAL)
					{
						switch (idt.table[lex.table[position].idxTI].iddatatype)
						{
						case IT::INT:
							ValuePush(lex, idt, file, position, boolliteral, intliteral, pintliteral, strliteral, signliteral);
							*file << MASM_PRINT_INT;
							break;
						case IT::PINT:
							ValuePush(lex, idt, file, position, boolliteral, intliteral, pintliteral, strliteral, signliteral);
							*file << MASM_PRINT_PINT;
							break;
						case IT::BOOL:
							*file << "\n\tmov bl, " << MASM_LITERAL("BOOL", boolliteral) << "\n\tpush ebx\n";
							*file << MASM_PRINT_BOOL;
							break;
						case IT::STR:
							*file << "\n\tmov eax, offset " << MASM_LITERAL("STR", strliteral) << "\n";
							*file << MASM_PRINT_STR(MASM_LITERAL("STR", strliteral));
							break;
						case IT::SIGN:
							*file << "\n\tmov eax, offset " << MASM_LITERAL("SIGN", signliteral) << "\n";
							*file << MASM_PRINT_SIGN(MASM_LITERAL("SIGN", signliteral));
							break;
						}
					}
					else if (lex.table[position].lexema == LEX_ID)
					{
						switch (idt.table[lex.table[position].idxTI].iddatatype)
						{
						case IT::INT:
							ValuePush(lex, idt, file, position);
							*file << MASM_PRINT_INT;
							break;
						case IT::PINT:
							ValuePush(lex, idt, file, position);
							*file << MASM_PRINT_PINT;
							break;
						case IT::BOOL:
							*file << "\n\tmov bl, " << MASM_VARIABLE(position) << "\n\tpush ebx\n";
							*file << MASM_PRINT_BOOL;
							break;
						case IT::STR:
							*file;
							break;
						case IT::SIGN:
							*file;
							break;
						}
					}
					break;
			case LEX_RETURN:
				break;
			default:
				break;
				}

			}
		}
	}

	void ExpressionGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& position, int& sourceposition, int& boolliteral, int& intliteral, int& pintliteral, int& strliteral, int& signliteral)
	{
		sourceposition = position - 1;
		PolishNotation::PolishNotation(++position, lex, idt);
		LT::LexTableOut(lex);
		for (position; lex.table[position].lexema != LEX_SEMICOLON; position++)
		{
			switch (lex.table[position].lexema)
			{
				// идентификатор помещается в стек для дальнейших действий
			case LEX_ID:
				ValuePush(lex, idt, file, position);
				break;
				// литерал помещается в стек для дальнейших действий
			case LEX_LITERAL:
				ValuePush(lex, idt, file, position, boolliteral, intliteral, pintliteral, strliteral, signliteral);
				break;
			case LEX_OPERATION:
				switch (lex.table[position].operation)
				{
				case '+':
					// сумма целочисленных значений
					if (idt.table[lex.table[sourceposition].idxTI].iddatatype == IT::INT || idt.table[lex.table[sourceposition].idxTI].iddatatype == IT::PINT)
					{
						*file << MASM_ADD;
					}
					// конкатенация строковых и символьных значений
					else
					{
						*file << MASM_CONCAT;
					}
					break;
				case '-':
					*file << MASM_SUB;
					break;
				case '*':
					*file << MASM_MUL;
					break;
				case '/':
					*file << MASM_SUB;
					break;
				case '&':
					*file << MASM_AND;
					break;
				case '\\':
					*file << MASM_OR;
					break;
				case '>':
					*file << MASM_JA(sourceposition);
					break;
				case '<':
					*file << MASM_JB(sourceposition);
					break;
				case '1':
					*file << MASM_JAE(sourceposition);
					break;
				case '2':
					*file << MASM_JBE(sourceposition);
					break;
				case '=':
					*file << MASM_JE(sourceposition);
					break;
				case '!':
					*file << MASM_JNE(sourceposition);
					break;
				}
			default:
				break;
			}
		}
		if (idt.table[lex.table[sourceposition].idxTI].iddatatype == IT::INT || idt.table[lex.table[sourceposition].idxTI].iddatatype == IT::PINT)
		{
			*file << MASM_MOV;
		}
		else if (idt.table[lex.table[sourceposition].idxTI].iddatatype == IT::BOOL && lex.table[sourceposition + 3].lexema == LEX_SEMICOLON)
		{
			*file << "\tmov " << MASM_VARIABLE(sourceposition) << ", bl\n";
		}
	}
}