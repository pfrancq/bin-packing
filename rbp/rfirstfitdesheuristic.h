/*

	Bin Packing Library

	RFirstFirtDesHeuristic.h

	First-fit Heuristic in Descending Order - Header

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
#ifndef RFirstFitDesHeuristic_H
#define RFirstFitDesHeuristic_H


//------------------------------------------------------------------------------
// include files for R Project
#include <rfirstfitheuristic.h>
#include <rdebug.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/**
* The RFitstFitDesHeuristic class provides a first fit descending heuristic.
* @author Pascal Francq
* @short First Fit Descending Heuristic.
*/
template<class cGroup,class cObj,class cGroups>
	class RFirstFitDesHeuristic : public R::RFirstFitHeuristic<cGroup,cObj,cGroups>
{
public:

	/**
	* This function is used to make a sort of the objects based on their size.
	* @param a              The first object.
	* @param b              The second object.
	* @return a-b
	*/
	static int sort_function_cObjs( const void *a, const void *b);

	/**
	* This function is used to make a sort of the objects based on their size
	* in descending order.
	* @param a              The first object.
	* @param b              The second object.
	* @return b-a
	*/
	static int sortdes_function_cObjs( const void *a, const void *b);

	/**
	* Construct the grouping heuristic.
	* @param r              The random genrator to use.
	* @param objs           Pointer to the objects.
	* @param debug          Debugger.
	*/
	RFirstFitDesHeuristic(R::RRandom& r,R::RCursor<cObj> objs,R::RDebug* debug=0);

	/**
	* Initialize the heuristic.
	* @param groups         Pointer to the groups.
	*/
	virtual void Init(cGroups* groups);

	/**
	* Destruct the grouping heuristic.
	*/
	virtual ~RFirstFitDesHeuristic(void);
};


//------------------------------------------------------------------------------
// Definitions of templates
#include <rfirstfitdesheuristic.hh>


}  //------- End of namespace R ------------------------------------------------


//------------------------------------------------------------------------------
#endif
