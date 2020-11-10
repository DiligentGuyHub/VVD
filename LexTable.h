#pragma once
#include "Input.h"
#include "IdTable.h"
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

#define LEX_MORE		'c' // >
#define LEX_LESS		'c' // <
#define	LEX_EQMORE		'c' // >=
#define LEX_EQLESS		'c' // <=
#define LEX_EQUALS		'c' // ==
#define LEX_NEQUALS		'c' // !=

#define LEX_INVERSION	'q' // ~
#define LEX_CONJUCTION	'b' // &
#define LEX_DISJUNCTION	'b' // \

#define LEX_PLUS		'v'
#define LEX_MINUS		'v' 
#define LEX_STAR		'v' 
#define LEX_DIRSLASH	'v' 

namespace LT		// таблица лексем
{
	struct Entry	// строка таблицы лексем
	{
		char			lexema;					// лексема
		char			operation;
		int				sn;						// номер строки в исходном тексте
		int				idxTI;					// индекс в таблице идентификаторов (или LT_TI_NULLIDX)
	};

	struct LexTable // экземпл€р таблицы лексем
	{
		int		maxsize;				// емкость таблица лексем < LT_MAXSIZE
		int		size;					// текущий размер таблица лексем < maxsize
		int		expressionsAmount;
		Entry* table;					// массив строк таблицы лексем
	};
	
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
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
