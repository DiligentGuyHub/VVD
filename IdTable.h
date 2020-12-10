#pragma once
#include "LexTable.h"
#define ID_MAXSIZE		10 // to fix
#define FUNC_MAXAMOUNT	64 // максимальное допустимое число вызовов функций
#define PARM_MAXAMOUNT	5 // максимальное число параметров функции
#define IT_MAXSIZE		4096
#define IT_INT_DEFAULT	0x00000000
#define IT_STR_DEFAULT	0x00
#define IT_NULLIDX		0xffffffff
#define IT_STR_MAXSIZE	255

namespace IT
{
	enum IDDATATYPE { INT = 1, PINT = 2, SIGN = 3, STR = 4, BOOL = 5, NONE = 0 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, C = 5, UNDEF = 0 };	// типы идентификаторов: переменная/функция/параметр/литерал/вызов

	struct Entry	// строка таблицы идентификаторов
	{
		int			idxfirstLE;		// индекс в таблице лексем
		char		id[ID_MAXSIZE];	// идентификатор (автоматически усекается до ID_MAXSIZE)
		IDDATATYPE	iddatatype;		// тип данных
		IDTYPE		idtype;			// тип идентификатора

		int			numbersystem;	// система счисления
		int			parmsamount;	// для вызовов: количество параметров
		bool		initialized;	// иницилизирован ли? (not used yet)

		int			index;					// глубина вхождения 
		char		function[ID_MAXSIZE];	// функция, которой принадлежит

		struct		// 
		{
			int vint;							// значение integer
			unsigned int vpint;
			struct
			{
				int len;						// количество символов в string
				char str[IT_STR_MAXSIZE - 1]{};	// символы string
			}vstr;								// значение string
			char vsign;
			struct
			{
				bool value;
				char str[6];
			}vbool;
		}value;		// значение идентификатора
	};

	struct IdTable	// экземпляр таблицы идентификаторов
	{
		int			maxsize;		// емкость таблицы < TI_MAXSIZE
		int			size;			// текущий размер таблицы идентификаторов < maxsize
		int			callamount;		// текущее количество вызовов функций
		Entry*		table;			// массив строк таблицы идентификаторов
	};

	IdTable Create(					// создание таблицы идентификаторов
		int size					// предполагаемая емкость таблицы < TI_MAXSIZE
	);

	void Add(	
		LT::LexTable& lex,
		IdTable& idtable,			// экземпляр таблицы идентификаторов
		Entry entry,				// добавляемая строка таблицы идентификаторов
		int line,
		int id
	);

	void Add(						// добавление строки в таблицу идентификаторов
		LT::LexTable& lex,
		IdTable& idtable,			// экземпляр таблицы идентификаторов
		Entry entry,				// добавляемая строка таблицы идентификаторов
		int line,
		int id,
		bool& withinCall			// флаг вызова функции (для считывания параметров)
	);

	void UpdatePrevious(
		IdTable& idt,
		Entry entry,
		bool isNumber
	);


	Entry GetEntry(					// получение строки таблицы идентификаторов
		IdTable& idtable,			// экземпляр таблицы идентификаторов
		int n						// номер получаемой строки
	);

	int IsId(						// возврат номера строки (если нет - TI_NULLIDX)
		IdTable& idtable,			// экземпляр таблицы идентификаторов
		char* id,					// идентификатор
		char* scope
	);

	void Delete(					// удаление таблицы идентификаторов (освобождение памяти) 
		IdTable& idtable			// экземпляр таблицы идентификаторов
	);

	IdTable& CreateEntry(
		IdTable& idtable,
		char* buffer,
		int line,
		int id
	);

	void IdTableOut(
		IdTable idt
	);

	IDDATATYPE CheckDataType(IdTable& idt, char* id, char* scope);
};
