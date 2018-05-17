/************************************************************************/
/* Copyright 2018 Lewis                                                            */
/* License GPL 3.0																		*/
/* Author:  Lewis                                                                      */
/* Description: Algorithms 4 - Graph										   */
/************************************************************************/
#include "Graph.h"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main()
{
	string filename;
	cout << "input filename: ";
	cin >> filename;

	ifstream fin;
	fin.open(filename.c_str());

	if (!fin.is_open())
		return 0;

	CGraph* G = new CGraph(fin);
	int v = G->getV();
	G->print();

//	DepthFirstPaths* search = new DepthFirstPaths(*G, 0);
	BreadthFirstPaths* search = new BreadthFirstPaths(*G, 0);
	// test path
	std::cout << "Path: \n";
	for (int j = 0; j < v; j++)
	{
		if ( !search->hasPathTo(j) ) continue;

		std::vector<int> p = search->pathTo(j);
		cout << "0 - " << j << ": ";
		for (int i = 0; i < p.size(); i++)
		{
			if( p[i] == 0 ) cout << p[i] ;
			else				 cout << "-" << p[i];
		}
		cout <<  endl;
	}
	// test connected component

	CC * ccon = new CC( *G, 0);
	int m = ccon->count();

	ccon->print(*G);

	delete search;
	delete ccon;
	delete G;

	return 0;
}

