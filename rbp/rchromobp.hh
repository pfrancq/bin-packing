/*

	RChromoG.hh

	Class representing a chromosome for a GGA - Inline implementation

	(C) 2001 by P. Francq.

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



//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::RChromoBP(cInst *inst,unsigned id) throw(bad_alloc)
		: RGGA::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>(inst,id),
		  HeuristicFFD(0), thObjs(0)
{
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Init(cThreadData *thData) throw(bad_alloc)
{
	// Initialisation of the parent
	RGGA::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Init(thData);
	HeuristicFFD=thData->HeuristicFFD;
	thObjs=thData->tmpObjs;
	thObjs2=thData->tmpObjs2;
	(*Fitness)=0;
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	bool RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Crossover(cChromo* parent1,cChromo* parent2)
{
	bool ret;
	RGGA::RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Change default heuristic to FFB
	Hold=Heuristic;
	Heuristic=HeuristicFFD;

	// Call the default crossover
	ret=RGGA::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Crossover(parent1,parent2);

	// Change to default heuristic
	Heuristic=Hold;

	return(ret);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	bool RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Mutation(void)
{
	double worstratio=1.1,actratio;
	cGroup* worst=0;
	bool ret;
	RGGA::RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Find the less filled group and release it
	for(Used.Start();!Used.End();Used.Next())
	{
		actratio=((double)Used()->GetMaxSize())/((double)Used()->GetSize());
		if(actratio<worstratio)
		{
			worstratio=actratio;
			worst=Used();
		}
	}
	ReleaseGroup(worst->GetId());

	// Change default heuristic to FFB
	Hold=Heuristic;
	Heuristic=HeuristicFFD;

	// Call the default mutation after it
	ret=RGGA::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Mutation();
	
	// Change to default heuristic
	Heuristic=Hold;

	return(ret);
}

//-----------------------------------------------------------------------------
//template<class cInst,class cChromo,class cFit,class cThreadData>
//	int RInst<cInst,cChromo,cFit,cThreadData>::sort_function_Objs(const void* a,const void* b)
//{
//	RObjBP* ao=(*(static_cast<RObjBP**>(a)));
//	RObjBP* bo=(*(static_cast<RObjBP**>(b)));
//
//	return(ao->GetSize()-bo->GetSize());
//}

//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::LocalOptimisation(void)
{
	bool bOpti;
	unsigned int nbobjs;
	unsigned int* ass;

	// Determine all non assigned objects
	for(ass=ObjectsAss,Objs->Start(),nbobjs=0;!Objs->End();ass++,Objs->Next())
	{
		if((*ass)==RGGA::NoGroup)
			thObjs[nbobjs++]=(*Objs)();
	}

	for(bOpti=true;bOpti&&nbobjs;)
	{
		// Order by size descending
		qsort(static_cast<void*>(thObjs),nbobjs,sizeof(RObjBP*),RFirstFitDesHeuristic<cGroup,cObj,cGroupData,cChromo>::sortdes_function_cObjs);
		bOpti=false;

		// Go trough existing groups
		for(Used.Start();!Used.End();Used.Next())
		{
			if(Used()->DoOptimisation(thObjs,nbobjs))
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
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>& RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::operator=(const RChromoBP& chromo)
{
  RGGA::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::operator=(chromo);
  return(*this);
}


//-----------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Evaluate(void)
{
	double sum=0.0;

	for(Used.Start();!Used.End();Used.Next())
		sum+=pow(((double)Used()->GetSize())/((double)Used()->GetMaxSize()),2);
	(*Fitness)=sum/((double)Used.NbPtr);
}


//---------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::~RChromoBP(void)
{
}
