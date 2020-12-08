#include "Semantic Analysis.h"
#include "IdTable.h"
#include "Error.h"
#include "PolishNotation.h"

namespace Semantic
{
	// Пошаговый анализ выражений, входящих в состав таблицы лексем
	void FindExpressions(LT::LEX& lex)
	{
		uint start_time = clock(), end_time;
		int begin = 0; // позиция итератора в начале каждой строки, для удобства вывода сообщений о позиции лексемы в строке
		for (int i = 0, lineCounter = 0; i < lex.lextable.size; i++)
		{
			// определение текущего номера строки
			if (lex.lextable.table[i].sn != lineCounter) 
			{
				begin = i;
				lineCounter = lex.lextable.table[i].sn;
				if (lineCounter == 7)
				{
					int a = 10;
				}
			}
			// если условная конструкция if/elif
			if (lex.lextable.table[i].lexema == '?' || lex.lextable.table[i].lexema == 'z')
			{
				CheckoutBooleanExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
			}
			// если объявление функции
			else if (lex.lextable.table[i].lexema == 'f')
			{
				while (lex.lextable.table[i].sn == lineCounter)
				{
					i++;
				}
			}
			// если идентификатор
			else if (lex.lextable.table[i].lexema == 'i')
			{
				switch (lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype)
				{
					case IT::INT:
						CheckoutIntegerExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
						break;
					case IT::PINT:
						CheckoutIntegerExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
						break;
					case IT::BOOL:
						CheckoutBooleanExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
						break;
					case IT::STR:
						CheckoutStringExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
						break;
					case IT::SIGN:
						CheckoutSignExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
						break;
					default:
						throw ERROR_THROW_IN(305, lineCounter, i - begin);
				}
			}
			else if (lex.lextable.table[i].lexema == 'p')
			{
				CheckoutPrint(lex.lextable, lex.idtable, begin, lineCounter, i);
			}
		}
		end_time = clock();
		std::cout << "\nСемантический анализ завершен успешно\nВремя выполнения: ";
		if (end_time - start_time == 0)
		{
			std::cout << "< 1 мс\n";
		}
		else
		{
			std::cout << end_time - start_time << " мс\n";
		}
		//PolishNotation::Checkout(lex.lextable, lex.idtable);
		return;
	}

	// Проверка выражений с целочисленными переменными (не логические)
	// допустимые типы: int, pint
	// допустимые операции: арифметические, битовые (один из двух)
	void CheckoutIntegerExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		LT::OPERATIONTYPE type = LT::UNDEF;

