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
// class RGroupBP<cGroup,cOb,cGroupData>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::RGroupBP(RGroupBP* grp)
		: RGGA::RGroup<cGroup,cObj,cGroupData>(grp), Size(grp->Size), MaxSize(grp->MaxSize)
{
}


//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::RGroupBP(RGGA::RGroups<cGroup,cObj,cGroupData>* owner,const unsigned int id,const cGroupData* data)
		: RGGA::RGroup<cGroup,cObj,cGroupData>(owner,id,data), Size(0.0), MaxSize(data->MaxSize)
{
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::Verify(void)
{
	if(!RGGA::RGroup<cGroup,cObj,cGroupData>::Verify())
		return(false);
	if(Size>MaxSize)
		return(false);
	return(true);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	void RGroupBP<cGroup,cObj,cGroupData>::Clear(void)
{
	RGGA::RGroup<cGroup,cObj,cGroupData>::Clear();
	Size=0.0;
}

//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::CanInsert(const cObj* obj)
{
	return(Size+obj->GetSize()<=MaxSize);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>& RGroupBP<cGroup,cObj,cGroupData>::operator=(const RGroupBP<cGroup,cObj,cGroupData>& grp)

{
	RGGA::RGroup<cGroup,cObj,cGroupData>::operator=(grp);
	MaxSize=grp.MaxSize;
	Size=grp.Size;
	return(*this);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::~RGroupBP(void)
{
}
