/*

	R Project Library

	kbinpackingview.cpp

	Description - Implementation.

	(C) 2001 by Pascal Francq

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
// include files for Qt
#include <qprinter.h>
#include <qpainter.h>
#include <qdir.h>


//-----------------------------------------------------------------------------
// application specific includes
#include "kbinpacking.h"
#include "kbinpackingview.h"
#include "kbinpackingdoc.h"


//-----------------------------------------------------------------------------
//
// class KBinPackingView
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBinPackingView::KBinPackingView(KBinPackingDoc* pDoc,QWidget* parent,const char* name,int wflags)
 : QWidget(parent,name,wflags)
{
	doc=pDoc;
}



//-----------------------------------------------------------------------------
KBinPackingDoc* KBinPackingView::getDocument(void) const
{
	return doc;
}


//-----------------------------------------------------------------------------
void KBinPackingView::update(KBinPackingView* pSender)
{
	if(pSender != this)
		repaint();
}


//-----------------------------------------------------------------------------
void KBinPackingView::print(QPrinter* pPrinter)
{
	if (pPrinter->setup(this))
	{
		QPainter p;
		p.begin(pPrinter);
		p.end();
	}
}

//-----------------------------------------------------------------------------
void KBinPackingView::closeEvent(QCloseEvent* /*e*/)
{
}


//-----------------------------------------------------------------------------
KBinPackingView::~KBinPackingView(void)
{
}
