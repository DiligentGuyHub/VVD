#pragma once
#include "Error.h"
typedef short GRBALPHABET;

namespace GRB
{

	struct Rule
	{
		GRBALPHABET nn;
		int iderror;
		short size;

		struct Chain
		{
			short size;
			GRBALPHABET* nt;

			Chain()
			{
				size = 0; nt = 0;
			};

			Chain(short psize, GRBALPHABET s, ...)
			{
				nt = new GRBALPHABET[size = psize];
				int* p = (int*)&s;
				for (short i = 0; i < psize; ++i) nt[i] = (GRBALPHABET)p[i];
			}

			char* getCChain(char* b);
			static GRBALPHABET T(char t)
			{
				return GRBALPHABET(t);
			}
			static GRBALPHABET N(char n)
			{
				return -GRBALPHABET(n);
			}
			static bool isT(GRBALPHABET s)
			{
				return s > 0;
			}
			static bool isN(GRBALPHABET s)
			{
				return !isT(s);
			}
			static char alphabet_to_char(GRBALPHABET s)
			{
				return isT(s) ? char(s) : char(-s);
			}
		}*chains;

		Rule()
		{
			nn = 0x00; size = 0;
		}
		Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...)
		{
			nn = pnn;
			iderror = piderror;
			chains = new Chain[size = psize];
			Chain* p = &c;
			for (int i = 0; i < size; i++) chains[i] = p[i];
		}

		char* getCRule(char* b, short nchain);
		short getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j); // ?
	};

	struct Greibach
	{
		short size;
		GRBALPHABET startN;
		GRBALPHABET stbottomT;
		Rule* rules;
		Greibach()
		{
			short size = 0;
			startN = 0;
			stbottomT = 0;
			rules = 0;
		}
		Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottomT, short psize, Rule r, ...)
		{
			startN = pstartN;
			stbottomT = pstbottomT;
			rules = new Rule[size = psize];
			Rule* p = &r;
			for (int i = 0; i < size; i++) rules[i] = p[i];
		}
		short getRule(GRBALPHABET pnn, Rule& prule);
		Rule getRule(short n);
	};

	Greibach getGreibach();
}