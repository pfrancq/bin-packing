/*

	R Project Library

	RGroupingHeuristic.h

	Generic Heuristic for Grouping - Header

	(C) 1998-2001 by P. Francq.

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
#ifndef RFirstFitDesHeuristicH
#define RFirstFitDesHeuristicH


//-----------------------------------------------------------------------------
// include files for R Project
#include <rgga/rfirstfitheuristic.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* The RFitstFitDesHeuristic class provides a first fit descending heuristic.
* @author Pascal Francq
* @short First Fit Descending Heuristic.
*/
template<class cGroup,class cObj,class cGroupData>
	class RFirstFitDesHeuristic : public RGGA::RFirstFitHeuristic<cGroup,cObj,cGroupData>
{
	/**
	* This function is used to make a sort of the objects based on their size.
	* @param a              The first object.
	* @param b              The second object.
	* @return a-b
	*/
	static int sort_function_cObjs( const void *a, const void *b);

public:

	/**
	* Construct the grouping heuristic.
	* @param r              The random genrator to use.
	* @param objs           Pointer to the objects.
	*/
	RFirstFitDesHeuristic(RRandom* r,RStd::RCursor<cObj,unsigned int>* objs);

	/**
	* Initialize the heuristic.
	* @param groups         Pointer to the groups.
	*/
	virtual void Init(RGGA::RGroups<cGroup,cObj,cGroupData>* groups);

	/**
	* Destruct the grouping heuristic.
	*/
	virtual ~RFirstFitDesHeuristic(void);
};


//-----------------------------------------------------------------------------
// Definitions of templates
#include <rbp/rfirstfitdesheuristic.hh>


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
