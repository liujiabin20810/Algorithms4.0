// PriorityQueue.cpp  
//

#include <array>
#include <iostream>
#include <assert.h>

using namespace std;

template <class Key> class MaxPQ
{

public:
	MaxPQ();
	MaxPQ(int maxN) {   pq = new Key[maxN];	N = 0;}
	~MaxPQ() {	delete[] pq; }

	bool isEmpty() { return N == 0 ; }

	int size() { return N; }

	void insert( Key v)
	{
		pq[++N] = v;

		swim(N);
	}

	Key delMax()
	{
		Key maxKey = pq[1];
		exch(1,N--);  // 与最后一个节点交换
		pq[N+1] = NULL; // 防止越界
		sink(1);

		return maxKey;
	}

	void show()
	{
		for(int i = 1; i <= N; i++)
			cout<<pq[i]<<" ";
		cout<<endl;
	}

private:

	void swim(int k); // 上浮
	void sink(int k); // 下沉
	bool less(int i, int j); // 比较
	void exch(int i, int j); // 交换

	Key* pq;

	int N ;
};

template<class Key> bool MaxPQ<Key>::less(int i, int j)
{
	return pq[i] < pq[j];
}

template<class Key> void MaxPQ<Key>::exch(int i, int j)
{
	Key temp = pq[i];
	pq[i] = pq[j];
	pq[j] = temp;
}

template<class Key> void MaxPQ<Key>::swim(int k)
{
	int j = k / 2;
	while(j > 0 && less(j,k))
	{		
		exch(j,k);
		k = j;
		j = j/2;
	}
}

template<class Key> void MaxPQ<Key>::sink(int k)
{
	while( 2*k <= N)
	{
		int j = 2*k;
		if(j < N && less(j,j+1)) j = j+1;

		if(!less(k,j)) break;
		
		exch(k,j);
		k = j;	
	}
}

int main()
{

	string data = "SORTEXAMPLE";
	int n = data.length();

	cout<<"n = " << n<<endl;

	MaxPQ<char>* priority_queue = new MaxPQ<char>(100);

	cout<<"input: ";
	char * ch = (char *) data.c_str();
	for (int i =0; i < n; i++)
	{
		cout<< ch[i] << " ";
		priority_queue->insert(ch[i]);
	}

	cout<<"\nbinary heap : ";
	priority_queue->show();

	delete priority_queue;

	return 0;
}

