/*

	Bin Packing GUI

	KBPGAView.h

	GA Window - Header.

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
#ifndef KBPGAView_H
#define KBPGAView_H


//-----------------------------------------------------------------------------
// include files for R Project
#include <rbpproblem.h>
#include <rdebug.h>
#include <robject.h>
#include <rqt.h>
using namespace std;
using namespace R;
using namespace RBP;


//-----------------------------------------------------------------------------
// include files for KDE/Qt
#include <QtGui/QMdiSubWindow>


//---------------------------------------------------------------------------
// include files for current application
#include <ui_kbpgaview.h>



//-----------------------------------------------------------------------------
/**
* The KVLSIGAView class provides a representation of a result of a GA that is
* running.
* @author Pascal Francq
*/
class KBPGAView : public QMdiSubWindow, public Ui_KBPGAView, public RObject
{
	Q_OBJECT

	/**
	* Identificator of the current showed solution.
	*/
	size_t CurId;

	/**
	* The GA that will be used.
	*/
	RFInstBP* Instance;

	/**
	* Number of generation already executed.
	*/
	size_t Gen;

	/**
	 * Number of windows.
	 */
	static size_t WinNb;

	/*
	 * Is the GA Running ?
	*/
	bool Running;

public:

	/**
	* Constructor for the view.
	* @param problem         The Problem.
	*/
	KBPGAView(RBPProblem* problem);

	/**
	* Run the GA.
	*/
	void RunGA(void);

	/**
	* Pause the GA.
	*/
	void PauseGA(void);

	/**
	 * See if the GA is running.
    * @return true if yes.
    */
	bool IsRunning(void) const {return(Running);}

	/**
	 * See if the GA is end.
    * @return true if yes.
    */
	bool End(void) const;

protected:

	/**
	 * catch a generation notification.
	 */
	void Generation(const R::RNotification& notification);

	/**
	 * catch a best notification.
	 */
	void BestChromo(const R::RNotification& notification);

	/**
	 * catch a interact notification.
	 */
	void Interact(const R::RNotification& notification);

	/**
	* Key release event method. The implementation is needed to change the
	* chromosome to show when the user uses the keys "Page Up" and "Page Down".
	*/
	virtual void keyReleaseEvent(QKeyEvent* e);

public:

	/**
	* Destruct the view.
	*/
	~KBPGAView(void);

	// friend classes
	friend class KBinPackingDoc;
};


//-----------------------------------------------------------------------------
#endif
