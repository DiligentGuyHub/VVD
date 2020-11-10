#include "Log.h"

namespace Log {

	LOG GetLog(char log_file[]) // �������� ������� - ��� ����� ��� log
	{
		LOG log;
		log.stream = new std::ofstream; // �������� ������ ������ ��� �������� ��������� LOG
		log.stream->open(log_file); // ������������ ����� ����� ��� ������ ������
		if (!log.stream->is_open())
			throw ERROR_THROW(6);
		strcpy_s(log.logfile, log_file); // ������������ ����� log_file � ���������
		return log;
	}

	void WriteLine(LOG log, const char* c, ...)
	{
		const char** pointer = &c;
		while (*pointer != "") {
			*log.stream << *pointer;
			pointer++;
		}
		return;
	}

	void WriteLine(LOG log, const wchar_t* c, ...)
	{
		const wchar_t** pointer = &c;
		char tmp[TEMPSIZE];
		while (*pointer != L"") {
			wcstombs(tmp, *pointer++, sizeof(tmp));
			*log.stream << tmp;
		}

		return;
	}

	void WriteLog(LOG log)
	{
		time_t current_time;
		tm time_info;
		char tmp[TEMPSIZE];
		time(&current_time);
		localtime_s(&time_info, &current_time);
		*log.stream << "\n-------��������:-------\n";
		strftime(tmp, sizeof(tmp), "����� ����������: %d.%m.%Y %A %H:%M:%S", &time_info);
		*log.stream << tmp << "\n";
	}

	void WriteIn(LOG log, In::IN in_)
	{
		*log.stream << "\n------�������� ������------\n";
		*log.stream << "\n����� ��������: " << in_.size;
		*log.stream << "\n����� �����: " << in_.lines - 1;
		*log.stream << "\n����� ���������: " << in_.ignor;
		*log.stream << "\n\n��������������� ����: \n" << in_.text << std::endl;
		/*std::cout << "\n------�������� ������------\n";
		std::cout << "\n����� ��������: " << in_.size;
		std::cout << "\n����� �����: " << in_.lines << std::endl;
		std::cout << "\n����� ���������: " << in_.ignor;
		std::cout << "\n\n��������������� ������: \n" << in_.text << std::endl;*/
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in_[PARM_MAX_SIZE];  strcpy_s(in_, parm.in);
		char out_[PARM_MAX_SIZE]; strcpy_s(out_, parm.out);
		char log_[PARM_MAX_SIZE]; strcpy_s(log_, parm.log);
		*log.stream << "\n------���������------\n";
		*log.stream << "-in:  " << in_ << std::endl;
		*log.stream << "-out: " << out_ << std::endl;
		*log.stream << "-log: " << log_ << std::endl;
		return;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream)
		{
			*log.stream << "\n������ " << error.id << ": " << error.message << std::endl;
			*log.stream << "������ " << error.inext.line << std::endl;
			*log.stream << "������� " << error.inext.col << std::endl;
		}
		std::cout << "\n������ " << error.id << ": " << error.message << std::endl;
		std::cout << "������ " << error.inext.line << std::endl;
		std::cout << "������� " << error.inext.col << std::endl;
		return;
	}
	void Close(LOG log)
	{
		log.stream->close();
		delete[] log.stream;
		return;
	}

	void WriteLex(LOG log, LT::LexTable lex, Parm::PARM parm)
	{
		*log.stream << "\n������� ������:\n";
		*log.stream << "00" << lex.table[0].sn << ' ';
		for (int i = 0; i < lex.size; i++)
		{
			if (lex.table[i].lexema == '|')
			{
				*log.stream << std::endl;
				*log.stream << std::setw(3) << std::setfill('0');
				*log.stream << lex.table[i].sn << ' ';
			}
			else
			{
				*log.stream << lex.table[i].lexema;
			}

		}
		return;
	}
}