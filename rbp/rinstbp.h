/*

	R Project Library

	RInstBP.h

	Instance of the Bin Packing Problem - Header

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
#ifndef RInstBPH
#define RInstBPH


//-----------------------------------------------------------------------------
// include files for R Project
#include <rgga/rinstg.h>
#include <rbp/rbp.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* This class represent "thread-dependent" data for the Bin Packing Problem.
* @author Pascal Francq
* @short BP "thread-dependent" Data.
*/
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RThreadDataBP : public RGGA::RThreadDataG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>
{
public:
	
	/**
	* Construct the data.
	* @param data           Owner of the data.
	*/
	RThreadDataBP(cInst *owner) throw(bad_alloc);

	/**
	* Destruct the data.
	*/
	virtual ~RThreadDataBP(void);
	
	friend class RChromoBP<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>;
};


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RInstBP : public RGGA::RInstG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>
{
public:

	/**
	* Construct the instance.
	* @param popsize        Size of the population.
	* @param objs           Objects to place in the tree.
	* @param nbobjs         Number of objects to place.
	* @param debug          Debugger.
	*/
	RInstBP(unsigned int popsize,cObj** objs,unsigned int nbobjs,RDebug *debug=0) throw(bad_alloc);

	/**
	* Initialisation of the instance.
	*/
	virtual void Init(void) throw(bad_alloc);

	/**
	* Destruct the instance.
	*/
	virtual ~RInstBP(void);

	friend class RChromoBP<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>;
};


}//------- End of namespace RBP -----------------------------------------------


//-----------------------------------------------------------------------------
#endif
