/*

  kvlsiprjview.cpp

  Description - Implementation.

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
// include files for ANSI C/C++
#include <stdio.h>


//-----------------------------------------------------------------------------
// include files for current application
#include "kbpprjview.h"
#include "kbinpackingdoc.h"



//-----------------------------------------------------------------------------
//
// class KBPPrjView
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBPPrjView::KBPPrjView(KBinPackingDoc* pDoc,QWidget *parent,const char *name,int wflags)
	: KBinPackingView(pDoc,parent,name,wflags),prj(0)
{
	prj=new QListView(this,"Project Elements"+doc->URL().path());
	prj->addColumn("Elements");
	prj->addColumn("Sizes");
	prj->setRootIsDecorated(true);
	createPrj();
}


//-----------------------------------------------------------------------------
void KBPPrjView::createPrj(void)
{
	char tmp[100];
	char tmp2[10];
	QListViewItem *item=0,*item2=0;
	RObjBP **obj;
	unsigned int i;
	unsigned int total=0;

	// Problem
	sprintf(tmp,"%u",doc->MaxSize);
	item=new QListViewItem(prj,"Problem",tmp);
	sprintf(tmp,"%u",doc->MinGroups);
	item=new QListViewItem(prj,"Best Solution Known",tmp);

	// Construct Objects
	sprintf(tmp,"Objects (%u)",doc->Objs->NbPtr);
	item = new QListViewItem(prj,item,tmp,"");
	item2=0;
	for(obj=doc->Objs->Tab,i=doc->Objs->NbPtr+1;--i;obj++)
	{
		total+=(*obj)->GetSize();
		sprintf(tmp,"%s (%u)",(*obj)->GetName().Latin1(),(*obj)->GetId());
		sprintf(tmp2,"%u",(*obj)->GetSize());
		item2 = new QListViewItem(item,item2,tmp,tmp2);
	}
	sprintf(tmp,"%u",total);
	item->setText(1,tmp);
	prj->setColumnWidth(0,prj->columnWidth(0)+20);
}


//-----------------------------------------------------------------------------
void KBPPrjView::resizeEvent(QResizeEvent *)
{
	prj->resize(width(),height());
}


//-----------------------------------------------------------------------------
KBPPrjView::~KBPPrjView()
{
}
