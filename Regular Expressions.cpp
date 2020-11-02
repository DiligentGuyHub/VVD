#include "FST.h"

#define INT(string)			{	string, \
							4, \
							FST::NODE(1, FST::RELATION('i', 1)), \
							FST::NODE(1, FST::RELATION('n', 2)), \
							FST::NODE(1, FST::RELATION('t', 3)), \
							FST::NODE() \
}

#define PINT(string)		{	string, \
							5, \
							FST::NODE(1, FST::RELATION('p', 1)), \
							FST::NODE(1, FST::RELATION('i', 2)), \
							FST::NODE(1, FST::RELATION('n', 3)), \
							FST::NODE(1, FST::RELATION('t', 4)), \
							FST::NODE() \
}

#define SIGN(string)		{	string, \
							5, \
							FST::NODE(1, FST::RELATION('s', 1)), \
							FST::NODE(1, FST::RELATION('i', 2)), \
							FST::NODE(1, FST::RELATION('g', 3)), \
							FST::NODE(1, FST::RELATION('n', 4)), \
							FST::NODE() \
}

#define STRING(string) {	string, \
							7, \
							FST::NODE(1, FST::RELATION('s', 1)), \
							FST::NODE(1, FST::RELATION('t', 2)), \
							FST::NODE(1, FST::RELATION('r', 3)), \
							FST::NODE(1, FST::RELATION('i', 4)), \
							FST::NODE(1, FST::RELATION('n', 5)), \
							FST::NODE(1, FST::RELATION('g', 6)), \
							FST::NODE() \
}

#define BOOL(string)		{	string, \
							5, \
							FST::NODE(1, FST::RELATION('b', 1)), \
							FST::NODE(1, FST::RELATION('o', 2)), \
							FST::NODE(1, FST::RELATION('o', 3)), \
							FST::NODE(1, FST::RELATION('l', 4)), \
							FST::NODE() \
}

#define OP(string)	{           string, \
								2, \
								FST::NODE(4,\
								FST::RELATION('+', 1), \
								FST::RELATION('-', 1), \
								FST::RELATION('*', 1), \
								FST::RELATION('/', 1)), \
								FST::NODE() \
}

#define MORE(string) {			string, \
								2, \
								FST::NODE(1, FST::RELATION('>', 1)),\
								FST::NODE()\
}

#define LESS(string) {			string, \
								2, \
								FST::NODE(1, FST::RELATION('<', 1)),\
								FST::NODE()\
}

#define EQMORE(string) {		string, \
								3, \
								FST::NODE(1, FST::RELATION('>', 1)),\
								FST::NODE(1, FST::RELATION('=', 2)),\
								FST::NODE()\
}

#define EQLESS(string)	 {		string, \
								3, \
								FST::NODE(1, FST::RELATION('<', 1)),\
								FST::NODE(1, FST::RELATION('=', 2)),\
								FST::NODE()\
}

#define EQUALS(string)	{		string, \
								3, \
								FST::NODE(1, FST::RELATION('=', 1)),\
								FST::NODE(1, FST::RELATION('=', 2)),\
								FST::NODE()\
}

#define NEQUALS(string)	{		string, \
								3, \
								FST::NODE(1, FST::RELATION('!', 1)),\
								FST::NODE(1, FST::RELATION('=', 2)),\
								FST::NODE()\
}

#define INVERSION(string) {		string, \
								2, \
								FST::NODE(1,\
								FST::RELATION('~', 1)), \
								FST::NODE() \
}

#define CONJUCTION(string) {	string, \
								2, \
								FST::NODE(1,\
								FST::RELATION('&', 1)), \
								FST::NODE() \
}

#define DISJUNCTION(string) {	string, \
								2, \
								FST::NODE(1,\
								FST::RELATION('\\', 1)), \
								FST::NODE() \
}

#define EQ(string) { string, \
								2, \
								FST::NODE(1,\
								FST::RELATION('=', 1)), \
								FST::NODE() \
}

