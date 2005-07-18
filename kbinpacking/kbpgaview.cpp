/*

  KBPGAView.cpp

  Description - Implementation.

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
// include files for R Project
#include <rfinstbp.h>
#include <rfchromobp.h>
using namespace R;


//-----------------------------------------------------------------------------
// include files for Qt/KDE
#include <klocale.h>
#include <kmessagebox.h>


//-----------------------------------------------------------------------------
// include files for Widgets
#include <qgamonitor.h>
#include <qxmlcontainer.h>


//-----------------------------------------------------------------------------
// include files for current application
#include "qdrawgroups.h"
#include "kbpgaview.h"
#include "kbinpackingdoc.h"



//-----------------------------------------------------------------------------
//
// class KBPGAView
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
KBPGAView::KBPGAView(KBinPackingDoc* pDoc,QWidget *parent, const char *name,int wflags)
	: KBinPackingView(pDoc,parent,name,wflags), CurId(0), Instance(0), Data(pDoc->MaxSize), DebugFile("/home/pfrancq/debug.xml","BP","Pascal Francq")
{
	static char tmp[100];
	setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)1, (QSizePolicy::SizeType)1, sizePolicy().hasHeightForWidth() ) );
	TabWidget = new QTabWidget( this, "TabWidget" );
	TabWidget->setGeometry(rect());
	TabWidget->setSizePolicy( QSizePolicy( (QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, TabWidget->sizePolicy().hasHeightForWidth() ) );
	TabWidget->setBackgroundOrigin( QTabWidget::ParentOrigin );

	// Stat part
	StatSplitter=new QSplitter(QSplitter::Vertical,TabWidget,"Statistic");
	TabWidget->insertTab(StatSplitter,"Statistic");
	StatSplitter->setGeometry(rect());
	Monitor=new	QGAMonitor(StatSplitter);
	Monitor->setMaxGen(theApp->GAMaxGen);
	Monitor->setMaxFitness(pDoc->GetNbObjs()/2);
	connect(this,SIGNAL(signalSetGen(const unsigned int,const unsigned int,const double)),Monitor,SLOT(slotSetGen(const unsigned int,const unsigned int,const double)));
	Debug=new QXMLContainer(StatSplitter,"KBinPacking","Pascal Francq");

	// Solution part
	Best = new QDrawGroups(TabWidget,pDoc->Objs);
	TabWidget->insertTab(Best,"Best Solution");

	// Solution part
	Sol = new QDrawGroups(TabWidget,pDoc->Objs);
	sprintf(tmp,"Solution (0/%u)",((KBinPackingApp*)parentWidget()->parentWidget()->parentWidget())->GAPopSize-1);
	TabWidget->insertTab(Sol,tmp);

	// Create GA
	try
	{
		Gen=0;
		Instance=new RFInstBP(theApp->GAMaxGen,theApp->GAPopSize,pDoc->Objs,theApp->GAHeur,pDoc->MaxSize,&DebugFile);
		Instance->AddReceiver(this);
		Instance->Init(&Data);
	}
	catch(eGA& e)
	{
		KMessageBox::error(this,e.GetMsg());
	}
	catch(RException& e)
	{
		KMessageBox::error(this,e.GetMsg());
	}
	catch(std::exception& e)
	{
		KMessageBox::error(this,e.what());
	}
	catch(...)
	{
		KMessageBox::error(this,"Unknown problem");
	}
}


//---------------------------------------------------------------------------
void KBPGAView::receiveGenSig(GenSig* sig)
{
	emit signalSetGen(sig->Gen,sig->BestGen,sig->Best->Used.GetNb()/*Fitness->Value*/);
	Sol->setGroups(Instance->Chromosomes[CurId]);
	Sol->setChanged();
}


//---------------------------------------------------------------------------
void KBPGAView::receiveInteractSig(InteractSig* /*sig*/)
{
	KApplication::kApplication()->processEvents();
}


////---------------------------------------------------------------------------
void KBPGAView::receiveBestSig(BestSig* sig)
{
	static char tmp[100];

	sprintf(tmp,"Best Solution (Id=%u) - Fitness=%f",sig->Best->Id,sig->Best->Fitness->Value);
	TabWidget->changeTab(Best,tmp);
	Best->setGroups(sig->Best);
	Best->setChanged();
}


//---------------------------------------------------------------------------
void KBPGAView::RunGA(void)
{
	if(Instance)
	{
		try
		{
			if(theApp->GAMaxGen>Gen)
			{
				if(theApp->GAStepGen==0)
					Gen=theApp->GAMaxGen;
				else
				{
					Gen+=theApp->GAStepGen;
					if(Gen>theApp->GAMaxGen) Gen=theApp->GAMaxGen;
				}
			}
			Instance->MaxGen=Gen;
			Instance->Run();
			if(Gen==theApp->GAMaxGen)
				theApp->GAPause->setEnabled(false);
			KMessageBox::information(this,"Done");
		}
		catch(eGA& e)
		{
			KMessageBox::error(this,e.GetMsg());
		}
		catch(RException& e)
		{
			KMessageBox::error(this,e.GetMsg());
		}
		catch(std::exception& e)
		{
			KMessageBox::error(this,e.what());
		}
		catch(...)
		{
			KMessageBox::error(this,"Unknown problem");
		}
	}
}


//---------------------------------------------------------------------------
void KBPGAView::PauseGA(void)
{
	ExternBreak=true;
}


//---------------------------------------------------------------------------
void KBPGAView::StopGA(void)
{
}


//---------------------------------------------------------------------------
void KBPGAView::keyReleaseEvent(QKeyEvent* e)
{
	static char tmp[100];
//	QGoToPopDlg *dlg;

	if(TabWidget->currentPage()!=Sol)
	{
		KBinPackingView::keyReleaseEvent(e);
		return;
	}
	switch(e->key())
	{
		case Key_PageUp:
			if(CurId<Instance->PopSize-1) CurId++; else CurId=0;
			sprintf(tmp,"Solution (%u/%u) - Fitness=%f",CurId,Instance->PopSize-1,Instance->Chromosomes[CurId]->Fitness->Value);
			TabWidget->changeTab(Sol,tmp);
			Sol->setGroups(Instance->Chromosomes[CurId]);
			Sol->setChanged();
			break;

		case Key_PageDown:
			if(CurId>0) CurId--; else CurId=Instance->PopSize-1;
			sprintf(tmp,"Solution (%u/%u) - Fitness=%f",CurId,Instance->PopSize-1,Instance->Chromosomes[CurId]->Fitness->Value);
			TabWidget->changeTab(Sol,tmp);
			Sol->setGroups(Instance->Chromosomes[CurId]);
			Sol->setChanged();
			break;

//		case Key_G:
//			if(e->state()==ControlButton)
//			{
//				dlg= new QGoToPopDlg(Doc->getPopSize());
//				if(dlg->exec())
//				{
//					CurId=dlg->PopIndex->value();
//					slotNewChromo();
//				}
//				delete dlg;
//			}
//			break;

		default:
			e->ignore();
	}
}


//-----------------------------------------------------------------------------
void KBPGAView::resizeEvent(QResizeEvent*)
{
	TabWidget->resize(size());
}


//-----------------------------------------------------------------------------
KBPGAView::~KBPGAView()
{
	if(Instance)
		delete Instance;
}
