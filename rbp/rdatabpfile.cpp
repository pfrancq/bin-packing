/*

	R Project Library

	RDataBPFile.cpp

	XML representing a bin packing problem - Implementation.

	Copyright 2000-2003 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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



//------------------------------------------------------------------------------
// include files for ANSI C/C++
#include <stdlib.h>


//------------------------------------------------------------------------------
// include files for R Project
#include <rstd/rxmlstruct.h>
#include <rstd/rxmlfile.h>
#include <rbp/rdatabpfile.h>
using namespace R;



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
	RXMLTag *tag,**tab;
	unsigned int i;
	
	f.Process();

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
		Objs=new RObjs<RObjBP>(tag->NbPtr);
		
		// Read each objects	
		for(i=0,tab=tag->Tab;i<tag->NbPtr;i++,tab++)
			if((*tab)->GetName()=="Object")
			{
				double d;
				RString str=(*tab)->GetAttrValue("Size");
				d=atof((*tab)->GetAttrValue("Size"));
				Objs->InsertPtr(new RObjBP(i,(*tab)->GetAttrValue("Id"),atoi((*tab)->GetAttrValue("Size"))));
			}
	}
	ObjsCursor.Set(Objs);
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
