#include "GItem.h"

template <class G>
GItem<G>::GItem()
{
	nextItem = 0;
	priority = 0;
}

template <class G>
GItem<G>::GItem(G itemObj)
{
	item = itemObj;
	nextItem = 0;
	priority = 0;
}

template <class G>
GItem<G>::GItem(G itemObj, int pri)
{
	item = itemObj;
	nextItem = 0;
	priority = pri;
}

template <class G>
GItem<G>::~GItem()
{
	while(nextItem != 0)
	{
		delete nextItem;
	}
}

template <class G>
G GItem<G>::getItem()
{
	return item;
}

template <class G>
void GItem<G>::setItem(G itemObj)
{
	item = itemObj;
}

template <class G>
GItem<G>* GItem<G>::getNextItem()
{
	return nextItem;
}

template <class G>
void GItem<G>::setNextItem(GItem<G>* itemObj)
{
	nextItem = itemObj;
}

template <class G>
int GItem<G>::getPriority()
{
	return priority;
}

template <class G>
void GItem<G>::setPriority(int pri)
{
	priority = pri;
}
