/*

  kvlsigaview.h

  Description - Header.

  (c) 2001 by P. Francq.

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
#ifndef KVLSIGAVIEW_H
#define KVLSIGAVIEW_H


//-----------------------------------------------------------------------------
// include files for R Project
#include <rga/rgasignals.h>
#include <rbp/rdatabpfile.h>
#include <rga/rdebug.h>
using namespace R;


//-----------------------------------------------------------------------------
// include files for Qt
#include <qwidget.h>
#include <qsplitter.h>
#include <qtabwidget.h>


//-----------------------------------------------------------------------------
// include files for current application
#include "kbinpackingview.h"


//-----------------------------------------------------------------------------
// forward declaration
namespace R
{
	class QGAMonitor;
	class QXMLContainer;
	class QDrawGroups;
//	class RFGroupG;
}


//-----------------------------------------------------------------------------
/**
* The KVLSIGAView class provides a representation of a result of a GA that is
* running.
* @author Pascal Francq
*/
class KBPGAView : public KBinPackingView, public RGASignalsReceiver<RFInstBP,RFChromoBP,RFitnessBP>
{
	Q_OBJECT

	/**
	* The tab widget.
	*/
	QTabWidget* TabWidget;
	
	/**
	* The widget that handle statistics about the running GA.	
	*/
	QGAMonitor* Monitor;
	
	/**
	* The widget that handle the debug information of the running GA.
	*/
	QXMLContainer* Debug;
	
	/**
	* The splitter that separate the monitor and the debug part.
	*/
	QSplitter* StatSplitter;
	
	/**
	* The best solution.
	*/
	QDrawGroups* Best;
	
	/**
	* The solutions.
	*/
	QDrawGroups* Sol;
	
	/**
	* Identificator of the current showed solution.
	*/
	unsigned int CurId;

	/**
	* The GA that will be used.
	*/
	RFInstBP* Instance;

	/**
	* Number of generation already executed.
	*/
	unsigned int Gen;

	/**
	* Data needed for the construction of the groups.
	*/
	RGroupDataBP Data;

	RDebugXML DebugFile;

public:

	/**
	* Constructor for the view.
	* @param pDoc           your document instance that the view represents. Create a
	*                       document before calling the constructor or connect an
	*                       already existing document to a new MDI child widget.
	*/
	KBPGAView(KBinPackingDoc* pDoc,QWidget *parent, const char *name,int wflags);

	/**
	* Return the type of the window.
	*/
	virtual BPViewType getType(void) {return(GA);}

	/**
	* GA signal to indicate that a new generation has been done.
	*/
	virtual void receiveGenSig(GenSig* sig);
	
	/**
	* GA signal to interact with the system.
	*/
	virtual void receiveInteractSig(InteractSig* sig);

	/**
	* GA signal to signify that the best chromosome has changed.
	*/
	virtual void receiveBestSig(BestSig* sig);

	/**
	* Run the GA.
	*/
	void RunGA(void);

	/**
	* Pause the GA.
	*/
	void PauseGA(void);

	/**
	* Stop the GA.
	*/
	void StopGA(void);

protected:

	/**
	* Key release event method. The implementation is needed to change the
	* chromosome to show when the user uses the keys "Page Up" and "Page Down".
	* With "Ctrl-G", a dialog box appears to select directly the identificator.
	*/
	virtual void keyReleaseEvent(QKeyEvent* e);

	/**
	* The function that handle the resize event.
	*/
	virtual void resizeEvent(QResizeEvent*);

signals:

	/**
	* Signal to emit after a generation is done.
	*/
	void signalSetGen(const unsigned int gen,const unsigned int best,const double value);

public:

	/**
	* Destruct the view.
	*/
	~KBPGAView();

	// friend classes
	friend class KBinPackingDoc;
};


//-----------------------------------------------------------------------------
#endif
