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
		std::ofstream* stream; // потоковый вывод ofstream из <fstream>
	};

	static const LOG INITLOG = { "", NULL }; // инициализаци€ LOG
	LOG	 GetLog(char logfile[]); // формирование структуры
	void WriteLine(LOG log, const wchar_t* c, ...); // вывод конкатенации строк
	void WriteLine(LOG log, const char* c, ...); // вывод конкатенации строк
	void WriteLog(LOG log); // вывод заголовка
	void WriteParm(LOG log, Parm::PARM parm); // информаци€ о входных параметрах
	void WriteIn(LOG log, In::IN in); // информаци€ о входном потоке
	void WriteError(LOG log, Error::ERROR error); // протокол об ошибке
	void Close(LOG log); // закрытие потока
	void WriteLex(LOG log, LT::LexTable lex, Parm::PARM parm);
}
