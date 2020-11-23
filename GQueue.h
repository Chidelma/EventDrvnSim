#include "GItem.hpp"
template <class G>
class GQueue
{
	private:
		GItem<G>* frontItem;
		GItem<G>* tailItem;
	public:
		GQueue();
		~GQueue();
		bool isEmpty();
		void queueItem(G event);
		void priQueueItem(G event, int pri);
		G dequeueItem();
		G getFrontData();
};
