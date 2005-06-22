/*

  rdatabpfile.h

  Description - Header.

  (c) 2000 by P. Francq.

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
#ifndef RDataBPFile_H
#define RDataBPFile_H


//-----------------------------------------------------------------------------
// include files for R Project
#include <rstd/rcursor.h>
#include <rga/robjs.h>
#include <rbp/rbp.h>
#include <rbp/robjbp.h>
#include <rbp/rgroupbp.h>


//------------------------------------------------------------------------------
namespace R{
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// forward class declaration
class RFChromoBP;
class RFInstBP;
class RFThreadDataBP;


//------------------------------------------------------------------------------
class RFGroupBP : public RGroupBP<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>
{
public:
	/**
	* Construct the group.
	* @param owner          Owner of the group.
	* @param id             Identificator of the group.
	* @param data           Data for the group.
	*/
	RFGroupBP(RFChromoBP* owner,const unsigned int id,RGroupDataBP* data);

	/**
	* Construct the group.
	* @param grp            Group used as source.
	*/
	RFGroupBP(RFGroupBP* grp);
};


//------------------------------------------------------------------------------
/**
* @author Pascal Francq
*/
class RDataBPFile
{

protected:

	/**
	* Objects.
	*/
	RObjs<RObjBP>* Objs;

	/**
	* Cursor on the Objects.
	*/
	RCursor<RObjBP> ObjsCursor;

	/**
	* Maximal size for the groups.
	*/
	unsigned int MaxSize;

	/**
	* Minimal Number of groups.
	*/
	unsigned int MinGroups;

public:

	/**
	*/
	RDataBPFile(void);

	void Load(char* name);
	void Clear(void);

	/**
	* Return the number of objects.
	*/
	unsigned int GetNbObjs(void) const {return(Objs->GetNb());}

	~RDataBPFile(void);
};


}  //------- End of namespace R ------------------------------------------------


//------------------------------------------------------------------------------
#endif
