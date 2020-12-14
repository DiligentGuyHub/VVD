#include "Error.h"

namespace Error {

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0,	"[SYS] Недопустимый код ошибки"),
		ERROR_ENTRY(1,	"[SYS] Системный сбой"),
		ERROR_ENTRY(2,	"[SYS] Параметр -in должен быть задан"), 
		ERROR_ENTRY(3,	"[SYS] Превышена длина входного параметра"), 
		ERROR_ENTRY(4,	"[SYS] Ошибка при открытии файла с исходным кодом (-in)"), 
		ERROR_ENTRY(5,	"[SYS] Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(6,	"[SYS] Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(7,	"[SYS] Ошибка при открытии файла вывода (-out)"),
		ERROR_ENTRY(8,	"[SYS] Ошибка при открытии файла вывода генерируемого кода (-outfile)"),
		ERROR_ENTRY(9,	"[GEN] Ошибка неопределенного типа идентификатора"),
		ERROR_ENTRY(10, "[GEN] Ошибка преобразования выражения в обратную польскую запись"),
		ERROR_ENTRY(11, "[SYS] Параметр -gen должен быть задан"),
		ERROR_ENTRY(12, "[GEN] "),
		ERROR_ENTRY(13, "[GEN] "),
		ERROR_ENTRY(14, "[GEN] "),
		ERROR_ENTRY(15, "[GEN] "),
		ERROR_ENTRY(16, "[GEN] "),
		ERROR_ENTRY(17, "[GEN] "),
		ERROR_ENTRY(18, "[GEN] "),
		ERROR_ENTRY(19, "[GEN] "), 
		ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30),
		ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50), ERROR_ENTRY_NODEF10(60),
		ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),

		ERROR_ENTRY(100, "[LEX] LT::Create: превышена максимальная емкость таблицы лексем"),
		ERROR_ENTRY(101, "[LEX] LT::Add: переполнение таблицы лексем"),
		ERROR_ENTRY(102, "[LEX] LT::GetEntry: элемент таблицы лексем не найден"),
		ERROR_ENTRY(103, "[LEX] LT::Delete: таблица лексем отсутствует"),
		ERROR_ENTRY(104, "[LEX] LT::CreateEntry: ошибка разбора цепочки"),
		ERROR_ENTRY_NODEF(105, "[LEX] LT::CreateEntry: точка входа main обязана быть иницилизирована"),
		ERROR_ENTRY(106, "[LEX] IT::Create: превышена максимальная емкость таблицы идентификаторов"),
		ERROR_ENTRY(107, "[LEX] IT::Add: переполнение таблицы идентификаторов"),
		ERROR_ENTRY(108, "[LEX] IT::GetEntry: элемент таблицы идентификаторов не найден"),
		ERROR_ENTRY(109, "[LEX] IT::Delete: таблица идентификаторов отсутствует"),
		ERROR_ENTRY_NODEF10(110), ERROR_ENTRY_NODEF10(120), ERROR_ENTRY_NODEF10(130),
		ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150), ERROR_ENTRY_NODEF10(160),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),

		ERROR_ENTRY(200, "[SYN]: Неверная структура программы"),
		ERROR_ENTRY(201, "[SYN]: Ошибка в конструкции языка"),
		ERROR_ENTRY(202, "[SYN]: Ошибка в выражении"),
		ERROR_ENTRY(203, "[SYN]: Ошибка в параметрах функции"),
		ERROR_ENTRY(204, "[SYN]: Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(205, "[SYN]: Ошибка в операции"),
		ERROR_ENTRY(206, "[SYN]: Ошибка в условной конструкции"),
		ERROR_ENTRY_NODEF(207),
		ERROR_ENTRY_NODEF(208),
		ERROR_ENTRY_NODEF(209),
		ERROR_ENTRY_NODEF10(210), ERROR_ENTRY_NODEF10(220), ERROR_ENTRY_NODEF10(230),
		ERROR_ENTRY_NODEF10(240), ERROR_ENTRY_NODEF10(250), ERROR_ENTRY_NODEF10(260),
		ERROR_ENTRY_NODEF10(270), ERROR_ENTRY_NODEF10(280), ERROR_ENTRY_NODEF10(290),

		ERROR_ENTRY(300, "[SEM] Точка входа main обязана быть единожды инициализирована"),
		ERROR_ENTRY(301, "[SEM] Имя функции должно начинаться с заглавной буквы"), 
		ERROR_ENTRY(302, "[SEM] Несоответствие функции объявленной сигнатуре"), 
		ERROR_ENTRY(303, "[SEM] Ошибка дублирования имени идентификатора"), 
		ERROR_ENTRY(304, "[SEM] Ошибка использования необъявленного идентификатора"),
		ERROR_ENTRY_NODEF(305, "[SEM] Ошибка присваемого идентификатору значения"),

		ERROR_ENTRY(306, "[SEM] Ошибка несоответствия параметров вызываемой функции ее сигнатуре"),
		ERROR_ENTRY(307, "[SEM] Превышение допустимых пределов целочисленного литерала"),
		ERROR_ENTRY(308, "[SEM] Превышение допустимых пределов целочисленного беззнакового литерала"),
		ERROR_ENTRY(309, "[SEM] Превышение допустимых пределов символьного литерала"),
		ERROR_ENTRY_NODEF(310, "[SEM] "),

		ERROR_ENTRY(311, "[SEM] Превышение длины имени идентификатора"),
		ERROR_ENTRY_NODEF(312, "[SEM] "),
		ERROR_ENTRY(313, "[SEM] Ошибка использования несовместимых типов операндов в пределах одного выражения"),
		ERROR_ENTRY(314, "[SEM] Ошибка использования несовместимых типов операций в пределах одного выражения"),
		ERROR_ENTRY(315, "[SEM] В логическом выражении допустимо использования не более одного логического оператора"),
		ERROR_ENTRY_NODEF(316, "[SEM] "),
		ERROR_ENTRY_NODEF(317, "[SEM]"),
		ERROR_ENTRY_NODEF(318, "[SEM]"),
		ERROR_ENTRY_NODEF(319, "[SEM]"),
		ERROR_ENTRY_NODEF10(320), ERROR_ENTRY_NODEF10(330),
		ERROR_ENTRY_NODEF10(340), ERROR_ENTRY_NODEF10(350), ERROR_ENTRY_NODEF10(360),
		ERROR_ENTRY_NODEF10(370), ERROR_ENTRY_NODEF10(380), ERROR_ENTRY_NODEF10(390),

		ERROR_ENTRY_NODEF100(400),
		ERROR_ENTRY_NODEF100(500),

		ERROR_ENTRY_NODEF100(600),
		ERROR_ENTRY_NODEF100(700),
		ERROR_ENTRY_NODEF100(800)
	};

	ERROR GetError(int id) 
	{
		ERROR trouble;
		if (id < 0 || id > ERROR_MAX_ENTRY)
			trouble = errors[0];
		else
			trouble = errors[id];
		return trouble;
	}

	ERROR GetErrorIn(int id, int line = -1, int col = -1) 
	{
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

