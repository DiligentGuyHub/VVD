#include "Error.h"

namespace Error {

	ERROR errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY(113, "Ошибка при открытии файла вывода (-out)"),

		ERROR_ENTRY(114, "LT::Create: превышен размер максимальной емкости таблицы лексем"),
		ERROR_ENTRY(115, "LT::Add: переполнение таблицы лексем"),
		ERROR_ENTRY(116, "LT::CreateEntry: запрещено вторичное обновление типа данных"),
		ERROR_ENTRY(117, "LT::GetEntry: элемент не найден"),
		ERROR_ENTRY(118, "LT::Delete: таблица отсутствует"),
		ERROR_ENTRY(119, "LT::CreateEntry: main не может быть инициализирован дважды"),
		ERROR_ENTRY(120, "LT::CreateEntry: main обязан быть иницилизирован"),
		ERROR_ENTRY(121, "LT::CreateEntry: идентификатор не может быть объявлен без типа данных "),
		ERROR_ENTRY(122, "IT::Create: превышен размер максимальной емкости таблицы идентификаторов"),
		ERROR_ENTRY(123, "IT::Add: переполнение таблицы идентификаторов"),
		ERROR_ENTRY(124, "IT::GetEntry: элемент таблицы идентификаторов не найден"),
		ERROR_ENTRY(125, "IT::Delete: таблица отсутствует"),
		ERROR_ENTRY(126, "IT::UpdatePrevious: ошибка инциализации из-за несоответствия типов данных"),

		ERROR_ENTRY(127, "LT::CreateEntry: else задан без if"),
		ERROR_ENTRY_NODEF(128, ""),
		ERROR_ENTRY_NODEF(129, ""),
		ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY_NODEF10(160), ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY_NODEF100(600), ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900),
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

