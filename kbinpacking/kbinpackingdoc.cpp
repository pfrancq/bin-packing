/*

	R Project Library

	kbinpackingdoc.cpp

	Description - Implementation.

	(C) 2001 by Pascal Francq

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
// include files for ANSI C/C++
#include <string.h>


//-----------------------------------------------------------------------------
// include files for Qt
#include <qdir.h>
#include <qfileinfo.h>
#include <qwidget.h>


//-----------------------------------------------------------------------------
// include files for KDE
#include <klocale.h>
#include <kmessagebox.h>
#include <kfiledialog.h>
#include <kio/job.h>
#include <kio/netaccess.h>


//-----------------------------------------------------------------------------
// application specific includes
#include "kbinpacking.h"
#include "kbinpackingview.h"
#include "kbinpackingdoc.h"



//-----------------------------------------------------------------------------
//
// class KBinPackingDoc
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBinPackingDoc::KBinPackingDoc(void)
	: QObject(), RDataBPFile()
{
	pViewList = new QList<KBinPackingView>;
	pViewList->setAutoDelete(false);
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::addView(KBinPackingView* view)
{
	pViewList->append(view);
	changedViewList();
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::removeView(KBinPackingView* view)
{
	pViewList->remove(view);
	if(!pViewList->isEmpty())
			changedViewList();
		else
			deleteContents();
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::changedViewList(void)
{
	KBinPackingView* w;
	if((int)pViewList->count() == 1)
	{
		w=pViewList->first();
		w->setCaption(URL().fileName());
	}
	else
	{
		int i;
		for(i=1,w=pViewList->first();w!=0;i++,w=pViewList->next())
			w->setCaption(QString(URL().fileName()+":%1").arg(i));
	}
}


//-----------------------------------------------------------------------------
bool KBinPackingDoc::isLastView(void)
{
	return((int)pViewList->count()==1);
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::updateAllViews(KBinPackingView* sender)
{
	KBinPackingView* w;
	for(w=pViewList->first(); w!=0; w=pViewList->next())
	{
		w->update(sender);
	}
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::setURL(const KURL& url)
{
	doc_url=url;
}


//-----------------------------------------------------------------------------
const KURL& KBinPackingDoc::URL(void) const
{
	return doc_url;
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::closeDocument(void)
{
	KBinPackingView* w;
	if(!isLastView())
	{
		for(w=pViewList->first();w!=0;w=pViewList->next())
		{
			if(!w->close())
				break;
		}
	}
	if(isLastView())
	{
		w=pViewList->first();
		w->close();
	}
}


//-----------------------------------------------------------------------------
bool KBinPackingDoc::newDocument(void)
{
	modified=false;
	return true;
}


//-----------------------------------------------------------------------------
bool KBinPackingDoc::openDocument(const KURL& url, const char* /*format*/)
{
	QString tmpfile;
	char tmp[100];

	// Load File
	KIO::NetAccess::download(url,tmpfile);
	QFile f(tmpfile);
	if(!f.open(IO_ReadOnly))
		return false;
	f.close();
	strcpy(tmp,tmpfile);
	Load(tmp);

	// Remove
	KIO::NetAccess::removeTempFile( tmpfile );
	doc_url=url;
	modified=false;
	return true;
}


//-----------------------------------------------------------------------------
bool KBinPackingDoc::saveDocument(const KURL& /*url*/, const char* /*format*/)
{
//	QFile f( filename );
//	if ( !f.open( IO_WriteOnly ) )
//		return false;
//
//  f.close();
//
//  modified=false;
//	m_filename=filename;
//	m_title=QFileInfo(f).fileName();
	return true;
}


//-----------------------------------------------------------------------------
void KBinPackingDoc::deleteContents(void)
{
}


//-----------------------------------------------------------------------------
bool KBinPackingDoc::canCloseFrame(KBinPackingView* pFrame)
{
	if(!isLastView())
		return true;

	bool ret=false;
	if(isModified())
	{
		KURL saveURL;
		switch(KMessageBox::warningYesNoCancel(pFrame, i18n("The current file has been modified.\n"
		       "Do you want to save it?"),URL().fileName()))
		{
			case KMessageBox::Yes:
				if(URL().fileName().contains(i18n("Untitled")))
				{
					saveURL=KFileDialog::getSaveURL(QDir::currentDirPath(),	i18n("*|All files"), pFrame, i18n("Save as..."));
					if(saveURL.isEmpty())
						return false;
				}
				else
					saveURL=URL();
				if(!saveDocument(saveURL))
				{
					switch(KMessageBox::warningYesNo(pFrame,i18n("Could not save the current document !\n"
					       "Close anyway ?"), i18n("I/O Error !")))
					{
						case KMessageBox::Yes:
							ret=true;
						case KMessageBox::No:
							ret=false;
					}
				}
				else
					ret=true;
				break;

			case KMessageBox::No:
				ret=true;
				break;

			case KMessageBox::Cancel:
			default:
				ret=false;
				break;
		}
	}
	else
		ret=true;

	return ret;
}


//-----------------------------------------------------------------------------
KBinPackingDoc::~KBinPackingDoc(void)
{
	delete pViewList;
}
