/*

  rdatabpfile.h

  Description - Header.

  (c) 2000 by P. Francq.

  Version $Revision$

  Last Modify: $Date$

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/



//-----------------------------------------------------------------------------
#ifndef RDataBPFileh
#define RDataBPFileh


//-----------------------------------------------------------------------------
// include files for R Project
#include <rbp/robjbp.h>


//-----------------------------------------------------------------------------
namespace RBP{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
/**
* @author Pascal Francq
*/
class RDataBPFile
{

protected:

	/**
	* Number of objects.
	*/
	unsigned int NbObjs;

	/**
	* Objects.
	*/
	RObjBP** Objs;

	/**
	* Maximal size for the groups.
	*/
	double MaxSize;

public:

	/**
	*/
	RDataBPFile(void);
	
	void Load(char* name);
	void Clear(void);

	/**
	* Return the number of objects.
	*/
	unsigned int GetNbObjs(void) const {return(NbObjs);}

	~RDataBPFile(void);
};


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
