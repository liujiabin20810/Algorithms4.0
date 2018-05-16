// SearchProj.cpp : 定义控制台应用程序的入口点。
//

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "SymbolTable.h"
#include "SymbolTable.cpp"

using namespace std;

void splitStr(std::string& s, std::vector<std::string>& v, const char& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;

	while(std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2-pos1));

		pos1 = pos2 + 1;
		pos2 = s.find(c, pos1);
		//std::cout << "p1: " << pos1 << " p2: " << pos2 << std::endl;
	}
	// under linux, the string maybe contains "\r"
	int pos3 = s.find("\r");  
	if (std::string::npos != pos3)
		s.erase(pos3);

	if(pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void readTxt(string file, int minlen)
{
	ifstream infile; 
	infile.open(file);   //将文件流对象与文件连接起来 
	
	if(!infile.is_open())
	{
		std::cout<<"Open file err. \n";
		return;
	}

	string s;

//	BinarySearchST<string,int> st(20000);
	BinarySearchST<string,int> *st = new BinarySearchST<string,int>();
	int nline = 0;

	while(getline(infile,s))
	{
		nline++;
		vector<string> vstr;
		splitStr(s,vstr,' ');
//  		for(int i = 0; i < vstr.size(); i++ )
//  			cout << vstr[i] << " ";
//  		cout<<endl;

		for(int i = 0; i < vstr.size(); i++ )
		{
			if(vstr[i].length() < minlen)
				continue;
			int val = st->get(vstr[i]);
			if(val < 0 ) val = 0;

			st->put(vstr[i],val+1);
		}

	}

//	st->print();

 	cout <<"Size: "<< st->size() << endl;
	cout <<"get: "<< st->get("business") <<endl;
	st->del("business");
	cout <<"del: "<< st->contains("business") << endl;
	cout<<"Size: "<< st->size() << endl;


	delete st;
	infile.close();             //close
}

//////////////////////////////////////////////////////////////////////////
// goolge utest

int main()
{
	int minlen = 0;
	string file;

	cout<< "input minLen & file: \n";
	cin >> minlen >> file;
	readTxt(file,minlen);


	return 0;
}

