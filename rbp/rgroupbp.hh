/*

	R Project Library

	RNodeGA.hh

	GA Node - Header.

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
// class RGroupBP<cInst,cChromo,cThreadData,cGroup,cObj>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RGroupBP<cInst,cChromo,cThreadData,cGroup,cObj>::RGroupBP(cChromo* owner,const unsigned int id,const double max)
		: RGGA:RGroup<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>(owner,id),
		  MaxSize(max), Size(0)
{
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	bool RBP::RGroupBP<cInst,cChromo,cThreadData,cGroup,cObj>::Verify(void)
{
	if(!RGGA::RGroup<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>::Verify())
		return(false);
	return(Size<=MaxSize);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cFit,class cThreadData,class cGroup,class cObj>
	bool RGGA::RGroup<cInst,cChromo,cFit,cThreadData,cGroup,cObj>::IsSameObjs(const RGroup* /*grp*/) const
{
	return(true);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cFit,class cThreadData,class cGroup,class cObj>
	RGGA::RGroup<cInst,cChromo,cFit,cThreadData,cGroup,cObj>& RGGA::RGroup<cInst,cChromo,cFit,cThreadData,cGroup,cObj>::operator=(const RGroup<cInst,cChromo,cFit,cThreadData,cGroup,cObj>& grp)

{
	return(*this);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cFit,class cThreadData,class cGroup,class cObj>
	RGGA::RGroup<cInst,cChromo,cFit,cThreadData,cGroup,cObj>::~RGroup(void)
{
}
