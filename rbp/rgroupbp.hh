/*

	R Project Library

	RNodeGA.hh

	GA Node - Header.

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



//-----------------------------------------------------------------------------
//
// class RGroupBP<cGroup,cObj,cGroupData>
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::RGroupBP(RGroupBP* grp)
		: RGGA::RGroup<cGroup,cObj,cGroupData>(grp), Size(grp->Size), MaxSize(grp->MaxSize)
{
}


//-----------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::RGroupBP(RGGA::RGroups<cGroup,cObj,cGroupData>* owner,const unsigned int id,const cGroupData* data)
		: RGGA::RGroup<cGroup,cObj,cGroupData>(owner,id,data), Size(0), MaxSize(data->MaxSize)
{
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::Verify(void)
{
	if(!RGGA::RGroup<cGroup,cObj,cGroupData>::Verify())
		return(false);
	if(Size>MaxSize)
	{
		cout<<"Size("<<Size<<") > MaxSize("<<MaxSize<<") for group "<<Id<<endl;
		return(false);
	}
	return(true);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	void RGroupBP<cGroup,cObj,cGroupData>::Clear(void)
{
	RGGA::RGroup<cGroup,cObj,cGroupData>::Clear();
	Size=0;
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::CanInsert(const cObj* obj)
{
	return(Size+obj->GetSize()<=MaxSize);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::TestNewSize(cObj** del,unsigned int& nbdel,unsigned int addsize,unsigned int size)
{
	unsigned int newsize,maxsize;
	unsigned int s1,s2,s3;
	cObj* cur1;
	cObj* cur2;
	cObj* cur3;
	unsigned int i,j,k;

	// New Size if addsize is added.
	newsize=Size+size+addsize;
	if(addsize>size) maxsize=addsize; else maxsize=size;
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
	if((nbdel>=3)||(!NbSubObjects)) return(false);
	for(i=0;i<NbSubObjects;i++)
	{
		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1==del[0])||(cur1==del[1])||(cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-cur1->GetSize();
		if((s1<=MaxSize)&&(s1>Size))
		{
			del[nbdel++]=cur1;
			return(true);
		}
	}

	// Try to del 2 object with Max 3 Objects deleted.
	if((nbdel>=2)||(NbSubObjects<2)) return(false);
	for(i=0;i<NbSubObjects-1;i++)
	{
		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1==del[0])||(cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-cur1->GetSize();
		for(j=i+1;j<NbSubObjects;j++)
		{
			cur2=Owner->GetObj(SubObjects+j);
//			if((cur2==del[0])||(cur2->GetSize()>=addsize)||(cur2->GetSize()>=size)) continue;
			s2=s1-cur2->GetSize();
			if((s2<=MaxSize)&&(s2>Size))
			{
				del[nbdel++]=cur1;
				del[nbdel++]=cur2;
				return(true);
			}
		}
	}

	// Try to del 3 object with Max 3 Objects deleted.
	if((nbdel)||(NbSubObjects<3)) return(false);
	for(i=0;i<NbSubObjects-2;i++)
	{
		cur1=Owner->GetObj(SubObjects+i);
//		if((cur1->GetSize()>=addsize)||(cur1->GetSize()>=size)) continue;
		s1=newsize-cur1->GetSize();
		for(j=i+1;j<NbSubObjects-1;j++)
		{
			cur2=Owner->GetObj(SubObjects+j);
//			if((cur2->GetSize()>=addsize)||(cur2->GetSize()>=size)) continue;
			s2=s1-cur2->GetSize();
			for(k=j+1;k<NbSubObjects;k++)
			{
				cur3=Owner->GetObj(SubObjects+k);
//				if((cur3->GetSize()>=addsize)||(cur3->GetSize()>=size)) continue;
				s3=s2-cur3->GetSize();
				if((s3<=MaxSize)&&(s3>Size))
				{
					del[nbdel++]=cur1;
					del[nbdel++]=cur2;
					del[nbdel++]=cur3;
					return(true);
				}
			}
		}
	}

	// Nothing can be done
	return(false);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::DoOptimisation(cObj** objs,unsigned int& nbobjs)
{
	unsigned int idx[2];           // Indexed of the objects to add in objs.
	cObj* del[3];                  // Pointers to the objects to delete.
	cObj* add[2];                  // Pointers to the objects to add.
	unsigned int nbdel;            // Number of objects to delete.
	unsigned int nbadd;            // Number of objects to add.
	cObj** obj;                    // Current object eventually to add.
	cObj** obj2;
	unsigned int i,j;
	unsigned int addsize;

	// If the groups is maximum filled, no optimisation needed.
	if(Size==MaxSize)
		return(false);

	// Init Part
	add[0]=add[1]=del[0]=del[1]=del[2]=0;   // No objs added or deleted
	idx[0]=idx[1]=RGGA::NoObject;
	nbdel=nbadd=0;


	// Try to add a first object
	if(!nbadd)
	{
		for(i=0,obj=objs;i<nbobjs;obj++,i++)
		{
			if(TestNewSize(del,nbdel,(*obj)->GetSize(),0))
			{
				idx[nbadd]=i;
				add[nbadd++]=(*obj);
				addsize=(*obj)->GetSize();
				break;
			}
		}
	}

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
		Delete(del[i]);
		objs[nbobjs++]=del[i];
	}

	// Insert the objects in the group and delete them from objs.
	// If idx[1] > idx[0] -> idx[1]-- because idx[0] will be deleted first.
	if(idx[1]>idx[0]) idx[1]--;
	for(i=0;i<nbadd;i++)
	{
		Insert(add[i]);
		memcpy(&objs[idx[i]],&objs[idx[i]+1],((--nbobjs)-idx[i])*sizeof(cObj*));
	}
	return(true);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>& RGroupBP<cGroup,cObj,cGroupData>::operator=(const RGroupBP<cGroup,cObj,cGroupData>& grp)

{
	RGGA::RGroup<cGroup,cObj,cGroupData>::operator=(grp);
	MaxSize=grp.MaxSize;
	Size=grp.Size;
	return(*this);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	RGroupBP<cGroup,cObj,cGroupData>::~RGroupBP(void)
{
}
