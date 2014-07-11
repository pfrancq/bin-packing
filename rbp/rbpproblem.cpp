/*

	Bin Packing Library

	RProblem.h

	Bin Packing Problem - Implementation.

	Copyright 2000-2014 by Pascal Francq (pascal@francq.info).

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/



//------------------------------------------------------------------------------
// include files for R Project
#include <rbpproblem.h>
using namespace std;
using namespace R;
using namespace RBP;



//------------------------------------------------------------------------------
//
// class RBPProblem
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RBPProblem::RBPProblem(void)
	: Objs(0), BinMaxSize(0), MinBins(0)
{
}


//------------------------------------------------------------------------------
void RBPProblem::Load(const RURI& name)
{
	RTextFile In(name);
	In.Open(RIO::Read);
	size_t Nb(In.GetInt());   // Number of Items
	Objs.VerifyTab(Nb);
	for(size_t i=0;i<Nb;i++)
		Objs.InsertPtr(new RObjBP(i,"Object "+RString::Number(i),In.GetInt())); // Item
	BinMaxSize=In.GetInt();               // Maximal size of a bin
	MinBins=In.GetInt();                  // Minimum number of bins
}


//------------------------------------------------------------------------------
void RBPProblem::Clear(void)
{
	Objs.Clear();
	BinMaxSize=0;
	MinBins=0;
}


//------------------------------------------------------------------------------
R::RCursor<RObjBP> RBPProblem::GetObjs(void) const
{
	return(RCursor<RObjBP>(Objs));
}


//------------------------------------------------------------------------------
RBPProblem::~RBPProblem(void)
{
	Clear();
}



//------------------------------------------------------------------------------
//
// class RFGroupBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFGroupBP::RFGroupBP(RFChromoBP* owner,size_t id)
	: RGroupBP<RFGroupBP,RObjBP,RFChromoBP>(owner,id)
{
}

//------------------------------------------------------------------------------
RFGroupBP::RFGroupBP(RFGroupBP* grp)
	: RGroupBP<RFGroupBP,RObjBP,RFChromoBP>(grp)
{
}



//------------------------------------------------------------------------------
//
// class RFChromoBP
//
//------------------------------------------------------------------------------


RFChromoBP::RFChromoBP(RFInstBP* inst,unsigned int id)
	: RChromoBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>(inst,id)
	{}


//------------------------------------------------------------------------------
//
// RFThreadDataBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFThreadDataBP::RFThreadDataBP(RFInstBP* owner)
	: RThreadDataBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>(owner)
{
}



//------------------------------------------------------------------------------
//
// RFInstBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFInstBP::RFInstBP(size_t popsize,R::RCursor<RObjBP> objs,double max,const R::RString& h,size_t maxgen,R::RDebug* debug)
	: RInstBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>(popsize,objs,max,h,debug),
		MaxGen(maxgen)
{
}


//------------------------------------------------------------------------------
bool RFInstBP::StopCondition(void)
{
	return(GetGen()==MaxGen);
}
