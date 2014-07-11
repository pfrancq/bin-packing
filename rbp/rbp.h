/*

	Bin Packing Library

	RBP.h

	Bin Packing - Header.

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
#ifndef RBP_H
#define RBP_H


//------------------------------------------------------------------------------
// includes files for R Project
#include <rfitness.h>
#include <rgga.h>
#include <robjg.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward class declaration
class RObjBP;
template<class cGroup,class cObj,class cChromo> class RGroupBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj> class RThreadDataBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj> class RChromoBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj> class RInstBP;


//------------------------------------------------------------------------------
/**
* The RFitnessBP provides a representation for a fitness function for the bin
* packing problem.
* @author Pascal Francq
* @short Bin Packing Fitness.
*/
class RFitnessBP : public R::RFitness<double,true>
{
public:

	/**
	* Constructor of the fitness function used for the Bin Packing.
	*/
	RFitnessBP(void) : R::RFitness<double,true>() {}

	/**
	* Assignment operator with a fitness f.
	*/
	RFitnessBP& operator=(const RFitnessBP &f)
	{
		R::RFitness<double,true>::operator=(f);
		return(*this);
	}

	/**
	* Assignment operator with a double value.
	*/
	RFitnessBP& operator=(const double val)
	{
		R::RFitness<double,true>::operator=(val);
		return(*this);
	}
};


//------------------------------------------------------------------------------
/**
* The RObjBP class provides a representation for an object for the Bin Packing
* Problem.
* @author Pascal Francq
* @short Bin Packing Object.
*/
class RObjBP : public R::RObjG
{
	/**
	* The size of the object.
	*/
	size_t Size;

public:

	/**
	* Construct the object.
	* @param id             Identificator.
	* @param name           Name of the object.
	* @param size           Size of the object.
	*/
	RObjBP(size_t id,const R::RString& name,size_t size);

	/**
	* Return the size of the object.
	*/
	size_t GetSize(void) const {return(Size);}

	/**
	* Compare two objects. This function is needed by RObjs.
	*/
	int Compare(const RObjBP& o) const {return(Id-o.Id);}

	/**
	* Compare two objects. This function is needed by RObjs.
	*/
	int Compare(const RObjBP* o) const {return(Id-o->Id);}

	/**
	* Destruct the object.
	*/
	virtual ~RObjBP(void);
};


}  //------- End of namespace RBP ----------------------------------------------


//------------------------------------------------------------------------------
#endif
