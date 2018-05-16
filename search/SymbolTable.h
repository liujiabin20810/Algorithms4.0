#pragma once
//#include <gtest/gtest.h>
#include <vector>

template <class Key, class Value> class ST
{
public:

	virtual ~ST(void)
	{}

	virtual void put(Key key, Value val) = 0;
	virtual Value get(Key key) const = 0 ;
	virtual int size() const = 0;

	virtual void del(Key key) = 0;
	virtual bool contains(Key key) const { return false; } 
	virtual bool isEmpty() const = 0;

};
//////////////////////////////////////////////////////////////////////////
template<class Key,class Value> class SequentialSearchST : public ST<Key,Value>
{
	struct Node
	{
		Key key;
		Value val;
		Node* next;

		Node(Key key, Value val, Node* next)
		{
			this->key = key;
			this->val = val;
			this->next = next;
		}
	};

	Node* root;

	int n;
public:

	SequentialSearchST():root(nullptr), n(0)
	{ 	}
	SequentialSearchST(Key key, Value val);

	~SequentialSearchST()
	{
		for (int i = 0; i < n; i++)
			del(root->key);
	}
	
	void put(Key key, Value val) ;
	Value get(Key key) const  ;
	int size() const;

	void del(Key key) ;
	bool contains(Key key) const;
	bool isEmpty() const ;

 	void print();
// 	Key min();
// 	Key max();
// 	Key floor();
// 	Key ceiling();
// 	int rank();
// 	Key select( int k);
// 	void delMax();
// 	void delMin();
};
//////////////////////////////////////////////////////////////////////////
template<class Key,class Value> class BinarySearchST : public ST<Key,Value>
{
	Key *keys;
	Value *vals;
	int N;
	int capacity;

public:
	BinarySearchST():N(0),capacity(2)
	{ 
		keys = new Key[capacity];
		vals = new Value[capacity];
	}

	BinarySearchST(int capacity);

	~BinarySearchST()
	{
		delete[] keys;
		delete[] vals;
	}
	
	int rank(Key key) const;
	void put(Key key, Value val) ;
	Value get(Key key) const  ;
	int size() const { return N; }

	void del(Key key) ;
	bool contains(Key key) const ;
	bool isEmpty() const { return N ==0 ; }
	void print();

};
//////////////////////////////////////////////////////////////////////////
template<class Key,class Value> class BST	: public ST<Key,Value>
{
	struct Node
	{
		Key		key;
		Value	val;
		Node*	right;
		Node*	left;
		int		N;

		Node(Key key, Value val,int N)
		{
			this->key = key;
			this->val = val;
			this->N = N;
			this->right	 = nullptr;
			this->left	= nullptr;
		}
	};

public:
	
	BST(): root(nullptr){}
	~BST()
	{
// 		while( root->N > 0 )
// 			delMin(root);
	}
	void put(Key key, Value val);
	Value get(Key key) const;
	int size() const;

	void del(Key key);
	bool isEmpty() const;

	Key min() const
	{ 
		if(isEmpty()) return nullptr;
		return ((Node*)min(root))->key; 
	}
	Key max() const
	{
		if(isEmpty()) return nullptr;

		return ((Node*)max(root))->key;
	}
	Key floor(Key key) // the key just smaller than key and nearby the key
	{ 
		if(isEmpty()) return nullptr;
		return ((Node*)floor(root,key))->key; 
	}
	Key select(int k)
	{ 
		if(isEmpty()) return nullptr;
		return ((Node*)select(root,k))->key; 
	}

	int rank(Key key) { return rank(root,key); }

	std::vector<Key> keys() { return keys(min(),max()); }

	std::vector<Key> keys(Key lo, Key hi)
	{
		std::vector<Key> queue;
		keys(root,queue,lo,hi);
		return queue;
	}

	void print() const
	{
		print(root);
	}
private:

	int		size(Node* node) const;

	Value	get(Node* node, Key key) const;
	void*	put(Node* node, Key key, Value val);

	void	del(Node* node, Key key);
	void	del(Node* node);
	void*	delMin(Node* node);

	void*	min(Node* node ) const;
	void*	max(Node* node ) const;
	void*	floor(Node* node, Key key);
	void*	select(Node* node,int k);
	int		rank(Node* node, Key key);

	void	keys(Node* node, std::vector<Key>& queue, Key lo, Key hi);

	void	print(Node* node) const;

	Node* root;
};