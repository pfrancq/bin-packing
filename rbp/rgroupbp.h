/*

	R Project Library

	RGroup.h

	Group of a GGA - Header.

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
#ifndef RGroupH
#define RGroupH


//-----------------------------------------------------------------------------
// include files for R Project
#include <rgga/rgroup.h>
#include <rbp/rbp.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	class RGroupBP : public RGGA:RGroup<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>
{
	/**
	* The size of the group.
	*/
	double Size;

	/**
	* Maximum size of the group.
	*/
	double MaxSize;

public:

	/**
	* Construct the group.
	* @param owner          Owner of the group.
	* @param id             Identificator of the group.
	* @param max            Maximum size of the group.
	*/
	RGroupBP(cChromo* owner,const unsigned int id,const double max);

	/**
	* Verify if the group is not violating the integrity of the system.
	* @return true if the group is correct, false else.
	*/
	bool Verify(void);

	/**
	* Compare two groups.
	* @returns always true.
	*/
	bool IsSameObjs(const RGroup* grp) const;

	/**
	* Look if an object can be insert in the group.
	* @param obj            Pointer to the object to insert.
	*/
	bool CanInsert(const cObj* obj);

	/**
	* Look if an object can be delete from the group.
	* @param obj            Pointer to the object to delete.
	*/
	bool CanDelete(const cObj* obj);

	/**
	* Assignment operator.
	* @param grp            The group used as source.
	*/
	RGroupBP& operator=(const RGroupBP& grp);

    /**
    * Destruct the group.
    */
	virtual ~RGroupBP(void);
	
	friend class RChromoBP<cInst,cChromo,FitnessBP,cThreadData,cGroup,cObj>;
};


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
