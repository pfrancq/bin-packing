/*

	Bin Packing Library

	RInstBP.hh

	Instance for a Bin Packing Problem - Implementation

	Copyright 2000-2014 by Pascal Francq (pascal@francq.info).

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2.0 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library, as a file COPYING.LIB; if not, write
	to the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
	Boston, MA  02111-1307  USA

*/



//------------------------------------------------------------------------------
//
// class RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>::RThreadDataBP(cInst *owner)
		: R::RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>(owner),
		  HeuristicFFD(0), tmpObjs(0)
{
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>::Init(void)
{
	R::RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::Init();
	HeuristicFFD = new RFirstFitDesHeuristic<cGroup,cObj,cChromo>(this->Owner->Random,this->Owner->Objs,this->Owner->Debug);
	tmpObjs=new cObj*[this->Owner->Objs.GetNb()];
	tmpObjs2=new cObj*[this->Owner->Objs.GetNb()];
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RThreadDataBP(void)
{
	if(HeuristicFFD)
		delete HeuristicFFD;
	if(tmpObjs)
		delete[] tmpObjs;
	if(tmpObjs2)
		delete[] tmpObjs2;
}



//------------------------------------------------------------------------------
//
// class RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>::RInstBP(size_t popsize,R::RCursor<cObj> objs,double max,const R::RString& h,R::RDebug* debug)
		: R::RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>(popsize,objs,h,"BinPacking",debug), MaxSize(max)
{
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>::Init(void)
{
	R::RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::Init();
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RInstBP(void)
{
}
