/*

	R Project Library

	kbinpacking.cpp

	Description - Implementation.

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
// include files for Qt
#include <qdir.h>
#include <qprinter.h>
#include <qvbox.h>
#include <qwhatsthis.h>
#include <qtooltip.h>
#include <qtoolbutton.h>
#include <qstring.h>


//-----------------------------------------------------------------------------
// include files for KDE
#include <kiconloader.h>
#include <kmessagebox.h>
#include <kfiledialog.h>
#include <kmenubar.h>
#include <klocale.h>
#include <kconfig.h>
#include <kstdaction.h>


//-----------------------------------------------------------------------------
// application specific includes
#include "kbinpacking.h"
#include "kbinpackingview.h"
#include "kbinpackingdoc.h"
#include "kbpprjview.h"
#include "kbpheuristicview.h"



//-----------------------------------------------------------------------------
//
// class KBinPacking
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBinPackingApp::KBinPackingApp(void)
	: KMainWindow(0,"KBinPacking")
{
	config=kapp->config();
	printer = new QPrinter;
	untitledCount=0;
	pDocList = new QList<KBinPackingDoc>();
	pDocList->setAutoDelete(true);

	initStatusBar();
	initView();
	initActions();
	readOptions();
	// disable actions at startup
	fileNew->setEnabled(false);
	fileSave->setEnabled(false);
	fileSaveAs->setEnabled(false);
	filePrint->setEnabled(false);
	editCut->setEnabled(false);
	editCopy->setEnabled(false);
	editPaste->setEnabled(false);
	windowNewWindow->setEnabled(false);
	heuristicFF->setEnabled(false);
	heuristicRun->setEnabled(false);
	heuristicNext->setEnabled(false);
}

//-----------------------------------------------------------------------------
void KBinPackingApp::initActions(void)
{
	// Menu "File"
	fileNew = KStdAction::openNew(this, SLOT(slotFileNew()), actionCollection());
	fileOpen = KStdAction::open(this, SLOT(slotFileOpen()), actionCollection());
	fileOpenRecent = KStdAction::openRecent(this, SLOT(slotFileOpenRecent(const KURL&)), actionCollection());
	fileSave = KStdAction::save(this, SLOT(slotFileSave()), actionCollection());
	fileSaveAs = KStdAction::saveAs(this, SLOT(slotFileSaveAs()), actionCollection());
	fileClose = KStdAction::close(this, SLOT(slotFileClose()), actionCollection());
	filePrint = KStdAction::print(this, SLOT(slotFilePrint()), actionCollection());
	fileQuit = KStdAction::quit(this, SLOT(slotFileQuit()), actionCollection());
	fileNew->setStatusText(i18n("Creates a new document"));
	fileOpen->setStatusText(i18n("Opens an existing document"));
	fileOpenRecent->setStatusText(i18n("Opens a recently used file"));
	fileSave->setStatusText(i18n("Saves the actual document"));
	fileSaveAs->setStatusText(i18n("Saves the actual document as..."));
	fileClose->setStatusText(i18n("Closes the actual document"));
	filePrint ->setStatusText(i18n("Prints out the actual document"));
	fileQuit->setStatusText(i18n("Quits the application"));

	// Menu "Edit"
	editCut = KStdAction::cut(this, SLOT(slotEditCut()), actionCollection());
	editCopy = KStdAction::copy(this, SLOT(slotEditCopy()), actionCollection());
	editPaste = KStdAction::paste(this, SLOT(slotEditPaste()), actionCollection());
	editCut->setStatusText(i18n("Cuts the selected section and puts it to the clipboard"));
	editCopy->setStatusText(i18n("Copies the selected section to the clipboard"));
	editPaste->setStatusText(i18n("Pastes the clipboard contents to actual position"));
	
	// Menu "Heuristic"
	heuristicFF=new KAction(i18n("&First Fit Heuristic"),KAccel::stringToKey("Alt+F"),this,SLOT(slotHeuristicFF(void)),actionCollection(),"heuristic_ff");
	heuristicRun=new KAction(i18n("&Run Heuristic"),"run",KAccel::stringToKey("Alt+R"),this,SLOT(slotHeuristicRun(void)),actionCollection(),"heuristic_run");
	heuristicNext=new KAction(i18n("&Next step for Heuristic"),"next",KAccel::stringToKey("Alt+N"),this,SLOT(slotHeuristicNext(void)),actionCollection(),"heuristic_next");

	// Menu "View"
	viewToolBar = KStdAction::showToolbar(this, SLOT(slotViewToolBar()), actionCollection());
	viewStatusBar = KStdAction::showStatusbar(this, SLOT(slotViewStatusBar()), actionCollection());
	viewToolBar->setStatusText(i18n("Enables/disables the toolbar"));
	viewStatusBar->setStatusText(i18n("Enables/disables the statusbar"));

	// Menu "Window"
	windowNewWindow = new KAction(i18n("New &Window"), 0, this, SLOT(slotWindowNewWindow()), actionCollection(),"window_new_window");
	windowTile = new KAction(i18n("&Tile"), 0, this, SLOT(slotWindowTile()), actionCollection(),"window_tile");
	windowCascade = new KAction(i18n("&Cascade"), 0, this, SLOT(slotWindowCascade()), actionCollection(),"window_cascade");
	windowMenu = new KActionMenu(i18n("&Window"), actionCollection(), "window_menu");
	connect(windowMenu->popupMenu(), SIGNAL(aboutToShow()), this, SLOT(windowMenuAboutToShow()));

	createGUI();
}


//-----------------------------------------------------------------------------
void KBinPackingApp::initStatusBar(void)
{
	statusBar()->insertItem(i18n("Ready."),1);
}


//-----------------------------------------------------------------------------
void KBinPackingApp::initView(void)
{
	QVBox* view_back = new QVBox(this);
	view_back->setFrameStyle(QFrame::StyledPanel|QFrame::Sunken);
	pWorkspace = new QWorkspace(view_back);
	connect(pWorkspace, SIGNAL(windowActivated(QWidget*)), this, SLOT(slotWindowActivated(QWidget*)));
	setCentralWidget(view_back);
}


//-----------------------------------------------------------------------------
void KBinPackingApp::createClient(KBinPackingDoc* doc)
{
	KBPPrjView* w = new KBPPrjView(doc,pWorkspace,"Project: "+doc->URL().fileName(),WDestructiveClose);
	w->installEventFilter(this);
	doc->addView(w);
	w->setIcon(kapp->miniIcon());
	w->show();
	w->resize(pWorkspace->sizeHint());
}


//-----------------------------------------------------------------------------
void KBinPackingApp::openDocumentFile(const KURL& url)
{
	slotStatusMsg(i18n("Opening file..."));
	KBinPackingDoc* doc;
	// check, if document already open. If yes, set the focus to the first view
	for(doc=pDocList->first();doc>0;doc=pDocList->next())
	{
		if(doc->URL()==url)
		{
			KBinPackingView* view=doc->firstView();
			view->setFocus();
			return;
		}
	}
	doc = new KBinPackingDoc();
	pDocList->append(doc);
	doc->newDocument();
	// Creates an untitled window if file is 0	
	if(url.isEmpty())
	{
		untitledCount+=1;
		QString fileName=QString(i18n("Untitled%1")).arg(untitledCount);
		KURL url;
		url.setFileName(fileName);
		doc->setURL(url);
	}
	else
	{
		if(!doc->openDocument(url))
		{
			KMessageBox::error (this,i18n("Could not open document !"), i18n("Error !"));
			delete doc;
			return;	
		}
		fileOpenRecent->addURL(url);
	}
	createClient(doc);
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::saveOptions(void)
{
	config->setGroup("General Options");
	config->writeEntry("Geometry", size());
	config->writeEntry("Show Toolbar", toolBar()->isVisible());
	config->writeEntry("Show Statusbar",statusBar()->isVisible());
	config->writeEntry("ToolBarPos", (int) toolBar("mainToolBar")->barPos());
	fileOpenRecent->saveEntries(config,"Recent Files");
}


//-----------------------------------------------------------------------------
void KBinPackingApp::readOptions(void)
{
	config->setGroup("General Options");

	// bar status settings
	bool bViewToolbar = config->readBoolEntry("Show Toolbar", true);
	viewToolBar->setChecked(bViewToolbar);
	slotViewToolBar();

	bool bViewStatusbar = config->readBoolEntry("Show Statusbar", true);
	viewStatusBar->setChecked(bViewStatusbar);
	slotViewStatusBar();

	// bar position settings
	KToolBar::BarPosition toolBarPos;
	toolBarPos=(KToolBar::BarPosition) config->readNumEntry("ToolBarPos", KToolBar::Top);
	toolBar("mainToolBar")->setBarPos(toolBarPos);

	// initialize the recent file list
	fileOpenRecent->loadEntries(config,"Recent Files");

	QSize size=config->readSizeEntry("Geometry");
	if(!size.isEmpty())
	{
		resize(size);
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::saveProperties(KConfig* /*_cfg*/)
{
}


