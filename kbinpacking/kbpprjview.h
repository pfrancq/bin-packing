/*

	Bin Packing GUI

	KBPPrjView.h

	Project Window - Header.

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
#ifndef KBPPrjView_H
#define KBPPrjView_H


//-----------------------------------------------------------------------------
// include files for Bin Packing
#include <rbpproblem.h>
using namespace R;
using namespace RBP;


//-----------------------------------------------------------------------------
// include files for KDE/Qt
#include <QtGui/QMdiSubWindow>


//---------------------------------------------------------------------------
// include files for current application
#include <ui_kbpprjview.h>


//-----------------------------------------------------------------------------
/**
* The KBPPrjView provides a representation of a project window.
* @author Pascal Francq
*/
class KBPPrjView : public QMdiSubWindow, public Ui_KBPPrjView
{
	Q_OBJECT

	/**
	* Problem
	*/
	RBPProblem* Problem;

public:

	/**
	* Construct the project view.
	* @param problem         The problem
	* @param uri             URI of the project file.
	*/
	KBPPrjView(RBPProblem* problem,const QString& uri);

	/**
	* Construct the project tree.
	*/
	void createPrj(void);

	/**
	* Destruct the project view.
	*/
	~KBPPrjView(void);
};


//-----------------------------------------------------------------------------
#endif