#define IF(string) { string, \
							3, \
							FST::NODE(1, FST::RELATION('i', 1)), \
							FST::NODE(1, FST::RELATION('f', 2)), \
							FST::NODE() \
}

#define ELIF(string) { string, \
							5, \
							FST::NODE(1, FST::RELATION('e', 1)), \
							FST::NODE(1, FST::RELATION('l', 2)), \
							FST::NODE(1, FST::RELATION('i', 3)), \
							FST::NODE(1, FST::RELATION('f', 4)), \
							FST::NODE() \
}

#define ELSE(string) { string, \
							5, \
							FST::NODE(1, FST::RELATION('e', 1)), \
							FST::NODE(1, FST::RELATION('l', 2)), \
							FST::NODE(1, FST::RELATION('s', 3)), \
							FST::NODE(1, FST::RELATION('e', 4)), \
							FST::NODE() \
}


#define ID(string)	{			string, \
								2, \
								FST::NODE(186,\
								FST::RELATION('a', 0), FST::RELATION('b', 0), \
								FST::RELATION('A', 0), FST::RELATION('B', 0), \
								FST::RELATION('c', 0), FST::RELATION('d', 0), \
								FST::RELATION('C', 0), FST::RELATION('D', 0), \
								FST::RELATION('e', 0), FST::RELATION('f', 0), \
								FST::RELATION('E', 0), FST::RELATION('F', 0), \
								FST::RELATION('g', 0), FST::RELATION('h', 0), \
								FST::RELATION('G', 0), FST::RELATION('H', 0), \
								FST::RELATION('i', 0), FST::RELATION('j', 0), \
								FST::RELATION('I', 0), FST::RELATION('J', 0), \
								FST::RELATION('k', 0), FST::RELATION('l', 0), \
								FST::RELATION('K', 0), FST::RELATION('L', 0), \
								FST::RELATION('m', 0), FST::RELATION('n', 0), \
								FST::RELATION('M', 0), FST::RELATION('N', 0), \
								FST::RELATION('o', 0), FST::RELATION('p', 0), \
								FST::RELATION('O', 0), FST::RELATION('P', 0), \
								FST::RELATION('q', 0), FST::RELATION('r', 0), \
								FST::RELATION('Q', 0), FST::RELATION('R', 0), \
								FST::RELATION('s', 0), FST::RELATION('t', 0), \
								FST::RELATION('S', 0), FST::RELATION('T', 0), \
								FST::RELATION('u', 0), FST::RELATION('v', 0), \
								FST::RELATION('U', 0), FST::RELATION('V', 0), \
								FST::RELATION('w', 0), FST::RELATION('x', 0), \
								FST::RELATION('W', 0), FST::RELATION('X', 0), \
								FST::RELATION('y', 0), FST::RELATION('z', 0), \
								FST::RELATION('Y', 0), FST::RELATION('Z', 0), \
								FST::RELATION('0', 0), FST::RELATION('1', 0), \
								FST::RELATION('2', 0), FST::RELATION('3', 0), \
								FST::RELATION('4', 0), FST::RELATION('5', 0), \
								FST::RELATION('6', 0), FST::RELATION('7', 0), \
								FST::RELATION('8', 0), FST::RELATION('9', 0), \
								FST::RELATION('a', 1), FST::RELATION('b', 1), \
								FST::RELATION('A', 1), FST::RELATION('B', 1), \
								FST::RELATION('c', 1), FST::RELATION('d', 1), \
								FST::RELATION('C', 1), FST::RELATION('D', 1), \
								FST::RELATION('e', 1), FST::RELATION('f', 1), \
								FST::RELATION('E', 1), FST::RELATION('F', 1), \
								FST::RELATION('g', 1), FST::RELATION('h', 1), \
								FST::RELATION('G', 1), FST::RELATION('H', 1), \
								FST::RELATION('i', 1), FST::RELATION('j', 1), \
								FST::RELATION('I', 1), FST::RELATION('J', 1), \
								FST::RELATION('k', 1), FST::RELATION('l', 1), \
								FST::RELATION('K', 1), FST::RELATION('L', 1), \
								FST::RELATION('m', 1), FST::RELATION('n', 1), \
								FST::RELATION('M', 1), FST::RELATION('N', 1), \
								FST::RELATION('o', 1), FST::RELATION('p', 1), \
								FST::RELATION('O', 1), FST::RELATION('P', 1), \
								FST::RELATION('q', 1), FST::RELATION('r', 1), \
								FST::RELATION('Q', 1), FST::RELATION('R', 1), \
								FST::RELATION('s', 1), FST::RELATION('t', 1), \
								FST::RELATION('S', 1), FST::RELATION('T', 1), \
								FST::RELATION('u', 1), FST::RELATION('v', 1), \
								FST::RELATION('U', 1), FST::RELATION('V', 1), \
								FST::RELATION('w', 1), FST::RELATION('x', 1), \
								FST::RELATION('W', 1), FST::RELATION('X', 1), \
								FST::RELATION('y', 1), FST::RELATION('z', 1), \
								FST::RELATION('Y', 1), FST::RELATION('Z', 1), \
								FST::RELATION('0', 1), FST::RELATION('1', 1), \
								FST::RELATION('2', 1), FST::RELATION('3', 1), \
								FST::RELATION('4', 1), FST::RELATION('5', 1), \
								FST::RELATION('6', 1), FST::RELATION('7', 1), \
								FST::RELATION('8', 1), FST::RELATION('9', 1), \
								FST::RELATION('a', 2), FST::RELATION('b', 2), \
								FST::RELATION('A', 2), FST::RELATION('B', 2), \
								FST::RELATION('c', 2), FST::RELATION('d', 2), \
								FST::RELATION('C', 2), FST::RELATION('D', 2), \
								FST::RELATION('e', 2), FST::RELATION('f', 2), \
								FST::RELATION('E', 2), FST::RELATION('F', 2), \
								FST::RELATION('g', 2), FST::RELATION('h', 2), \
								FST::RELATION('G', 2), FST::RELATION('H', 2), \
								FST::RELATION('i', 2), FST::RELATION('j', 2), \
								FST::RELATION('I', 2), FST::RELATION('J', 2), \
								FST::RELATION('k', 2), FST::RELATION('l', 2), \
								FST::RELATION('K', 2), FST::RELATION('L', 2), \
								FST::RELATION('m', 2), FST::RELATION('n', 2), \
								FST::RELATION('M', 2), FST::RELATION('N', 2), \
								FST::RELATION('o', 2), FST::RELATION('p', 2), \
								FST::RELATION('O', 2), FST::RELATION('P', 2), \
								FST::RELATION('q', 2), FST::RELATION('r', 2), \
								FST::RELATION('Q', 2), FST::RELATION('R', 2), \
								FST::RELATION('s', 2), FST::RELATION('t', 2), \
								FST::RELATION('S', 2), FST::RELATION('T', 2), \
								FST::RELATION('u', 2), FST::RELATION('v', 2), \
								FST::RELATION('U', 2), FST::RELATION('V', 2), \
								FST::RELATION('w', 2), FST::RELATION('x', 2), \
								FST::RELATION('W', 2), FST::RELATION('X', 2), \
								FST::RELATION('y', 2), FST::RELATION('z', 2), \
								FST::RELATION('Y', 2), FST::RELATION('Z', 2), \
								FST::RELATION('0', 2), FST::RELATION('1', 2), \
								FST::RELATION('2', 2), FST::RELATION('3', 2), \
								FST::RELATION('4', 2), FST::RELATION('5', 2), \
								FST::RELATION('6', 2), FST::RELATION('7', 2), \
								FST::RELATION('8', 2), FST::RELATION('9', 2) \
								),\
								FST::NODE() \
}

