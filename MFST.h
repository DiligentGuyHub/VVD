#pragma once
#include <stack>
#include "GRB.h"
#include "LexTable.h"
#include "IdTable.h"


#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3

#define MFST_TRACE_START std::cout<<std::setw( 4)<<std::left<<"Шаг" << ":" \
								<<std::setw(20)<<std::left<<" Правило" \
								<<std::setw(30)<<std::left<<" Входная лента" \
								<<std::setw(20)<<std::left<<" Стек" \
								<<std::endl;

#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n) GRB::Rule::Chain::isN(n)



class MFSTSTSTACK :public std::stack<short> {
public:
	using std::stack<short>::c;
};
//typedef std::stack<short> MFSTSTSTACK;

namespace MFST
{

	struct MfstState
	{
		short lenta_position;
		short nrule;
		short nrulechain;
		MFSTSTSTACK st;
		MfstState()
		{
			lenta_position = 0;
			nrule = -1;
			nrulechain = -1;
		}
		MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)
		{
			lenta_position = pposition;
			st = pst;
			nrulechain = pnrulechain;
		}
		MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
		{
			lenta_position = pposition;
			st = pst;
			nrule = pnrule;
			nrulechain = pnrulechain;
		}

	};

	class MFSTSTATE :public std::stack<MfstState> {
	public:
		using std::stack<MfstState>::c;
	};

	struct Mfst
	{
		enum RC_STEP
		{
			NS_OK, NS_NORULE, NS_NORULECHAIN, NS_ERROR, TS_OK, TS_NOK, LENTA_END, SURPRISE
		};

		struct MfstDiagnosis
		{
			short lenta_position;
			RC_STEP rc_step;
			short nrule;
			short nrule_chain;
			MfstDiagnosis()
			{
				lenta_position = -1;
				rc_step = SURPRISE;
				nrule = -1;
				nrule_chain = -1;
			}
			MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
			{
				lenta_position = plenta_position;
				rc_step = prc_step;
				nrule = pnrule;
				nrule_chain = pnrule_chain;
			}
		} diagnosis[MFST_DIAGN_NUMBER];

		GRBALPHABET* lenta;
		short lenta_position;
		short nrule;
		short nrulechain;
		short lenta_size;
		GRB::Greibach grebach;
		LT::LexTable lex;
		IT::IdTable idt;
		MFSTSTSTACK st;
		MFSTSTATE storestate;

		Mfst()
		{
			lenta = 0;
			lenta_size = lenta_position = 0;
		}
		Mfst(LT::LexTable plex, GRB::Greibach pgrebach)
		{
			grebach = pgrebach;
			lex = plex;
			lenta = new short[lenta_size = lex.size];
			for (int k = 0; k < lenta_size; k++) lenta[k] = TS(lex.table[k].lexema);
			lenta_position = 0;
			st.push(grebach.stbottomT);
			st.push(grebach.startN);
			nrulechain = -1;
		}

		char* getCSt(char* buf);
		char* getCLenta(char* buf, short pos, short n = 25);
		char* getDiagnosis(short n, char* buf);
		bool savestate();
		bool reststate();
		bool push_chain(GRB::Rule::Chain chain);
		RC_STEP step();
		bool start();
		bool savediagnosis(RC_STEP pprc_step);
		void printrules();

		struct Deducation
		{
			short size;
			short* nrules;
			short* nrulechains;
			Deducation()
			{
				size = 0; nrules = 0; nrulechains = 0;
			}
		} deducation;

		bool savededucation();
	};
}