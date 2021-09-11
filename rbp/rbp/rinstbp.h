/*

	Bin Packing Library

	RInstBP.h

	Instance for a Bin Packing Problem - Header

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
#ifndef RInstBP_H
#define RInstBP_H


//------------------------------------------------------------------------------
// include files for R Project
#include <rinstg.h>
#include <rbp.h>
#include <rfirstfitdesheuristic.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/**
* This class represent "thread-dependent" data for the Bin Packing Problem.
* @author Pascal Francq
* @short BP "thread-dependent" Data.
*/
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RThreadDataBP : public R::RThreadDataG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>
{
	/**
	* FFB Heuristic used for the crossover.
	*/
	R::RGroupingHeuristic<cGroup,cObj,cChromo>* HeuristicFFD;

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
	RThreadDataBP(cInst *owner);

	/**
	* Initialise the data.
	*/
	virtual void Init(void);

	/**
	* Destruct the data.
	*/
	virtual ~RThreadDataBP(void);

	friend class RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>;
};


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RInstBP : public R::RInstG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>
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
	* @param max            Maximal size of a group.
	* @param h              The heuristic that has to be used.
	* @param debug          Debugger.
	*/
	RInstBP(size_t popsize,R::RCursor<cObj> objs,double max,const R::RString& h,R::RDebug* debug=0);

	/**
	* Initialisation of the instance.
	* @param gdata          The Data to use for the construction of the groups.
	*/
	virtual void Init(void);

	/**
	 * Get the maximal size of the bins.
    */
	double GetMaxSize(void) {return(MaxSize);}

	/**
	* Destruct the instance.
	*/
	virtual ~RInstBP(void);

	// friend classes
	friend class RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>;
	friend class RThreadDataBP<cInst,cChromo,cThreadData,cGroup,cObj>;
};


//------------------------------------------------------------------------------
// inline implementation
#include <rinstbp.hh>


}//------- End of namespace R --------------------------------------------------


//------------------------------------------------------------------------------
#endif
