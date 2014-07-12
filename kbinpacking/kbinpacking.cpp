/*

	Bin Packing GUI

	KBinPacking.cpp

	Main Window - Implementation.

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
// include files for Qt
#include <qdir.h>
#include <qwhatsthis.h>
#include <qtooltip.h>
#include <qtoolbutton.h>
#include <qstring.h>
#include <qworkspace.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qcombobox.h>


//-----------------------------------------------------------------------------
// include files for KDE
#include <kstatusbar.h>
#include <kactioncollection.h>
#include <kstandardaction.h>
#include <KDE/KLocale>
#include <kapplication.h>
#include <KDE/KConfigGroup>
#include <kmessagebox.h>
#include <kfiledialog.h>


//-----------------------------------------------------------------------------
// application specific includes
#include <kbinpacking.h>
#include <kbpprjview.h>
#include <kbpgaview.h>
#include <kappoptions.h>



//-----------------------------------------------------------------------------
//
// class KBinPacking
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBinPacking::KBinPacking(int argc, char *argv[])
	: KXmlGuiWindow(0), RApplication("KBinPacking",argc,argv),
	  Desktop(new QMdiArea(this)), Status(new QLabel(statusBar())), Problem(0)
{
   setAcceptDrops(true);
   setCentralWidget(Desktop);
   initActions();
	Status->setPixmap(KIconLoader::global()->loadIcon("project-development-close",KIconLoader::Small));
	statusBar()->insertWidget(0,Status);
	statusBar()->insertItem(i18n("Ready."),1);
   statusBar()->show();
   setupGUI();
   Init();
	connect(Desktop,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(subWindowActivated(QMdiSubWindow*)));
	readOptions();
	fileOpened(false);
}


//-----------------------------------------------------------------------------
KAction* KBinPacking::addAction(const char* title,const char* name,const char* slot,const char* icon,const char* key)
{
	KAction* ptr(new KAction(i18n(title),this));
	if(icon)
		ptr->setIcon(KIcon(icon));
	if(key)
		ptr->setShortcut(QKeySequence(tr(key)));
	actionCollection()->addAction(QLatin1String(name),ptr);
	connect(ptr,SIGNAL(triggered(bool)),this,slot);
	return(ptr);
}


//-----------------------------------------------------------------------------
void KBinPacking::initActions(void)
{
	// Menu "file"
	aFileOpen= KStandardAction::open(this, SLOT(openFile()), actionCollection());
	aFileOpenRecent = KStandardAction::openRecent(this, SLOT(openRecentFile(const KUrl&)), actionCollection());
	Actions.insert(Actions.size(),KStandardAction::close(this, SLOT(closeFile()), actionCollection()));
	KStandardAction::quit(this, SLOT(applicationQuit()), actionCollection());

	// Menu "Window"
	KAction* windowCloseAll(new KAction(i18n("&Close All"),this));
	actionCollection()->addAction(QLatin1String("window_closeall"),windowCloseAll);
	connect(windowCloseAll,SIGNAL(triggered(bool)),Desktop,SLOT(closeAllSubWindows()));
	KAction* windowTile(new KAction(i18n("&Tile"),this));
	actionCollection()->addAction(QLatin1String("window_tile"),windowTile);
	connect(windowTile,SIGNAL(triggered(bool)),Desktop,SLOT(tileSubWindows()));
	KAction* windowCascade(new KAction(i18n("&Cascade"),this));
	actionCollection()->addAction(QLatin1String("window_cascade"),windowCascade);
	connect(windowCascade,SIGNAL(triggered(bool)),Desktop,SLOT(cascadeSubWindows()));

	// Menu "GA"
	Actions.insert(Actions.size(),aGAInit=addAction("&Initialize","ga_init",SLOT(GAInit()),"reload","ALT+I"));
	Actions.insert(Actions.size(),aGAStart=addAction("&Start","ga_start",SLOT(GAStart()),"exec","ALT+S"));
	Actions.insert(Actions.size(),aGAPause=addAction("&Pause","ga_pause",SLOT(GAPause()),"player_pause","ALT+P"));

	// Menu Settings
	KStandardAction::preferences(this,SLOT(optionsPreferences()),actionCollection());
}


//-----------------------------------------------------------------------------
void KBinPacking::fileOpened(bool opened)
{
	aFileOpen->setEnabled(!opened);
	aFileOpenRecent->setEnabled(!opened);
	for(int i=0;i<Actions.count();i++)
		Actions.at(i)->setEnabled(opened);
}


//-----------------------------------------------------------------------------
void KBinPacking::saveOptions(void)
{
	KConfig Config;
	KConfigGroup General(&Config,"KBinPacking");
	KAppOptions::saveOptions();
	aFileOpenRecent->saveEntries(General);
}


//-----------------------------------------------------------------------------
void KBinPacking::readOptions(void)
{
	KConfig Config;
	KConfigGroup General(&Config,"KBinPacking");
	KAppOptions::readOptions();
	aFileOpenRecent->loadEntries(General);
}


//-----------------------------------------------------------------------------
void KBinPacking::CreateConfig(void)
{
	Config.InsertParam(new RParamValue("Log File","/home/pfrancq/bp.log"));
	Config.InsertParam(new RParamValue("Debug File","/home/pfrancq/debug-bp.xml"));
	Config.InsertParam(new RParamValue("Population Size",16));
	Config.InsertParam(new RParamValue("Max Gen",30));
	Config.InsertParam(new RParamValue("Step",false));
	Config.InsertParam(new RParamValue("Step Gen",0));
}


//------------------------------------------------------------------------------
void KBinPacking::Init(void)
{
	// Parent initialization
	RApplication::Init();

	// Get the parameters
	Apply();

	try
	{
		// Create (if necessary) Log file
		if(LogFileName!=RString::Null)
		{
			//cout<<"Create log file "<<LogFileName<<"...";
			//cout.flush();
			Log=new RTextFile(LogFileName,"utf8");
			Log->Open(RIO::Append);
			//cout<<"OK"<<endl;
		}
	}
	catch(...)
	{
		std::cerr<<"Error: Cannot create log file "<<LogFileName<<std::endl;
	}

	try
	{
		// Create (if necessary) the debug file
		if(DebugFileName!=RString::Null)
			Debug=new RDebugXML(DebugFileName);
	}
	catch(...)
	{
		std::cerr<<"Error: Cannot create debug file "<<DebugFileName<<std::endl;
	}
}


//-----------------------------------------------------------------------------
void  KBinPacking::Apply(void)
{
	LogFileName=Config.Get("Log File");
	DebugFileName=Config.Get("Debug File");
	PopSize=Config.GetUInt("Population Size");
	MaxGen=Config.GetUInt("Max Gen");
	Step=Config.GetBool("Step");
	StepGen=Config.GetUInt("Step Gen");
}


//-----------------------------------------------------------------------------
void  KBinPacking::statusMsg(const QString& text)
{
	statusBar()->changeItem(text,1);
}


//-----------------------------------------------------------------------------
void  KBinPacking::openDocumentFile(const KUrl& url)
{
	bool DestroyDoc(false);

	statusMsg(i18n("Opening file..."));

	// check, if document already open.
	if(Problem)
		mThrowRException("Big Problem : No Bin Packing session should exist");

	// Create the document
	try
	{
		DestroyDoc=true;
		Problem=new RBPProblem();
		Problem->Load(FromQString(url.path()));
		fileOpened(true);
		KBPPrjView* ptr(new KBPPrjView(Problem,url.path()));
		DestroyDoc=false;
		Desktop->addSubWindow(ptr);
		ptr->adjustSize();
		ptr->show();
		aFileOpenRecent->addUrl(url,url.fileName());
		Status->setPixmap(QPixmap(KIconLoader::global()->loadIcon("project-open",KIconLoader::Small)));
		statusMsg(i18n("Data Loaded"));
	}
	catch(RException& e)
	{
		KMessageBox::error(this,ToQString(e.GetMsg()),"R Exception");
	}
	catch(std::exception& e)
	{
		KMessageBox::error(this,e.what(),"std::exception");
	}
	catch(...)
	{
		KMessageBox::error(this,"Undefined Error");
	}
	if(DestroyDoc)
	{
		delete Problem;
		Problem=0;
	}
	statusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPacking::optionsPreferences(void)
{
	statusMsg(i18n("Set the options..."));

	KAppOptions Dlg(this);
	Dlg.exec(this);
	statusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPacking::subWindowActivated(QMdiSubWindow* window)
{
	KBPGAView* GA;

	if(dynamic_cast<KBPPrjView*>(window))
	{
		aGAInit->setEnabled(true);
		aGAStart->setEnabled(false);
		aGAPause->setEnabled(false);
	}
	else if((GA=dynamic_cast<KBPGAView*>(window)))
	{
		aGAInit->setEnabled(false);
		aGAStart->setEnabled((!GA->IsRunning())&&(!GA->End()));
		aGAPause->setEnabled(GA->IsRunning());
	}
}


//-----------------------------------------------------------------------------
void KBinPacking::openFile(void)
{
	statusMsg(i18n("Opening file..."));
	KUrl url(KFileDialog::getOpenFileName(KUrl("~"),"*.BPP|Bin Packing files",Desktop,"Open File..."));
	if(url.isEmpty())
		QMessageBox::critical(this,"KBinPacking","File could not be found");
	else
	{
		openDocumentFile(url);
		aFileOpenRecent->addUrl(url);
	}
	statusMsg(i18n("Ready."));
}


////-----------------------------------------------------------------------------
void KBinPacking::openRecentFile(const KUrl& url)
{
	statusMsg(i18n("Opening file..."));
	openDocumentFile(url);
	statusMsg(i18n("Ready."));
}


//-----------------------------------------------------------------------------
void KBinPacking::closeFile(void)
{
	if(Problem)
	{
		Desktop->closeAllSubWindows();
		delete Problem;
		Problem=0;
		fileOpened(false);
		statusMsg(i18n("No VLSI !"));
		Status->setPixmap(KIconLoader::global()->loadIcon("project-development-close",KIconLoader::Small));
	}
}


//-----------------------------------------------------------------------------
void KBinPacking::applicationQuit(void)
{
	statusMsg(i18n("Exiting..."));
	saveOptions();
	closeFile();
	statusMsg(i18n("Ready."));
	close();
}

//-----------------------------------------------------------------------------
void KBinPacking::GAInit(void)
{
	KBPGAView* ptr(new KBPGAView(Problem));
	Desktop->addSubWindow(ptr);
	ptr->adjustSize();
	ptr->show();
}


//-----------------------------------------------------------------------------
void KBinPacking::GAStart(void)
{
	KBPGAView* Win(dynamic_cast<KBPGAView*>(Desktop->activeSubWindow()));
	if(Win)
		Win->RunGA();
}


//-----------------------------------------------------------------------------
void KBinPacking::GAPause(void)
{
	KBPGAView* Win(dynamic_cast<KBPGAView*>(Desktop->activeSubWindow()));
	if(Win)
		Win->PauseGA();
}


//-----------------------------------------------------------------------------
KBinPacking::~KBinPacking(void)
{
}
