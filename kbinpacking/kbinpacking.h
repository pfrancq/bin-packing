/*

	Bin Packing GUI

	KBinPacking.h

	Main Window - Header.

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
#ifndef KBinPacking_H
#define KBinPacking_H


//-----------------------------------------------------------------------------
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


//-----------------------------------------------------------------------------
// include files for R Project
#include <rqt.h>
#include <rapplication.h>
using namespace R;


//-----------------------------------------------------------------------------
// include files for Qt/KDE
#include <QtGui/QMdiArea>
#include <QtGui/QLabel>
#include <QtCore/QList>
#include <kaction.h>
#include <krecentfilesaction.h>
#include <kxmlguiwindow.h>


//-----------------------------------------------------------------------------
// include files for the Bin Packing
#include <rbpproblem.h>
using namespace RBP;


//-----------------------------------------------------------------------------
/**
* The KBinPacking application windows.
*
* @author Pascal Francq
* @short Bin Packing Application.
*/
class KBinPacking : public KXmlGuiWindow, public RApplication
{
	Q_OBJECT

	/**
	 * Desktop of the application.
	 */
	QMdiArea* Desktop;

	/**
	 * Label to hold an image representing the status of the file opened.
	 */
	QLabel* Status;

	/**
	 * Connect to the session.
	 */
	KAction* aFileOpen;

	/**
	 * Initialize a new GA.
	 */
	KAction* aGAInit;

	/**
	 * Satrt a GA.
	 */
	KAction* aGAStart;

	/**
	 * Pause a GA.
	 */
	KAction* aGAPause;

	/**
	 * Open a recent file.
	 */
	KRecentFilesAction* aFileOpenRecent;

	/**
	 * All available actions once a file is connected.
	 */
	QList<KAction*> Actions;

	/**
	* Run the heuristics in step mode.
	*/
	bool Step;

	/**
	* Maximum number of generation.
	*/
	size_t MaxGen;

	/**
	* Step of generation.
	*/
	size_t StepGen;

	/**
	* Size of the Population.
	*/
	size_t PopSize;

	/**
	* A log file.
	*/
	RTextFile* Log;

	/**
	* Debug file.
	*/
	RDebugXML* Debug;

	/**
	* The Log file.
	*/
	RString LogFileName;

	/**
	* The debug file.
	*/
	RString DebugFileName;

	/**
	 * Bin packing problem.
    */
	 RBPProblem* Problem;

public:

	/**
	* Construtor of KBinPackingApp.
	* @param argc            Number of arguments.
	* @param argv            Values of arguments.
	*/
	KBinPacking(int argc, char *argv[]);

	/**
	 * Get the problem.
    */
	RBPProblem* GetProblem(void) const {return(Problem);}

private:

	/**
	 * Create an action for a given menu item.
	 * @param title          Title of the menu item.
	 * @param name           Name of the action (as appearing in .rc file).
	 * @param slot           Corresponding slot.
	 * @param icon           Icon associated.
	 * @param key            Shortcut associated.
	 */
	KAction* addAction(const char* title,const char* name,const char* slot,const char* icon=0,const char* key=0);

	/**
	* Initializes the KActions of the application.
	*/
	void initActions(void);

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
	* Create the configuration structure. New parameters can be added by
	* defining a new method.
	*/
	virtual void CreateConfig(void);

	/**
	* Initialization of the application.
	*/
	virtual void Init(void);

public:

	/**
	 * Apply the configuration.
    */
	void Apply(void);

private:

	/**
	* Changes the status bar contents for the standard label permanently, used
	* to indicate current actions.
	* @param text            Text that is displayed in the status bar.
	*/
	void statusMsg(const QString& text);

	/**
	 * Call when a file is opened or not. Basically, it enable/disable
	 * the menu items.
	 * @param opened      Opened?
	 */
	void fileOpened(bool opened);

	/**
	* Open a specific file.
	* @param url             URL of the file.
	*/
	void openDocumentFile(const KUrl& url);

private slots:

	/**
	 * Set the preferences.
	 */
	void optionsPreferences(void);

public slots:

	/**
	 * Called when a window was activated.
	 * @param window          Window activated (or 0 if no more window).
    */
	void subWindowActivated(QMdiSubWindow* window);

private slots:
	
	/**
	* Open a file and load it into the document.
	*/
	void openFile(void);

	/**
	* Opens a file from the recent files menu.
	*/
	void openRecentFile(const KUrl& url);

	/**
	* Asks for saving if the file is modified, then closes the actual file and
	* window.
	*/
	void closeFile(void);

	/**
	* Closes all documents and quits the application.
	*/
	void applicationQuit(void);

	/**
	* Initialize the GA.
	*/
	void GAInit(void);

	/**
	* Start the GA.
	*/
	void GAStart(void);

	/**
	* Pause the GA.
	*/
	void GAPause(void);

public:

	/**
	* Destructor of the Application.
	*/
	~KBinPacking(void);

	// friend classes
	friend class KBPGAView;
};


//-----------------------------------------------------------------------------
/**
* Global pointer to the KMainWindow of the Application.
*/
extern KBinPacking* theApp;


//-----------------------------------------------------------------------------
#endif // KBINPACKING_H
