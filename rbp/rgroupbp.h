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
#ifndef RGroupBPH
#define RGroupBPH


//-----------------------------------------------------------------------------
// include files for R Project
#include <rgga/rgroups.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* The RGroupDataBP provides a representation of the information needed to
* construct a group in the Bin Packing Problem.
* @author Pascal Francq
* @short Data for Bin Packing Group.
*/
class RGroupDataBP
{
public:

	/**
	* Maximum size of the groups.
	*/
	double MaxSize;

	/**
	* Constructor of the group data.
	* @param m              Maximum size of the groups.
	*/
	RGroupDataBP(const double m) : MaxSize(m) {}
};


//-----------------------------------------------------------------------------
/**
* The RGroupBP provides a representation for a group for the Bin Packing
* Problem.
* @author Pascal Francq
* @short Bin Packing Group.
*/
template<class cGroup,class cObj,class cGroupData>
	class RGroupBP : public RGGA::RGroup<cGroup,cObj,cGroupData>
{
protected:

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
	* @param grp            Group used as source.
	*/
	RGroupBP(RGroupBP* grp);

	/**
	* Construct the group.
	* @param owner          Owner of the group.
	* @param id             Identificator of the group.
	* @param data           Data needed for the group.
	*/
	RGroupBP(RGGA::RGroups<cGroup,cObj,cGroupData>* owner,const unsigned int id,const cGroupData* data);

	/**
	* Verify if the group is not violating the integrity of the system.
	* @return true if the group is correct, false else.
	*/
	virtual bool Verify(void);

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
	double GetSize(void) {return(Size);}

	/**
	* Return the maximal size of the group.
	*/
	double GetMaxSize(void) {return(MaxSize);}

	/**
	* Method call after an object was inserted in the group.
	* @param obj            Pointer to the object to insert.
	*/
	virtual void PostInsert(const cObj* obj) {Size+=obj->GetSize();}

	/**
	* Method call after an object was deleted from the group.
	* @param obj            Pointer to the object to delete.
	*/
	virtual void PostDelete(const cObj* obj) {Size-=obj->GetSize();}

	/**
	* Assignment operator.
	* @param grp            The group used as source.
	*/
	RGroupBP& operator=(const RGroupBP& grp);

    /**
    * Destruct the group.
    */
	virtual ~RGroupBP(void);
};


//-----------------------------------------------------------------------------
// inline implementation
#include <rbp/rgroupbp.hh>


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
