/*

	R Project Library

	RInstBP.h

	Instance of the Bin Packing Problem - Header

	Copyright 2001-2003 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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



//------------------------------------------------------------------------------
#ifndef RInstBP_H
#define RInstBP_H


//------------------------------------------------------------------------------
// include files for R Project
#include <rgga/rinstg.h>
#include <rbp/rbp.h>
#include <rbp/rfirstfitdesheuristic.h>


//------------------------------------------------------------------------------
namespace R{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/**
* This class represent "thread-dependent" data for the Bin Packing Problem.
* @author Pascal Francq
* @short BP "thread-dependent" Data.
*/
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	class RThreadDataBP : public RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>
{
	/**
	* FFB Heuristic used for the crossover.
	*/
	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* HeuristicFFD;

	/**
	* Temporary array of objects used for the local optimisation.
	*/
	cObj** tmpObjs;

	/**
	* Temporary array of objects used for the local optimisation.
	*/
	cObj** tmpObjs2;

public:

	/**
	* Construct the data.
	* @param data           Owner of the data.
	*/
	RThreadDataBP(cInst *owner) throw(std::bad_alloc);

	/**
	* Initialise the data.
	*/
	virtual void Init(void) throw(std::bad_alloc);

	/**
	* Destruct the data.
	*/
	virtual ~RThreadDataBP(void);

	friend class RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>;
};


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	class RInstBP : public RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>
{
protected:

	/**
	* Maximal size for the groups.
	*/
	double MaxSize;

public:

	/**
	* Construct the instance.
	* @param popsize        Size of the population.
	* @param objs           Objects to group.
	* @param h              The heuristic that has to be used.
	* @param max            Maximal size of the groups.
	* @param debug          Debugger.
	*/
	RInstBP(unsigned int popsize,RObjs<cObj>* objs,HeuristicType h,const double max,RDebug *debug=0) throw(std::bad_alloc);

	/**
	* Initialisation of the instance.
	* @param gdata          The Data to use for the construction of the groups.
	*/
	virtual void Init(cGroupData* gdata) throw(std::bad_alloc);

	/**
	* Destruct the instance.
	*/
	virtual ~RInstBP(void);

	// friend classes
	friend class RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>;
	friend class RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>;
};


//------------------------------------------------------------------------------
// inline implementation
#include <rbp/rinstbp.hh>


}//------- End of namespace R --------------------------------------------------


//------------------------------------------------------------------------------
#endif
