#include "Output.h"


using namespace std;

namespace Out {
	char simbols[11] = { '+', '-', '/',  '*',  '=',  '(',  ')',  '{',  '}',  ';',  ',' };

	char* DeleteSimbol(char* text, int position) {
		for (int i = position; char(text[i]) != '\0'; i++) {
			text[i] = text[i + 1];
		}
		return text;
	}

	void Output(IN input, char outfile[]) {
		ofstream file(outfile);

		if (!file.is_open())
			throw ERROR_THROW(113);
		/*if (text[in_text.size - 1] == ')' || text[in_text.size - 1] == ';' || text[in_text.size - 1] == '{' || text[in_text.size - 1] == '}') {
			text[in_text.size + 1] = in_text.code[simbol];
			text[in_text.size] = '|';
			in_text.size += 2;
			position += 2;
		}*/

		/*for (int i = 0; char(input.text[i]) != '\0'; i++) {
			if (input.text[i] == '\n') {
				if (input.text[i - 1] == ')' || input.text[i - 1] == ';' || input.text[i - 1] == '{' || input.text[i - 1] == '}') {

				}
			}
		}*/

		for (int x = 0, i; x < 11; x++) {
			for (i = 0; char(input.text[i]) != '\0'; i++) {
				if (input.text[i] == simbols[x]) {
					if (input.text[i + 1] == ' ' && input.text[i - 1] == ' ') {
						input.text = DeleteSimbol(input.text, i - 1);
						input.text = DeleteSimbol(input.text, i);
					}
					else if (input.text[i + 1] == ' ') {
						input.text = DeleteSimbol(input.text, i + 1);
					}
					else if (input.text[i - 1] == ' ') {
						input.text = DeleteSimbol(input.text, i - 1);
					}


				}
			}
			input.text[i + 1] = '\0';
		}

		//cout << "\nЗапись завершена\n";
		//cout << "Ошибок не обнаружено\n";
		file << input.text;
	}
}