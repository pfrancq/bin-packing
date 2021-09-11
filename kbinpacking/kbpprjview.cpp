/*

	Bin Packing GUI

	KBPPrjView.cpp

	Project Window - Implementation.

	Copyright 2000-2014 by Pascal Francq (pascal@francq.info).

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
// include files for R Project
#include <rqt.h>
using namespace R;


//-----------------------------------------------------------------------------
// include files for current application
#include <kbpprjview.h>



//-----------------------------------------------------------------------------
//
// class KBPPrjView
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBPPrjView::KBPPrjView(RBPProblem* problem,const QString& uri)
	: QMdiSubWindow(), Ui_KBPPrjView(), Problem(problem)
{
	QWidget* ptr=new QWidget();
	setupUi(ptr);
	setWidget(ptr);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle(uri);
	createPrj();
}


//-----------------------------------------------------------------------------
void KBPPrjView::createPrj(void)
{
	QTreeWidgetItem* item=0,*item2=0,*item3=0;

	// Problem
	item=new QTreeWidgetItem(Elements,QStringList()<<"Problem");

	// Problem
	new QTreeWidgetItem(item,QStringList()<<"Maximal size of the bins: "+QString::number(Problem->GetBinMaxSize()));
	new QTreeWidgetItem(item,QStringList()<<"Minimal number of the bins: "+QString::number(Problem->GetMinBins()));

	// Objects
	item2=new QTreeWidgetItem(item,item2);
	item2->setText(0,"Objects ("+QString::number(Problem->GetNbObjs())+")");
	RCursor<RObjBP> Cur(Problem->GetObjs());
	for(Cur.Start(),item3=0;!Cur.End();Cur.Next())
	{
		if(item3)
		{
			item3=new QTreeWidgetItem(item2,item3);
			item3->setText(0,ToQString(Cur()->GetName())+" ("+QString::number(Cur()->GetSize())+")");
		}
		else
			item3=new QTreeWidgetItem(item2,QStringList()<<ToQString(Cur()->GetName())+" ("+QString::number(Cur()->GetSize())+")");
	}
}


//-----------------------------------------------------------------------------
KBPPrjView::~KBPPrjView(void)
{
}
