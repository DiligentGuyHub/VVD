#include "Semantic Analysis.h"
#include "IdTable.h"
#include "Error.h"
#include "PolishNotation.h"

namespace Semantic
{
	// ��������� ������ ���������, �������� � ������ ������� ������
	void FindExpressions(LT::LEX& lex)
	{
		uint start_time = clock(), end_time;
		int begin = 0; // ������� ��������� � ������ ������ ������, ��� �������� ������ ��������� � ������� ������� � ������
		for (int i = 0, lineCounter = 0; i < lex.lextable.size; i++)
		{
			// ����������� �������� ������ ������
			if (lex.lextable.table[i].sn != lineCounter) 
			{
				begin = i;
				lineCounter = lex.lextable.table[i].sn;
				if (lineCounter == 7)
				{
					int a = 10;
				}
			}
			// ���� �������� ����������� if/elif
			if (lex.lextable.table[i].lexema == '?' || lex.lextable.table[i].lexema == 'z')
			{
				CheckoutBooleanExpression(lex.lextable, lex.idtable, begin - 1, lineCounter, i);
			}
			// ���� ���������� �������
			else if (lex.lextable.table[i].lexema == 'f')
			{
				while (lex.lextable.table[i].sn == lineCounter)
				{
					i++;
				}
			}
			// ���� �������������
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
		std::cout << "\n������������� ������ �������� �������\n����� ����������: ";
		if (end_time - start_time == 0)
		{
			std::cout << "< 1 ��\n";
		}
		else
		{
			std::cout << end_time - start_time << " ��\n";
		}
		//PolishNotation::Checkout(lex.lextable, lex.idtable);
		return;
	}

	// �������� ��������� � �������������� ����������� (�� ����������)
	// ���������� ����: int, pint
	// ���������� ��������: ��������������, ������� (���� �� ����)
	void CheckoutIntegerExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		LT::OPERATIONTYPE type = LT::UNDEF;

		for (int i = pos; ; i++)
		{
			// ���� ������� �������� ���������
			if (lex.table[i].operation != NULL)
			{
				// ���� ��� �������� �� ���������
				if (type == LT::UNDEF)
				{
					// ���������� ��� �������� �������� ������, ��� ��� ���������� � �������� �� ������� ���������
					if (lex.table[i].operationtype == LT::L)
					{
						throw ERROR_THROW_IN(313, line, i - begin);
					}
					// ��� �������� ����� ���� ��������� ��� �������������� ��� �������
					type = lex.table[i].operationtype;
				}
				// ���� �� ��� �������� ��� ���������
				else if (type != LT::UNDEF)
				{
					// ���� �� ������������� ����� �������������
					if (type == lex.table[i].operationtype)
					{
						continue;
					}
					// � ��������� ������ ������
					throw ERROR_THROW_IN(311, line, i - begin); // ������ ���� ������������� ���������
				}
			}
			// ���� �� ������� �������� ���������������/��������� � �� ����� �� ������ �� ������������� �����
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::INT && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::PINT
				)
			{
				// ���� ������������ �� ������������������ ����������,�� ������
				if (idt.table[lex.table[i].idxTI].iddatatype == IT::NONE)
				{
					throw ERROR_THROW_IN(305, line, i - begin);
				}
				// ���� ����� ����� �������������� �����, �� ������
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// ���� �� ����� �� ������� ������, �� ��������� ������ �������
			if (lex.table[i + 1].sn != line)
			{
				return;
			}
		}
	}

	// �������� ���������� ���������
	// ���������� ����: int, pint, bool
	// ���������� ��������: ����������
	void CheckoutBooleanExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// ���� �������� ����������, �� �� ������������ ���������� ���, �� ������
			if (lex.table[i].operation != NULL && lex.table[i].operationtype != LT::L)
			{
				throw ERROR_THROW_IN(311, line, i - begin); // ������ ���� ������������� ���������
			}
			// ���� �� ������� �������� ���������������/���������, �� �� ����������� �� � ������ �� ������������ �����, �� ������
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::INT &&\
				idt.table[lex.table[i].idxTI].iddatatype != IT::PINT && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::BOOL \
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// ���� �� ����� �� ������� ������, �� ��������� ������ �������
			if (lex.table[i + 1].sn != line)
			{
				pos = i;
				return;
			}
		}
	}

	// �������� ��������� ��� ��������� �����
	// ���������� ���: string
	// ���������� ��������: ������������ (+)
	void CheckoutStringExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// ���� �������� ����������, �� �� �������� �������������
			if (lex.table[i].operation != NULL && lex.table[i].operation != '+')
			{
				throw ERROR_THROW_IN(311, line, i - begin); // ������ ���� ������������� ���������
			}
			// ���� �� ������� �������� ���������������/���������, �� �� ����������� �� � ������ �� ������������ �����, �� ������
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::STR && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::SIGN
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// ���� �� ����� �� ������� ������, �� ��������� ������ �������
			if (lex.table[i + 1].sn != line)
			{
				pos = i;
				return;
			}
		}
	}

	// �������� ��������� ��� ����������� �����
	// ���������� ���: sign
	// ���������� ��������: ������������ ����� �������� (+)
	void CheckoutSignExpression(LT::LexTable& lex, IT::IdTable& idt, int begin, int line, int& pos)
	{
		for (int i = pos; ; i++)
		{
			// ���� ��� �������� ���������, �� �� ��������� � ����������, �� ������
			if (lex.table[i].operation != NULL && lex.table[i].operation != '+')
			{
				throw ERROR_THROW_IN(311, line, i - begin); // ������ ���� ������������� ���������
			}
			// ���� �� ������� �������� ���������������, �� �� ��� �� ������������� �����������, �� ������
			else if (lex.table[i].idxTI != LT_TI_NULLIDX && \
				idt.table[lex.table[i].idxTI].iddatatype != IT::SIGN
				)
			{
				throw ERROR_THROW_IN(313, line, i - begin);
			}
			// ���� �� ����� �� ������� ������, �� ��������� ������ �������
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
			// ���� ������� �������� ���������
			if (lex.table[i].operation != NULL)
			{
				// ���� ��� �������� �� ���������
				if (type == LT::UNDEF)
				{
					// ��� �������� ����� ���� ��������� �������� � �� ����� ���������� � �������� ���������
					type = lex.table[i].operationtype;
				}
				// ���� �� ��� �������� ��� ���������
				else if (type != LT::UNDEF)
				{
					// ���� �� ������������� ����� �������������
					if (type == lex.table[i].operationtype)
					{
						continue;
					}
					// � ��������� ������ ������
					throw ERROR_THROW_IN(312, line, i - begin); // ������ ���� ������������� ���������
				}
			}
			// ���� �� ������� �������� ���������������/���������
			else if (lex.table[i].idxTI != LT_TI_NULLIDX)
			{
				// ���� ��� ��������� �� ���������
				if (previous == IT::NONE)
				{
					previous = idt.table[lex.table[i].idxTI].iddatatype;
				}
				// ���� ��� ��������� ���������
				else
				{
					// ���� ��� ��� �������������, ���� ��� ���� ����������, ���� ���� ����� ����� �����
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
			// ���� �� ����� �� ������� ������, �� ��������� ������ �������
			if (lex.table[i + 1].sn != line)
			{
				return;
			}
		}
	}
}