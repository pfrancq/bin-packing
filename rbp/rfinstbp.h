/*

	R Project Library

	RFInstBP.h

	Final Instance for Bin Packing Problem - Header

	(C) 1999-2000 by P. Francq.

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
#ifndef RFInstBPH
#define RFInstBPH


//-----------------------------------------------------------------------------
// include files for Rainbow
#include <rbp/rdatabpfile.h>
#include <rbp/rinstbp.h>


//-----------------------------------------------------------------------------
namespace R{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* This class represent "thread-dependent" data for the final Bin Packing GA.
* @author Pascal Francq
* @short Final Bin Packing GA "thread-dependent" Data.
*/
class RFThreadDataBP : public RThreadDataBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>
{
public:

	/**
	* Construct the data.
	* @param owner          The instance of the problem.
	*/
	RFThreadDataBP(RFInstBP* owner);
};


//-----------------------------------------------------------------------------
/**
* The instance of the VLSI problem.
* @author Pascal Francq
* @short VLSI GA Instance.
*/
class RFInstBP : public RInstBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>
{
public:

	/**
	* The maximum number of generations.
	*/
	unsigned long MaxGen;

	/**
	* Construct the instance.
	* @param max            Maximal number of generations.
	* @param popsize        The size of the population.	
	* @param prob           The problem.
	* @param h              The type of heuristic to be used.
	* @param maxv           Maximal size of the groups.
	* @param debug          Debugger.
	*/
	RFInstBP(unsigned int max,unsigned int popsize,RObjs<RObjBP>* objs,HeuristicType h,const double maxv,RDebug *debug=0) throw(bad_alloc);

	/**
	* This function determines if the GA must be stopped. Actually, it is the case
	* when the maximal number of generation is calculated.
	* @return	The function returns true if the GA must stop.
	*/
	virtual bool StopCondition(void);
};


}  //-------- End of namespace RBP --------------------------------------------


//-----------------------------------------------------------------------------
#endif
