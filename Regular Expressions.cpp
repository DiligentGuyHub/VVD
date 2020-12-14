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

#define TRUE(string)		{	string, \
							5, \
							FST::NODE(1, FST::RELATION('T', 1)), \
							FST::NODE(1, FST::RELATION('r', 2)), \
							FST::NODE(1, FST::RELATION('u', 3)), \
							FST::NODE(1, FST::RELATION('e', 4)), \
							FST::NODE() \
}
	
#define FALSE(string)		{	string, \
							6, \
							FST::NODE(1, FST::RELATION('F', 1)), \
							FST::NODE(1, FST::RELATION('a', 2)), \
							FST::NODE(1, FST::RELATION('l', 3)), \
							FST::NODE(1, FST::RELATION('s', 4)), \
							FST::NODE(1, FST::RELATION('e', 5)), \
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

#define NUMBER10(string) {	string, \
							2, \
							FST::NODE(30,	\
											FST::RELATION('1', 0), FST::RELATION('2', 0), \
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

#define NEG_NUMBER10(string) {	string, \
							3, \
							FST::NODE(1,	FST::RELATION('-', 1)),\
							FST::NODE(30,	\
											FST::RELATION('1', 1), FST::RELATION('2', 1), \
											FST::RELATION('3', 1), FST::RELATION('4', 1), \
											FST::RELATION('5', 1), FST::RELATION('6', 1), \
											FST::RELATION('7', 1), FST::RELATION('8', 1), \
											FST::RELATION('9', 1), FST::RELATION('0', 1), \
											FST::RELATION('1', 2), FST::RELATION('2', 2), \
											FST::RELATION('3', 2), FST::RELATION('4', 2), \
											FST::RELATION('5', 2), FST::RELATION('6', 2), \
											FST::RELATION('7', 2), FST::RELATION('8', 2), \
											FST::RELATION('9', 2), FST::RELATION('0', 2), \
											FST::RELATION('1', 3), FST::RELATION('2', 3), \
											FST::RELATION('3', 3), FST::RELATION('4', 3), \
											FST::RELATION('5', 3), FST::RELATION('6', 3), \
											FST::RELATION('7', 3), FST::RELATION('8', 3), \
											FST::RELATION('9', 3), FST::RELATION('0', 3)),\
						  FST::NODE() \
}

#define NUMBER2(string) { string, \
						  4, \
						  FST::NODE(1,	FST::RELATION('2', 1)), \
						  FST::NODE(1,	FST::RELATION('.', 2)),	\
						  FST::NODE(6,	FST::RELATION('1', 2), FST::RELATION('0', 2), \
										FST::RELATION('1', 3), FST::RELATION('0', 3), \
										FST::RELATION('1', 4), FST::RELATION('0', 4)), \
						  FST::NODE()\
}


#define NEG_NUMBER2(string) { string, \
						  5, \
							  FST::NODE(1,	FST::RELATION('-', 1)),\
							  FST::NODE(1,	FST::RELATION('2', 2)), \
							  FST::NODE(1,	FST::RELATION('.', 3)),	\
							  FST::NODE(6,	FST::RELATION('1', 3), FST::RELATION('0', 3), \
											FST::RELATION('1', 4), FST::RELATION('0', 4), \
											FST::RELATION('1', 5), FST::RELATION('0', 5)), \
							  FST::NODE()\
}

#define NUMBER8(string) {  string, \
						  4, \
						  FST::NODE(1,	FST::RELATION('8', 1)), \
						  FST::NODE(1,	FST::RELATION('.', 2)),	\
						  FST::NODE(24,	FST::RELATION('1', 2), FST::RELATION('0', 2), \
										FST::RELATION('2', 2), FST::RELATION('7', 2), \
										FST::RELATION('3', 2), FST::RELATION('6', 2), \
										FST::RELATION('4', 2), FST::RELATION('5', 2), \
										FST::RELATION('1', 3), FST::RELATION('0', 3), \
										FST::RELATION('2', 3), FST::RELATION('7', 3), \
										FST::RELATION('3', 3), FST::RELATION('6', 3), \
										FST::RELATION('4', 3), FST::RELATION('5', 3), \
										FST::RELATION('1', 4), FST::RELATION('0', 4), \
										FST::RELATION('2', 4), FST::RELATION('7', 4), \
										FST::RELATION('3', 4), FST::RELATION('6', 4), \
										FST::RELATION('4', 4), FST::RELATION('5', 4)), \
						  FST::NODE()\
}

