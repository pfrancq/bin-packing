/*

	Bin Packing GUI

	QDrawGroups.h

	Widget to Draw Bins - Header.

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
#ifndef QDrawGroupsH
#define QDrawGroupsH


//-----------------------------------------------------------------------------
// include files for Qt
#include <qwidget.h>
#include <qpixmap.h>
#include <qmenu.h>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsPolygonItem>


//-----------------------------------------------------------------------------
// include files for Bin Packing
#include <rbpproblem.h>
using namespace std;
using namespace R;
using namespace RBP;


//-----------------------------------------------------------------------------
// include files for current application
#include <ui_qdrawgroups.h>



//-----------------------------------------------------------------------------
/**
* @author Pascal Francq
*/
class QDrawGroups : public QWidget, public Ui_QDrawGroups
{
	class QBin;

	Q_OBJECT

	/**
	* Width of group representation.
	*/
	double Width;

	/**
	* X Incremental for the groups.
	*/
	double IncX;

	/**
	* Maximal Y size.
	*/
	int MaxY;

	/**
	* Factor to multiply to the total size of a group.
	*/
	double FactorY;

	/**
	* Maximal size of the group.
	*/
	unsigned int MaxSize;

	/**
	* Maximal number of groups.
	*/
	unsigned int MaxGroups;

	/**
	* Number of rows for groups.
	*/
	unsigned int Rows;

	/**
	* Number of groups in a row.
	*/
	unsigned int Cols;

	/**
	* A red brush.
	*/
	QBrush RedBrush;

	/**
	 * A black pen.
	 */
	QPen BlackPen;

	/**
	 * A red pen.
	 */
	QPen RedPen;

	/**
	 * The scene.
	 */
	QGraphicsScene Scene;

	/**
	* Groups to paint.
	*/
	RGroups<RFGroupBP,RObjBP,RFChromoBP>* Groups;

public:

	/**
	* Constructor of the Widget.
	* @param parent         Parent of the widget.
	*/
	QDrawGroups(QWidget* parent);

	/**
	* Set the groups.
	*/
	void setGroups(RGroups<RFGroupBP,RObjBP,RFChromoBP>* grps);

	/**
	* Create a scene with the bins.
	*/
	void paintBins(void);

protected:

	/**
	* Compute the dimensions of the groups.
	*/
	void ComputeGroupsDim(QRect& r);

	/**
	* Compute the X and Y position for a given index of group.
	*/
	void ComputeXY(int& x,int &y,const unsigned idx);

	/**
	* Resize event method.
	*/
	virtual void resizeEvent(QResizeEvent*);

public:

	/**
	* Destructor of the widget.
	*/
	~QDrawGroups();
};


//-----------------------------------------------------------------------------
#endif
