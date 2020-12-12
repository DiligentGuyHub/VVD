#pragma once
#include "Input.h"
#define LEXEMA_FIXSIZE	1
#define LEXEMA_MAXSIZE	50
#define LT_MAXSIZE		4096
#define LT_TI_NULLIDX	0xfffffff

#define LEX_INT			't' // int
#define LEX_PINT		't' // pint
#define LEX_SIGN		't' // sign
#define LEX_STRING		't' // string
#define LEX_BOOL		't' // string

#define LEX_ID			'i' // identificator
#define LEX_LITERAL		'l' // literal
#define LEX_FUNCTION	'f' // function

#define LEX_MAIN		'm' // main
#define LEX_DEF			'd' // def
#define LEX_RETURN		'r' // return
#define LEX_PRINT		'p' // print

#define LEX_IF			'?' // if
#define LEX_ELIF		'z' // elif
#define LEX_ELSE		'e' // else

#define LEX_SEMICOLON	';'	// ;
#define LEX_COMMA		',' // ,
#define LEX_LEFTBRACE	'{' // {
#define LEX_BRACELET	'}' // }
#define LEX_LEFTHESIS	'(' // (
#define LEX_RIGHTHESIS	')' // )
#define LEX_EQUAL		':' // =

#define LEX_OPERATION	'v'

#define LEX_MORE		'v' // >
#define LEX_LESS		'v' // <
#define	LEX_EQMORE		'v' // >=
#define LEX_EQLESS		'v' // <=
#define LEX_EQUALS		'v' // ==
#define LEX_NEQUALS		'v' // !=

#define LEX_INVERSION	'v' // ~
#define LEX_CONJUCTION	'v' // &
#define LEX_DISJUNCTION	'v' // \

#define LEX_PLUS		'v'
#define LEX_MINUS		'v' 
#define LEX_STAR		'v' 
#define LEX_DIRSLASH	'v' 

namespace LT		// таблица лексем
{
	enum OPERATIONTYPE {A = 0, B = 1, L = 2, S = 3, UNDEF = 4}; // арифметический, булевый, логический, строковый, неопределенный

	struct Entry	// строка таблицы лексем
	{
		char			lexema;					// лексема
		char			operation = '\0';		// если лексема €вл€етс€ операцией
		OPERATIONTYPE	operationtype = UNDEF;
		int				sn;						// номер строки в исходном тексте
		int				idxTI;					// индекс в таблице идентификаторов (или LT_TI_NULLIDX)
	};

	struct LexTable // экземпл€р таблицы лексем
	{
		int		maxsize;				// емкость таблица лексем < LT_MAXSIZE
		int		size;					// текущий размер таблица лексем < maxsize
		Entry* table;					// массив строк таблицы лексем
	};

	LexTable Create(					// создание таблица лексем
		int size						// предполагаема€ емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(							// добавление строки в таблицу лексем
		LexTable& lextable,				// экземпл€р таблица лексем
		Entry entry						// строка дл€ добавлени€ в таблицу лексем
	);

	Entry GetEntry(						// получение строки из таблицы лексем
		LexTable& lextable,				// экземпл€р таблицы лексем
		int n							// строка таблицы лексем
	);

	void Delete(						// удаление таблицы лексем (освобождение пам€ти)
		LexTable& lextable				// экземпл€р таблицы лексем
	);

}
