#pragma once
#include "VVD.h"

#define IN_MAX_LEN_TEXT 1024*1024
#define IN_CODE_NULL '\0'
#define ENDL '\n'
#define SPACE ' '

#define IN_CODE_TABLE {\
	/*0*/ IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::I,	IN::T,	ENDL,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*16*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*32*/SPACE,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*48*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*64*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*80*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*96*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*112*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	\
	/*128*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*144*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*160*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*176*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*192*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*208*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*224*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	/*240*/IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,	IN::T,\
	} // таблица допустимых, запрещенных и заменяемых символов на основе таблицы ASCII

namespace In {

	struct IN {
		enum { T = 1024, F = 2048, I = 4096, S = 8192 }; // true, false, ignor
		int size; // количество символов
		int lines; // количество строк
		int ignor; // число игнорируемых элементов
		char* text; // указатель на беззнаковую строку
		int code[256] = IN_CODE_TABLE; // массив с кодовой таблицей из макроопределения IN_CODE_TABLE
	};

	IN GetIn(char infile[]);

}