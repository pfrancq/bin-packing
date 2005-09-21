/*

	R Project Library

	RDataBPFile.cpp

	XML representing a bin packing problem - Implementation.

	Copyright 2000-2003 by the Universit�Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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



//------------------------------------------------------------------------------
// include files for ANSI C/C++
#include <stdlib.h>


//------------------------------------------------------------------------------
// include files for R Project
#include <rxmlstruct.h>
#include <rxmlfile.h>
#include <rdatabpfile.h>
#include <rfchromobp.h>
using namespace R;



//------------------------------------------------------------------------------
//
// class RFGroupBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFGroupBP::RFGroupBP(RFChromoBP* owner,const unsigned int id,RGroupDataBP* data)
	: RGroupBP<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>(owner,id,data)
{
}

//------------------------------------------------------------------------------
RFGroupBP::RFGroupBP(RFGroupBP* grp)
	: RGroupBP<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>(grp)
{
}



//------------------------------------------------------------------------------
//
// class RDataBPFile
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RDataBPFile::RDataBPFile(void)
	: Objs(0), MaxSize(0)
{
}


//------------------------------------------------------------------------------
void RDataBPFile::Load(char* name)
{
	RXMLStruct s;
	RXMLFile f(name,&s);
	RXMLTag *tag;
	unsigned int i;

	f.Open(RIO::Read);

	// Take the Maximal Size
	tag=s.GetTag("Groups");
	if(tag)
	{
		MaxSize=atoi(tag->GetAttrValue("Size"));
		MinGroups=atoi(tag->GetAttrValue("Best"));
	}

	// Objects
	tag=s.GetTag("Objects");
	if(tag)
	{
		// Read number objects info
		Objs=new RObjs<RObjBP>(tag->GetNbNodes());

		// Read each objects
		RCursor<RXMLTag> tab(tag->GetNodes());
		for(i=0,tab.Start();i<tag->GetNbNodes();i++,tab.Next())
			if(tab()->GetName()=="Object")
			{
				double d;
				RString str=tab()->GetAttrValue("Size");
				d=atof(tab()->GetAttrValue("Size"));
				Objs->InsertPtr(new RObjBP(i,tab()->GetAttrValue("Id"),atoi(tab()->GetAttrValue("Size"))));
			}
	}
	ObjsCursor.Set(*Objs);
}


//------------------------------------------------------------------------------
void RDataBPFile::Clear(void)
{
	if(Objs)
	{
		delete Objs;
		Objs=0;
	}
	MaxSize=0;
}


//------------------------------------------------------------------------------
RDataBPFile::~RDataBPFile(void)
{
	Clear();
}
