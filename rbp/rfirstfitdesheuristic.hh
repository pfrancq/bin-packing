/*

	R Project Library

	RGroupingHeuristic.hh

	Generic Heuristic for Grouping - Inline Implemenation

	(C) 1998-2001 by By P. Francq.

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
// RFirstFitDesHeuristic<cGroup,cObj,cGroupData>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RFirstFitDesHeuristic<cGroup,cObj,cGroupData>::RFirstFitDesHeuristic(RRandom* r,const unsigned int maxobjs)
	: RGGA::RFirstFitHeuristic<cGroup,cObj,cGroupData>(r,maxobjs)
{
}


//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	int RFirstFitDesHeuristic<cGroup,cObj,cGroupData>::sort_function_cObjs( const void *a, const void *b)
{
	double as=(*(cObj**)a)->GetSize();
	double bs=(*(cObj**)b)->GetSize();

	if(as<bs)
		return(+1);
	if(as==bs)
		return(0);
	else
		return(-1);
}


//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	void RFirstFitDesHeuristic<cGroup,cObj,cGroupData>::Init(cObj** objs,RGGA::RGroups<cGroup,cObj,cGroupData>* groups,const unsigned int nbobjs)
{
	RGGA::RFirstFitHeuristic<cGroup,cObj,cGroupData>::Init(objs,groups,nbobjs);

	// Order by size descending
	qsort(static_cast<void*>(Order),NbObjs,sizeof(cObj*),sort_function_cObjs);
}

//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RFirstFitDesHeuristic<cGroup,cObj,cGroupData>::~RFirstFitDesHeuristic(void)
{
}
