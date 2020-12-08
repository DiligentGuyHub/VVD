#include "Code Generation.h"
#include "PolishNotation.h"


namespace Generation
{
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
						*file << MASM_VARIABLE_STR(idt.table[i].id) << idt.table[i].value.vstr.str << ", 0\n";
						break;
					case IT::SIGN:
						*file << MASM_VARIABLE_SIGN(idt.table[i].id) << idt.table[i].value.vsign << ", 0\n";
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
			*file << "\tmov\tal, BOOL" << boolliteral++ << "\n";
			break;
		case IT::STR:
			*file << MASM_PUSH_OFFSET_ << "STR" << strliteral++ << "\n";
			break;
		case IT::SIGN:
			*file << "\tmov\tal, SIGN" << signliteral++ << "\n";
			break;
		default:
			break;
		}
		return;
	}

	void ValuePush(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& position)
	{
		*file << MASM_PUSH(idt.table[lex.table[position].idxTI].id);
		return;
	}

	void WithinFunctionGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file, int& position, int& boolliteral, int& intliteral, int& pintliteral, int& strliteral, int& signliteral)
	{
		for (position; lex.table[position].lexema != LEX_BRACELET; position++)
		{
			int sourceposition = 0;
			switch (lex.table[position].lexema)
			{
			case LEX_EQUAL:
				sourceposition = position - 1; // позиция идентификатора, которому присваивается значение
				PolishNotation::PolishNotation(++position, lex, idt);
				LT::LexTableOut(lex);
				for (position; lex.table[position].lexema != LEX_SEMICOLON; position++)
				{
					switch (lex.table[position].lexema)
					{
					case LEX_ID:
						ValuePush(lex, idt, file, position);
						break;
					case LEX_LITERAL:
						ValuePush(lex, idt, file, position, boolliteral, intliteral, pintliteral, strliteral, signliteral);
						break;
					case LEX_OPERATION:
						switch (lex.table[position].operation)
						{
						case '+':
							*file << MASM_ADD;
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

							break;
						case '<':

							break;
						case '1':

							break;
						case '2':

							break;
						case '=':

							break;
						case '!':

							break;
						}
					default:
						break;
					}
				}
				*file << MASM_MOV;
				break;
			case LEX_IF:
				break;
			case LEX_PRINT:
				// выражение
				if (++position == LEX_LEFTHESIS)
				{

				}
				// одиночное значение
				else
				{
					if (lex.table[position].lexema == LEX_LITERAL)
					{

					}
					else if (lex.table[position].lexema == LEX_ID)
					{
						switch (idt.table[lex.table[position].idxTI].iddatatype)
						{
						case IT::INT:
							*file << MASM_PRINT_INT;
							break;
						case IT::PINT:
							*file;
							break;
						case IT::BOOL:
							*file;
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

	void ExpressionGeneration(LT::LexTable& lex, IT::IdTable& idt, std::ofstream* file)
	{

		for (int i = 0; lex.table[i].lexema != LEX_SEMICOLON; i++)
		{
			
		}

	}
}