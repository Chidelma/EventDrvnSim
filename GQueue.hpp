#include "GQueue.h"

template <class G>
GQueue<G>::GQueue()
{
	frontItem = 0;
	tailItem = 0;
}

template <class G>
GQueue<G>::~GQueue()
{
	while(!isEmpty())
	{
		dequeueItem();
	}
}

template <class G>
bool GQueue<G>::isEmpty()
{
	return (frontItem == 0);
}

template <class G>
void GQueue<G>::queueItem(G newItem)
{
	GItem<G>* genItem = new GItem<G>(newItem);
	if(tailItem != 0)
	{
		tailItem->setNextItem(genItem);
	}
	else
	{
		frontItem = genItem;
	}
	tailItem = genItem;
}

template <class G>
void GQueue<G>::priQueueItem(G newItem, int pri)
{
	GItem<G>* genItem = new GItem<G>(newItem, pri);
	if(frontItem == 0 || frontItem->getPriority() > pri)
	{
		if(frontItem != 0)
		{
			genItem->setNextItem(frontItem);
		}
		frontItem = genItem;
		if(tailItem == 0)
		{
			tailItem = frontItem;
		}
	}
	else
	{
		GItem<G>* t = frontItem;
		while((t->getNextItem() != 0) && (t->getNextItem()->getPriority() <= pri))
		{
			t = t->getNextItem();
		}
		genItem->setNextItem(t->getNextItem());
		t->setNextItem(genItem);
		if(genItem->getNextItem() == 0)
		{
			tailItem = genItem;
		}
	}
}

template <class G>
G GQueue<G>::dequeueItem()
{
	G fItem;
	if(frontItem != 0)
	{
		fItem = frontItem->getItem();
		frontItem = frontItem->getNextItem();
		if(frontItem == 0)
		{
			tailItem = 0;
		}
	}
	return fItem;
}

template <class G>
G GQueue<G>::getFrontData()
{
	G fItem;
	if(frontItem != 0)
	{
		fItem = frontItem->getItem();
	}
	return fItem;
}
