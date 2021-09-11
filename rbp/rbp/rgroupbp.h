/*

	Bin Packing Library

	RGroupBP.h

	Group for a Bin Packing Problem - Header.

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
#ifndef RGroupBP_H
#define RGroupBP_H


//------------------------------------------------------------------------------
// include files for ANSI C/C++
#include <math.h>


//------------------------------------------------------------------------------
// include files for R Project
#include <rgroups.h>
#include <rfirstfitdesheuristic.h>


//------------------------------------------------------------------------------
namespace RBP{
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/**
* The RGroupBP provides a representation for a group for the Bin Packing
* Problem.
* @author Pascal Francq
* @short Bin Packing Group.
*/
template<class cGroup,class cObj,class cChromo>
	class RGroupBP : public R::RGroup<cGroup,cObj,cChromo>
{
protected:

	/**
	* The size of the group.
	*/
	size_t Size;

	/**
	* Maximum size of the group.
	*/
	size_t MaxSize;

public:

	/**
	* Construct the group.
	* @param grp            Group used as source.
	*/
	RGroupBP(RGroupBP* grp);

	/**
	* Construct the group.
	* @param owner          Owner of the group.
	* @param id             Identificator of the group.
	*/
	RGroupBP(cChromo* owner,size_t id);

	/**
	* Verify if the group is not violating the integrity of the system.
	*/
	virtual void Verify(void);

	/**
	* Clear the information container in a group.
	*/
	virtual void Clear(void);

	/**
	* Look if an object can be insert in the group.
	* @param obj            Pointer to the object to insert.
	*/
	virtual bool CanInsert(const cObj* obj);

	/**
	* Return the actual size of the group.
	*/
	size_t GetSize(void) const {return(Size);}

	/**
	* Return the maximal size of the group.
	*/
	size_t GetMaxSize(void) const {return(MaxSize);}

	/**
	 * Get the percentage of volume occupied.
    */
	double GetPerc(void) const
	{
		return(static_cast<double>(Size*100)/static_cast<double>(MaxSize));
	}

	/**
	* Method call after an object was inserted in the group.
	* @param obj            Pointer to the object to insert.
	*/
	virtual void PostInsert(const cObj* obj);

	/**
	* Method call after an object was deleted from the group.
	* @param obj            Pointer to the object to delete.
	*/
	virtual void PostDelete(const cObj* obj);

	/**
	* Do a local optimisation by checking whether it is possible to replace up
	* to three objects in the group by one or two objects of objs, in such a
	* way that the total size of the group increases. If so, perform the
	* changes in the group and in objs.
	* @return true if at least one exchange has been done.
	*/
	bool DoOptimisation(cObj** objs,size_t& nbobjs);

	/**
	* Assignment operator.
	* @param grp            The group used as source.
	*/
	RGroupBP& operator=(const RGroupBP& grp);

	/**
	* Destruct the group.
	*/
	virtual ~RGroupBP(void);

protected:

	/**
	* Test if a new better size can be assigned to group by deleting maximum 3
	* objects.
	*/
	bool TestNewSize(cObj** del,size_t& nbdel,size_t addsize,size_t size);
};


//------------------------------------------------------------------------------
// inline implementation
#include <rgroupbp.hh>


}  //------- End of namespace R ------------------------------------------------


//------------------------------------------------------------------------------
#endif
