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

namespace LT		// ������� ������
{
	struct Entry	// ������ ������� ������
	{
		char			lexema;					// �������
		char			operation;
		int				sn;						// ����� ������ � �������� ������
		int				idxTI;					// ������ � ������� ��������������� (��� LT_TI_NULLIDX)
	};

	struct LexTable // ��������� ������� ������
	{
		int		maxsize;				// ������� ������� ������ < LT_MAXSIZE
		int		size;					// ������� ������ ������� ������ < maxsize
		int		expressionsAmount;
		Entry* table;					// ������ ����� ������� ������
	};
	
	struct LEX
	{
		LT::LexTable lextable;
		IT::IdTable idtable;
	};

	LexTable Create(					// �������� ������� ������
		int size						// �������������� ������� ������� ������ < LT_MAXSIZE
	);

	void Add(							// ���������� ������ � ������� ������
		LexTable& lextable,				// ��������� ������� ������
		Entry entry						// ������ ��� ���������� � ������� ������
	);

	Entry GetEntry(						// ��������� ������ �� ������� ������
		LexTable& lextable,				// ��������� ������� ������
		int n							// ������ ������� ������
	);

	void Delete(						// �������� ������� ������ (������������ ������)
		LexTable& lextable				// ��������� ������� ������
	);

}
