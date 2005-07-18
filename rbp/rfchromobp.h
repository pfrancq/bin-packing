/*

	R Project Library

	RFChromoBP.h

	Final Chromosome for Bin Packing Problem - Header

	(C) 1999-2000 by P. Francq.

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
#ifndef RFChromoBP_H
#define RFChromoBP_H


//-----------------------------------------------------------------------------
// include files for R Project
#include <rdatabpfile.h>
#include <rchromobp.h>


//------------------------------------------------------------------------
namespace R{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* The chromosome for the VLSI GA.
* @author Pascal Francq
* @short VLSI GA Chromosome.
*/
class RFChromoBP : public RChromoBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>
{
public:

	/**
	* Construct the chromosome.
	* @param inst           The instance of the problem.
	* @param id             The identificator of the chromosome.
	*/
	RFChromoBP(RFInstBP* inst,unsigned int id) throw(std::bad_alloc);
};


}  //-------- End of namespace RBP --------------------------------------------


//-----------------------------------------------------------------------------
#endif
