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
		ERROR_ENTRY(8, "[SYS] Ошибка при открытии файла вывода генерируемого кода (-outfile)"),
		ERROR_ENTRY(9, ""),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "[LEX] LT::Create: превышена максимальная емкость таблицы лексем"),
		ERROR_ENTRY(101, "[LEX] LT::Add: переполнение таблицы лексем"),
		ERROR_ENTRY(102, "[LEX] LT::GetEntry: элемент таблицы лексем не найден"),
		ERROR_ENTRY(103, "[LEX] LT::Delete: таблица лексем отсутствует"),
		// 
		// удалить, так как добавлено в семантические проверки
		ERROR_ENTRY(104, "[LEX] LT::CreateEntry: точка входа main не может быть инициализирована дважды"),
		ERROR_ENTRY(105, "[LEX] LT::CreateEntry: точка входа main обязана быть иницилизирована"),
		//
		ERROR_ENTRY(106, "[LEX] IT::Create: превышена максимальная емкость таблицы идентификаторов"),
		ERROR_ENTRY(107, "[LEX] IT::Add: переполнение таблицы идентификаторов"),
		ERROR_ENTRY(108, "[LEX] IT::GetEntry: элемент таблицы идентификаторов не найден"),
		ERROR_ENTRY(109, "[LEX] IT::Delete: таблица идентифиаторов отсутствует"),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200, "[SYN]: Неверная структура программы"),
		ERROR_ENTRY(201, "[SYN]: Ошибочный оператор"),
		ERROR_ENTRY(202, "[SYN]: Ошибка в выражении"),
		ERROR_ENTRY(203, "[SYN]: Ошибка в параметрах функции"),
		ERROR_ENTRY(204, "[SYN]: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(205, "[SYN]: Ошибка в арифметической операции"),
		ERROR_ENTRY(206, "[SYN]: Ошибка в битовой операции"),
		ERROR_ENTRY(207, "[SYN]: Ошибка в логической операции"),
		ERROR_ENTRY(208, "[SYN]: Ошибка в условной конструкции"),
		ERROR_ENTRY(209, "[SYN]: Ошибка в выражении условной конструкции"),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),

		ERROR_ENTRY(300, "[SEM] Точка входа main обязана быть единожды инициализирована"),
		ERROR_ENTRY(301, "[SEM] Имя идентификатора не может совпадать с ключевым словом"),
		ERROR_ENTRY(302, "[SEM] Ошибка дублирования имени функции"),
		ERROR_ENTRY(303, "[SEM] Ошибка дублирования имени идентификатора"),
		ERROR_ENTRY(304, "[SEM] Ошибка использования необъявленной функции"),
		ERROR_ENTRY(305, "[SEM] Ошибка использования необъявленной переменной"),
		ERROR_ENTRY(306, "[SEM] Ошибка несоответствия параметров вызываемой функции ее сигнатуре"),
		ERROR_ENTRY(307, "[SEM] Превышение допустимых пределов целочисленного литерала"),
		ERROR_ENTRY(308, "[SEM] Превышение допустимых пределов целочисленного беззнакового литерала"),
		ERROR_ENTRY(309, "[SEM] Превышение допустимых пределов символьного литерала"),
		ERROR_ENTRY(310, "[SEM] Превышение допустимых пределов строкового литерала"),
		ERROR_ENTRY(311, "[SEM] Ошибка типа используемого выражения"), // в if(...) только логические функции
		ERROR_ENTRY(312, "[SEM] Ошибка использования нескольких типов операций в пределах одного выражения"),
		ERROR_ENTRY(313, "[SEM] Ошибка использования типов данных/операций в пределах одного выражения"),
		ERROR_ENTRY(314, "[SEM] Ошибка использования литералов"),
		ERROR_ENTRY(315, "[SEM] "),
		ERROR_ENTRY(316, "[SEM] "),
		ERROR_ENTRY(317, "[SEM]"),
		ERROR_ENTRY(318, "[SEM]"),
		ERROR_ENTRY(319, "[SEM]"),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800)
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

