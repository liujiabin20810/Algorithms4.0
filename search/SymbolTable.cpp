#include "SymbolTable.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
template<class Key, class Value> SequentialSearchST<Key, Value>::SequentialSearchST(Key key, Value val)
{
	root = new Node(key,val,nullptr);
	n = 1;
}
//----------------------------------------------
template<class Key, class Value> Value SequentialSearchST<Key, Value>::get(Key key) const
{
	for (Node* x = root; x != nullptr ; x = x->next)
	{
		if( key == x->key)
			return x->val;
	}

	return 0;
}
//----------------------------------------------
template<class Key, class Value> void SequentialSearchST<Key, Value>::put(Key key, Value val)
{
	for (Node* x = root; x != nullptr; x = x->next)
	{
		if( key == x->key)
		{
			x->val = val;
			return;
		}
	}

	Node* p = new Node(key,val,root);
	root = p;

	n++;

}
//----------------------------------------------
template<class Key, class Value> int SequentialSearchST<Key, Value>::size() const
{
	return n;
}
//----------------------------------------------
template<class Key, class Value> void SequentialSearchST<Key, Value>::del(Key key)
{
	if (nullptr == root) return;

	if( root->key == key ) { Node* p = root; root = root->next; delete p;  n--;}
	else
	{
		Node* x = root->next;
		Node* parent = root;
		while( x )
		{
			if( x-> key == key )
			{
				parent->next = x->next;
				delete x;
				n--;
				break;
			}
			else
			{
				x = x->next;
				parent = x;
			}
		}

	}

}
//----------------------------------------------
template<class Key, class Value> bool SequentialSearchST<Key, Value>::contains(Key key) const
{
	return get(key) != 0;
}
//----------------------------------------------
template<class Key, class Value> bool SequentialSearchST<Key, Value>::isEmpty() const
{
	return n > 0;
}
//----------------------------------------------
template<class Key, class Value> void SequentialSearchST<Key, Value>::print()
{
	for (Node* x = root; x != nullptr; x = x->next)
	{
		std::cout<< x->key <<" "<< x->val<<"\n ";
	}

	std::cout<<std::endl;
}
//////////////////////////////////////////////////////////////////////////
template<class Key,class Value> BinarySearchST<Key,Value>::BinarySearchST(int capacity)
{
	if(capacity < 2)	capacity = 2;

	keys = new Key[capacity];
	vals = new Value[capacity];

	N = 0;
	this->capacity = capacity;
}
//----------------------------------------------
template<class Key,class Value> void BinarySearchST<Key,Value>::put(Key key, Value val)
{
	if( capacity/2 < N)
	{
		capacity = 2*capacity;
		Key* larger_keys = new Key[capacity];
		Value* larger_vals = new Value[capacity];

//		cout<< larger_vals[0] <<" "<< larger_vals[N]<<" "<<larger_vals[capacity-1]<<endl;
		for (int i= 0; i < N; i++)
		{
			larger_keys[i] = keys[i];
			larger_vals[i] = vals[i];
		}

		delete [] keys;
		delete [] vals;

		keys = larger_keys;
		vals = larger_vals;

//		print();
	}

	int i = rank(key);
	// already exist
	if( contains(key) )
	{
		vals[i] = val; return;
	}
	// new key, move the front to end
	for(int j = N-1; j >= i; j--)
	{
		keys[j+1]	= keys[j];
		vals[j+1]	= vals[j];
	}

	keys[i] = key; vals[i] = val;	// add new key
	N++;
}
//----------------------------------------------
template<class Key, class Value> Value BinarySearchST<Key,Value>::get(Key key) const
{
	if(isEmpty())
		return 0;
	
	if( !contains(key) )
		return 0;
	
	int i = rank(key);
	return vals[i];
}
//----------------------------------------------
template<class Key, class Value> int BinarySearchST<Key,Value>::rank(Key key) const
{
	int lo = 0, hi = N-1;
	while ( lo <= hi )
	{
		int mid =  lo + (hi - lo)/2;
		if( key > keys[mid] )
			lo = mid + 1;
		else if( key < keys[mid] )
			hi = mid - 1;
		else
			return mid;
	}
	// hi may be less than 0, and do not check it when use( get , put method )
	return lo;
}

