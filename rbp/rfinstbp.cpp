/*

	R Project Library

	RFInstBP.cpp

	Final Instance for Bin Packing Problem - Implementation

	(C) 1999-2001 by P. Francq.

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
// include files for R Project
#include <rbp/rdatabpfile.h>
#include <rbp/rfinstbp.h>
#include <rbp/rfchromobp.h>
using namespace RBP;



//-----------------------------------------------------------------------------
//
// RFThreadDataBP
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
RFThreadDataBP::RFThreadDataBP(RFInstBP* owner)
	: RThreadDataBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>(owner)
{
}



//-----------------------------------------------------------------------------
//
// RFInstBP
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
RFInstBP::RFInstBP(unsigned int max,unsigned int popsize,RGA::RObjs<RObjBP>* objs,RGGA::HeuristicType h,const double maxv,RDebug *debug) throw(bad_alloc)
	: RInstBP<RFInstBP,RFChromoBP,RFThreadDataBP,RFGroupBP,RObjBP,RGroupDataBP>(popsize,objs,h,maxv,debug),
		MaxGen(max)
{
}


//-----------------------------------------------------------------------------
bool RFInstBP::StopCondition(void)
{
	return(Gen==MaxGen);
}
