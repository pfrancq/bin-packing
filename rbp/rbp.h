/*

	R Project Library

	rbp.h

	GA for the Bin Packing Problem - Header.

	Copyright 2001-2003 by the Université Libre de Bruxelles

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be)

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
#ifndef RBPH
#define RBPH


//------------------------------------------------------------------------------
// includes files for R Project
#include <rga/rfitness.h>
#include <rgga/rgga.h>


//------------------------------------------------------------------------------
/**
* \namespace RBP
* \brief Generic Algorithm Classes for the Bin Packing Problem.
*
* This namespace declares classes to resolve the Bin Packing Problem.
*/


//------------------------------------------------------------------------------
namespace R{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Forward class declaration
class RObjBP;
template<class cGroup,class cObj,class cGroupData,class cChromo> class RGroupBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData> class RThreadDataBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData> class RChromoBP;
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData> class RInstBP;


//------------------------------------------------------------------------------
/**
* The RFitnessBP provides a representation for a fitness function for the bin
* packing problem.
* @author Pascal Francq
* @short Bin Packing Fitness.
*/
class RFitnessBP : public RFitness<double,true>
{
public:

	/**
	* Constructor of the fitness function used for the Bin Packing.
	*/
	RFitnessBP(void) : RFitness<double,true>() {}

	/**
	* Assignment operator with a fitness f.
	*/
	RFitnessBP& operator=(const RFitnessBP &f)
	{
		RFitness<double,true>::operator=(f);
		return(*this);
	}

	/**
	* Assignment operator with a double value.
	*/
	RFitnessBP& operator=(const double val)
	{
		RFitness<double,true>::operator=(val);
		return(*this);
	}
};


}  //------- End of namespace R ------------------------------------------------


//------------------------------------------------------------------------------
#endif
