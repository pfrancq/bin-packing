/*

	R Project Library

	kbinpacking.h

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
#ifndef KBINPACKING_H
#define KBINPACKING_H
 

//-----------------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


//-----------------------------------------------------------------------------
// include files for Qt
#include <qstrlist.h>
#include <qworkspace.h>


//-----------------------------------------------------------------------------
// include files for KDE
#include <kapp.h>
#include <kmainwindow.h>
#include <kaction.h>


//-----------------------------------------------------------------------------
// forward declaration of the KBinPacking classes
class KBinPackingDoc;
class KBinPackingView;



//-----------------------------------------------------------------------------
/**
* The base class for KBinPacking application windows.
* @see KMainWindow
* @see KApplication
* @see KConfig
* @see KAccel
*
* @author Pascal Francq
* @short Bin Packing Application.
*/
class KBinPackingApp : public KMainWindow
{
	Q_OBJECT

	/**
	* The configuration object of the application.
	*/
	KConfig* config;

	/**
	* pWorkspace is the MDI frame widget that handles MDI child widgets.
	* Inititalized in initView().
	*/
	QWorkspace* pWorkspace;

	/**
	* The printer instance.
	*/
	QPrinter* printer;

	/**
	* A counter that gets increased each time the user creates a new document
	* with "File"->"New".
	*/
	int untitledCount;

	/**
	* A list of all open documents. If the last window of a document gets
	* closed, the installed eventFilter removes this document from the list.
	* The document list is checked for modified documents when the user is
	* about to close the application.
	*/
	QList<KBinPackingDoc> *pDocList;

public:

	/**
	* Construtor of KBinPackingApp, calls all init functions to create the
	* application.
	* @see initMenuBar initToolBar
	*/
	KBinPackingApp(void);

	/**
	* Opens a file specified by commandline option.
	*/
	void openDocumentFile(const KURL& url=0);

protected:

	/**
	* queryClose is called by KTMainWindow on each closeEvent of a window.
	* Against the default implementation (only returns true), this overridden
	* function retrieves all modified documents from the open document list and
	* asks the user to select which files to save before exiting the
	* application.
	* @see KTMainWindow#queryClose
	* @see KTMainWindow#closeEvent
	*/
	virtual bool queryClose(void);

	/**
	* queryExit is called by KTMainWindow when the last window of the
	* application is going to be closed during the closeEvent(). Against the
	* default implementation that just returns true, this calls saveOptions()
	* to save the settings of the last window's properties.
	* @see KTMainWindow#queryExit
	* @see KTMainWindow#closeEvent
	*/
	virtual bool queryExit(void);

	/**
	* Saves the window properties for each open window during session end to
	* the session config file, including saving the currently opened file by a
	* temporary filename provided by KApplication.
	* @see KTMainWindow#saveProperties
	*/
	virtual void saveProperties(KConfig* _cfg);

	/**
	* Reads the session config file and restores the application's state
	* including the last opened files and documents by reading the temporary
	* files saved by saveProperties().
	* @see KTMainWindow#readProperties
	*/
	virtual void readProperties(KConfig* _cfg);

	/**
	* Event filter to catch close events for MDI child windows and is installed
	* in createClient() on every child window. Closing a window calls the
	* eventFilter first which removes the view from the connected documents'
	* view list. If the last view is going to be closed, the eventFilter()
	* tests if the document is modified; if yes, it asks the user to save the
	* document. If the document title contains "Untitled", slotFileSaveAs()
	* gets called to get a save name and path.
	*/
	virtual bool eventFilter(QObject* object,QEvent* event);

	/**
	* Creates a new child window. The document that will be connected to it has
	* to be created before and the instances filled, with e.g. openDocument().
	* Then call createClient() to get a new MDI child window.
	* @see KBinPackingDoc#addView
	* @see KBinPackingDoc#openDocument
	* @param doc            pointer to the document instance that the view will
	*                       be connected to.
	*/
	void createClient(KBinPackingDoc* doc);

private slots:

	/**
	* Clears the document in the actual view to reuse it as the new document.
	*/
	void slotFileNew(void);

	/**
	* Open a file and load it into the document.
	*/
	void slotFileOpen(void);

	/**
	* Opens a file from the recent files menu.
	*/
	void slotFileOpenRecent(const KURL& url);

	/**
	* Save a document.
	*/
	void slotFileSave(void);

	/**
	* Save a document by a new filename.
	*/
	void slotFileSaveAs(void);

	/**
	* Asks for saving if the file is modified, then closes the actual file and
	* window.
	*/
	void slotFileClose(void);

	/**
	* Print the actual file.
	*/
	void slotFilePrint(void);

	/**
	* Closes all documents and quits the application.
	*/
	void slotFileQuit(void);

	/**
	* Reverts the last user action for the active window.
	*/
	void slotEditUndo(void);

	/**
	* Put the marked text/object into the clipboard and remove it from the
	* document.
	*/
	void slotEditCut(void);

	/**
	* Put the marked text/object into the clipboard.
	*/
	void slotEditCopy(void);

	/**
	* Paste the clipboard into the document.
	*/
	void slotEditPaste(void);

	/**
	* Toggles the toolbar.
	*/
	void slotViewToolBar(void);

	/**
	* Toggles the statusbar.
	*/
	void slotViewStatusBar(void);

	/**
	* Creates a new view for the document in the active child window and adds
	* the new view to the list of views the document maintains.
	*/
	void slotWindowNewWindow(void);

	/**
	* Changes the statusbar contents for the standard label permanently, used
	* to indicate current actions.
	* @param text           Text to display in the statusbar.
	*/
	void slotStatusMsg(const QString& text);

	/**
	* Gets called when the window menu is activated; recreates the window menu
	* with all opened window titles.
	*/
	void windowMenuAboutToShow(void);

	/**
	* Activates the MDI child widget when it gets selected from the window menu.
	*/
	void windowMenuActivated(int id);

	/**
	* Tile all the windows.
	*/
	void slotWindowTile(void);

	/**
	* Cascade all the windows.
	*/
  void slotWindowCascade(void);

private:

	/**
	* Save general Options like all bar positions and status as well as the
	* geometry and the recent file list to the configuration file.
	*/
	void saveOptions(void);

	/**
	* Read general Options again and initialize all variables like the recent
	* file list.
	*/
	void readOptions(void);

	/**
	* Initializes the KActions of the application.
	*/
	void initActions(void);

	/**
	* Sets up the statusbar for the main window by initialzing a status label.
	*/
	void initStatusBar(void);

	/**
	* Creates the main view of the KTMainWindow instance and initializes the
	* MDI view area including any needed connections.
	*/
	void initView(void);

public:

	/**
	* Destructor of the Application.
	*/
	~KBinPackingApp(void);

	// KAction pointers to enable/disable actions.
	KAction* fileNew;
	KAction* fileOpen;
	KRecentFilesAction* fileOpenRecent;
	KAction* fileSave;
	KAction* fileSaveAs;
	KAction* fileClose;
	KAction* filePrint;
	KAction* fileQuit;
	KAction* editCut;
	KAction* editCopy;
	KAction* editPaste;
	KAction* windowNewWindow;
	KAction* windowTile;
	KAction* windowCascade;
	KToggleAction* viewToolBar;
	KToggleAction* viewStatusBar;
	KActionMenu* windowMenu;
};


//-----------------------------------------------------------------------------
#endif // KBINPACKING_H
