/*

	R Project Library

	kbinpackingdoc.h

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
#ifndef KBINPACKINGDOC_H
#define KBINPACKING_H


//-----------------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


//-----------------------------------------------------------------------------
// include files for R Project
#include <rbp/rdatabpfile.h>


//-----------------------------------------------------------------------------
// include files for Qt
#include <qobject.h>
#include <qstring.h>
#include <qlist.h>


//-----------------------------------------------------------------------------
// include files for KDE
#include <kurl.h>


//-----------------------------------------------------------------------------
// forward declaration of the KBinPacking classes
class KBinPackingView;


//-----------------------------------------------------------------------------
/**
* KBinPackingDoc provides a document object for a document-view model.
* @author Pascal Francq
* @short Bin Packing Document.
*/
class KBinPackingDoc : public QObject , public RBP::RDataBPFile
{
	Q_OBJECT

	friend KBinPackingView;

public:

	/**
	* Constructor for the fileclass of the application.
	*/
	KBinPackingDoc(void);

	/**
	* Adds a view to the document which represents the document contents.
	* Usually this is your main view.
	*/
	void addView(KBinPackingView* view);

	/**
	* Removes a view from the list of currently connected views.
	*/
	void removeView(KBinPackingView* view);

	/**
	* Gets called if a view is removed or added.
	*/
	void changedViewList(void);

	/**
	* Returns the first view instance.
	*/
	KBinPackingView* firstView(void) {return pViewList->first();}

	/**
	* Returns true, if the requested view is the last view of the document.
	*/
	bool isLastView(void);

	/**
	* This method gets called when the user is about to close a frame window.
	* It checks, if more than one view is connected to the document (then the
	* frame can be closed), if pFrame is the last view and the document is
	* modified, the user gets asked if he wants to save the document.
	*/
	bool canCloseFrame(KBinPackingView* pFrame);

	/**
	* Sets the modified flag for the document after a modifying action on the
	* view connected to the document.
	*/
	void setModified(bool _m=true) {modified=_m;}

	/**
	* Returns if the document is modified or not. Use this to determine if your
	* document needs saving by the user on closing.
	*/
	bool isModified(void) {return modified;}

	/**
	* Deletes the document's contents.
	*/
	void deleteContents(void);

	/**
	* Initializes the document generally.
	*/
	bool newDocument(void);

	/**
	* Closes the acutal document.
	*/
	void closeDocument(void);

	/**
	* Loads the document by filename and format and emits the updateViews()
	* signal.
	*/
	bool openDocument(const KURL& url,const char* format=0);

	/**
	* Saves the document under filename and format.
	*/
	bool saveDocument(const KURL& url,const char* format=0);

	/**
	* Returns the KURL of the document.
	*/
	const KURL& URL(void) const;

	/**
	* Sets the URL of the document.
	*/
	void setURL(const KURL& url);

public slots:

	/**
	* Calls repaint() on all views connected to the document object and is
	* called by the view by which the document has been changed. As this view
	* normally repaints itself, it is excluded from the paintEvent.
	*/
	void updateAllViews(KBinPackingView* sender);

private:

	/**
	* The modified flag of the current document.
	*/
	bool modified;

	/**
	* The URL representing the document.
	*/
	KURL doc_url;

	/**
	* The list of the views currently connected to the document.
	*/
	QList<KBinPackingView> *pViewList;

public:

	/**
	* Destructor for the fileclass of the application.
	*/
	~KBinPackingDoc(void);

	// friend classes
	friend class KBPPrjView;
	friend class KBPHeuristicView;
	friend class KBPGAView;
};


//-----------------------------------------------------------------------------
#endif // KBINPACKINGDOC_H
