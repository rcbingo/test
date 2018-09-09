#pragma once

#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct Line {
	string id;
	string cmd;
	string pos;
	string exp;
	string name;
	string unit;
	string format;
};

class Extract {
	ifstream m_import;
	ofstream m_export;
	ofstream m_export2;
	string m_import_file;
	string m_export_file;
	string m_export_file2;
	map<string, string> exp_map, cmd_map, name_map, text_map;
public:
	Extract(string import_file, string export_file, string export_file2);
	~Extract();
	bool init();
	bool get_dict(string path, map<string,string>& dict, string spt = "\t");
	string spe_string_replace(string& str, int _num, Line& _line);
	string spe_string_replace2(string& str, int _num, Line& _line);
	string spe_xbit_replace(string& str, int _num, Line& _line);
	string spe_x1bit_replace(string& str, int _num, Line& _line);
	void spe_sprintf_handle(string& str, Line& _line);
	void get_HEX_ASCII_pos(string& str, Line& _line);
	void parse_exp(string str, Line& _line);
	bool parse_line(string str, Line& _line, string spt = " ");
	void parse();
	void write_line(Line& _line);
	void write_line2(Line& _line);
	void write_module_id(string id);
};
