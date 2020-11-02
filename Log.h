#pragma once
#pragma warning(disable : 4996)
#include "VVD.h"
#include "Error.h"
#include "Parameters.h"
#include "Input.h"
#include "LexTable.h"
#define TEMPSIZE 100


namespace Log
{
	struct LOG
	{
		char logfile[PARM_MAX_SIZE];
		std::ofstream* stream; // ��������� ����� ofstream �� <fstream>
	};

	static const LOG INITLOG = { "", NULL }; // ������������� LOG
	LOG	 GetLog(char logfile[]); // ������������ ���������
	void WriteLine(LOG log, const wchar_t* c, ...); // ����� ������������ �����
	void WriteLine(LOG log, const char* c, ...); // ����� ������������ �����
	void WriteLog(LOG log); // ����� ���������
	void WriteParm(LOG log, Parm::PARM parm); // ���������� � ������� ����������
	void WriteIn(LOG log, In::IN in); // ���������� � ������� ������
	void WriteError(LOG log, Error::ERROR error); // �������� �� ������
	void Close(LOG log); // �������� ������
	void WriteLex(LOG log, LT::LexTable lex, Parm::PARM parm);
}
