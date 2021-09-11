/*

	Bin Packing GUI

	KBPGAView.cpp

	GA Window - Implementation.

	Copyright 2000-2014 by Pascal Francq (pascal@francq.info).

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
// include files for Qt/KDE
#include <kmessagebox.h>
#include <QtGui/QKeyEvent>


//-----------------------------------------------------------------------------
// include files for Widgets
#include <qrgamonitor.h>
#include <qrdebug.h>


//-----------------------------------------------------------------------------
// include files for current application
#include <qdrawgroups.h>
#include <kbpgaview.h>
#include <kbinpacking.h>



//-----------------------------------------------------------------------------
//
// class KBPGAView
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
size_t KBPGAView::WinNb=0;

//-----------------------------------------------------------------------------
KBPGAView::KBPGAView(RBPProblem* problem)
	: QMdiSubWindow(), Ui_KBPGAView(), RObject("GAView "+RString::Number(++WinNb)), CurId(0), Instance(0), Gen(0), Running(false)
{
 	QWidget* ptr=new QWidget();
	setupUi(ptr);
	setWidget(ptr);
	setAttribute(Qt::WA_DeleteOnClose);
	setWindowTitle("Bin Packing Genetic Algorithm");
	Monitor->setParams(theApp->MaxGen,0.0,1.0);

 	// Create GA
	try
	{
		Gen=0;
		Instance=new RFInstBP(theApp->PopSize,problem->GetObjs(),problem->GetBinMaxSize(),"",theApp->MaxGen,Debug);
		Instance->Init();
		reinterpret_cast<RObject*>(this)->InsertObserver(reinterpret_cast<tNotificationHandler>(&KBPGAView::Generation),"RInst::Generation",Instance);
		reinterpret_cast<RObject*>(this)->InsertObserver(reinterpret_cast<tNotificationHandler>(&KBPGAView::BestChromo),"RInst::Best",Instance);
		reinterpret_cast<RObject*>(this)->InsertObserver(reinterpret_cast<tNotificationHandler>(&KBPGAView::Interact),"RInst::Interact",Instance);
		Main->setTabText(1,"Best Solution - Fitness=?");
		Main->setTabText(2,"Solution Undefined  - Fitness=?");
	}
	catch(RException& e)
	{
		KMessageBox::error(this,ToQString(e.GetMsg()));
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
void KBPGAView::RunGA(void)
{
	if(Instance)
	{
		try
		{
			if(theApp->MaxGen>Gen)
			{
				if(theApp->StepGen==0)
					Gen=theApp->MaxGen;
				else
				{
					Gen+=theApp->StepGen;
					if(Gen>theApp->MaxGen) Gen=theApp->MaxGen;
				}
			}
			Instance->MaxGen=Gen;
			Running=true;
			theApp->subWindowActivated(this);
			Instance->Run();
			Running=false;
			KMessageBox::information(this,"Done");
		}
		catch(RException& e)
		{
			KMessageBox::error(this,ToQString(e.GetMsg()));
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
bool KBPGAView::End(void) const
{
	return(Gen==theApp->MaxGen);
}


//---------------------------------------------------------------------------
void KBPGAView::PauseGA(void)
{
	if(Running)
	{
		ExternBreak=true;
		Running=false;
	}
}


//---------------------------------------------------------------------------
void KBPGAView::Generation(const R::RNotification& notification)
{
	Monitor->setGenInfo(GetData<size_t>(notification),Instance->GetAgeBest(),Instance->GetBestChromosome()->Fitness->Value);
	Main->setTabText(2," Solutions ("+QString::number(CurId)+"/"+QString::number(Instance->GetPopSize()-1)+") - Fitness="+QString::number(Instance->Chromosomes[CurId]->Fitness->Value));
	Sol->setGroups(Instance->Chromosomes[CurId]);
}


//---------------------------------------------------------------------------
void KBPGAView::BestChromo(const R::RNotification&)
{
	Main->setTabText(1," Best Solution - Fitness="+QString::number(Instance->GetBestChromosome()->Fitness->Value));
	Best->setGroups(Instance->GetBestChromosome());
}


//---------------------------------------------------------------------------
void KBPGAView::Interact(const R::RNotification&)
{
	QCoreApplication::processEvents();
}


//---------------------------------------------------------------------------
void KBPGAView::keyReleaseEvent(QKeyEvent* e)
{
 	if(Main->currentIndex()!=2)
		return;
	switch(e->key())
	{
		case Qt::Key_PageUp:
			if(CurId<Instance->GetPopSize()-1) CurId++; else CurId=0;
			Main->setTabText(2," Solutions ("+QString::number(CurId)+"/"+QString::number(Instance->GetPopSize()-1)+") - Fitness="+QString::number(Instance->Chromosomes[CurId]->Fitness->Value));
			Sol->setGroups(Instance->Chromosomes[CurId]);
			break;

		case Qt::Key_PageDown:
			if(CurId>0) CurId--; else CurId=Instance->GetPopSize()-1;
			Main->setTabText(2," Solutions ("+QString::number(CurId)+"/"+QString::number(Instance->GetPopSize()-1)+") - Fitness="+QString::number(Instance->Chromosomes[CurId]->Fitness->Value));			Sol->setGroups(Instance->Chromosomes[CurId]);
			break;

		default:
			e->ignore();
	}
}


//-----------------------------------------------------------------------------
KBPGAView::~KBPGAView(void)
{
	if(Instance)
		delete Instance;
}
