/*

	R Project Library

	QDrawGroups.cpp

	Widget to draw the bins - Implementation.

	(C) 2001-2002 by Pascal Francq

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
// include files for ANSI C/C++
#include <stdio.h>
#include <math.h>


//-----------------------------------------------------------------------------
// include files for R Project
#include <rga/robjs.h>
#include <rbp/robjbp.h>
#include <rbp/rfchromobp.h>
#include <rbp/rdatabpfile.h>
using namespace R;


//-----------------------------------------------------------------------------
// include files for Qt
#include <qpainter.h>


//-----------------------------------------------------------------------------
// include files for Qt Widgets
#include "qdrawgroups.h"


//-----------------------------------------------------------------------------
//
// QInfoBox
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
QInfoBox::QInfoBox(QWidget* parent,RFGroupBP* grp,RObjs<RObjBP>* objs)
	: QPopupMenu(0,"Info Box")
{
	char Tmp[50];
	unsigned int* o;
	unsigned int* ptr;

	if(!grp)
	{
		insertItem("This group isn't used");
	}
	else
	{
		sprintf(Tmp,"Group: '%u'",grp->GetId());
		insertItem(Tmp);
		sprintf(Tmp,"Use: %u/%u (%.1f%%)",grp->GetSize(),grp->GetMaxSize(),((double)grp->GetSize()*100)/((double)grp->GetMaxSize()));
		insertItem(Tmp);
		ptr=o=grp->GetObjectsId();
		if((*ptr)!=NoObject)
		{
			insertItem("Objects:");
			for(;(*ptr)!=NoObject;ptr++)
			{
				sprintf(Tmp,"   %s (%u)",objs->Tab[*ptr]->GetName().Latin1(),objs->Tab[*ptr]->GetSize());
				insertItem(Tmp);
			}
		}
		delete[] o;
	}
	afterFocus=parent;
	afterFocus->parentWidget()->setFocus();
}


//-----------------------------------------------------------------------------
QInfoBox::QInfoBox(QWidget* parent,RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps)
	: QPopupMenu(0,"Info Box")
{
	char Tmp[50];
	double sum=0.0;

	sprintf(Tmp,"Nb Groups: '%u'",grps->Used.NbPtr);
	insertItem(Tmp);
	if(grps->Used.NbPtr)
	{
		for(grps->Used.Start();!grps->Used.End();grps->Used.Next())
			sum+=grps->Used()->GetSize()/grps->Used()->GetMaxSize();
		sprintf(Tmp,"Avg use: %.1f%%",(sum*100.0)/((double)grps->Used.NbPtr));
		insertItem(Tmp);
	}
	afterFocus=parent;
	afterFocus->parentWidget()->setFocus();
}


//-----------------------------------------------------------------------------
void QInfoBox::mouseReleaseEvent(QMouseEvent*)
{
	afterFocus->parentWidget()->setFocus();
	delete(this);
}



//-----------------------------------------------------------------------------
//
// class QDrawGroups
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
QDrawGroups::QDrawGroups(QWidget* parent,RObjs<RObjBP>* objs,const char* name)
	: QWidget(parent,name),MaxSize(0),pixmap(0),Rows(1), Cols(0),
	  Changed(false),brRed(red,BDiagPattern),Groups(0), Objs(objs)
{
	IncX=5;
}


//-----------------------------------------------------------------------------
QDrawGroups::QDrawGroups(QWidget* parent,RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps,RObjs<RObjBP>* objs,const char* name)
	: QWidget(parent,name),MaxSize(0),pixmap(0), Rows(1), Cols(0),
	  Changed(false),brRed(red,BDiagPattern), Groups(grps), Objs(objs)
{
	IncX=5;
	MaxGroups=Groups->NbPtr;
	for(Groups->Start();!Groups->End();Groups->Next())
		if((*Groups)()->GetMaxSize()>MaxSize)
			MaxSize=(*Groups)()->GetMaxSize();
}


//-----------------------------------------------------------------------------
void QDrawGroups::setGroups(RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps)
{
	Groups=grps;
	MaxGroups=Groups->NbPtr;
	for(Groups->Start();!Groups->End();Groups->Next())
		if((*Groups)()->GetMaxSize()>MaxSize)
			MaxSize=(*Groups)()->GetMaxSize();
	Groups=grps;
}


//-----------------------------------------------------------------------------
void QDrawGroups::ComputeGroupsDim(QRect& r)
{
	int w,h;
	double width;

	// Sizes
	w=r.width();
	h=r.height();

	// Minimum horizontal increment between groups
	IncX=5.0;

	// Compute Number of cols and rows to have at leadt Width>=10
	for(Rows=0,Cols=0,width=0.0;width<10.0;)
	{
		Rows++;
		Cols=(unsigned int)ceil((double)MaxGroups/(double)Rows);
		width=((double)(w-(IncX*Cols+1.0)))/((double)Cols);
	}

	// Compute IncX
	Width=width;
	IncX=((double)w-(double)(Cols*width))/((double)(Cols+1.0));

	// Compute Vertical dimensions
	MaxY=(int)((h-20.0-(Rows*10.0))/(double)Rows);
	FactorY=(h-20.0-(Rows*12.0))/(Rows*MaxSize);
}


//-----------------------------------------------------------------------------
void QDrawGroups::ComputeXY(int& x,int &y,const unsigned idx)
{
	unsigned int row,col;

	row=idx/Cols;
	col=idx-row*Cols;
	x=(int)((col+1)*IncX+(col*Width));
	y=(int)(10+row*(10+MaxY));
}


//-----------------------------------------------------------------------------
unsigned int QDrawGroups::ComputeId(const unsigned int x,const unsigned int y)
{
	unsigned int row,col,tmp;

	// Compute the row
	for(row=0;row<Rows;row++)
	{
		tmp=10+row*(10+MaxY);
		if((y>=tmp)&&(y<=tmp+MaxY))
			break;
	}
	if(row==Rows) return(NoGroup);

	// Compute the col
	for(col=0;col<Cols;col++)
	{
		tmp=(unsigned int)((col+1)*IncX+(col*Width));
		if((x>=tmp)&&(x<=tmp+Width))
			break;
	}
	if(col==Cols) return(NoGroup);

	// Return the index
	tmp=row*Cols+col;
	if(tmp>=MaxGroups) tmp=NoGroup;
	return(tmp);
}


//-----------------------------------------------------------------------------
void QDrawGroups::paintEvent(QPaintEvent*)
{
	QRect r=rect();
	if(!pixmap)
	{
		ComputeGroupsDim(r);
		pixmap=new QPixmap(r.size());
		Changed=true;
	}
	if(Changed)
	{
		unsigned int i;
		int x,y,l;

		pixmap->fill(this,r.topLeft());
		QPainter* Painter=new QPainter(pixmap);
		CHECK_PTR(Painter);

		if(Groups)
		{
			// Paint all groups rectangle
			Painter->setBrush(NoBrush);
			Painter->setPen(black);
			for(i=0;i<MaxGroups;i++)
			{
				ComputeXY(x,y,i);
				Painter->drawRect(x,y,(int)Width,MaxY);
			}

			// Paint all use groups
			Painter->setPen(red);
			Painter->setBrush(brRed);
			for(i=0,Groups->Used.Start();!Groups->Used.End();i++,Groups->Used.Next())
			{
				ComputeXY(x,y,i);
				if(Groups->Used()->GetSize()==Groups->Used()->GetMaxSize())
					Painter->drawRect(x+1,y+1,((int)Width)-2,MaxY-2);
				else
				{
					l=(int)(Groups->Used()->GetSize()*FactorY);
					Painter->drawRect(x+1,MaxY-l+y+1,(int)(Width-2),l);
				}
			}
		}
        
		delete Painter;
		Painter=0;
		Changed=false;
	}
	bitBlt(this,r.topLeft(),pixmap);
}


//-----------------------------------------------------------------------------
void QDrawGroups::resizeEvent(QResizeEvent*)
{
	if(pixmap)
	{
		QRect r=rect();
		pixmap->resize(r.size());
		ComputeGroupsDim(r);
		Changed=true;
	}
}


//-----------------------------------------------------------------------------
void QDrawGroups::mousePressEvent(QMouseEvent* e)
{
	QInfoBox* InfoBox;

	if((e->button()==RightButton)&&Groups)
	{
		unsigned int idx=ComputeId((unsigned int)e->x(),(unsigned int)e->y());
		if(idx==NoGroup)
			InfoBox=new QInfoBox(this,Groups);
		else
			InfoBox = new QInfoBox(this,Groups->Tab[idx],Objs);
		InfoBox->popup(e->globalPos());
	}
	else
		QWidget::mousePressEvent(e);
}


//-----------------------------------------------------------------------------
QDrawGroups::~QDrawGroups()
{
}
