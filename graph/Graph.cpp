/************************************************************************/
/* Copyright 2018 Lewis                                                            */
/* License GPL 3.0																		*/
/* Author:  Lewis                                                                      */
/* Description: Algorithms 4 - Graph										   */
/************************************************************************/
#include "Graph.h"
#include <iostream>
#include <queue>
//------------------------------------------------------------------------
CGraph::CGraph()
{
	this->V = 0;
	this->E = 0;

	adj.clear();
}
//------------------------------------------------------------------------
CGraph::CGraph( std::ifstream& fin)
{
	fin >> V;
	fin >> E;
	adj.resize(V);

	for (int i =0; i < E; i++)
	{
		int v,w;
		fin >> v >> w;
		addEdge(v,w);
	}
}
//------------------------------------------------------------------------
void CGraph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}
//------------------------------------------------------------------------
std::vector<int> CGraph::getAdj(int v)
{
	// reverse the added edge, LIFO
	std::vector<int> vec;
	int n = adj[v].size();

	for (int i = n - 1; i >= 0; i--)
		vec.push_back(adj[v][i]);

	return vec;
}
//------------------------------------------------------------------------
void CGraph::print()
{
	std::cout << "=====================\n";
	std::cout << V << " vertices , " << E << " edges\n";
	for (int i = 0; i < V; i++)
	{
		std::vector<int> adj = getAdj(i);
		std::cout << i << " ";
		for (int j : adj)
			std::cout << j << " ";
		std::cout << std::endl;
	}
	std::cout << "=====================\n";
}
//////////////////////////////////////////////////////////////////////////
DepthFirstPaths::DepthFirstPaths(CGraph G, int s)
{
	int n = G.getV();
	marked = new bool[n];
	edgeTo = new int[n];
	// init
	for (int i = 0; i < n; i++)
	{
		marked[i] = false;
		edgeTo[i] = -1;
	}
	this->s = s;

	dfs(G, s);

}
//------------------------------------------------------------------------
void DepthFirstPaths::dfs(CGraph G, int v)
{
	marked[v] = true;

	//for (int w : G.getAdj(v)) std::cout << w << " ";
	//std::cout << std::endl;
	for (int w : G.getAdj(v))
	{
		if (!marked[w])
		{
			edgeTo[w] = v;
			dfs(G, w);
		}
	}
}
//------------------------------------------------------------------------
bool DepthFirstPaths::hasPathTo(int v)
{
	return marked[v];
}
//------------------------------------------------------------------------
std::vector<int> DepthFirstPaths::pathTo(int v)
{
	std::vector <int> path;
	if (!hasPathTo(v)) 
		return path;

	// first in last out: v is the end , want to find path to source
	// thus, the result path is reverse order.
	std::stack<int> st_path;
	for (int x = v; x != this->s; x = edgeTo[x]) st_path.push(x);
	st_path.push(this->s);

	int n = st_path.size();
	for (int i = 0; i < n; i++)
	{
		path.push_back(st_path.top());
		st_path.pop();
	}
	return path;

}
//------------------------------------------------------------------------
BreadthFirstPaths::BreadthFirstPaths(CGraph G, int s)
{
	int v = G.getV();

	marked = new bool[v];
	edgeTo = new int[v];
	this->s = s;
	for (int i = 0; i < v; i++)
	{
		marked[i] = false;
		edgeTo[i] = -1;
	}

	bfs(G,  s);
}
//------------------------------------------------------------------------
BreadthFirstPaths::~BreadthFirstPaths()
{
	delete[] marked;
	delete[] edgeTo;
}
//------------------------------------------------------------------------
std::vector<int> BreadthFirstPaths::pathTo(int v)
{
	std::vector <int> path;
	if (!hasPathTo(v))
		return path;

	std::stack<int> st;
	for (int x = v; x != s; x = edgeTo[x]) st.push(x);
	st.push(s);

	int n = st.size();
	for (int i = 0; i < n; i++)
	{
		path.push_back(st.top());
		st.pop();
	}

	return path;
}
//------------------------------------------------------------------------
void BreadthFirstPaths::bfs(CGraph G, int v)
{
	std::queue<int> q;
	q.push(v);
	marked[v] = true;
	while ( !q.empty() )
	{
		int t = q.front();
		q.pop();
		for (int w : G.getAdj(t))  // search in adjacent
		{
			if ( marked[w] ) continue; // being marked before
			
			edgeTo[w] = t;
			marked[w] = true;
			q.push(w);			
		}
	}

	for (int i = 0; i < G.getV(); i++)
		std::cout << edgeTo[i] << " ";
	std::cout << std::endl;

}

//////////////////////////////////////////////////////////////////////////
CC::CC(CGraph G, int s)
{
	int V = G.getV();

	marked	= new bool[V];
	id			= new int[V];
	n			= 0;
	for (int i = 0; i< V; i++ )
	{
		marked[i]	= false;
		id[i]			= -1;
	}

	for (int w = 0; w < V; w++)
	{
		if ( marked[w] ) continue;
		
		dfs(G, w);
		n++;
	}
}
//------------------------------------------------------------------------
void CC::print(CGraph G)
{
	std::cout << "=========================\n";
	std::cout << n << " components:\n";

	std::vector<std::vector<int>> componets(n);
	for (int i = 0; i < G.getV() ; i++)
	{
		int id = getId(i);
		componets[id].push_back(i);
	}

	for (int i = 0; i < n; i++)
	{
		for (int w : componets[i])
			std::cout << w << " ";
		std::cout << "\n";
	}
	std::cout << "=========================\n";
}
//------------------------------------------------------------------------
CC::~CC()
{
	delete[] marked;
	delete[] id;
}
void CC::dfs(CGraph G, int v)
{
	marked[v] = true;
	id[v] = n;

	for (int w : G.getAdj(v))	
		if ( !marked[w] ) 	dfs(G, w);

}