		for (int i = pos; ; i++)
		{
			// если лексема явялется операцией
			if (lex.table[i].operation != NULL)
			{
				// если тип операции не определен
				if (type == LT::UNDEF)
				{
					// логический тип операции вызывает ошибку, так как недопустим в пределах не булевых выражений
					if (lex.table[i].operationtype == LT::L)
					{
						throw ERROR_THROW_IN(313, line, i - begin);
					}
					// тип операции может быть определен как арифметический или битовый
					type = lex.table[i].operationtype;
				}
				// если же тип операции уже определен
				else if (type != LT::UNDEF)
				{
					// если он соответствует ранее определенному
					if (type == lex.table[i].operationtype)
					{
						continue;
					}
					// в противном случае ошибка
					throw ERROR_THROW_IN(311, line, i - begin); // Ошибка типа используемого выражения
				}
			}
			// если же лексема является идентификатором/литералом и не равна ни одному из целочисленных типов
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::INT && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::PINT
				)
			{
				// если используется не инициализированная переменная,то ошибка
				if (idt.table[lex.table[i].idxTI].iddatatype == IT::NONE)
				{
					throw ERROR_THROW_IN(305, line, i - begin);
				}
				// если имеет место несоответствие типов, то ошибка
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// если мы вышли за пределы строки, то завершаем работу функции
			if (lex.table[i + 1].sn != line)
			{
				return;
			}
		}
	}

	// Проверка логических выражений
	// допустимые типы: int, pint, bool
	// допустимые операции: логические
	void CheckoutBooleanExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// если операция определена, но не представляет логический тип, то ошибка
			if (lex.table[i].operation != NULL && lex.table[i].operationtype != LT::L)
			{
				throw ERROR_THROW_IN(311, line, i - begin); // Ошибка типа используемого выражения
			}
			// если же лексема является идентификатором/литералом, но не пренадлежит ни к одному из целочиленных типов, то ошибка
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::INT &&\
				idt.table[lex.table[i].idxTI].iddatatype != IT::PINT && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::BOOL \
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// если мы вышли за пределы строки, то завершаем работу функции
			if (lex.table[i + 1].sn != line)
			{
				pos = i;
				return;
			}
		}
	}

	// Проверка выражений над строковым типом
	// Допустимый тип: string
	// Допустимые операции: конкатенация (+)
	void CheckoutStringExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// если операция определена, но не является конкатенацией
			if (lex.table[i].operation != NULL && lex.table[i].operation != '+')
			{
				throw ERROR_THROW_IN(311, line, i - begin); // Ошибка типа используемого выражения
			}
			// если же лексема является идентификатором/литералом, но не пренадлежит ни к одному из целочиленных типов, то ошибка
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::STR && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::SIGN
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// если мы вышли за пределы строки, то завершаем работу функции
			if (lex.table[i + 1].sn != line)
			{
				pos = i;
				return;
			}
		}
	}

	// Проверка выражений над символьными типом
	// Допустимый тип: sign
	// Допустимые операции: суммирование кодов символов (+)
	void CheckoutSignExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// если тип операций определен, но не относится к символьным, то ошибка
			if (lex.table[i].operation != NULL && lex.table[i].operation != '+')
			{
				throw ERROR_THROW_IN(311, line, i - begin); // Ошибка типа используемого выражения
			}
			// если же лексема является идентификатором, но ее тип не соответствует символьному, то ошибка
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::SIGN
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// если мы вышли за пределы строки, то завершаем работу функции
			if (lex.table[i + 1].sn != line)
			{
				pos = i;
				return;
			}
		}
	}

	void CheckoutPrint(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		LT::OPERATIONTYPE type = LT::UNDEF;
		IT::IDDATATYPE previous = IT::NONE;
		int printposition = pos - 1;

		for (int i = pos; ; i++)
		{
			// если лексема явялется операцией
			if (lex.table[i].operation != NULL)
			{
				// если тип операции не определен
				if (type == LT::UNDEF)
				{
					// тип операции может быть определен единожды и не может изменяться в пределах выражения
					type = lex.table[i].operationtype;
				}
				// если же тип операции уже определен
				else if (type != LT::UNDEF)
				{
					// если он соответствует ранее определенному
					if (type == lex.table[i].operationtype)
					{
						continue;
					}
					// в противном случае ошибка
					throw ERROR_THROW_IN(312, line, i - begin); // Ошибка типа используемого выражения
				}
			}
			// если же лексема является идентификатором/литералом
			else if (lex.table[i].idxTI != LT_TI_NULLIDX)
			{
				// если тип операндов не определен
				if (previous == IT::NONE)
				{
					previous = idt.table[lex.table[i].idxTI].iddatatype;
				}
				// если тип операндов определен
				else
				{
					// если оба тип целочисленные, либо оба типа символьные, либо типы равны между собой
					if ((previous == IT::PINT && idt.table[lex.table[i].idxTI].iddatatype == IT::INT) || \
						(previous == IT::INT && idt.table[lex.table[i].idxTI].iddatatype == IT::PINT) || \
						(previous == IT::STR && idt.table[lex.table[i].idxTI].iddatatype == IT::SIGN) || \
						(previous == IT::SIGN && idt.table[lex.table[i].idxTI].iddatatype == IT::STR) || \
						previous == idt.table[lex.table[i].idxTI].iddatatype \
						)
					{
						continue;
					}
					else
					{
						throw ERROR_THROW_IN(313, line, i - begin);
					}
				}
			}
			// если мы вышли за пределы строки, то завершаем работу функции
			if (lex.table[i + 1].sn != line)
			{
				return;
			}
		}
	}
}