#include "VVD.h"
#include "IdTable.h"
#include "FST.h"
#include "Error.h"

namespace IT {


	IdTable Create(int size)
	{
		if (size > IT_MAXSIZE) throw ERROR_THROW(106);
		IdTable idt;
		idt.maxsize = size;
		idt.size = 0;
		idt.table = new Entry[size];
		return idt;
	}

	int idxfle = 0;

	void Add(IdTable& idt, Entry entry, int line, int id)
	{
		if (idt.size >= idt.maxsize) throw ERROR_THROW(107);

		for (int i = 0; i < idt.size; i++)
		{
			if ((!strcmp(idt.table[i].id, entry.id) && entry.idtype != L && \
				idt.table[i].index <= entry.index && !strcmp(idt.table[i].function, entry.function)) || \
				(!strcmp(idt.table[i].id, entry.id) && idt.table[i].idtype == F)
				)
			{
				idxfle = idt.table[i].idxfirstLE;
				return;
			}
		}
		//if (entry.iddatatype == NONE) throw ERROR_THROW_IN(121, line, id);
		idt.table[idt.size++] = entry;
		return;
	}

	/*void UpdatePrevious(IdTable& idt, Entry entry, bool isNumber)
	{
		for (int i = 0; i < idt.size; i++)
		{
			if (idt.table[i].idxfirstLE == idxfle)
			{
				if (idt.table[i].iddatatype == INT)
				{
					if (isNumber == false) throw ERROR_THROW(126);
					idt.table[i].value.vint = entry.value.vint;
				}

				else if (idt.table[i].iddatatype == STR)
				{
					if (isNumber == true) throw ERROR_THROW(126);
					strcpy_s(idt.table[i].value.vstr.str, entry.value.vstr.str);
				}

				return;
			}
		}
		return;
	}*/

	Entry GetEntry(IdTable& idtable, int n)
	{
		if (n <= idtable.size)
		{
			return idtable.table[n];
		}
		throw ERROR_THROW(108);
	}

	int IsId(IdTable& idtable, char* id, char* scope) // scope = functionName
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!strcmp(idtable.table[i].id, id) && !strcmp(scope, idtable.table[i].function) ||
				idtable.table[i].idtype == F && !strcmp(idtable.table[i].id, id))
				return i;
		}
		return IT_NULLIDX;
	}

	IDDATATYPE CheckDataType(IdTable& idt, char* id, char* scope)
	{
		for (int i = 0; i < idt.size; i++)
		{
			//if (strcmp(id, idt.table[i].id) == 0 && strcmp(scope, idt.table[i].functionName) == 0)
			if (strcmp(id, idt.table[i].id) == 0)
				return idt.table[i].iddatatype;
		}
		return NONE;
	}

	void Delete(IdTable& idtable)
	{
		if (idtable.table == nullptr) throw ERROR_THROW(109);
		idtable.maxsize = 0;
		idtable.size = 0;
		delete[] idtable.table;
		return;
	}

	IdTable& CreateEntry(IdTable& idt, char* buffer, int ival, char* sval, char lex, IDTYPE type, IDDATATYPE dtype, int line, int id)
	{
		IT::Entry en; // создаем запись таблицы id
		en.idtype = type; // записываем туда тип идентификатора
		en.iddatatype = dtype; // уточняем тип данных идентификатора
		en.idxfirstLE = line; // уточняем строку инициализации
		for (int i = 0; i < ID_MAXSIZE; i++)
		{
			// посимвольно записываем имя идентификатора с усечением
			en.id[i] = buffer[i];
		}
		// определяем значение идентификатора в зависимости от типа данных
		if (dtype == INT) en.value.vint = ival;
		else strcpy_s(en.value.vstr.str, sval);
		Add(idt, en, line, id);
		return idt;
	}

	void IdTableOut(IdTable idt)
	{
		std::cout << "\n\nНомер\tНазвание\tОбласть\t\tИндекс\t\tТип данных\tТип идентификатора\tЗначение\n";
		for (int i = 0; i < idt.size; i++)
		{
			std::cout << " " << std::setw(2) << std::setfill('0'); \
				std::cout << i << '\t';

			std::cout << " " << idt.table[i].id << '\t';

			std::cout << "\t" << idt.table[i].function << "\t";

			/*std::cout << "\t" << std::setw(4) << std::setfill(' ');
			std::cout << idt.table[i].index << '\t';*/

			std::cout << '\t' << std::setw(5) << std::setfill('0');
			std::cout << idt.table[i].idxfirstLE << '\t';
			switch (idt.table[i].iddatatype)
			{
			case INT:
				std::cout << "\tint\t";
				break;
			case PINT:
				std::cout << "\tpint\t";
				break;
			case SIGN:
				std::cout << "\tsign\t";
				break;
			case STR:
				std::cout << "\tstring\t";
				break;
			case BOOL:
				std::cout << "\tbool\t";
				break;
			default:
				std::cout << "\tunknown\t";
				break;
			}
			switch (idt.table[i].idtype)
			{
			case F:
				std::cout << "\tfunction\t";
				std::cout << '\t' << "-" << '\n';
				break;
			case V:
				std::cout << "\tvariable\t";
				if (idt.table[i].iddatatype == INT)
					std::cout << '\t' << idt.table[i].value.vint << '\n';
				else if (idt.table[i].iddatatype == PINT)
					std::cout << '\t' << idt.table[i].value.vpint << '\n';
				else if (idt.table[i].iddatatype == STR || idt.table[i].iddatatype == SIGN)
					std::cout << "\t" << idt.table[i].value.vstr.str << "\n";
				else if (idt.table[i].iddatatype == BOOL)
					std::cout << "\t" << idt.table[i].value.vbool.str << "\n";
				else
					std::cout << '\t' << "uninitialized" << '\n';

				break;
			case P:
				std::cout << "\tparameter\t";
				if (idt.table[i].iddatatype == INT)
					std::cout << '\t' << idt.table[i].value.vint << '\n';
				else if (idt.table[i].iddatatype == STR)
					std::cout << "\t" << idt.table[i].value.vstr.str << "\n";
				else
					std::cout << '\t' << "uninitialized" << '\n';
				break;
			case L:
				std::cout << "\tliteral \t";
				if (idt.table[i].iddatatype == INT)
					std::cout << '\t' << idt.table[i].value.vint << '\n';
				else if (idt.table[i].iddatatype == STR)
					std::cout << "\t" << idt.table[i].value.vstr.str << "\n";
				else
					std::cout << '\t' << "uninitialized" << '\n';
				break;
			default:
				std::cout << "\tunknown \t";
				std::cout << '\t' << '\t' << '\n';
			}

		}
	}
}