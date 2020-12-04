﻿#include "VVD.h"
#include "Parameters.h"
#include "Log.h"
#include "Input.h"
#include "FST.h"
#include "Output.h"
#include "LexTable.h"
#include "IdTable.h"
#include "Lexical Analysis.h"
#include "MFST.h"

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

		LexTableFill(lex, lexcopy, input, idt);
		LT::LEX Lex = { lex, idt };

		MFST_TRACE_START
			MFST::Mfst mfst(Lex, GRB::getGreibach());
		mfst.start();

		mfst.savededucation();
		mfst.printrules();

		system("pause");

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