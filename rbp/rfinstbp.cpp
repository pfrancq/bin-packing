/*

	R Project Library

	RFInstBP.cpp

	Final Instance for Bin Packing Problem - Implementation

	Copyright 1999-2003 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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
// include files for R Project
#include <rdatabpfile.h>
#include <rfinstbp.h>
#include <rfchromobp.h>
using namespace R;



//------------------------------------------------------------------------------
//
// RFThreadDataBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFThreadDataBP::RFThreadDataBP(RFInstBP* owner)
	: RThreadDataBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>(owner)
{
}



//------------------------------------------------------------------------------
//
// RFInstBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RFInstBP::RFInstBP(unsigned int max,unsigned int popsize,RObjs<RObjBP>* objs,HeuristicType h,const double maxv,RDebug *debug) throw(std::bad_alloc)
	: RInstBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>(popsize,objs,h,maxv,debug),
		MaxGen(max)
{
}


//------------------------------------------------------------------------------
bool RFInstBP::StopCondition(void)
{
	return(Gen==MaxGen);
}
