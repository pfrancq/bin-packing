/*

	R Project Library

	RObjBP.h

	Object for the Bin Packing Problem - Header.

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
#ifndef RObjBPH
#define RObjBPH


//------------------------------------------------------------------------------
// includes files for R Project
#include <rgga/robjg.h>


//------------------------------------------------------------------------------
namespace R{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
/**
* The RObjBP class provides a representation for an object for the Bin Packing
* Problem.
* @author Pascal Francq
* @short Bin Packing Object.
*/
class RObjBP : public RObjG
{
	/**
	* The size of the object.
	*/
	unsigned int Size;

public:

	/**
	* Construct the object.
	* @param id             Identificator.
	* @param name           Name of the object.
	* @param size           Size of the object.
	*/
	RObjBP(const unsigned int id,const RString& name,const unsigned int size);

	/**
	* Copy Construct.
	* @param obj            Source used.
	*/
	RObjBP(const RObjBP* obj);

	/**
	* Return the size of the object.
	*/
	unsigned int GetSize(void) const {return(Size);}

	/**
	* Compare two objects. This function is needed by RObjs.
	*/
	int Compare(const RObjBP *o) {return(Id-o->Id);}

	/**
	* Destruct the object.
	*/
	virtual ~RObjBP(void);
};


}  //------- End of namespace R ------------------------------------------------


//------------------------------------------------------------------------------
#endif
