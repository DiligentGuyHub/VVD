#pragma once
#define ID_MAXSIZE		10 // to fix
#define IT_MAXSIZE		4096
#define IT_INT_DEFAULT	0x00000000
#define IT_STR_DEFAULT	0x00
#define IT_NULLIDX		0xffffffff
#define IT_STR_MAXSIZE	255

namespace IT
{
	enum IDDATATYPE { INT = 1, PINT = 2, SIGN = 3, STR = 4, BOOL = 5, NONE = 0 };
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, UNDEF = 0 };	// типы идентификаторов: переменная/функция/параметр/литерал

	struct Entry	// строка таблицы идентификаторов
	{
		int			idxfirstLE;		// индекс в таблице лексем
		char		id[ID_MAXSIZE];	// идентификатор (автоматически усекается до ID_MAXSIZE)
		IDDATATYPE	iddatatype;		// тип данных
		IDTYPE		idtype;			// тип идентификатора

		int			numbersystem;	// система счисления
		bool		initialized;	// иницилизирован ли?

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
		Entry* table;			// массив строк таблицы идентификаторов
	};

	IdTable Create(					// создание таблицы идентификаторов
		int size					// предполагаемая емкость таблицы < TI_MAXSIZE
	);

	void Add(						// добавление строки в таблицу идентификаторов
		IdTable& idtable,			// экземпляр таблицы идентификаторов
		Entry entry,				// добавляемая строка таблицы идентификаторов
		int line,
		int id
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
