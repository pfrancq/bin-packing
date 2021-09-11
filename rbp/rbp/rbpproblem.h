/*

	Bin Packing Library

	RProblem.h

	Bin Packing Problem - Header.

	Copyright 2000-2014 by Pascal Francq (pascal@francq.info).

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/



//-----------------------------------------------------------------------------
#ifndef RBPProblem_H
#define RBPProblem_H


//-----------------------------------------------------------------------------
// include files for R Project
#include <rcursor.h>
#include <rbp.h>
#include <rgroupbp.h>
#include <rchromobp.h>
#include <rinstbp.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forward class declaration
class RFChromoBP;
class RFInstBP;
class RFThreadDataBP;


//------------------------------------------------------------------------------
/**
* @author Pascal Francq
*/
class RBPProblem
{
	/**
	* Objects.
	*/
	R::RContainer<RObjBP,true,true> Objs;

	/**
	* Maximal size of a bin.
	*/
	size_t BinMaxSize;

	/**
	* Minimal Number of bins.
	*/
	size_t MinBins;

public:

	/**
	* Constructor.
	*/
	RBPProblem(void);

	/**
	 * Load a problem froma  file.
	 */
	void Load(const R::RURI& name);

	/**
	 * Clear the problem.
	 */
	void Clear(void);

	/**
	 * Get the maximal size of a bin.
    */
	size_t GetBinMaxSize(void) const {return(BinMaxSize);}

	/**
	 * Get the theoritical minimal number of bins that solve the problem.
    */
	size_t GetMinBins(void) const {return(MinBins);}

	/**
	* Return the number of objects.
	*/
	size_t GetNbObjs(void) const {return(Objs.GetNb());}

	/**
	 * Get an object.
    * @param idx            Index of the object.
    * @return pointer to the object.
    */
	const RObjBP* GetObj(size_t idx) const {return(Objs[idx]);}

	/**
	 * Get a cursor over the object to group.
    * @return
    */
	R::RCursor<RObjBP> GetObjs(void) const;

	/**
	 * Destructor.
	 */
	~RBPProblem(void);
};


//------------------------------------------------------------------------------
class RFGroupBP : public RGroupBP<RFGroupBP,RObjBP,RFChromoBP>
{
public:
	/**
	* Construct the group.
	* @param owner          Owner of the group.
	* @param id             Identificator of the group.
	* @param data           Data for the group.
	*/
	RFGroupBP(RFChromoBP* owner,size_t id);

	/**
	* Construct the group.
	* @param grp            Group used as source.
	*/
	RFGroupBP(RFGroupBP* grp);
};


//-----------------------------------------------------------------------------
/**
* The chromosome for the VLSI GA.
* @author Pascal Francq
* @short VLSI GA Chromosome.
*/
class RFChromoBP : public RChromoBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>
{
public:

	/**
	* Construct the chromosome.
	* @param inst           The instance of the problem.
	* @param id             The identificator of the chromosome.
	*/
	RFChromoBP(RFInstBP* inst,unsigned int id);
};


//-----------------------------------------------------------------------------
/**
* This class represent "thread-dependent" data for the final Bin Packing GA.
* @author Pascal Francq
* @short Final Bin Packing GA "thread-dependent" Data.
*/
class RFThreadDataBP : public RThreadDataBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>
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
class RFInstBP : public RInstBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP>
{
public:

	/**
	* The maximum number of generations.
	*/
	size_t MaxGen;

	/**
	* Construct the instance.
	* @param popsize        Size of the population.
	* @param objs           Objects to group.
	* @param max            Maximal size of a group.
	* @param h              The heuristic that has to be used.
	* @param maxgen         Maximal number of generations to run.
	* @param debug          Debugger.
	*/
	RFInstBP(size_t popsize,R::RCursor<RObjBP> objs,double max,const R::RString& h,size_t maxgen,R::RDebug* debug=0);

	/**
	* This function determines if the GA must be stopped. Actually, it is the case
	* when the maximal number of generation is calculated.
	* @return	The function returns true if the GA must stop.
	*/
	virtual bool StopCondition(void);
};


}  //------- End of namespace RBP ----------------------------------------------


//------------------------------------------------------------------------------
#endif