#define FUNCTION(string){	string, \
							9, \
							FST::NODE(1, FST::RELATION('f', 1)), \
							FST::NODE(1, FST::RELATION('u', 2)), \
							FST::NODE(1, FST::RELATION('n', 3)), \
							FST::NODE(1, FST::RELATION('c', 4)), \
							FST::NODE(1, FST::RELATION('t', 5)), \
							FST::NODE(1, FST::RELATION('i', 6)), \
							FST::NODE(1, FST::RELATION('o', 7)), \
							FST::NODE(1, FST::RELATION('n', 8)), \
							FST::NODE() \
}

#define DEF(string) {	string, \
							4, \
							FST::NODE(1, FST::RELATION('d', 1)), \
							FST::NODE(1, FST::RELATION('e', 2)), \
							FST::NODE(1, FST::RELATION('f', 3)), \
							FST::NODE() \
}

#define MAIN(string) {		string, \
							5, \
							FST::NODE(1, FST::RELATION('m', 1)), \
							FST::NODE(1, FST::RELATION('a', 2)), \
							FST::NODE(1, FST::RELATION('i', 3)), \
							FST::NODE(1, FST::RELATION('n', 4)), \
							FST::NODE() \
}

#define PRINT(string) {		string, \
							6, \
							FST::NODE(1, FST::RELATION('p', 1)), \
							FST::NODE(1, FST::RELATION('r', 2)), \
							FST::NODE(1, FST::RELATION('i', 3)), \
							FST::NODE(1, FST::RELATION('n', 4)), \
							FST::NODE(1, FST::RELATION('t', 5)), \
							FST::NODE() \
}

