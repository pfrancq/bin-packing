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
// RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>::RThreadDataG(cInst *owner) throw(bad_alloc)
		: RGGA::RThreadDataG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>(owner)
{
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RThreadDataBP(void)
{
}



//-----------------------------------------------------------------------------
//
// RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>
//
//-----------------------------------------------------------------------------

//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>::RInstG(unsigned int popsize,cObj** objs,unsigned int nbobjs,RDebug *debug) throw(bad_alloc)
		: RGGA:RInstG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>(popsize,objs,nbobjs,debug)
{
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RP::RInstP<cInst,cChromo,cThreadData,cGroup,cObj>::Init(void) throw(bad_alloc)
{
	RGGA::RInstG<cInst,cChromo,FitnessBP,cThreadData>::Init();
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RInstBP(void)
{
}
