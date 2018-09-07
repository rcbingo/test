#pragma once

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

class Extract {
	ifstream m_file;
public:
	~Extract();
	bool load(string path);
	bool get_dict(string path, map<string,string>& dict, string spt = "\t");
	void parse();
};
