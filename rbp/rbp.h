/*

	R Project Library

	rbp.h

	GA for the Bin Packing Problem - Header.

	(C) 2001 by Pascal Francq

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
#ifndef RBPH
#define RBPH


//-----------------------------------------------------------------------------
// includes files for R Project
#include <rga/rfitness.h>
#include <rgga/rgga.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* The RFitnessBP provides a representation for a fitness function for the bin
* packing problem.
* @author Pascal Francq
* @short Bin Packing Fitness.
*/
class RFitnessBP : public RGA::RFitness<unsigned int,false>
{
public:
	RFitnessBP(void) : RGA::RFitness<unsigned int,false>() {}
};


//-----------------------------------------------------------------------------
// Heuristic Types
enum HeuristicType{FirstFit=0};


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
