/*

 	Bin Packing Library

	RChromoBP.h

	Chromosome for a Bin Packing Problem - Header

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
#ifndef RChromoBP_H
#define RChromoBP_H


//------------------------------------------------------------------------------
// includes files for ANSI C/C++
#include <math.h>
#include <iostream>
#include <limits>


//------------------------------------------------------------------------------
// include files for R Project
#include <rchromog.h>
#include <rbp.h>
#include <rfirstfitdesheuristic.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RChromoBP : public R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>
{
protected:

	/**
	* FFB Heuristic used for the crossover.
	*/
	R::RGroupingHeuristic<cGroup,cObj,cChromo>* HeuristicFFD;

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
	RChromoBP(cInst* inst,unsigned int id);

	/**
	* Initialisation of the chromosome.
	* @param thData         Pointer to the "thread-dependent" data of the
	*                       chromosome.
	*/
	virtual void Init(cThreadData *thData);

	/**
	* Do a crossover by using the chromosome as child. The crossover select
	* first a first fit descending heuristic, and call then the default
	* crossover of the GGA.
	* @param parent1        First parent used.
	* @param parent2        Second parent used.
	*/
	virtual void Crossover(cChromo* parent1,cChromo* parent2);

	/**
	* Do a mutation of the chromosome, by destroy the less filled group and
	* then call the default mutation of the GGA.
	*/
	virtual void Mutation(void);

	/**
	* Perform a local optimisation. This function is called by the crossover
	* and the mutation operators just before the use of the heuristic to find
	* a group for the objects not yet assigned.<BR>
	* This local optimisation is the one described in the Bin Packing Crossover
	* with remplacement (RPRX) operator.
	*/
	virtual void LocalOptimisation(void);

	/**
	* The assigment operator.
	* @param chromo         The chromosome used as source.
	*/
	RChromoBP& operator=(const RChromoBP& chromo);

	/**
	* Evaluate the fitness of the chromosome.
	*/
	virtual void Evaluate(void);

	/**
	* Destruct the chromosome.
	*/
	virtual ~RChromoBP(void);

	friend class RInstBP<cInst,cChromo,cThreadData,cGroup,cObj>;
	friend class RGroupBP<cGroup,cObj,cChromo>;
};


//------------------------------------------------------------------------------
// inline implementation
#include <rchromobp.hh>


}//------- End of namespace R --------------------------------------------------


//------------------------------------------------------------------------------
#endif