//----------------------------------------------
template<class Key, class Value> bool BinarySearchST<Key,Value>::contains(Key key) const
{
	if(isEmpty()) return false;
	
	int i = rank(key);
	if( i < N && keys[i] == key)	return true;
	else							return false;

}
//----------------------------------------------
template<class Key, class Value> void BinarySearchST<Key,Value>::del(Key key)
{
	if( isEmpty() ) return ;
	if( !contains(key) )	// not found
		return; 

	int i = rank(key);
	for(int j = i; j < N-2; j++)
	{
		keys[j] = keys[j+1];
		vals[j] = vals[j+1];
	}

	keys[N-1] = keys[N];
	vals[N-1] = vals[N];
	N--;
}
//----------------------------------------------
template<class Key, class Value> void BinarySearchST<Key,Value>::print()
{
	for (int i = 0; i <  N; i++)
		std::cout<<"Key: "<<keys[i]<<", Value: "<<vals[i]<<std::endl;
	std::cout<<std::endl;
}
//////////////////////////////////////////////////////////////////////////
// Note: it need return the Node pointer after create a new Node
// otherwise, the node will be free by destruct function
template<class Key,class Value> void* BST<Key,Value>::put(Node* node,Key key, Value val)
{
	if (nullptr == node)
	{
		node = new Node(key,val,1);
		return node;
	}

	if( node->key > key)	// left node smaller
		node->left = (Node*)put(node->left,key,val);
	else if( node->key < key )	// right node bigger
		node->right = (Node*)put(node->right,key,val);
	else
		node->val = val;

	node->N = size(node->left) + size(node->right) + 1;

	return node;
}
//----------------------------------------------
template<class Key,class Value> void BST<Key,Value>::put(Key key, Value val)
{
	root = (Node*)put(root,key,val);
}
//----------------------------------------------
template<class Key,class Value> Value BST<Key,Value>::get(Node* node, Key key) const
{
	if (nullptr == node) 	return 0;

	if( node->key > key)
		return get(node->left,key);
	else if(node->key < key)
		return get(node->right,key);
	else
		return node->val;

}
//----------------------------------------------
template<class Key,class Value> Value BST<Key,Value>::get(Key key) const
{
	return get(root,key);
}
//----------------------------------------------
template<class Key,class Value> int BST<Key,Value>::size(Node* node) const
{
	if ( nullptr == node ) return 0;
	else							return node->N;
}
//----------------------------------------------
template<class Key,class Value> int BST<Key,Value>::size() const
{
	return size(root);
}
//----------------------------------------------
template<class Key,class Value> void* BST<Key,Value>::delMin(Node* node)
{
	if (nullptr == node->left)
	{
		Node* tmp = node;
		node = node->right;
		delete tmp;

		return node;
	}

	node->left = (Node*)delMin(node->left);
	node->N = size(node->left) + size(node->right) + 1;

	return node;
}
//----------------------------------------------
template<class Key,class Value> void BST<Key,Value>::del(Node* node, Key key)
{
	if (  nullptr == node) return;

	if( node->key > key ) 
		del(node->left,key);
	else if( node->key < key )
		del(node->right, key);
	else
	{
		// current Node: node
		Node* tmpNode = node;
		if( node->left == NULL) node = node->right;		
		else if( node->right == NULL ) node = node->left;
		else
		{
			node = (Node*)min(tmpNode->right);
			node->right = (Node*)delMin(tmpNode->right);
			node->left	= tmpNode->left;
		}

		delete tmpNode;
	}

	node->N = size(node->left) + size(node->right) + 1;
}
//----------------------------------------------
template<class Key,class Value> void BST<Key,Value>::del(Key key)
{
	del(root,key);
}
//----------------------------------------------

//----------------------------------------------
template<class Key,class Value> bool BST<Key,Value>::isEmpty() const
{
	return nullptr == root;
}
//----------------------------------------------
template<class Key,class Value> void* BST<Key,Value>::min(Node* node ) const
{
	if (nullptr == node) return nullptr;

	if (nullptr != node->left)
		return min(node->left);
	else
		return node;
}
//----------------------------------------------
template<class Key,class Value> void* BST<Key,Value>::max(Node* node) const
{
	if (nullptr == node) return nullptr;

	if (nullptr != node->right) return max(node->right);
	else					  return node;
}
//----------------------------------------------
template<class Key,class Value> void* BST<Key,Value>::floor(Node* node, Key key)
{
	if (nullptr == node) return nullptr;
	
	if( node->key > key )	return floor(node->left,key);
	else if( node->key == key ) return node;
	else
	{
		Node* t = (Node*) floor(node->right,key);
		if (nullptr == t)	return node;
		else			return t;
	}
}
//----------------------------------------------
template<class Key,class Value> void* BST<Key,Value>::select(Node* node,int k)
{
	if (nullptr == node) return nullptr;

	int t = size( node->left );
	if( t > k )			return select( node->left, k );
	else if ( t < k )	return select( node->right, k -t - 1 ); // Note: change the order index
	else				return node;
}
//----------------------------------------------
// return the number of items that key less than the node
template<class Key,class Value> int BST<Key,Value>::rank(Node* node, Key key)
{
	if (nullptr == node) return 0;
	if( node->key > key )		return rank(node->left, key);
	else if( node->key < key )	return 1 + size( node->left ) + rank(node->right,key);
	else						return size(node->left);
}
//----------------------------------------------
template<class Key,class Value> void BST<Key,Value>::keys(Node* node, std::vector<Key>& queue, Key lo, Key hi)
{
	if (nullptr == node) return;
	if( node->key > lo ) keys(node->left, queue,lo,hi);			// add left child tree
	if( node->key >= lo && node->key <= hi ) queue.push_back(node->key); // Note: add self, be careful of the condition
	if( node->key < hi ) 	keys(node->right, queue, lo, hi);	// add right child tree

}
//----------------------------------------------
template<class Key,class Value> void BST<Key,Value>::print(Node* node) const
{
	if (nullptr == node)		return;

	print( node->left );
	std::cout <<"Key: "<<node->key <<" Value: "<< node->val<<std::endl; 
	print( node->right);

}