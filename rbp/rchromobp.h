/*

	RChromoG.h

	Class representing a chromosome of a GGA - Header

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
#ifndef RChromoBPH
#define RChromoBPH


//-----------------------------------------------------------------------------
// include files for R Project
#include <rgga/rchromog.h>
#include <rbp/rbp.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RChromoBP : public RGGA::RChromoG<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>
{
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
	* The assigment operator.
	* @param chromo         The chromosome used as source.
	*/
	RChromoBP& operator=(const RChromoBP& chromo);

	/**
	* Destruct the chromosome.
	*/
	virtual ~RChromoBP(void);

	friend class RInstBP<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>;
	friend class RGroupBP<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>;
};


}//------- End of namespace RBP -----------------------------------------------


//-----------------------------------------------------------------------------
#endif
