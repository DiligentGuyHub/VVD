#include "VVD.h"
#include "Input.h"
#include "Error.h"
#include "Parameters.h"

namespace In {

	bool readExtraSimbols = false;

	IN GetIn(char infile[]) {
		IN in_text;
		in_text.ignor = 0;
		in_text.lines = 1;
		in_text.size = 0;
		int position = 1;
		char* text = new char[IN_MAX_LEN_TEXT];

		std::ifstream file(infile);

		if (!file.is_open())
			throw ERROR_THROW(4);

		while (in_text.size < IN_MAX_LEN_TEXT && !file.eof()) {
			char read;
			file.get(read);
			unsigned char simbol = read;
			if (file.eof()) {
				text[in_text.size] = IN_CODE_NULL;
				in_text.lines++;
				break;
			}

			switch (in_text.code[simbol]) {
			case in_text.T:
				if (simbol == '\'')
					readExtraSimbols = !readExtraSimbols;

				text[in_text.size] = simbol;
				in_text.size++;
				position++;
				break;
			case in_text.I:
				in_text.ignor++;
				break;
			case '\n':
				text[in_text.size] = '|';
				in_text.size += 1;
				position += 1;
				break;
			case ' ':
				if (text[in_text.size - 1] != ' ' || readExtraSimbols == true) {
					text[in_text.size] = simbol;
					in_text.size++;
					position++;
				}
				break;
			case in_text.F:
				throw ERROR_THROW_IN(5, in_text.lines, position)
			default:
				text[in_text.size] = in_text.code[simbol];
				in_text.size++;
				position++;
				break;
			}
			if (simbol == ENDL) {
				in_text.lines++;
				position = 1;
			}
		}
		in_text.text = text;
		return in_text;
	}

}