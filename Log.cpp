#include "Log.h"

namespace Log {

	LOG GetLog(char log_file[]) // аргумент функции - имя файла для log
	{
		LOG log;
		log.stream = new std::ofstream; // создание потока вывода для элемента структуры LOG
		log.stream->open(log_file); // присваивание имени файла для потока вывода
		if (!log.stream->is_open())
			throw ERROR_THROW(6);
		strcpy_s(log.logfile, log_file); // корпирование файла log_file в структуру
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
		*log.stream << "\n-------ПРОТОКОЛ:-------\n";
		strftime(tmp, sizeof(tmp), "ВРЕМЯ ВЫПОЛНЕНИЯ: %d.%m.%Y %A %H:%M:%S", &time_info);
		*log.stream << tmp << "\n";
	}

	void WriteIn(LOG log, In::IN in_)
	{
		*log.stream << "\n------ИСХОДНЫЕ ДАННЫЕ------\n";
		*log.stream << "\nВсего символов: " << in_.size;
		*log.stream << "\nВсего строк: " << in_.lines - 1;
		*log.stream << "\nВсего пропущено: " << in_.ignor;
		*log.stream << "\n\nПреобразованный файл: \n" << in_.text << std::endl;
		/*std::cout << "\n------ИСХОДНЫЕ ДАННЫЕ------\n";
		std::cout << "\nВсего символов: " << in_.size;
		std::cout << "\nВсего строк: " << in_.lines << std::endl;
		std::cout << "\nВсего пропущено: " << in_.ignor;
		std::cout << "\n\nПреобразованная строка: \n" << in_.text << std::endl;*/
	}

	void WriteParm(LOG log, Parm::PARM parm)
	{
		char in_[PARM_MAX_SIZE];  strcpy_s(in_, parm.in);
		char out_[PARM_MAX_SIZE]; strcpy_s(out_, parm.out);
		char log_[PARM_MAX_SIZE]; strcpy_s(log_, parm.log);
		*log.stream << "\n------ПАРАМЕТРЫ------\n";
		*log.stream << "-in:  " << in_ << std::endl;
		*log.stream << "-out: " << out_ << std::endl;
		*log.stream << "-log: " << log_ << std::endl;
		return;
	}

	void WriteError(LOG log, Error::ERROR error)
	{
		if (log.stream)
		{
			*log.stream << "\nОшибка " << error.id << ": " << error.message << std::endl;
			*log.stream << "Строка " << error.inext.line << std::endl;
			*log.stream << "Позиция " << error.inext.col << std::endl;
		}
		std::cout << "\nОшибка " << error.id << ": " << error.message << std::endl;
		std::cout << "Строка " << error.inext.line << std::endl;
		std::cout << "Позиция " << error.inext.col << std::endl;
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
		*log.stream << "\nТаблица лексем:\n";
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