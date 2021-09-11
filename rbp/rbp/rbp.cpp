/*

	Bin Packing Library

	RObjBP.cpp

	Bin Packing - Implementation.

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
#include <rbp.h>
using namespace R;
using namespace RBP;



//------------------------------------------------------------------------------
//
// class RObjBP
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
RObjBP::RObjBP(size_t id,const RString& name,size_t size)
	: RObjG(id,name), Size(size)
{
}


//------------------------------------------------------------------------------
RObjBP::~RObjBP(void)
{
}
