/*

	RInsth.hh

	Class representing an instance of a HGA - Implementation

	(C) 2001 by P. Francq.

	Version $Revision$

	Last Modify: $Date$

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



//-----------------------------------------------------------------------------
//
// RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::RThreadDataBP(cInst *owner) throw(bad_alloc)
		: RGGA::RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>(owner),
		  HeuristicFFB(0)
{
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Init(void) throw(bad_alloc)
{
	RGGA::RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Init();
	HeuristicFFB = new RFirstFitDesHeuristic<cGroup,cObj,cGroupData>(Owner->Random,Owner->NbObjs);
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::~RThreadDataBP(void)
{
	if(HeuristicFFB)
		delete HeuristicFFB;
}



//-----------------------------------------------------------------------------
//
// RInstBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>
//
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RInstBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::RInstBP(unsigned int popsize,cObj** objs,unsigned int nbobjs,RGGA::HeuristicType h,const double max,RDebug *debug) throw(bad_alloc)
		: RGGA::RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>(popsize,objs,nbobjs,h,debug), MaxSize(max)
{
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RInstBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Init(cGroupData* gdata) throw(bad_alloc)
{
	RGGA::RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Init(gdata);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RInstBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::~RInstBP(void)
{
}
