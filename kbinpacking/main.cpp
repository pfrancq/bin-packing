/*

	Bin Packing GUI

	Main.cpp

	Main file - Implementation.

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
// include files for KDE
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <KDE/KLocale>


//-----------------------------------------------------------------------------
// include files for current project
#include "kbinpacking.h"
using namespace std;


//-----------------------------------------------------------------------------
static const char *description =I18N_NOOP("KBinPacking\nApplication for the Bin Packing Problem");
KBinPacking* theApp;


//-----------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	setlocale(LC_CTYPE,"");

    // Information about the application
	KAboutData aboutData("kbinpacking",0,ki18n("KBinPacking"),"1.89",ki18n(description),
			KAboutData::License_GPL,ki18n("(C) 2001-2014 by Pascal Francq\n"),
			KLocalizedString(),"http://www.otlet-institute.org", "pascal@francq.info");
	aboutData.addAuthor(ki18n("Pascal Francq"),ki18n("Project Manager"),"pascal@francq.info");

	// Init
	KCmdLineArgs::init( argc, argv, &aboutData );
   KCmdLineOptions options;
	KCmdLineArgs::addCmdLineOptions(options);

	// Run
	try
	{
		KApplication app;
		theApp=new KBinPacking(argc,argv);
		if(app.isSessionRestored())
		{
//			RESTORE(theApp);
		}
		else
		{
			theApp->show();
		}
		return(app.exec());
	}
	catch(RException& e)
	{
		cout<<e.GetMsg()<<endl;
	}
	catch(exception& e)
	{
		cout<<e.what()<<endl;
	}
	catch(...)
	{
		cout<<"Unknown problem"<<endl;
	}
 	return(0);
}
