/*

	RChromoG.h

	Class representing a chromosome of a GGA - Header

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
#ifndef RChromoBP_H
#define RChromoBP_H


//------------------------------------------------------------------------------
// includes files for ANSI C/C++
#include <math.h>
#include <iostream>


//------------------------------------------------------------------------------
// include files for R Project
#include <rgga/rchromog.h>
#include <rbp/rbp.h>
#include <rbp/rfirstfitdesheuristic.h>


//------------------------------------------------------------------------------
namespace R{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	class RChromoBP : public RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>
{
protected:

	/**
	* FFB Heuristic used for the crossover.
	*/
	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* HeuristicFFD;

	/**
	* Temporary array of objects used for the local optimisation. Thread-depend
	* data.
	*/
	cObj** thObjs;

	/**
	* Temporary array of objects used for the local optimisation. Thread-depend
	* data.
	*/
	cObj** thObjs2;

public:

	/**
	* Construct the chromosome.
	* @param inst           The instance.
	* @param id             Identificator of the chromosome.
	*/
	RChromoBP(cInst* inst,unsigned int id) throw(bad_alloc);

	/**
	* Initialisation of the chromosome.
	* @param thData         Pointer to the "thread-dependent" data of the
	*                       chromosome.
	*/
	virtual void Init(cThreadData *thData) throw(bad_alloc);

	/**
	* Do a crossover by using the chromosome as child. The crossover select
	* first a first fit descending heuristic, and call then the default
	* crossover of the GGA.
	* @param parent1        First parent used.
	* @param parent2        Second parent used.
	*/
	virtual void Crossover(cChromo* parent1,cChromo* parent2) throw(eGA);

	/**
	* Do a mutation of the chromosome, by destroy the less filled group and
	* then call the default mutation of the GGA.
	*/
	virtual void Mutation(void) throw(eGA);

	/**
	* Perform a local optimisation. This function is called by the crossover
	* and the mutation operators just before the use of the heuristic to find
	* a group for the objects not yet assigned.<BR>
	* This local optimisation is the one described in the Bin Packing Crossover
	* with remplacement (RPRX) operator.
	*/
	virtual void LocalOptimisation(void) throw(eGA);

	/**
	* The assigment operator.
	* @param chromo         The chromosome used as source.
	*/
	RChromoBP& operator=(const RChromoBP& chromo);

	/**
	* Evaluate the fitness of the chromosome.
	*/
	virtual void Evaluate(void) throw(eGA);

	/**
	* Destruct the chromosome.
	*/
	virtual ~RChromoBP(void);

	friend class RInstBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>;
	friend class RGroupBP<cGroup,cObj,cGroupData,cChromo>;
};


//------------------------------------------------------------------------------
// inline implementation
#include <rbp/rchromobp.hh>


}//------- End of namespace R --------------------------------------------------


//------------------------------------------------------------------------------
#endif