#define NEG_NUMBER8(string) {  string, \
						  5, \
						  FST::NODE(1,	FST::RELATION('-', 1)),\
						  FST::NODE(1,	FST::RELATION('8', 2)), \
						  FST::NODE(1,	FST::RELATION('.', 3)),	\
						  FST::NODE(24,	FST::RELATION('1', 3), FST::RELATION('0', 3), \
										FST::RELATION('2', 3), FST::RELATION('7', 3), \
										FST::RELATION('3', 3), FST::RELATION('6', 3), \
										FST::RELATION('4', 3), FST::RELATION('5', 3), \
										FST::RELATION('1', 4), FST::RELATION('0', 4), \
										FST::RELATION('2', 4), FST::RELATION('7', 4), \
										FST::RELATION('3', 4), FST::RELATION('6', 4), \
										FST::RELATION('4', 4), FST::RELATION('5', 4), \
										FST::RELATION('1', 5), FST::RELATION('0', 5), \
										FST::RELATION('2', 5), FST::RELATION('7', 5), \
										FST::RELATION('3', 5), FST::RELATION('6', 5), \
										FST::RELATION('4', 5), FST::RELATION('5', 5)), \
						  FST::NODE()\
}

#define INV_NUMBER8(string) {  string, \
						  5, \
						  FST::NODE(1,	FST::RELATION('~', 1)),\
						  FST::NODE(1,	FST::RELATION('8', 2)), \
						  FST::NODE(1,	FST::RELATION('.', 3)),	\
						  FST::NODE(24,	FST::RELATION('1', 3), FST::RELATION('0', 3), \
										FST::RELATION('2', 3), FST::RELATION('7', 3), \
										FST::RELATION('3', 3), FST::RELATION('6', 3), \
										FST::RELATION('4', 3), FST::RELATION('5', 3), \
										FST::RELATION('1', 4), FST::RELATION('0', 4), \
										FST::RELATION('2', 4), FST::RELATION('7', 4), \
										FST::RELATION('3', 4), FST::RELATION('6', 4), \
										FST::RELATION('4', 4), FST::RELATION('5', 4), \
										FST::RELATION('1', 5), FST::RELATION('0', 5), \
										FST::RELATION('2', 5), FST::RELATION('7', 5), \
										FST::RELATION('3', 5), FST::RELATION('6', 5), \
										FST::RELATION('4', 5), FST::RELATION('5', 5)), \
						  FST::NODE()\
}


#define INV_NUMBER2(string) { string, \
						  5, \
							  FST::NODE(1,	FST::RELATION('~', 1)),\
							  FST::NODE(1,	FST::RELATION('2', 2)), \
							  FST::NODE(1,	FST::RELATION('.', 3)),	\
							  FST::NODE(6,	FST::RELATION('1', 3), FST::RELATION('0', 3), \
											FST::RELATION('1', 4), FST::RELATION('0', 4), \
											FST::RELATION('1', 5), FST::RELATION('0', 5)), \
							  FST::NODE()\
}

#define INV_NUMBER10(string) {	string, \
							3, \
							FST::NODE(1,	FST::RELATION('~', 1)),\
							FST::NODE(30,	\
											FST::RELATION('1', 1), FST::RELATION('2', 1), \
											FST::RELATION('3', 1), FST::RELATION('4', 1), \
											FST::RELATION('5', 1), FST::RELATION('6', 1), \
											FST::RELATION('7', 1), FST::RELATION('8', 1), \
											FST::RELATION('9', 1), FST::RELATION('0', 1), \
											FST::RELATION('1', 2), FST::RELATION('2', 2), \
											FST::RELATION('3', 2), FST::RELATION('4', 2), \
											FST::RELATION('5', 2), FST::RELATION('6', 2), \
											FST::RELATION('7', 2), FST::RELATION('8', 2), \
											FST::RELATION('9', 2), FST::RELATION('0', 2), \
											FST::RELATION('1', 3), FST::RELATION('2', 3), \
											FST::RELATION('3', 3), FST::RELATION('4', 3), \
											FST::RELATION('5', 3), FST::RELATION('6', 3), \
											FST::RELATION('7', 3), FST::RELATION('8', 3), \
											FST::RELATION('9', 3), FST::RELATION('0', 3)),\
						  FST::NODE() \
}

