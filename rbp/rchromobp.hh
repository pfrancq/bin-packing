/*

	RChromoG.hh

	Class representing a chromosome for a GGA - Inline implementation

	Copyright 2001-2003 by the Université Libre de Bruxelles.

	Authors:
		Pascal Francq (pfrancq@ulb.ac.be).

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



//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::RChromoBP(cInst *inst,unsigned id) throw(std::bad_alloc)
		: RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>(inst,id),
		  HeuristicFFD(0), thObjs(0)
{
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Init(cThreadData *thData) throw(std::bad_alloc)
{
	// Initialisation of the parent
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Init(thData);
	HeuristicFFD=thData->HeuristicFFD;
	thObjs=thData->tmpObjs;
	thObjs2=thData->tmpObjs2;
	(*Fitness)=0;
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Crossover(cChromo* parent1,cChromo* parent2) throw(eGA)
{
	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Change default heuristic to FFB
	Hold=Heuristic;
	Heuristic=HeuristicFFD;

	// Call the default crossover
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Crossover(parent1,parent2);

	// Change to default heuristic
	Heuristic=Hold;
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Mutation(void) throw(eGA)
{
	double worstratio=1.1,actratio;
	cGroup* worst=0;
	RGroupingHeuristic<cGroup,cObj,cGroupData,cChromo>* Hold;

	// Find the less filled group and release it
	for(Used.Start();!Used.End();Used.Next())
	{
		actratio=((double)Used()->GetSize())/((double)Used()->GetMaxSize());
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
	RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::Mutation();

	// Change to default heuristic
	Heuristic=Hold;
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::LocalOptimisation(void) throw(eGA)
{
	bool bOpti;
	unsigned int nbobjs;
	unsigned int* ass;

	// Determine all non assigned objects
	for(ass=ObjectsAss,Objs->Start(),nbobjs=0;!Objs->End();ass++,Objs->Next())
	{
		if((*ass)==NoGroup)
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


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>& RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::operator=(const RChromoBP& chromo)
{
  RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj,cGroupData>::operator=(chromo);
  return(*this);
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::Evaluate(void) throw(eGA)
{
	double sum;

	for(Used.Start(),sum=0.0;!Used.End();Used.Next())
		sum+=pow(((double)Used()->GetSize())/((double)Used()->GetMaxSize()),2);
	(*Fitness)=sum/((double)Used.NbPtr);
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj,class cGroupData>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj,cGroupData>::~RChromoBP(void)
{
}
