  /*

	R Project Library

	kbinpackingview.h

	Description - Header.

	(C) 2001 by Pascal Francq

	Version $Revision$

	Last Modify: $Date$

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
#ifndef KBINPACKINGVIEW_H
#define KBINPACKINGVIEW_H


//-----------------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


//-----------------------------------------------------------------------------
// include files for Qt
#include <qwidget.h>


//-----------------------------------------------------------------------------
// Enum declaration
/**
* Defines all the possible type of view for a document.
*/
enum BPViewType{Nothing,Project,Heuristic,GA};


//-----------------------------------------------------------------------------
// forward class declaration
class KBinPackingDoc;


//-----------------------------------------------------------------------------
/**
* The KBinPackingView class provides the view widget for the document instance
* connected to it and is displayed as a MDI child window in the main view area
* of the KBinPackingApp class instance.
* @author Pascal Francq
* @short Bin Packing View.
*/
class KBinPackingView : public QWidget
{
	Q_OBJECT

	friend KBinPackingDoc;

public:

	/**
	* Constructor for the view
	* @param pDoc  your document instance that the view represents.
	*/
	KBinPackingView(KBinPackingDoc* pDoc,QWidget* parent  ,const char* name,int wflags);

	/**
	* Returns a pointer to the document connected to the view.
	*/
	KBinPackingDoc* getDocument(void) const;

	/**
	* Gets called to redraw the document contents if it has been modified.
	*/
	void update(KBinPackingView* pSender);

	/**
	* Contains the implementation for printing functionality and gets called by
	* KBinPackingApp::slotFilePrint().
	*/
	void print(QPrinter* pPrinter);

	/**
	* Return the type of the window.
	*/
	virtual BPViewType getType(void)=0;

protected:

	/**
	* Overwritten QWidget::closeEvent() to catch closing views. Does nothing,
	* as the closeEvents for KBinPackingView's are processed by
	* KBinPackingApp::eventFilter(), so this overwitten closeEvent is necessary
	* and has to be empty. Don't overwrite this method !
	*/
	virtual void closeEvent(QCloseEvent* e);

	/**
	* The document connected to the view, specified in the constructor.
	*/
	KBinPackingDoc* doc;

public:

	/**
	* Destructor for the main view.
	*/
	~KBinPackingView(void);
};


//-----------------------------------------------------------------------------
#endif // KBINPACKINGVIEW_H
