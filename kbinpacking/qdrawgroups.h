/*

	R Project Library

	QDrawGroups.h

	Widget to draw the bins - Header.

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
#ifndef QDrawGroupsH
#define QDrawGroupsH


//-----------------------------------------------------------------------------
// include files for Qt
#include <qwidget.h>
#include <qpixmap.h>
#include <qpopupmenu.h>


//-----------------------------------------------------------------------------
namespace R{
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// forward class declaration
template<class cGroup,class cObj,class cGroupData,class cGroups> class RGroups;
template<class cObj> class RObjs;
class RFGroupBP;
class RFChromoBP;
class RObjBP;
class RGroupDataBP;


//-----------------------------------------------------------------------------
/**
* The QInfoBox class provides a popupmenu that display informartion about a
* specific object and geometric information.
* @author Pascal Francq
* @short Popup object information
*/
class QInfoBox : public QPopupMenu
{
	/**
	* Widget that must have the focus after.
	*/
	QWidget* afterFocus;

public:

	/**
	* Constructor of the popup.
	* @param parent        Parent of the widget.
	* @param grp           Group.
	* @param objs          Objects.
	*/
	QInfoBox(QWidget* parent,RFGroupBP* grp,RObjs<RObjBP>* objs);

	/**
	* Constructor of the popup.
	* @param parent        Parent of the widget.
	* @param grps          Groups.
	*/
	QInfoBox(QWidget* parent,RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps);

protected:

	/**
	* Mouse release event method. When the mouse bouton is released, the popup
	* is closed.
	*/
	virtual void mouseReleaseEvent(QMouseEvent*);
};


//-----------------------------------------------------------------------------
/**
* @author Pascal Francq
*/
class QDrawGroups : public QWidget
{
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
	* A pixmap to hold the display.
	*/
	QPixmap* pixmap;

	/**
	* Number of rows for groups.
	*/
	unsigned int Rows;

	/**
	* Number of groups in a row.
	*/
	unsigned int Cols;

	/**
	* Has the display changed.
	*/
	bool Changed;

	/**
	* A black brush.
	*/
	QBrush brRed;

	/**
	* Groups to paint.
	*/
	RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* Groups;

	/**
	* Objects that were placed.
	*/
	RObjs<RObjBP>* Objs;

public:

	/**
	* Constructor of the Widget.
	* @param parent         Parent of the widget.
	* @param objs           Objects.
	* @param name           Name of the widget.
	*/
	QDrawGroups(QWidget* parent,RObjs<RObjBP>* objs,const char* name=0);

	/**
	* Constructor of the Widget.
	* @param parent         Parent of the widget.
	* @param grps           Groups.
	* @param objs           Objects.
	* @param name           Name of the widget.
	*/
	QDrawGroups(QWidget* parent,RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps,RObjs<RObjBP>* objs,const char* name=0);

	/**
	* The widget has changed and has to be repainted.
	*/
	void setChanged(void) {Changed=true;repaint();}

	/**
	* Set the groups.
	*/
	void setGroups(RGroups<RFGroupBP,RObjBP,RGroupDataBP,RFChromoBP>* grps);

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
	* Compute the index of a group given (X,Y) or NoGroup if nothing.
	*/
	unsigned int ComputeId(const unsigned int x,const unsigned int y);

	/**
	* Paint event method.
	*/
	virtual void paintEvent(QPaintEvent*);

	/**
	* Resize event method.
	*/
	virtual void resizeEvent(QResizeEvent*);

	/**
	* Mouse button press event method.
	* @param e             MouseEvent info.
	*/
	virtual void mousePressEvent(QMouseEvent* e);

public:

	/**
	* Destructor of the widget.
	*/
	~QDrawGroups();
};


}  //------- End of namespace RBP ---------------------------------------------


//-----------------------------------------------------------------------------
#endif
