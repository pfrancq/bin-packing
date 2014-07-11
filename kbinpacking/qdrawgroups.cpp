/*

	Bin Packing GUI

	QDrawGroups.cpp

	Widget to Draw Bins - Implementation.

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



//-----------------------------------------------------------------------------
// include files for ANSI C/C++
#include <stdio.h>
#include <math.h>


//-----------------------------------------------------------------------------
// include files for R Project
#include <rqt.h>
#include <rbp.h>
using namespace std;
using namespace R;
using namespace RBP;


//-----------------------------------------------------------------------------
// include files for Qt
#include <qpainter.h>
#include <QMouseEvent>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsSceneMouseEvent>


//-----------------------------------------------------------------------------
// include files for the current application
#include <qdrawgroups.h>
#include "kbinpacking.h"



//-----------------------------------------------------------------------------
//
// QInfoBox
//
//-----------------------------------------------------------------------------
class QInfoBox : public QMenu
{
public:

	static bool Enable;

	QInfoBox(QWidget* parent,RFGroupBP* grp)
		: QMenu("Info Box",parent)
	{
		addAction(" Group: '"+QString::number(grp->GetId())+"'");
		addAction("Use: "+QString::number(grp->GetSize())+"/"+QString::number(grp->GetMaxSize())+" ("+QString::number(grp->GetPerc())+")");
		addAction("Objects:");
		RCursor<RObjBP> Obj(grp->GetObjs());
		for(Obj.Start();!Obj.End();Obj.Next())
			addAction("   "+ToQString(Obj()->GetName())+" ("+QString::number(Obj()->GetSize())+")");
		QInfoBox::Enable=true;
	}

	QInfoBox(QWidget* parent,RGroups<RFGroupBP,RObjBP,RFChromoBP>* grps)
	: QMenu("Info Box",parent)
	{
		addAction(" Nb Groups: '"+QString::number(grps->Used.GetNb())+"'");
		if(grps->Used.GetNb())
		{
			double sum=0.0;
			RCursor<RFGroupBP> Used(grps->Used);
			for(Used.Start();!Used.End();Used.Next())
				sum+=Used()->GetPerc();
			addAction("Avg use: "+QString::number(sum/static_cast<double>(grps->Used.GetNb()))+"%");
		}
		QInfoBox::Enable=true;
	}

	virtual void mouseReleaseEvent(QMouseEvent*)
	{
		QInfoBox::Enable=false;
		delete(this);
	}
};

//-----------------------------------------------------------------------------
bool QInfoBox::Enable=false;



//-----------------------------------------------------------------------------
//
// QBin
//
//-----------------------------------------------------------------------------
class QDrawGroups::QBin : public QGraphicsRectItem
{
public:
	QWidget* Parent;
	RFGroupBP* Grp;

	QBin(QWidget* parent,RFGroupBP* grp)
		: QGraphicsRectItem(), Parent(parent), Grp(grp)
	{
	}

	void addScene(QGraphicsScene& scene,int x,int y,int w,int h,const QPen& black,const QPen& red,const QBrush& brush,double factor)
	{
		setRect(x,y,w,h);
		setPen(black);
		setBrush(Qt::NoBrush);
		scene.addItem(this);
		if(Grp->GetSize()==Grp->GetMaxSize())
				scene.addRect(x+1,y+1,w-2,h-2,red,brush);
		else
		{
			int l=(int)(Grp->GetSize()*factor);
			scene.addRect(x+1,h-l+y+1,w-2,l,red,brush);
		}
	}

	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		QGraphicsItem::mousePressEvent(event);
		if(event->button()!=Qt::RightButton)
			return;
		QInfoBox* InfoBox(new QInfoBox(Parent,Grp));
		InfoBox->popup(event->screenPos());
	}

	int Compare(const QBin&) const {return(-1);}
};



//-----------------------------------------------------------------------------
//
// class QBoard
//
//-----------------------------------------------------------------------------
class QBoard : public QGraphicsRectItem
{
public:
	QWidget* Parent;
	RGroups<RFGroupBP,RObjBP,RFChromoBP>* Groups;

	QBoard(QWidget* parent,RGroups<RFGroupBP,RObjBP,RFChromoBP>* groups,const QRect& rect)
		: QGraphicsRectItem(rect), Parent(parent), Groups(groups)
	{
	}

	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event)
	{
		QGraphicsItem::mousePressEvent(event);
		if((event->button()!=Qt::RightButton)||(QInfoBox::Enable))
			return;
		QInfoBox* InfoBox(new QInfoBox(Parent,Groups));
		InfoBox->popup(event->screenPos());
	}
};



//-----------------------------------------------------------------------------
//
// class QDrawGroups
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
QDrawGroups::QDrawGroups(QWidget* parent)
	: QWidget(parent),MaxSize(0), Rows(1), Cols(0),
	  RedBrush(Qt::red,Qt::BDiagPattern), BlackPen(Qt::black),
	  RedPen(Qt::red), Groups(0)
{
	IncX=5;
	setupUi(this);
	Draw->setScene(&Scene);
}


//-----------------------------------------------------------------------------
void QDrawGroups::setGroups(RGroups<RFGroupBP,RObjBP,RFChromoBP>* grps)
{
	Groups=grps;
	MaxGroups=Groups->GetNb();
	RCursor<RFGroupBP> Cur(Groups->GetUsedGroups());
	for(Cur.Start();!Cur.End();Cur.Next())
	{
		if(Cur()->GetMaxSize()>MaxSize)
			MaxSize=Cur()->GetMaxSize();
	}
	paintBins();
	repaint();
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
	if(MaxY<0)
		MaxY=10;
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

//------------------------------------------------------------------------------
void QDrawGroups::paintBins(void)
{
	int x,y;

	if(!Groups)
		return;

	QRect Rect(Draw->viewport()->rect());
	Scene.clear();
	Scene.setSceneRect(Rect);
	ComputeGroupsDim(Rect);
	Scene.addItem(new QBoard(this,Groups,Rect));

	// Paint the bins
	RCursor<RFGroupBP> Cur(Groups->GetUsedGroups());
	for(Cur.Start();!Cur.End();Cur.Next())
	{
		ComputeXY(x,y,Cur.GetPos());
		QBin* Bin(new QBin(this,Cur()));
		Bin->addScene(Scene,x,y,(int)Width,MaxY,BlackPen,RedPen,RedBrush,FactorY);
	}
}


//-----------------------------------------------------------------------------
void QDrawGroups::resizeEvent(QResizeEvent* event)
{
	QWidget::resizeEvent(event);
	paintBins();
	repaint();
}



//-----------------------------------------------------------------------------
QDrawGroups::~QDrawGroups()
{
}
