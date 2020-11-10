#include "Error.h"

namespace Error {

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "[SYS] Недопустимый код ошибки"),
		ERROR_ENTRY(1, "[SYS] Системный сбой"),
		ERROR_ENTRY(2, "[SYS] Параметр -in должен быть задан"), //
		ERROR_ENTRY(3, "[SYS] Превышена длина входного параметра"), //
		ERROR_ENTRY(4, "[SYS] Ошибка при открытии файла с исходным кодом (-in)"), //
		ERROR_ENTRY(5, "[SYS] Недопустимый символ в исходном файле (-in)"), //
		ERROR_ENTRY(6, "[SYS] Ошибка при создании файла протокола (-log)"), //
		ERROR_ENTRY(7, "[SYS] Ошибка при открытии файла вывода (-out)"), //
		ERROR_ENTRY(8, ""),
		ERROR_ENTRY(9, ""),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "[LEX] LT::Create: превышена максимальная емкость таблицы лексем"),
		ERROR_ENTRY(101, "[LEX] LT::Add: переполнение таблицы лексем"),
		ERROR_ENTRY(102, "[LEX] LT::GetEntry: элемент таблицы лексем не найден"),
		ERROR_ENTRY(103, "[LEX] LT::Delete: таблица лексем отсутствует"),
		ERROR_ENTRY(104, "[LEX] LT::CreateEntry: точка входа main не может быть инициализирована дважды"),
		ERROR_ENTRY(105, "[LEX] LT::CreateEntry: точка входа main обязана быть иницилизирована"),
		ERROR_ENTRY(106, "[LEX] IT::Create: превышена максимальная емкость таблицы идентификаторов"),
		ERROR_ENTRY(107, "[LEX] IT::Add: переполнение таблицы идентификаторов"),
		ERROR_ENTRY(108, "[LEX] IT::GetEntry: элемент таблицы идентификаторов не найден"),
		ERROR_ENTRY(109, "[LEX] IT::Delete: таблица идентифиаторов отсутствует"),
		ERROR_ENTRY_NODEF10(110),
		ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY(600, "[SYN]: Неверная структура программы"),
		ERROR_ENTRY(601, "[SYN]: Ошибочный оператор"),
		ERROR_ENTRY(602, "[SYN]: Ошибка в выражении"),
		ERROR_ENTRY(603, "[SYN]: Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "[SYN]: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605, "[SYN]: Ошибка в арифметической операции"),
		ERROR_ENTRY(606, "[SYN]: Ошибка в битовой операции"),
		ERROR_ENTRY(607, "[SYN]: Ошибка в логической операции"),
		ERROR_ENTRY(608, "[SYN]: Ошибка в условной конструкции"),

		ERROR_ENTRY_NODEF(609),

		ERROR_ENTRY_NODEF10(610),
		ERROR_ENTRY_NODEF10(620),
		ERROR_ENTRY_NODEF10(630),
		ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(650),
		ERROR_ENTRY_NODEF10(660),
		ERROR_ENTRY_NODEF10(670),
		ERROR_ENTRY_NODEF10(680),
		ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
	};

	ERROR GetError(int id) {
		ERROR trouble;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			trouble = errors[0];
		else
			trouble = errors[id];
		return trouble;
	}

	ERROR GetErrorIn(int id, int line = -1, int col = -1) {
		ERROR trouble;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			trouble = errors[0];
		else {
			trouble = errors[id];
			trouble.inext.line = line;
			trouble.inext.col = col;
		}
		return trouble;
	}
}

