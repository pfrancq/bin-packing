/*

	R Project Library

	RGroupingHeuristic.hh

	Generic Heuristic for Grouping - Inline Implemenation

	Copyright 1998-2005 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.Be).

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
// class RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData,class cGroups>
	RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>::RFirstFitDesHeuristic(RRandom* r,RCursor<cObj>* objs,RDebug* debug)
	: RFirstFitHeuristic<cGroup,cObj,cGroupData,cGroups>(r,objs,debug)
{
	this->Name="First-Fit Descending Heuristic";
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData,class cGroups>
	int RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>::sort_function_cObjs( const void *a, const void *b)
{
	unsigned int as=(*(cObj**)a)->GetSize();
	unsigned int bs=(*(cObj**)b)->GetSize();

	return(as-bs);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData,class cGroups>
	int RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>::sortdes_function_cObjs( const void *a, const void *b)
{
	unsigned int as=(*(cObj**)a)->GetSize();
	unsigned int bs=(*(cObj**)b)->GetSize();

	return(bs-as);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData,class cGroups>
	void RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>::Init(cGroups* groups)
{
	RFirstFitHeuristic<cGroup,cObj,cGroupData,cGroups>::Init(groups);

	// Order by size descending
	qsort(static_cast<void*>(this->Order),this->NbObjs,sizeof(cObj*),sortdes_function_cObjs);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData,class cGroups>
	RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cGroups>::~RFirstFitDesHeuristic(void)
{
}