//-----------------------------------------------------------------------------
void KBinPackingApp::readProperties(KConfig* /*_cfg*/)
{
}


//-----------------------------------------------------------------------------
bool KBinPackingApp::queryClose(void)
{
	QStringList saveFiles;
	KBinPackingDoc* doc;
	if(pDocList->isEmpty())
		return true;

	for(doc=pDocList->first();doc!=0;doc=pDocList->next())
	{
		if(doc->isModified())
			saveFiles.append(doc->URL().fileName());
	}
	if(saveFiles.isEmpty())
		return true;

	switch(KMessageBox::questionYesNoList(this,i18n("One or more documents have been modified.\nSave changes before exiting?"),saveFiles))
	{
		case KMessageBox::Yes:
			for(doc=pDocList->first(); doc!=0;doc=pDocList->next())
			{
				if(doc->URL().fileName().contains(i18n("Untitled")))
					slotFileSaveAs();
				else
				{
					if(!doc->saveDocument(doc->URL()))
					{
						KMessageBox::error (this,i18n("Could not save the current document !"), i18n("I/O Error !"));
						return false;
					}
				}
			}
			return true;

		case KMessageBox::No:
		default:
			return true;
	}
}


//-----------------------------------------------------------------------------
bool KBinPackingApp::queryExit(void)
{
	saveOptions();
	return true;
}