#define RETURN(string) {	string, \
							7, \
							FST::NODE(1, FST::RELATION('r', 1)), \
							FST::NODE(1, FST::RELATION('e', 2)), \
							FST::NODE(1, FST::RELATION('t', 3)), \
							FST::NODE(1, FST::RELATION('u', 4)), \
							FST::NODE(1, FST::RELATION('r', 5)), \
							FST::NODE(1, FST::RELATION('n', 6)), \
							FST::NODE() \
}

#define SEMICOLON(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION(';',1)), \
							FST::NODE() \
}

#define COMMA(string) {		string, \
							2, \
							FST::NODE(1, FST::RELATION(',',1)), \
							FST::NODE() \
}

#define SEMICOLON(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION(';',1)), \
							FST::NODE() \
}

#define LEFTBRACE(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION('{',1)), \
							FST::NODE() \
}

#define BRACELET(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION('}',1)), \
							FST::NODE() \
}

#define LEFTHESIS(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION('(',1)), \
							FST::NODE() \
}

#define RIGHTHESIS(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION(')',1)), \
							FST::NODE() \
}

#define PLUS(string) {		string, \
							2, \
							FST::NODE(1, FST::RELATION('+',1)), \
							FST::NODE() \
}

#define MINUS(string) {		string, \
							2, \
							FST::NODE(1, FST::RELATION('-',1)), \
							FST::NODE() \
}

#define STAR(string) {		string, \
							2, \
							FST::NODE(1, FST::RELATION('*',1)), \
							FST::NODE() \
}

#define DIRSLASH(string) { string, \
							2, \
							FST::NODE(1, FST::RELATION('/',1)), \
							FST::NODE() \
}

