// SortProj.cpp 
//

#include <assert.h>
#include <iostream>
#include <random>
#include <string>
#ifdef WIN32
	#include<ctime> 
#endif // WIN32

#ifdef linux
#include <time.h>
#endif // linux

#include <algorithm>

using namespace std;

template <class T> class SortMethod
{
public:
	SortMethod(){}
	
	~SortMethod(){}
	
	static bool isSortd(T a[] ,int N)
	{
		for(int i = 1;i < N; i++)
			if(less(a[i],a[i-1]))
				return false;
		
		return true;
	}

	static void print(T a[], int N)
	{
		for (int i = 0 ; i < N; i++)
		{
			cout<< a[i]<<" ";
		}
		cout<<endl;
	}

	static void select_sort(T a[], int N);
	static void bubble_sort(T a[], int N);
	static void insert_sort(T a[], int N);
	static void shell_sort(T a[], int N);
	//////////////////////////////////////////////////////////////////////////
	void merge_sort(T a[], int N);
	//////////////////////////////////////////////////////////////////////////
	static void quick_sort(T a[], int N);
	//////////////////////////////////////////////////////////////////////////
	static void heap_sort(T a[], int N);

private:
	static bool less(T a, T b)
	{
		return a < b;
	}

	static void heap_exch( T a[], int i, int j)
	{
		exch(a,i-1,j-1);
	}

	static void exch(T a[], int i, int j)
	{
		T t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	void merge(T a[], int lo, int mid , int hi);
	void merge_sort_Up2Down(T a[], int lo, int hi);
	void merge_sort_Down2Up(T a[], int N);

	//////////////////////////////////////////////////////////////////////////
	static int partition(T a[], int lo,int hi);
	static void quick_sort(T a[], int lo, int hi);
	static void quick3_sort(T a[], int lo, int hi);

	//////////////////////////////////////////////////////////////////////////
	static void sink(T a[], int k, int N);

	T *aux;
};

// 选择排序
template<class T> void SortMethod<T>::select_sort(T a[], int N)
{
	for (int i = 0 ; i < N; i++)
	{
		int min = i;
		for(int j = i+1; j < N; j++)
			if(less(a[j],a[min])) min = j;

		exch(a,i,min);
	}
}
// 冒泡排序
template<class T> void SortMethod<T>::bubble_sort(T a[], int N)
{
	for (int i = 0; i < N; i++)
	{
		for(int j = 1; j < N-i; j++)
		{
			if(less(a[j],a[j-1]))
				exch(a,j-1,j);
		}
	}
}
// 插入排序
template<class T> void SortMethod<T>::insert_sort(T a[], int N)
{
	for(int i = 1; i < N; i++ )
	{
		// 将a[i] 插入到 a[i-1], a[i-2],a[i-3],...之中
		for(int j = i; j > 0 && less(a[j],a[j-1]); j--)
		{
			exch(a,j,j-1); // 很有意思的过程
		}
	}
}
// 希尔排序
template<class T> void SortMethod<T>::shell_sort(T a[], int N)
{
	int h = 1;
	while(h < N/3) h = 3*h + 1;
	while(h >= 1)
	{
		// 将数组变为h有序
		for(int i = h; i < N; i++)
		{
			// 将a[i] 插入到a[i-h],a[i-2*h],a[i-3*h],...之中
			for (int j = i; j >= h && less(a[j],a[j-h]); j -= h) 
				exch(a,j,j-h);
		}

		h = h/3;
	}
}

template<class T> void SortMethod<T>::merge(T a[], int lo, int mid , int hi)
{
	assert(aux != NULL);  // auxiliary array
	int i = lo, j = mid+1;
	for(int k = lo; k <= hi; k++ )  // copy source data
		aux[k] = a[k];

	for(int k = lo; k <= hi; k++ )
	{
		if		(i > mid)				a[k] = aux[j++]; // ①
		else if (j > hi)				a[k] = aux[i++]; // ②
		else if	(less(aux[i],aux[j]))	a[k] = aux[i++]; // ④
		else							a[k] = aux[j++]; // ③
	}

}

template<class T> void SortMethod<T>::merge_sort_Up2Down(T a[], int lo, int hi)
{
	if(lo >= hi) return;
	int mid = (lo + hi)/2;
	// partition
	merge_sort_Up2Down(a,lo,mid);   // sort left part
	merge_sort_Up2Down(a,mid+1,hi); // sort right part
	// merge
	merge(a,lo,mid,hi);
}

#define  MIN(a,b) (a) < (b) ? (a) : (b)
template<class T> void SortMethod<T>::merge_sort_Down2Up(T a[], int N )
{
	for(int sz = 1; sz < N; sz *= 2 )
		for (int lo = 0; lo < N - sz; lo += 2*sz )
		{
			int mid = lo + sz-1;
			int hi = MIN(lo + 2*sz -1 , N-1);
			merge(a,lo,mid,hi);
		}
}

//////////////////////////////////////////////////////////////////////////

template<class T> int SortMethod<T>::partition(T a[], int lo,int hi)
{
	// 将数组切分为 a[lo,...,i-1],a[i],a[i+1,...,hi]
	int i = lo, j = hi + 1;
	T temp = a[lo]; // 切分元素

	while(true)
	{
		// 扫描左右，检查扫描是否结束并交换元素
		while( less(a[++i],temp) ) if( i == hi ) break;
		while( less(temp,a[--j]) ) if( j == lo ) break;

		if( i >= j ) break;
		exch(a,i,j);
	}

	exch(a,lo,j);

	return j;
}

template<class T> void SortMethod<T>::quick_sort(T a[], int lo, int hi)
{
	if( lo >= hi ) return;
	int j = partition(a,lo,hi); // 切分

	quick_sort(a,lo,j-1);  // sort left part 
	quick_sort(a,j+1,hi);  // sort right part 
}

template<class T> void SortMethod<T>::quick3_sort(T a[], int lo, int hi)
{
	if( hi <= lo ) return;
	int lt = lo, i = lo + 1, gt = hi;
	
	T temp = a[lo];
	while(i <= gt )
	{
		if( less(a[i],temp ) )
			exch(a,lt++,i++);
		else if( less( temp,a[i]))
			exch(a ,i, gt--);
		else
			i++;
	} // a[lo...lt-1] < temp = a[lt...gt] < a[gt+1...hi]

	quick3_sort(a, lo, lt-1);
	quick3_sort(a, gt+1, hi);

}

//////////////////////////////////////////////////////////////////////////
template<class T> void SortMethod<T>::sink(T a[], int k, int N)
{
	while( 2*k <= N)
	{
		int j = 2*k;
		if( j < N && less(a[j-1],a[j]) ) j++;

		if(!less(a[k-1],a[j-1])) break;

		heap_exch(a,k,j);
		k = j;
	}
}

//////////////////////////////////////////////////////////////////////////
// 归并排序
template<class T> void SortMethod<T>::merge_sort(T a[], int N)
{
	aux = new T[N];
	//merge_sort_Up2Down(a,0,N-1);
	merge_sort_Down2Up(a,N);
	delete [] aux;
}
// 快速排序
template<class T> void SortMethod<T>::quick_sort(T a[], int N)
{
	// 为了避免最坏情况，可对数组a随机打乱 
	//random_shuffle();
//	quick_sort(a,0,N-1);
	quick3_sort(a,0,N-1);
}
// 堆排序
template<class T> void SortMethod<T>::heap_sort(T a[], int N)
{
	// 1.堆构造
	for (int k = N/2; k >=1; k--)
		sink(a,k,N);

	// 2.下沉排序
	while(N>1)
	{
		heap_exch(a,1,N--);
		sink(a,1,N);
	}
}

class SortCompare
{
public:

	static double timeRandomData(string sortType, int N, int T)
	{
		double total = 0.0;
		int *a = new int[N];

		assert(a != NULL);

		std::default_random_engine generator;  
		std::uniform_int_distribution<int> dis(0,500);

		for(int t =0 ; t< T; t++) // 重复T次
		{
			for (int i =0 ; i < N; i++) // 数组长度N
			{
				a[i] = dis(generator);
			}

			total += run_time(sortType,a,N);
		}

		delete []a;

		return total;
	}

private:

	static double run_time(string sortType, int a[], int N)
	{
		time_t start_time,stop_time;
		start_time = time(nullptr);

		if(sortType.compare("select") == 0 )
			SortMethod<int>::select_sort(a,N);
		else if(sortType.compare("bubble") == 0)
			SortMethod<int>::bubble_sort(a,N);
		else if(sortType.compare("insert") == 0 )
			SortMethod<int>::insert_sort(a,N);
		else if(sortType.compare("shell") == 0 )
			SortMethod<int>::shell_sort(a,N);

		stop_time = time(nullptr);

		return (stop_time - start_time)*1.0/1000;
	}
};

int main()
{
	char ch[12] = {'S','O','R','T','E','X','A','M','P','L','E'};
	SortMethod<char>::print(ch,11);
	SortMethod<char>::select_sort(ch,11);
	bool sorted = SortMethod<char>::isSortd(ch,11);
	SortMethod<char>::print(ch,11);
	cout<<"sorted: "<<sorted<<endl;

	int a[10] = {8,9,1,7,2,3,5,4,6,0};
	SortMethod<int>::print(a,10);
	SortMethod<int>::select_sort(a,10);
	sorted = SortMethod<int>::isSortd(a,10);
	SortMethod<int>::print(a,10);
	cout<<"sorted: "<<sorted<<endl;

	int b[10] = {8,9,1,7,2,3,5,4,6,0};
	SortMethod<int>::print(b,10);
	SortMethod<int>::bubble_sort(b,10);
	sorted = SortMethod<int>::isSortd(b,10);
	SortMethod<int>::print(b,10);
	cout<<"sorted: "<<sorted<<endl;

	int c[10] = {8,9,1,7,2,3,5,4,6,0};
	SortMethod<int>::print(c,10);
	SortMethod<int>::insert_sort(c,10);
	sorted = SortMethod<int>::isSortd(c,10);
	SortMethod<int>::print(c,10);
	cout<<"sorted: "<<sorted<<endl;


	int d[10] = {8,9,1,7,2,3,5,4,6,0};
	SortMethod<int>::print(d,10);
	SortMethod<int>::shell_sort(d,10);
	sorted = SortMethod<int>::isSortd(d,10);
	SortMethod<int>::print(d,10);
	cout<<"sorted: "<<sorted<<endl;

	cout<<"============================"<<endl;
// 	string str = "MERGESORTEXAMPLE";
// 	char* data = (char*)str.c_str();
// 
// 	int N = str.length();
// 	SortMethod<char>::print(data,N);
// 
// 	SortMethod<char> merger;
// 	merger.merge_sort(data,N);
// 
// 	SortMethod<char>::print(data,N);
// 	sorted = SortMethod<char>::isSortd(data,N);
// 	cout<<"sorted: "<<sorted<<endl;

	//////////////////////////////////////////////////////////////////////////

// 	string str = "RBWWRWBRRWBR";
// 	char* data = (char*)str.c_str();
// 
// 	int N = str.length();
// 	SortMethod<char>::print(data,N);
// 	SortMethod<char>::quick_sort(data,N);
// 	SortMethod<char>::print(data,N);
// 	sorted = SortMethod<char>::isSortd(data,N);
// 	cout<<"sorted: "<<sorted<<endl;

	string str = "SORTEXAMPLE";
	char* data = (char*)str.c_str();

	int N = str.length();
	SortMethod<char>::print(data,N);
	SortMethod<char>::heap_sort(data,N);
	SortMethod<char>::print(data,N);
	sorted = SortMethod<char>::isSortd(data,N);
	cout<<"sorted: "<<sorted<<endl;

// 	int N = 10000;
// 	int T = 100;
// 	string type1 = "shell";
// 	string type2 = "insert";
// 	double t1 = SortCompare::timeRandomData(type1,N,T);
// 	double t2 = SortCompare::timeRandomData(type2,N,T);
// 
// 	cout<<"For "<< N << " random Ints "<<endl;
// 	cout<<type1<<" cost :"<<t1<<" s and " <<type2 <<" costs :"<<t2<<" s."<<endl;

	return 0;
}

