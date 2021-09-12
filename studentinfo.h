//heap class variables,methods
class Heap
{
	public:
		Heap(int size);
		int insert (char * newkey);
		char * remove();
	private:
		int totalelements;
		int elementno;
		char **heaparray;
		void swap(int i, int j);
		int compare(int i,int j);
};

