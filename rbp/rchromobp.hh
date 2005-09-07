/*

	RChromoG.hh

	Class representing a chromosome for a GGA - Inline implementation

	Copyright 2001-2005 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::RChromoBP(cInst *inst,unsigned id)
		: RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>(inst,id),
		  HeuristicFFD(0), thObjs(0)
{
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Init(cThreadData *thData)
{
	// Initialisation of the parent
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Init(thData);
	HeuristicFFD=thData->HeuristicFFD;
	thObjs=thData->tmpObjs;
	thObjs2=thData->tmpObjs2;
	(*this->Fitness)=0;
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Crossover(cChromo* parent1,cChromo* parent2)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("Crossover","RChromoBP");
	#endif

	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Change default heuristic to FFB
	Hold=this->Heuristic;
	this->Heuristic=HeuristicFFD;

	// Call the default crossover
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Crossover(parent1,parent2);

	// Change to default heuristic
	this->Heuristic=Hold;

	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->EndFunc("Crossover","RChromoBP");
	#endif
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Mutation(void)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("Mutation","RChromoBP");
	#endif

	double worstratio=1.1,actratio;
	cGroup* worst=0;
	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Find the less filled group and release it
	RCursor<cGroup> Cur(this->Used);
	for(Cur.Start();!Cur.End();Cur.Next())
	{
		actratio=static_cast<double>(Cur()->GetSize())/static_cast<double>(Cur()->GetMaxSize());
		if(actratio<worstratio)
		{
			worstratio=actratio;
			worst=Cur();
		}
	}
	ReleaseGroup(worst);

	// Change default heuristic to FFB
	Hold=this->Heuristic;
	this->Heuristic=HeuristicFFD;

	// Call the default mutation after it
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Mutation();

	// Change to default heuristic
	this->Heuristic=Hold;

	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->EndFunc("Mutation","RChromoBP");
	#endif
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::LocalOptimisation(void)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("LocalOptimisation","RChromoBP");
	#endif

	bool bOpti;
	unsigned int nbobjs;
	unsigned int* ass;

	// Determine all non assigned objects
	for(ass=this->ObjectsAss,this->Objs->Start(),nbobjs=0;!this->Objs->End();ass++,this->Objs->Next())
	{
		if((*ass)==NoGroup)
			thObjs[nbobjs++]=(*this->Objs)();
	}

	for(bOpti=true;bOpti&&nbobjs;)
	{
		// Order by size descending
		qsort(static_cast<void*>(thObjs),nbobjs,sizeof(RObjBP*),RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cChromo>::sortdes_function_cObjs);
		bOpti=false;

		// Go trough existing groups
		RCursor<cGroup> Cur(this->Used);
		for(Cur.Start();!Cur.End();Cur.Next())
		{
			if(Cur()->DoOptimisation(thObjs,nbobjs))
			{
				bOpti=true;
//				// Order by size descending
//				qsort(static_cast<void*>(thObjs),nbobjs,sizeof(RObjBP*),RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cChromo>::sort_function_cObjs);
				break;
//			}
//			if(!nbobjs)
//			{
//				bOpti=false;
//				break;
			}
		}
	}

	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->EndFunc("LocalOptimisation","RChromoBP");
	#endif
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>& RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::operator=(const RChromoBP& chromo)
{
  RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::operator=(chromo);
  return(*this);
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Evaluate(void)
{
	double sum;

	RCursor<cGroup> Cur(this->Used);
	for(Cur.Start(),sum=0.0;!Cur.End();Cur.Next())
		sum+=pow(static_cast<double>(Cur()->GetSize())/static_cast<double>(Cur()->GetMaxSize()),2);
	(*this->Fitness)=sum/static_cast<double>(this->Used.GetNb());
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::~RChromoBP(void)
{
}
