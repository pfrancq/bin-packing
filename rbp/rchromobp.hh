/*

	RChromoG.hh

	Class representing a chromosome for a GGA - Inline implementation

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



//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::RChromoBP(cInst *inst,unsigned id) throw(bad_alloc)
		: RGGA::RChromoG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>(inst,id)
{
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RBP::RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::Init(cThreadData *thData) throw(bad_alloc)
{
	// Initialisation of the parent
	RGGA::RChromoG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>::Init(thData);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>& RGGA::RChromoG<cInst,cChromo,cFit,cThreadData,cGroup,cObj>::operator=(const RChromoG& chromo)
{
  RGGA::RChromoG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>::operator=(chromo);
  return(*this);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RBP::RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RChromoBP(void)
{
}
