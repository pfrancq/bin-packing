/*

	R Project Library

	RObjBP.h

	Object for the Bin Packing Problem - Header.

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
#ifndef RObjBPH
#define RObjBPH


//-----------------------------------------------------------------------------
// includes files for R Project
#include <rgga/robjg.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* The RObjBP class provides a representation for an object for the Bin Packing
* Problem.
* @author Pascal Francq
* @short Bin Packing Object.
*/
class RObjBP : public RGGA::RObjG
{
	/**
	* The size of the object.
	*/
	double Size;

public:

	/**
	* Construct the object.
	* @param id             Identificator.
	* @param name           Name of the object.
	* @param size           Size of the object.
	*/
	RObjBP(const unsigned int id,const RString& name,const double size);

	/**
	* Return the size of the object.
	*/
	double GetSize(void) {return(Size);}

	/**
	* Destruct the object.
	*/
	virtual ~RObjBP(void);
};


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
