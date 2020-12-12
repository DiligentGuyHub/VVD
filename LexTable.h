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

namespace LT		// ������� ������
{
	enum OPERATIONTYPE {A = 0, B = 1, L = 2, S = 3, UNDEF = 4}; // ��������������, �������, ����������, ���������, ��������������

	struct Entry	// ������ ������� ������
	{
		char			lexema;					// �������
		char			operation = '\0';		// ���� ������� �������� ���������
		OPERATIONTYPE	operationtype = UNDEF;
		int				sn;						// ����� ������ � �������� ������
		int				idxTI;					// ������ � ������� ��������������� (��� LT_TI_NULLIDX)
	};

	struct LexTable // ��������� ������� ������
	{
		int		maxsize;				// ������� ������� ������ < LT_MAXSIZE
		int		size;					// ������� ������ ������� ������ < maxsize
		Entry* table;					// ������ ����� ������� ������
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
