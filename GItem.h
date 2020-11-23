template <class G>
class GItem
{
	private:
		G item;
		int priority;
		GItem<G>* nextItem;

	public:
		GItem();
		GItem(G itemObj);
		GItem(G itemObj,int pri);
		~GItem();

		G getItem();
		void setItem(G itemObj);

		GItem<G>* getNextItem();
		void setNextItem(GItem<G>* itemObj);

		int getPriority();
		void setPriority(int pri);
};
