/*

	Bin Packing GUI

	KAppOptions.cpp

	Application options - Implementation.

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



//------------------------------------------------------------------------------
// include files for R
#include <rqt.h>


//------------------------------------------------------------------------------
// includes files for current application
#include <kbinpacking.h>
#include <kappoptions.h>



//------------------------------------------------------------------------------
//
// class KAppOptions
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
KAppOptions::KAppOptions(QWidget* parent)
	: KDialog(parent), Ui_KAppOptions()
{
	setCaption("Preferences");
	QWidget* widget=new QWidget(this);
	setupUi(widget);
	setMainWidget(widget);
	setButtons(KDialog::Cancel|KDialog::Apply);
	connect(this,SIGNAL(applyClicked()),this,SLOT(accept()));
}


//------------------------------------------------------------------------------
void KAppOptions::exec(KBinPacking* app)
{
	// Init
	PopSize->setValue(app->GetConfig()->GetUInt("Population Size"));
	MaxGen->setValue(app->GetConfig()->GetUInt("Max Gen"));
	Step->setChecked(app->GetConfig()->GetBool("Step"));
	StepGen->setValue(app->GetConfig()->GetUInt("Step Gen"));
	StepGen->setEnabled(Step->isChecked());
	if(KDialog::exec())
	{
		app->GetConfig()->SetBool("Step",Step->isChecked());
		app->GetConfig()->SetUInt("Population Size",PopSize->value());
		app->GetConfig()->SetUInt("Max Gen",MaxGen->value());
		app->GetConfig()->SetUInt("Step Gen",StepGen->value());
		app->Apply();
	}
}


//------------------------------------------------------------------------------
void KAppOptions::readOptions(void)
{
	KConfig Config;
	KConfigGroup General(&Config,"Configure");
}


//------------------------------------------------------------------------------
void KAppOptions::saveOptions(void)
{
	KConfig Config;
	KConfigGroup General(&Config,"Configure");
}
