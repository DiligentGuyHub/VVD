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
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, UNDEF = 0 };	// ���� ���������������: ����������/�������/��������/�������

	struct Entry	// ������ ������� ���������������
	{
		int			idxfirstLE;		// ������ � ������� ������
		char		id[ID_MAXSIZE];	// ������������� (������������� ��������� �� ID_MAXSIZE)
		IDDATATYPE	iddatatype;		// ��� ������
		IDTYPE		idtype;			// ��� ��������������

		int			numbersystem;	// ������� ���������
		bool		initialized;	// �������������� ��?

		int			index;					// ������� ��������� 
		char		function[ID_MAXSIZE];	// �������, ������� �����������

		struct		// 
		{
			int vint;							// �������� integer
			unsigned int vpint;
			struct
			{
				int len;						// ���������� �������� � string
				char str[IT_STR_MAXSIZE - 1]{};	// ������� string
			}vstr;								// �������� string
			char vsign;
			struct
			{
				bool value;
				char str[6];
			}vbool;
		}value;		// �������� ��������������
	};

	struct IdTable	// ��������� ������� ���������������
	{
		int			maxsize;		// ������� ������� < TI_MAXSIZE
		int			size;			// ������� ������ ������� ��������������� < maxsize
		Entry* table;			// ������ ����� ������� ���������������
	};

	IdTable Create(					// �������� ������� ���������������
		int size					// �������������� ������� ������� < TI_MAXSIZE
	);

	void Add(						// ���������� ������ � ������� ���������������
		IdTable& idtable,			// ��������� ������� ���������������
		Entry entry,				// ����������� ������ ������� ���������������
		int line,
		int id
	);

	void UpdatePrevious(
		IdTable& idt,
		Entry entry,
		bool isNumber
	);


	Entry GetEntry(					// ��������� ������ ������� ���������������
		IdTable& idtable,			// ��������� ������� ���������������
		int n						// ����� ���������� ������
	);

	int IsId(						// ������� ������ ������ (���� ��� - TI_NULLIDX)
		IdTable& idtable,			// ��������� ������� ���������������
		char* id,					// �������������
		char* scope
	);

	void Delete(					// �������� ������� ��������������� (������������ ������) 
		IdTable& idtable			// ��������� ������� ���������������
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
