#include "VVD.h"
#include "Parameters.h"
#include "Log.h"
#include "Input.h"
#include "FST.h"
#include "Output.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Lexical Analysis.h"
#include "MFST.h"
#include "Semantic Analysis.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	Log::LOG log = Log::INITLOG;
	try
	{
		LT::LexTable lex = LT::Create(LT_MAXSIZE);
		LT::LexTable lexcopy = LT::Create(LT_MAXSIZE);
		IT::IdTable idt = IT::Create(IT_MAXSIZE);
		Parm::PARM parm = Parm::GetParm(argc, argv);
		log = Log::GetLog(parm.log);
		IN input = GetIn(parm.in);

		Out::Output(input, parm.out);

		uint lexical_analysis_start_time = clock();
		LexTableFill(lex, lexcopy, input, idt);
		uint lexical_analysis_end_time = clock();

		LT::LexicalAnalysisStatistics(lexical_analysis_start_time, lexical_analysis_end_time);
		LT::LEX Lex = { lex, idt };

#ifdef DEBUG_MODE
		MFST_TRACE_START
#endif

#ifdef SYNTAX_ANALYSIS
		MFST::Mfst mfst(Lex, GRB::getGreibach());
		mfst.start();

		mfst.savededucation();
		mfst.printrules();
#endif

#ifdef SEMANTIC_ANALYSIS
		Semantic::FindExpressions(Lex);
#endif

		LexTableOut(lex);
		IdTableOut(idt);

		WriteLog(log);
		WriteParm(log, parm);
		WriteIn(log, input);
		WriteLex(log, lex, parm);
		Close(log);
	}
	catch (Error::ERROR error)
	{
		WriteError(log, error);
	}
	return 0;

};