#define NUMBER(string) {  string, \
						  2, \
						  FST::NODE(30, FST::RELATION('1', 0), FST::RELATION('2', 0), \
										FST::RELATION('3', 0), FST::RELATION('4', 0), \
										FST::RELATION('5', 0), FST::RELATION('6', 0), \
										FST::RELATION('7', 0), FST::RELATION('8', 0), \
										FST::RELATION('9', 0), FST::RELATION('0', 0), \
										FST::RELATION('1', 1), FST::RELATION('2', 1), \
										FST::RELATION('3', 1), FST::RELATION('4', 1), \
										FST::RELATION('5', 1), FST::RELATION('6', 1), \
										FST::RELATION('7', 1), FST::RELATION('8', 1), \
										FST::RELATION('9', 1), FST::RELATION('0', 1), \
										FST::RELATION('1', 2), FST::RELATION('2', 2), \
										FST::RELATION('3', 2), FST::RELATION('4', 2), \
										FST::RELATION('5', 2), FST::RELATION('6', 2), \
										FST::RELATION('7', 2), FST::RELATION('8', 2), \
										FST::RELATION('9', 2), FST::RELATION('0', 2)),\
						  FST::NODE() \
}
#define LITERAL(string) { string, \
							4, \
							FST::NODE(1,	FST::RELATION('"',1)), \
							FST::NODE(203,	FST::RELATION('!', 1), \
											FST::RELATION('a', 1), FST::RELATION('b', 1), \
											FST::RELATION('c', 1), FST::RELATION('d', 1), \
											FST::RELATION('e', 1), FST::RELATION('f', 1), \
											FST::RELATION('g', 1), FST::RELATION('h', 1), \
											FST::RELATION('i', 1), FST::RELATION('j', 1), \
											FST::RELATION('k', 1), FST::RELATION('l', 1), \
											FST::RELATION('m', 1), FST::RELATION('n', 1), \
											FST::RELATION('o', 1), FST::RELATION('p', 1), \
											FST::RELATION('q', 1), FST::RELATION('r', 1), \
											FST::RELATION('s', 1), FST::RELATION('t', 1), \
											FST::RELATION('u', 1), FST::RELATION('v', 1), \
											FST::RELATION('w', 1), FST::RELATION('x', 1), \
											FST::RELATION('y', 1), FST::RELATION('z', 1), \
											FST::RELATION('à', 1), FST::RELATION('í', 1), \
											FST::RELATION('á', 1), FST::RELATION('î', 1), \
											FST::RELATION('â', 1), FST::RELATION('ï', 1), \
											FST::RELATION('ã', 1), FST::RELATION('ð', 1), \
											FST::RELATION('ä', 1), FST::RELATION('ñ', 1), \
											FST::RELATION('å', 1), FST::RELATION('ò', 1), \
											FST::RELATION('¸', 1), FST::RELATION('ó', 1), \
											FST::RELATION('æ', 1), FST::RELATION('ô', 1), \
											FST::RELATION('ç', 1), FST::RELATION('õ', 1), \
											FST::RELATION('è', 1), FST::RELATION('ö', 1), \
											FST::RELATION('é', 1), FST::RELATION('÷', 1), \
											FST::RELATION('ê', 1), FST::RELATION('ø', 1), \
											FST::RELATION('ë', 1), FST::RELATION('ù', 1), \
											FST::RELATION('ì', 1), FST::RELATION('ü', 1), \
											FST::RELATION('ú', 1), FST::RELATION('û', 1), \
											FST::RELATION('ý', 1), FST::RELATION('þ', 1), \
											FST::RELATION('ÿ', 1), \
											FST::RELATION('+', 1), FST::RELATION('-', 1), \
											FST::RELATION('/', 1), FST::RELATION('*', 1), \
											FST::RELATION('A', 1), FST::RELATION('B', 1), \
											FST::RELATION('C', 1), FST::RELATION('D', 1), \
											FST::RELATION('E', 1), FST::RELATION('F', 1), \
											FST::RELATION('G', 1), FST::RELATION('H', 1), \
											FST::RELATION('I', 1), FST::RELATION('J', 1), \
											FST::RELATION('K', 1), FST::RELATION('L', 1), \
											FST::RELATION('M', 1), FST::RELATION('N', 1), \
											FST::RELATION('O', 1), FST::RELATION('P', 1), \
											FST::RELATION('Q', 1), FST::RELATION('R', 1), \
											FST::RELATION('S', 1), FST::RELATION('T', 1), \
											FST::RELATION('U', 1), FST::RELATION('V', 1), \
											FST::RELATION('W', 1), FST::RELATION('X', 1), \
											FST::RELATION('Y', 1), FST::RELATION('Z', 1), \
											FST::RELATION('1', 1), FST::RELATION('2', 1), \
											FST::RELATION('3', 1), FST::RELATION('4', 1), \
											FST::RELATION('5', 1), FST::RELATION('6', 1), \
											FST::RELATION('7', 1), FST::RELATION('8', 1), \
											FST::RELATION('9', 1), FST::RELATION('0', 1), \
											FST::RELATION('!', 2), \
											FST::RELATION(' ', 1), FST::RELATION(' ', 2), \
											FST::RELATION('a', 2), FST::RELATION('b', 2), \
											FST::RELATION('c', 2), FST::RELATION('d', 2), \
											FST::RELATION('e', 2), FST::RELATION('f', 2), \
											FST::RELATION('g', 2), FST::RELATION('h', 2), \
											FST::RELATION('i', 2), FST::RELATION('j', 2), \
											FST::RELATION('k', 2), FST::RELATION('l', 2), \
											FST::RELATION('m', 2), FST::RELATION('n', 2), \
											FST::RELATION('o', 2), FST::RELATION('p', 2), \
											FST::RELATION('q', 2), FST::RELATION('r', 2), \
											FST::RELATION('s', 2), FST::RELATION('t', 2), \
											FST::RELATION('u', 2), FST::RELATION('v', 2), \
											FST::RELATION('w', 2), FST::RELATION('x', 2), \
											FST::RELATION('y', 2), FST::RELATION('z', 2), \
											FST::RELATION('à', 2), FST::RELATION('í', 2), \
											FST::RELATION('á', 2), FST::RELATION('î', 2), \
											FST::RELATION('â', 2), FST::RELATION('ï', 2), \
											FST::RELATION('ã', 2), FST::RELATION('ð', 2), \
											FST::RELATION('ä', 2), FST::RELATION('ñ', 2), \
											FST::RELATION('å', 2), FST::RELATION('ò', 2), \
											FST::RELATION('¸', 2), FST::RELATION('ó', 2), \
											FST::RELATION('æ', 2), FST::RELATION('ô', 2), \
											FST::RELATION('ç', 2), FST::RELATION('õ', 2), \
											FST::RELATION('è', 2), FST::RELATION('ö', 2), \
											FST::RELATION('é', 2), FST::RELATION('÷', 2), \
											FST::RELATION('ê', 2), FST::RELATION('ø', 2), \
											FST::RELATION('ë', 2), FST::RELATION('ù', 2), \
											FST::RELATION('ì', 2), FST::RELATION('ü', 2), \
											FST::RELATION('ú', 2), FST::RELATION('û', 2), \
											FST::RELATION('ý', 2), FST::RELATION('þ', 2), \
											FST::RELATION('ÿ', 2), \
											FST::RELATION('+', 2), FST::RELATION('-', 2), \
											FST::RELATION('/', 2), FST::RELATION('*', 2), \
											FST::RELATION('A', 2), FST::RELATION('B', 2), \
											FST::RELATION('C', 2), FST::RELATION('D', 2), \
											FST::RELATION('E', 2), FST::RELATION('F', 2), \
											FST::RELATION('G', 2), FST::RELATION('H', 2), \
											FST::RELATION('I', 2), FST::RELATION('J', 2), \
											FST::RELATION('K', 2), FST::RELATION('L', 2), \
											FST::RELATION('M', 2), FST::RELATION('N', 2), \
											FST::RELATION('O', 2), FST::RELATION('P', 2), \
											FST::RELATION('Q', 2), FST::RELATION('R', 2), \
											FST::RELATION('S', 2), FST::RELATION('T', 2), \
											FST::RELATION('U', 2), FST::RELATION('V', 2), \
											FST::RELATION('W', 2), FST::RELATION('X', 2), \
											FST::RELATION('Y', 2), FST::RELATION('Z', 2), \
											FST::RELATION('1', 2), FST::RELATION('2', 2), \
											FST::RELATION('3', 2), FST::RELATION('4', 2), \
											FST::RELATION('5', 2), FST::RELATION('6', 2), \
											FST::RELATION('7', 2), FST::RELATION('8', 2), \
											FST::RELATION('9', 2), FST::RELATION('0', 2) \
											),\
											FST::NODE(1, FST::RELATION('"',3)), \
											FST::NODE() \
}