#pragma once
#include "VVD.h"

#define AMOUNT 8

namespace FST {

	struct RELATION { // ребро:символ -> вершина графа переходов  ј (?)
		char symbol; // символ перехода (r, q, s, c, p, e)
		short nnode; // номер смежной вершины (?)
		RELATION( // (?)
			char c = 0x00, // символ перехода 
			short ns = NULL // новое состо€ние (?)
		);
	};

	struct NODE { // вершина графа переходов
		short n_relation; // количество инциндентных ребер (?)
		RELATION* relations;
		NODE();
		NODE(
			short n, // количество инциндентных ребер
			RELATION rel, ... // список ребер
		);
	};


	struct FST {
		const char* string; // цепочка
		short position; // текуща€ позици€ в цепочке
		short nstates; // количество состо€ний автомата
		NODE* nodes; // граф переходов: [0] - начальное состо€ние, [nstate-1] - конечное состо€ние
		short* rstates; // возможные состо€ни€ на данной позиции
		FST(
			const char* s,
			short ns,
			NODE n, ...
		);
	};

	bool execute(FST& fst, int line);
}