//-----------------------------------------------------------------------------
bool KBinPackingApp::eventFilter(QObject* object,QEvent* event)
{
	if((event->type() == QEvent::Close)&&((KBinPackingApp*)object!=this))
	{
		QCloseEvent* e=(QCloseEvent*)event;

		KBinPackingView* pView=(KBinPackingView*)object;
		KBinPackingDoc* pDoc=pView->getDocument();
		if(pDoc->canCloseFrame(pView))
		{
			pDoc->removeView(pView);
			if(!pDoc->firstView())
				pDocList->remove(pDoc);
			e->accept();
		}
		else
			e->ignore();
	}
	return QWidget::eventFilter(object,event);    // standard event processing
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotHeuristicFF(void)
{
	KApplication::kApplication()->processEvents(1000);
	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m&&(m->getType()==Project))
	{
		KBinPackingDoc* doc = m->getDocument();
		KBPHeuristicView* w = new KBPHeuristicView(doc,FirstFit,pWorkspace,0,WDestructiveClose);
		w->installEventFilter(this);
		doc->addView(w);
		w->setIcon(kapp->miniIcon());
		w->resize(pWorkspace->sizeHint());
		w->show();
		w->setFocus();
		w->RunHeuristic();
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotEndHeuristic(void)
{
	bool bRun=false;
	KBinPackingView* v;
	QWidgetList list;

	KApplication::kApplication()->processEvents(1000);

	// Scan all documents to see if all heuristics are end.
	list=pWorkspace->windowList();
	for(v=(KBinPackingView*)list.first();v!=0;v=(KBinPackingView*)list.next())
	{
		if(v->getType()==Heuristic)
		{
			if(((KBPHeuristicView*)v)->Running())
				bRun=true;
		}
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotHeuristicNext(void)
{
	KApplication::kApplication()->processEvents(1000);
	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m&&(m->getType()==Heuristic))
	{
		((KBPHeuristicView*)m)->NextStep();
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotHeuristicRun(void)
{
	KApplication::kApplication()->processEvents(1000);
	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m&&(m->getType()==Heuristic))
	{
		((KBPHeuristicView*)m)->RunToEnd();
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileNew(void)
{
	slotStatusMsg(i18n("Creating new document..."));
	openDocumentFile();
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileOpen(void)
{
	slotStatusMsg(i18n("Opening file..."));
	KURL url=KFileDialog::getOpenURL("/home/pfrancq/data/projects/hp/data",i18n("*.bp|Bin Packing files"), this, i18n("Open File..."));
	if(!url.isEmpty())
	{
		openDocumentFile(url);
		fileOpenRecent->addURL(url);
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileOpenRecent(const KURL& url)
{
	slotStatusMsg(i18n("Opening file..."));
	openDocumentFile(url);
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileSave(void)
{
	slotStatusMsg(i18n("Saving file..."));
	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m)
	{
		KBinPackingDoc* doc = m->getDocument();
		if(doc->URL().fileName().contains(i18n("Untitled")))
			slotFileSaveAs();
		else
			if(!doc->saveDocument(doc->URL()))
				KMessageBox::error (this,i18n("Could not save the current document !"), i18n("I/O Error !"));
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileSaveAs(void)
{
	slotStatusMsg(i18n("Saving file with a new filename..."));
	KURL url=KFileDialog::getSaveURL(QDir::currentDirPath(),i18n("*|All files"), this, i18n("Save as..."));
	if(!url.isEmpty())
	{
		KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
		if(m)
		{
			KBinPackingDoc* doc = m->getDocument();
			if(!doc->saveDocument(url))
			{
				KMessageBox::error (this,i18n("Could not save the current document !"), i18n("I/O Error !"));
				return;
			}
			doc->changedViewList();
//      setWndTitle(m);
			fileOpenRecent->addURL(url);
		}
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileClose(void)
{
	slotStatusMsg(i18n("Closing file..."));
	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m)
	{
		KBinPackingDoc* doc=m->getDocument();
		doc->closeDocument();
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFilePrint(void)
{
	slotStatusMsg(i18n("Printing..."));
	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
	if(m)
		m->print(printer);
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotFileQuit(void)
{
	slotStatusMsg(i18n("Exiting..."));
	saveOptions();
	// close the first window, the list makes the next one the first again.
	// This ensures that queryClose() is called on each window to ask for closing
	KMainWindow* w;
	if(memberList)
	{
		for(w=memberList->first(); w!=0; w=memberList->first())
		{
			// only close the window if the closeEvent is accepted. If the user presses Cancel on the saveModified() dialog,
			// the window and the application stay open.
			if(!w->close())
				break;
		}
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotEditUndo(void)
{
	slotStatusMsg(i18n("Reverting last action..."));
//	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
//	if(m)
//		m->undo();
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotEditCut(void)
{
	slotStatusMsg(i18n("Cutting selection..."));
//	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
//	if ( m )
//		m->cut();
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotEditCopy(void)
{
	slotStatusMsg(i18n("Copying selection to clipboard..."));
//	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
//	if(m)
//		m->copy();
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotEditPaste(void)
{
	slotStatusMsg(i18n("Inserting clipboard contents..."));
//	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
//	if(m)
//    m->paste();
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotViewToolBar(void)
{
	slotStatusMsg(i18n("Toggle the toolbar..."));
	if(!viewToolBar->isChecked())
	{
		toolBar("mainToolBar")->hide();
	}
	else
	{
		toolBar("mainToolBar")->show();
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotViewStatusBar(void)
{
	slotStatusMsg(i18n("Toggle the statusbar..."));
	if(!viewStatusBar->isChecked())
	{
		statusBar()->hide();
	}
	else
	{
		statusBar()->show();
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotWindowNewWindow(void)
{
	slotStatusMsg(i18n("Opening a new application window..."));
	KBinPackingView* m = (KBinPackingView*) pWorkspace->activeWindow();
	if(m)
	{
		KBinPackingDoc* doc = m->getDocument();
		createClient(doc);
	}
	slotStatusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotWindowTile(void)
{
	pWorkspace->tile();
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotWindowCascade(void)
{
	pWorkspace->cascade();
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotStatusMsg(const QString& text)
{
	statusBar()->clear();
	statusBar()->changeItem(text,1);
}


//-----------------------------------------------------------------------------
void KBinPackingApp::windowMenuAboutToShow(void)
{
	windowMenu->popupMenu()->clear();
	windowMenu->insert(windowNewWindow);
	windowMenu->insert(windowCascade);
	windowMenu->insert(windowTile);

	if(pWorkspace->windowList().isEmpty())
	{
		windowNewWindow->setEnabled(false);
		windowCascade->setEnabled(false);
		windowTile->setEnabled(false);
	}
	else
	{
		windowNewWindow->setEnabled(true);
		windowCascade->setEnabled(true);
		windowTile->setEnabled(true);
	}
	windowMenu->popupMenu()->insertSeparator();
	QWidgetList windows = pWorkspace->windowList();
	for(int i=0;i<int(windows.count());++i)
	{
		int id = windowMenu->popupMenu()->insertItem(QString("&%1 ").arg(i+1)+windows.at(i)->caption(),this,SLOT(windowMenuActivated(int)));
		windowMenu->popupMenu()->setItemParameter(id,i);
		windowMenu->popupMenu()->setItemChecked(id,pWorkspace->activeWindow()==windows.at(i));
	}
}


//-----------------------------------------------------------------------------
void KBinPackingApp::windowMenuActivated(int id)
{
	QWidget* w=pWorkspace->windowList().at(id);
	if (w)
		w->setFocus();
}


//-----------------------------------------------------------------------------
void KBinPackingApp::slotWindowActivated(QWidget*)
{
	bool bPrj,bGA,bHeuristic;

	KBinPackingView* m = (KBinPackingView*)pWorkspace->activeWindow();
	if(m)
	{
		// Update caption
		setCaption(m->caption());

		// Update menu
		switch(m->getType())
		{
			case Project:
				bPrj=true;
				bGA=false;
				bHeuristic=false;
				break;

			case Heuristic:
				bPrj=false;
				bGA=false;
				bHeuristic=true;
				break;

			case GA:
				bPrj=false;
				bGA=true;
				bHeuristic=false;
				break;

			default:
				bPrj=false;
				bGA=false;
				bHeuristic=false;
				break;
		}
//		GAInit->setEnabled(bPrj);
		heuristicFF->setEnabled(bPrj);
//		GAStart->setEnabled(bGA);
//		GAPause->setEnabled(bGA);
//		GAStop->setEnabled(bGA);
		heuristicRun->setEnabled(bHeuristic);
		heuristicNext->setEnabled(bHeuristic);
	}
	else
	{
		setCaption("");
//		GAInit->setEnabled(false);
		heuristicFF->setEnabled(false);
//		GAStart->setEnabled(false);
//		GAPause->setEnabled(false);
//		GAStop->setEnabled(false);
		heuristicRun->setEnabled(false);
		heuristicNext->setEnabled(false);
	}
}


//-----------------------------------------------------------------------------
KBinPackingApp::~KBinPackingApp(void)
{
	delete printer;
}
