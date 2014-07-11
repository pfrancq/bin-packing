/*

	Bin Packing Library

	RGroupBP.hh

	Group for a Bin Packing Problem - Header.

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
//
// class RGroupBP<cGroup,cObj,cChromo>
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	RGroupBP<cGroup,cObj,cChromo>::RGroupBP(RGroupBP* grp)
		: R::RGroup<cGroup,cObj,cChromo>(grp), Size(grp->Size), MaxSize(grp->MaxSize)
{
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	RGroupBP<cGroup,cObj,cChromo>::RGroupBP(cChromo* owner,size_t id)
		: R::RGroup<cGroup,cObj,cChromo>(owner,id), Size(0), MaxSize(owner->Instance->GetMaxSize())
{
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	void RGroupBP<cGroup,cObj,cChromo>::Verify(void)
{
	char tmp[200];

	R::RGroup<cGroup,cObj,cChromo>::Verify();
	if(Size>MaxSize)
	{
		sprintf(tmp,"Size(%lu) > MaxSize(%lu) for group %lu",Size,MaxSize,this->Id);
		mThrowRGAException("Verify",tmp);
	}
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	void RGroupBP<cGroup,cObj,cChromo>::Clear(void)
{
	R::RGroup<cGroup,cObj,cChromo>::Clear();
	Size=0;
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	bool RGroupBP<cGroup,cObj,cChromo>::CanInsert(const cObj* obj)
{
	return(Size+obj->GetSize()<=MaxSize);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	void RGroupBP<cGroup,cObj,cChromo>::PostInsert(const cObj* obj)
{
	Size+=obj->GetSize();
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	void RGroupBP<cGroup,cObj,cChromo>::PostDelete(const cObj* obj)
{
	Size-=obj->GetSize();
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	bool RGroupBP<cGroup,cObj,cChromo>::TestNewSize(cObj** del,size_t& nbdel,size_t addsize,size_t size)
{
	size_t newsize;
	//size_t maxsize;
	size_t s1,s2,s3;
	cObj** cur1;
	cObj** cur2;
	cObj** cur3;
	size_t i,j,k;
	cObj** thObjs2=this->Owner->thObjs2;

	// fill thObjs2 with the objects of the group and order it by ascending order
	R::RCursor<cObj> obj=this->Owner->GetObjs(*static_cast<cGroup*>(this));
	for(obj.Start(),cur1=thObjs2;!obj.End();obj.Next(),cur1++)
		(*cur1)=obj();
	qsort(static_cast<void*>(thObjs2),this->NbSubObjects,sizeof(cObj*),RFirstFitDesHeuristic<cGroup,cObj,cChromo>::sort_function_cObjs);

	// New Size if addsize is added.
	newsize=Size+size+addsize;
	//if(addsize>size) maxsize=addsize; else maxsize=size;
//	if(size==0.0)
//		size=addsize;
//	for(i=0;i<nbdel;i++)
//		if(del[i])
//			newsize-=del[i]->GetSize();

	// If MaxSize is not reach, look if the new size is greather or lesser than
	// the old ize.
	if(newsize<=MaxSize)
	{
		if(newsize>=Size)
			return(true);
		else
			return(false);
	}

	// Try to del 1 object with Max 3 Objects deleted.
	if((nbdel>=3)||(!this->NbSubObjects)) return(false);
	for(i=this->NbSubObjects+1,cur1=thObjs2;--i;cur1++)
	{
//		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1==del[0])||(cur1==del[1])||(cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-(*cur1)->GetSize();
		if((s1<=MaxSize)&&(s1>Size))
		{
			del[nbdel++]=(*cur1);
			return(true);
		}
	}

	// Try to del 2 object with Max 3 Objects deleted.
	if((nbdel>=2)||(this->NbSubObjects<2)) return(false);
	for(i=this->NbSubObjects,cur1=thObjs2;--i;cur1++)
	{
//		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1==del[0])||(cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-(*cur1)->GetSize();
		for(j=i+1,cur2=cur1+1;--j;cur2++)
		{
//			cur2=Owner->GetObj(SubObjects+j);
//			if((cur2==del[0])||(cur2->GetSize()>=addsize)||(cur2->GetSize()>=size)) continue;
			s2=s1-(*cur2)->GetSize();
			if((s2<=MaxSize)&&(s2>Size))
			{
				del[nbdel++]=(*cur1);
				del[nbdel++]=(*cur2);
				return(true);
			}
		}
	}

	// Try to del 3 object with Max 3 Objects deleted.
	if((nbdel)||(this->NbSubObjects<3)) return(false);
	for(i=this->NbSubObjects-1,cur1=thObjs2;--i;cur1++)
	{
//		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-(*cur1)->GetSize();
		for(j=i+1,cur2=cur1+1;--j;cur2++)
		{
//			cur2=Owner->GetObj(SubObjects+j);
//			if((cur2->GetSize()>=addsize)||(cur2->GetSize()>=size)) continue;
			s2=s1-(*cur2)->GetSize();
			for(k=j+1,cur3=cur2+1;--k;cur3++)
			{
//				cur3=Owner->GetObj(SubObjects+k);
//				if((cur3->GetSize()>=addsize)||(cur3->GetSize()>=size)) continue;
				s3=s2-(*cur3)->GetSize();
				if((s3<=MaxSize)&&(s3>Size))
				{
					del[nbdel++]=(*cur1);
					del[nbdel++]=(*cur2);
					del[nbdel++]=(*cur3);
					return(true);
				}
			}
		}
	}

	// Nothing can be done
	return(false);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	bool RGroupBP<cGroup,cObj,cChromo>::DoOptimisation(cObj** objs,size_t& nbobjs)
{
	size_t idx[2];                 // Indexed of the objects to add in objs.
	cObj* del[3];                  // Pointers to the objects to delete.
	cObj* add[2];                  // Pointers to the objects to add.
	size_t nbdel;                  // Number of objects to delete.
	size_t nbadd;                  // Number of objects to add.
	cObj** obj;                    // Current object eventually to add.
	cObj** obj2;
	size_t i,j;
//	size_t addsize;

	// If the groups is maximum filled, no optimisation needed.
	if(Size==MaxSize)
		return(false);

	// Init Part
	add[0]=add[1]=del[0]=del[1]=del[2]=0;   // No objs added or deleted
	idx[0]=idx[1]=R::cNoRef;
	nbdel=nbadd=0;

	// Try to add two objects
	if(!nbadd)
	{
		for(i=0,obj=objs;i<nbobjs-1;obj++,i++)
		{
			for(j=i+1,obj2=obj+1;j<nbobjs;obj2++,j++)
			{
				if(TestNewSize(del,nbdel,(*obj)->GetSize(),(*obj2)->GetSize()))
				{
					idx[nbadd]=i;
					add[nbadd++]=(*obj);
					idx[nbadd]=j;
					add[nbadd++]=(*obj2);
					break;
				}
			}
			if(nbadd) break;
		}
	}

	// Try to add a first object
	if(!nbadd)
	{
		for(i=0,obj=objs;i<nbobjs;obj++,i++)
		{
			if(TestNewSize(del,nbdel,(*obj)->GetSize(),0))
			{
				idx[nbadd]=i;
				add[nbadd++]=(*obj);
//				addsize=(*obj)->GetSize();
				break;
			}
		}
	}



//	// Try to add a second object
//	for(i=0,obj=objs;i<nbobjs;obj++,i++)
//	{
//		if((*obj)==add[0]) continue;
//		if(TestNewSize(del,nbdel,(*obj)->GetSize(),addsize))
//		{
//			idx[nbadd]=i;
//			add[nbadd++]=(*obj);
//			break;
//		}
//	}

	if(!nbadd) return(false);
	// Delete the objects from the group and insert them in objs.
	for(i=0;i<nbdel;i++)
	{
		this->Delete(del[i]);
		objs[nbobjs++]=del[i];
	}

	// Insert the objects in the group and delete them from objs.
	// If idx[1] > idx[0] -> idx[1]-- because idx[0] will be deleted first.
	if(idx[1]>idx[0]) idx[1]--;
	for(i=0;i<nbadd;i++)
	{
		this->Insert(add[i]);
		memmove(&objs[idx[i]],&objs[idx[i]+1],((--nbobjs)-idx[i])*sizeof(cObj*));
	}
	return(true);
}


//------------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	RGroupBP<cGroup,cObj,cChromo>& RGroupBP<cGroup,cObj,cChromo>::operator=(const RGroupBP<cGroup,cObj,cChromo>& grp)
{
	R::RGroup<cGroup,cObj,cChromo>::operator=(grp);
	MaxSize=grp.MaxSize;
	Size=grp.Size;
	return(*this);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cChromo>
	RGroupBP<cGroup,cObj,cChromo>::~RGroupBP(void)
{
}
