/*

 	Bin Packing Library

	RChromoBP.hh

	Chromosome for a Bin Packing Problem - Inline implementation

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
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::RChromoBP(cInst *inst,unsigned id)
		: R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>(inst,id),
		  HeuristicFFD(0), thObjs(0)
{
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::Init(cThreadData *thData)
{
	// Initialisation of the parent
	R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::Init(thData);
	HeuristicFFD=thData->HeuristicFFD;
	thObjs=thData->tmpObjs;
	thObjs2=thData->tmpObjs2;
	(*this->Fitness)=0;
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::Crossover(cChromo* parent1,cChromo* parent2)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("Crossover","RChromoBP");
	#endif

	R::RGroupingHeuristic<cGroup,cObj,cChromo>* Hold;

	// Change default heuristic to FFB
	Hold=this->Heuristic;
	this->Heuristic=HeuristicFFD;

	// Call the default crossover
	R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::Crossover(parent1,parent2);

	// Change to default heuristic
	this->Heuristic=Hold;

	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->EndFunc("Crossover","RChromoBP");
	#endif
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::Mutation(void)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("Mutation","RChromoBP");
	#endif

	double worstratio=std::numeric_limits<double>::max();
	double actratio;
	cGroup* worst=0;
	R::RGroupingHeuristic<cGroup,cObj,cChromo>* Hold;

	// Find the less filled group and release it
	R::RCursor<cGroup> Cur(this->Used);
	for(Cur.Start();!Cur.End();Cur.Next())
	{
		actratio=static_cast<double>(Cur()->GetSize())/static_cast<double>(Cur()->GetMaxSize());
		if(actratio>1)
			mThrowRGAException("Mutation","Maximum size is exceeded ("+R::RString::Number(Cur()->GetSize())+">"+R::RString::Number(Cur()->GetMaxSize())+")");
		if(actratio<worstratio)
		{
			worstratio=actratio;
			worst=Cur();
		}
	}
	this->ReleaseGroup(worst);

	// Change default heuristic to FFB
	Hold=this->Heuristic;
	this->Heuristic=HeuristicFFD;

	// Call the default mutation after it
	R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::Mutation();

	// Change to default heuristic
	this->Heuristic=Hold;

	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->EndFunc("Mutation","RChromoBP");
	#endif
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::LocalOptimisation(void)
{
	#ifdef RGADEBUG
		if(this->Instance->Debug) this->Instance->Debug->BeginFunc("LocalOptimisation","RChromoBP");
	#endif

	bool bOpti;
	size_t nbobjs;
	size_t* ass;

	// Determine all non assigned objects
	for(ass=this->ObjectsAss,this->Objs.Start(),nbobjs=0;!this->Objs.End();ass++,this->Objs.Next())
	{
		if((*ass)==R::cNoRef)
			thObjs[nbobjs++]=this->Objs();
	}

	for(bOpti=true;bOpti&&nbobjs;)
	{
		// Order by size descending
		qsort(static_cast<void*>(thObjs),nbobjs,sizeof(RObjBP*),RFirstFitDesHeuristic<cGroup,cObj,cChromo>::sortdes_function_cObjs);
		bOpti=false;

		// Go trough existing groups
		R::RCursor<cGroup> Cur(this->Used);
		for(Cur.Start();!Cur.End();Cur.Next())
		{
			if(Cur()->DoOptimisation(thObjs,nbobjs))
			{
				bOpti=true;
//				// Order by size descending
//				qsort(static_cast<void*>(thObjs),nbobjs,sizeof(RObjBP*),RFirstFitDesHeuristic<cGroup,cObj,cChromo>::sort_function_cObjs);
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
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>& RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::operator=(const RChromoBP& chromo)
{
	R::RChromoG<cInst,cChromo,RFitnessBP,cThreadData,cGroup,cObj>::operator=(chromo);
	return(*this);
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	void RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::Evaluate(void)
{
	double sum;

	R::RCursor<cGroup> Cur(this->Used);
	for(Cur.Start(),sum=0.0;!Cur.End();Cur.Next())
		sum+=pow(static_cast<double>(Cur()->GetSize())/static_cast<double>(Cur()->GetMaxSize()),2);
	(*this->Fitness)=sum/static_cast<double>(this->Used.GetNb());
}


//------------------------------------------------------------------------------
template<class cInst,class cChromo,class cThreadData,class cGroup,class cObj>
	RChromoBP<cInst,cChromo,cThreadData,cGroup,cObj>::~RChromoBP(void)
{
}
