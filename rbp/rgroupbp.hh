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
// class RGroupBP<cGroup,cOb,cGroupData>
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
		: RGGA::RGroup<cGroup,cObj,cGroupData>(owner,id,data), Size(0.0), MaxSize(data->MaxSize)
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
		cout<<"Size>MaxSize for group "<<Id<<endl;
		return(false);
	}
	return(true);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	void RGroupBP<cGroup,cObj,cGroupData>::Clear(void)
{
	RGGA::RGroup<cGroup,cObj,cGroupData>::Clear();
	Size=0.0;
}

//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::CanInsert(const cObj* obj)
{
	return(Size+obj->GetSize()<=MaxSize);
}


//---------------------------------------------------------------------------
template<class cGroup,class cObj,class cGroupData>
	bool RGroupBP<cGroup,cObj,cGroupData>::DoOptimisation(cObj** objs,unsigned int& nbobjs)
{
	unsigned int idx[2];           // Indexed of the objects to add in objs.
	cObj* del[3];                  // Pointers to the objects to delete.
	cObj* add[2];                  // Pointers to the objects to add.
	unsigned int trydel;           // Number of try for deleting objects.
	unsigned int nbdel;            // Number of objects to delete.
	unsigned int nbadd;            // Number of objects to add.
	char tryfind;                  // Number of try to do.
	double size;                   // Current size with the add and del.
	double minsize;                // Minimum size of the object of the group.
	double s;                      // Size of the object eventually to add.
	double newsize;                // Size of the group whith the object eventually to add.
	cObj** obj;                    // Current object eventually to add.
	cObj* best;                    // Object from the group with the minimum size.
	cObj* cur;                     // Current object of the group treated.
	unsigned int i,j;

	// If the groups is maximum filled, no optimisation needed.
	if(Size==MaxSize)
		return(false);

	// Init Part
	size=Size;                              // The "actual" size of the group.
	add[0]=add[1]=del[0]=del[1]=del[2]=0;   // No objs added or deleted
	idx[0]=idx[1]=RGGA::NoObject;
	nbdel=nbadd=0;
	tryfind=2;                              // Maximum 2 try
	
	while((tryfind--)&&(nbadd<2)&&(nbdel<3))           // Maximum 2 objects to add and 3 objects to del.
	{

		// Go through the objects not yet assign to a group.
		for(i=0,obj=objs;(i<nbobjs)&&(nbadd<2);obj++,i++)
		{
		
			// Test if the current object eventually to add is not already
			// selected.
			if(((*obj)==add[0])||((*obj)==add[1]))
				continue;

			// Test if this object can be added.
			s=(*obj)->GetSize();
			newsize=size+s;

			// while the size of the group plus the object eventually to add is greather than
			// the maximum size, try to delete maximum 3 objs.
			trydel=0;
			while((newsize>MaxSize)&&(nbdel+trydel<3))
			{
				minsize=s;
				best=0;

				// Test all the object of the group or until one has be found
				// that fit the condition.
				for(j=0;j<NbSubObjects;j++)
				{
					cur=Owner->GetObj(SubObjects+j);

					// Verify that cur is not already used &nd that is smaller
					// than the object eventually to add.
					if((cur==del[0])||(cur==del[1])||(cur==del[2])||(cur->GetSize()>=s))
						continue;

					// Test if the maximum size is not exceed whithout the
					// current object, delete it.
					if(newsize-cur->GetSize()<=MaxSize)
					{
						best=cur;
						break;
					}

					// Find the smallest object of the group.
					if(cur->GetSize()<minsize)
					{
						minsize=cur->GetSize();
						best=cur;
					}
				}

				// If an object was found, it can be deleted.
				if(best)
				{
					del[nbdel+(trydel++)]=best;
					newsize-=best->GetSize();
				}
				else
					break;
			}

			// If the maximum size of the group is not exceed with the object
			// eventually to add and the new size is greather than the old one, add it.
			if((newsize<=MaxSize)&&(newsize>Size))
			{
				nbdel+=trydel;
				idx[nbadd]=i;
				add[nbadd++]=(*obj);
				size=newsize;
			}
		}

		// If after one tour, no object could be added, another tour resolves nothing.
		if(!nbadd)
			return(false);
	}

	// Some assertion to verify
	RReturnValIfFail(nbadd,false);
	RReturnValIfFail(size>Size,false);
	RReturnValIfFail(size<=MaxSize,false);

//	cout<<"MaxSize: "<<MaxSize<<"    Futur: "<<size<<"    Before: "<<Size;
	// Delete the objects from the group and insert them in objs.
	for(i=0;i<nbdel;i++)
	{
		Delete(del[i]);
		objs[nbobjs++]=del[i];
	}

//	cout<<"   After Delete: "<<Size;
	// Insert the objects in the group and delete them from objs.
	// If idx[1] > idx[0] -> idx[1]-- because idx[0] will be deleted first.
	if(idx[1]>idx[0]) idx[1]--;
	for(i=0;i<nbadd;i++)
	{
		Insert(add[i]);
//		if(!Verify())
//			cout<<"Problem after Insert an obj in group "<<Id<<endl;
		memcpy(&objs[idx[i]],&objs[idx[i]+1],((--nbobjs)-idx[i])*sizeof(cObj*));
	}
//	cout<<"   After Insert: "<<Size<<endl;

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
