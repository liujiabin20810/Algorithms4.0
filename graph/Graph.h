/************************************************************************/
/* Copyright 2018 Lewis                                                            */
/* License GPL 3.0																		*/
/* Author:  Lewis                                                                      */
/* Description: Algorithms 4 - Graph										   */
/************************************************************************/
#pragma once
#include <vector>
#include <stack>

#include <fstream>

// simple graph, undirected,  no self loops, using adjacency table
class CGraph
{
public:
	CGraph();
	CGraph( std::ifstream& fin );

	~CGraph(void) { }

	void addEdge(int v, int w);
	std::vector<int> getAdj(int v);

	int getV() { return V; }
	int getE() { return E; }

	void print();
private:
	int V;  // vertex
	int E;  // edge
	std::vector<std::vector<int>> adj;
};
// depth first fearch
class DepthFirstPaths
{
	bool *marked;
	int* edgeTo;
	int s;  

public:
	

	DepthFirstPaths(CGraph G, int s);
	~DepthFirstPaths();

	bool hasPathTo(int v);
	std::vector<int> pathTo( int v);

private:
	void dfs(CGraph G, int v);


};
// breadth first search
class BreadthFirstPaths
{
	bool* marked;
	int* edgeTo;
	int s;

public:
	BreadthFirstPaths( CGraph G, int s);
	~BreadthFirstPaths();

	bool hasPathTo(int v) {  return marked[v];  }
	std::vector<int> pathTo(int v);

private:
	void bfs(CGraph G, int v);
};
//connected component
class CC
{
public:
	CC(CGraph G, int s);
	~CC();

	bool connected(int v, int w) { return id[v] == id[w]; }		// is connected?
	int count() { return n;  }								// count of connected component
	int getId(int v) { return id[v];  }							// the index of connected component 

	void print(CGraph G);
private:
	void dfs(CGraph G, int v);

	bool*	marked;
	int *		id;
	int			n;
};

