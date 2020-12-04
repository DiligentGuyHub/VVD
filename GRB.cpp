#include "GRB.h"
#include <string.h>

#define GRB_ERROR_SERIES 200

namespace GRB
{
#define NS(n) Rule::Chain::N(n)
#define TS(n) Rule::Chain::T(n)

	Greibach greibach(NS('S'), TS('$'),
		10,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 0,
			5,
			Rule::Chain(13, TS('f'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(8,	TS('f'), TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(7,  TS('f'), TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}')),
			Rule::Chain(9,	TS('f'), TS('m'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S')),
			Rule::Chain(8,	TS('f'), TS('m'), TS('{'), TS('r'), NS('E'), TS(';'), TS('}'), NS('S'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES + 1,
			15,
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS(':'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS(':'), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS(':'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(2, TS('?'), NS('I')),

			Rule::Chain(3, TS('?'), NS('I'), NS('N')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),

			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 2,
			12,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),

			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('i'), NS('B')),
			Rule::Chain(2, TS('i'), NS('L')),
			Rule::Chain(2, TS('l'), NS('M')),

			Rule::Chain(2, TS('l'), NS('B')),
			Rule::Chain(2, TS('l'), NS('L')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'), GRB_ERROR_SERIES + 4,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES + 4,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 5,
			2,
			Rule::Chain(2, TS('v'), NS('E')),
			Rule::Chain(3, TS('v'), NS('E'), NS('M'))
		),
		Rule(
			NS('B'), GRB_ERROR_SERIES + 6,
			3,
			Rule::Chain(1, TS('q')),
			Rule::Chain(2, TS('b'), NS('E')),
			Rule::Chain(3, TS('b'), NS('E'), NS('B'))
		),
		Rule(
			NS('L'), GRB_ERROR_SERIES + 7,
			2,
			Rule::Chain(2, TS('c'), NS('E')),
			Rule::Chain(3, TS('c'), NS('E'), NS('L'))
		),
		Rule(
			NS('I'), GRB_ERROR_SERIES + 8,
			4,
			Rule::Chain(6, TS('('), NS('X'), TS(')'), TS('{'), NS('N'), TS('}')),
			Rule::Chain(7,	TS('('), NS('X'), TS(')'), TS('{'), NS('N'), TS('}'), NS('I')),
			Rule::Chain(8, TS('z'), TS('('), NS('X'), TS(')'), TS('{'), NS('N'), TS('}'), NS('I')),
			Rule::Chain(4,	TS('e'), TS('{'), NS('N'), TS('}'))
		),
		Rule(
			NS('X'), GRB_ERROR_SERIES + 9,
			2,
			Rule::Chain(2, TS('i'), NS('L')),
			Rule::Chain(2, TS('l'), NS('L'))
		)
	);

	Greibach getGreibach() { return greibach; }

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule)
	{
		short rc = -1;
		short k = 0;
		while (k < size && rules[k].nn != pnn) k++;
		if (k < size) prule = rules[rc = k];
		return rc;
	}

	Rule Greibach::getRule(short n)
	{
		Rule rc;
		if (n < size) rc = rules[n];
		return rc;
	}

	char* Rule::getCRule(char* b, short nchain)
	{
		char bchain[200];
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00;
		chains[nchain].getCChain(bchain);
		strcat_s(b, sizeof(bchain) + 5, bchain);
		return b;
	}

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j)
	{
		short rc = -1;
		while (j < size && chains[j].nt[0] != t) ++j;
		rc = (j < size ? j : -1);
		if (rc >= 0) pchain = chains[rc];
		return rc;
	}

	char* Rule::Chain::getCChain(char* b)
	{
		for (int i = 0; i < size; i++) b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	}
}