// 66
//#define CYRILLIC(n)\
//										FST::RELATION('à', n), FST::RELATION('í', n), \
//										FST::RELATION('á', n), FST::RELATION('î', n), \
//										FST::RELATION('â', n), FST::RELATION('ï', n), \
//										FST::RELATION('ã', n), FST::RELATION('ð', n), \
//										FST::RELATION('ä', n), FST::RELATION('ñ', n), \
//										FST::RELATION('å', n), FST::RELATION('ò', n), \
//										FST::RELATION('¸', n), FST::RELATION('ó', n), \
//										FST::RELATION('æ', n), FST::RELATION('ô', n), \
//										FST::RELATION('ç', n), FST::RELATION('õ', n), \
//										FST::RELATION('è', n), FST::RELATION('ö', n), \
//										FST::RELATION('é', n), FST::RELATION('÷', n), \
//										FST::RELATION('ê', n), FST::RELATION('ø', n), \
//										FST::RELATION('ë', n), FST::RELATION('ù', n), \
//										FST::RELATION('ì', n), FST::RELATION('ü', n), \
//										FST::RELATION('ú', n), FST::RELATION('û', n), \
//										FST::RELATION('ý', n), FST::RELATION('þ', n), \
//										FST::RELATION('ÿ', n), \
//										FST::RELATION('À', n), FST::RELATION('Í', n), \
//										FST::RELATION('Á', n), FST::RELATION('Î', n), \
//										FST::RELATION('Â', n), FST::RELATION('Ï', n), \
//										FST::RELATION('Ã', n), FST::RELATION('Ð', n), \
//										FST::RELATION('Ä', n), FST::RELATION('Ñ', n), \
//										FST::RELATION('Å', n), FST::RELATION('Ò', n), \
//										FST::RELATION('¨', n), FST::RELATION('Ó', n), \
//										FST::RELATION('Æ', n), FST::RELATION('Ô', n), \
//										FST::RELATION('Ç', n), FST::RELATION('Õ', n), \
//										FST::RELATION('È', n), FST::RELATION('Ö', n), \
//										FST::RELATION('É', n), FST::RELATION('×', n), \
//										FST::RELATION('Ê', n), FST::RELATION('Ø', n), \
//										FST::RELATION('Ë', n), FST::RELATION('Ù', n), \
//										FST::RELATION('Ì', n), FST::RELATION('Ü', n), \
//										FST::RELATION('Ú', n), FST::RELATION('Û', n), \
//										FST::RELATION('Ý', n), FST::RELATION('Þ', n), \
//										FST::RELATION('ß', n) \

// 52
#define LATIN(n)\
										FST::RELATION('a', n), FST::RELATION('b', n), \
										FST::RELATION('c', n), FST::RELATION('d', n), \
										FST::RELATION('e', n), FST::RELATION('f', n), \
										FST::RELATION('g', n), FST::RELATION('h', n), \
										FST::RELATION('i', n), FST::RELATION('j', n), \
										FST::RELATION('k', n), FST::RELATION('l', n), \
										FST::RELATION('m', n), FST::RELATION('n', n), \
										FST::RELATION('o', n), FST::RELATION('p', n), \
										FST::RELATION('q', n), FST::RELATION('r', n), \
										FST::RELATION('s', n), FST::RELATION('t', n), \
										FST::RELATION('u', n), FST::RELATION('v', n), \
										FST::RELATION('w', n), FST::RELATION('x', n), \
										FST::RELATION('y', n), FST::RELATION('z', n), \
										FST::RELATION('A', n), FST::RELATION('B', n), \
										FST::RELATION('C', n), FST::RELATION('D', n), \
										FST::RELATION('E', n), FST::RELATION('F', n), \
										FST::RELATION('G', n), FST::RELATION('H', n), \
										FST::RELATION('I', n), FST::RELATION('J', n), \
										FST::RELATION('K', n), FST::RELATION('L', n), \
										FST::RELATION('M', n), FST::RELATION('N', n), \
										FST::RELATION('O', n), FST::RELATION('P', n), \
										FST::RELATION('Q', n), FST::RELATION('R', n), \
										FST::RELATION('S', n), FST::RELATION('T', n), \
										FST::RELATION('U', n), FST::RELATION('V', n), \
										FST::RELATION('W', n), FST::RELATION('X', n), \
										FST::RELATION('Y', n), FST::RELATION('Z', n)
// 18
#define NUMSANDOPS(n)\
										FST::RELATION('&', n), FST::RELATION('\\', n), \
										FST::RELATION('~', n), FST::RELATION('/', n), \
										FST::RELATION('+', n), FST::RELATION('-', n), \
										FST::RELATION('/', n), FST::RELATION('*', n), \
										FST::RELATION('1', n), FST::RELATION('2', n), \
										FST::RELATION('3', n), FST::RELATION('4', n), \
										FST::RELATION('5', n), FST::RELATION('6', n), \
										FST::RELATION('7', n), FST::RELATION('8', n), \
										FST::RELATION('9', n), FST::RELATION('0', n) \
// 11
#define PUNCTUATION(n)\
										FST::RELATION(' ', n),\
										FST::RELATION('!', n), FST::RELATION('?', n), \
										FST::RELATION('.', n), FST::RELATION(',', n), \
										FST::RELATION(':', n), FST::RELATION(';', n), \
										FST::RELATION('(', n), FST::RELATION(')', n), \
										FST::RELATION('{', n), FST::RELATION('}', n) \

#define STR_LITERAL(string) { string, \
							4, \
							FST::NODE(1,	FST::RELATION('"',1)), \
							FST::NODE(162,	\
											LATIN(1), \
											NUMSANDOPS(1), \
											PUNCTUATION(1), \
											LATIN(2),\
											NUMSANDOPS(2), \
											PUNCTUATION(2) \
											),\
							FST::NODE(1, FST::RELATION('"',3)), \
							FST::NODE() \
}

#define SIGN_LITERAL(string) { string, \
							4, \
							FST::NODE(1,	FST::RELATION('"',1)), \
							FST::NODE(81,	\
											LATIN(2),\
											NUMSANDOPS(2), \
											PUNCTUATION(2) \
											),\
							FST::NODE(1, FST::RELATION('"',3)), \
							FST::NODE() \
}