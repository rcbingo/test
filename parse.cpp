#include "parse.h"
#include "common.h"
using namespace std;

Extract::Extract(string import_file, string export_file, string export_file2) :m_import_file(import_file), m_export_file(export_file),
	m_export_file2(export_file2) {}

Extract::~Extract() {
	if (m_import)
		m_import.close();
	if (m_export)
		m_export.close();
	if (m_export2)
		m_export2.close();
}

bool
Extract::init() {
	m_import.open(m_import_file, ios::in);
	if (!m_import) return false;
	m_export.open(m_export_file, ios::out);
	m_export2.open(m_export_file2, ios::out);
	return true;
}

bool
Extract::get_dict(string path, map<string, string>& dict, string spt) {
	ifstream file;
	file.open(path, ios::in);
	if (!file) return false;
	char text[2048];
	while (!file.eof()) {
		memset(text, 0, 2048);
		file.getline(text, 2048);
		if (strlen(text)) {
			string str = text;
			int begin_pos = str.find(spt);
			int end_pos = str.size();
			string key = str.substr(0, begin_pos);
			string value = str.substr(begin_pos + 1, end_pos);
			dict.insert(pair<string, string>(key, value));
		}
	}
	file.close();
	return true;
}

string
Extract::spe_string_replace(string& str, int _num, Line& _line) {
	string spe_str = "y=string";
	_line.format = "";
	for (int i = 0;i < _num;i++) {
		if (i) _line.format += "|";
		int pos = str.find(spe_str);
		string ss = str.substr(pos + 9, 19);
		handle_key(ss);
		if (text_map.count(ss))
			_line.format += text_map[ss];
		else
			_line.format += "-*-";
		char s[3];
		sprintf_s(s, "%d", i);
		string s_tmp = s;
		str = str.replace(str.begin() + pos, str.begin() + pos + 29, s_tmp);
	}
	replace(_line.format, "\"", "");
	return str;
}

string
Extract::spe_string_replace2(string& str, int _num, Line& _line) {
	string spe_str = "y=string";
	string spe_str2 = ":string";
	_line.format = "";
	for (int i = 0;i < _num;i++) {
		if (i) _line.format += "|";
		int pos = str.find(spe_str2);
		string ss = str.substr(pos + 8, 19);
		if (pos == -1) {
			pos = str.find(spe_str);
			ss = str.substr(pos + 9, 19);
		}
		handle_key(ss);
		if (text_map.count(ss))
			_line.format += text_map[ss];
		else
			_line.format += "-*-";
		char s[3];
		sprintf_s(s, "%d", i);
		string s_tmp = s;
		str = str.replace(str.begin() + pos, str.begin() + pos + 29, s_tmp);
	}
	replace(_line.format, "\"", "");
	return str;
}

string
Extract::spe_xbit_replace(string& str, int _num, Line& _line) {
	if (_num == 1) {
		int pos = str.find("x.bit");
		if (str.find("x.bit0") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x01");
		else if (str.find("x.bit1") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x02");
		else if (str.find("x.bit2") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x04");
		else if (str.find("x.bit3") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x08");
		else if (str.find("x.bit4") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x10");
		else if (str.find("x.bit5") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x20");
		else if (str.find("x.bit6") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x40");
		else if (str.find("x.bit7") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x80");
		
	}
	else {
		for (int i = 0;i < _num;i++) {
			int pos = str.find("x.bit");
			if (str.find("x.bit0") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x01)");
			else if (str.find("x.bit1") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x02)");
			else if (str.find("x.bit2") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x04)");
			else if (str.find("x.bit3") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x08)");
			else if (str.find("x.bit4") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x10)");
			else if (str.find("x.bit5") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x20)");
			else if (str.find("x.bit6") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x40)");
			else if (str.find("x.bit7") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x80)");
		}
	}
	return str;
}

string
Extract::spe_x1bit_replace(string& str, int _num, Line& _line) {
	if (_num == 1) {
		int pos = str.find("x1.bit");
		if (str.find("x1.bit0") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x01");
		else if (str.find("x1.bit1") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x02");
		else if (str.find("x1.bit2") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x04");
		else if (str.find("x1.bit3") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x08");
		else if (str.find("x1.bit4") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x10");
		else if (str.find("x1.bit5") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x20");
		else if (str.find("x1.bit6") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x40");
		else if (str.find("x1.bit7") != -1)
			str = str.replace(str.begin() + pos, str.begin() + pos + 6, "x&0x80");

	}
	else {
		for (int i = 0;i < _num;i++) {
			int pos = str.find("x1.bit");
			if (str.find("x1.bit0") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x01)");
			else if (str.find("x1.bit1") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x02)");
			else if (str.find("x1.bit2") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x04)");
			else if (str.find("x1.bit3") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x08)");
			else if (str.find("x1.bit4") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x10)");
			else if (str.find("x1.bit5") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x20)");
			else if (str.find("x1.bit6") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x40)");
			else if (str.find("x1.bit7") != -1)
				str = str.replace(str.begin() + pos, str.begin() + pos + 6, "(x&0x80)");
		}
	}
	return str;
}

string get_sprintf_exp(string& str) {
	int begin_pos = str.find("SPRINTF");
	int end_pos = str.find(";");
	string s = str.substr(begin_pos, end_pos - begin_pos);
	str = str.replace(str.begin() + begin_pos, str.begin() + end_pos, "");
	return s;
}

void
Extract::spe_sprintf_handle(string& str, Line& _line) {
	string s = get_sprintf_exp(str);
	int begin_pos = s.find("[");
	int end_pos = s.find("]");
	int flag = 0;
	string format = s.substr(begin_pos + 1, end_pos - begin_pos - 1);
	if (format.find("%s") != -1) flag = 1;
	if (flag) {
		while (true) {
			int pos = s.find("string");
			if (pos == -1) break;
			string str_tmp = s.substr(pos + 7, 19);
			handle_key(str_tmp);
			if (text_map.count(str_tmp))
				format = replace_once(format, "%s", text_map[str_tmp]);
			else
				format = replace_once(format, "%s", "-*-");
			s = s.replace(s.begin() + pos, s.begin() + pos + 28, "");
		}
		_line.format = replace(format, "\"", "");
	}
	else {
		_line.format = format;
		_line.exp = "";
		int num = count(s, "X") + count(s, "x");
		int pos = atoi(_line.pos.c_str());
		_line.pos = "";
		for (int i = pos;i < pos + num;i++) {
			if (i > pos) _line.pos += ",";
			char pos_tmp[5];
			sprintf_s(pos_tmp, "%d", i);
			string pos_s = pos_tmp;
			_line.pos += pos_s;
		}
	}
	str = "";
}

void
Extract::get_HEX_ASCII_pos(string& str, Line& _line) {
	int pos = atoi(_line.pos.c_str());
	int num = count(str, "x");
	if (num > 4)
		_line.format += "@SPC";
	_line.pos = "";
	for (int i = pos;i < pos + num;i++) {
		if (i > pos) _line.pos += ",";
		char pos_tmp[5];
		sprintf_s(pos_tmp, "%d", i);
		string pos_s = pos_tmp;
		_line.pos += pos_s;
	}
	_line.exp = "";
}

void
Extract::parse_exp(string str, Line& _line) {
	str = str.substr(1, str.size() - 2);
	_line.exp = str;
	_line.format = "%d";
	if (str.find("x2") != -1 && str.find("==0x2") == -1) {
		int pos = atoi(_line.pos.c_str());
		char pos_tmp[5];
		sprintf_s(pos_tmp, ",%d", pos + 1);
		string pos_s = pos_tmp;
		_line.pos += pos_s;
		if (str.find("x4") != -1) {
			char pos_tmp2[10];
			sprintf_s(pos_tmp2, ",%d,%d", pos + 2, pos + 3);
			string pos_s2 = pos_tmp2;
			_line.pos += pos_s2;
		}
	}
	if (str.find("0.") != -1)
		_line.format = "%.2f";
	else if (str.find("HEX") != -1) {
		_line.format = "%02X";
		get_HEX_ASCII_pos(str, _line);
	}
	else if (str.find("ASCII") != -1) {
		_line.format = "%c";
		get_HEX_ASCII_pos(str, _line);
	}
	if (str.find("switch") != -1) {
		int num = count(str, "string");
		if (num) 
			_line.exp = spe_string_replace2(str, num, _line);
	}
	else if (str.find("SPRINTF") != -1) {
		spe_sprintf_handle(str, _line);
	}
	else if (str.find("y=string") != -1) {
		int num = count(str, "y=string");
		_line.exp = spe_string_replace(str, num, _line);
	}
	if (str.find("x.bit") != -1) {
		int num = count(str, "x.bit");
		_line.exp = spe_xbit_replace(str, num, _line);
	}
	if (str.find("x1.bit") != -1) {
		int num = count(str, "x1.bit");
		_line.exp = spe_x1bit_replace(str, num, _line);
	}
	if (str.find("y=x") != -1)
		_line.exp = replace(str, "y=x", "x");
	if (str.find("y=") != -1)
		_line.exp = replace(str, "y=", "");
	if (str.find("Y=") != -1)
		_line.exp = replace(str, "Y=", "");
}

bool
Extract::parse_line(string str, Line& _line, string spt) {
	if (!str.size()) return false;
	static string id = "";
	int begin_pos = str.find(spt);
	_line.id = str.substr(0, begin_pos);
	if (_line.id != id) {
		id = _line.id;
		write_module_id(id);
	}
	str = str.substr(begin_pos + 1, str.size());
	begin_pos = str.find(spt);
	string cmd_str = str.substr(0, begin_pos);
	str = str.substr(begin_pos + 1, str.size());
	begin_pos = str.find(spt);
	int pos = htoi(str.substr(0, begin_pos).c_str());
	if (pos <= 4 || pos >= 255) return false;
	if (cmd_map.find(cmd_str) == cmd_map.end()) return false;
	_line.cmd = cmd_map[cmd_str].substr(40, 39);
	char pos_tmp[4];
	sprintf_s(pos_tmp, "%d", pos - 4);
	_line.pos = pos_tmp;
	str = str.substr(begin_pos + 1, str.size());
	begin_pos = str.find(spt);
	string exp_tmp = str.substr(0, begin_pos);
	if (exp_map.find(exp_tmp) == exp_map.end()) return false;
	parse_exp(exp_map[exp_tmp], _line);
	string str_tmp = str.substr(begin_pos + 1, str.size());
	if (name_map.find(str_tmp) == name_map.end()) return false;
	str = name_map[str_tmp];
	begin_pos = str.find("\t");
	_line.name = str.substr(1, begin_pos - 2);
	str = str.substr(begin_pos + 1, str.size());
	_line.unit = str.substr(1, str.size() - 2);
	return true;
}

void
Extract::write_module_id(string id) {
	m_export.write("\nmodule = ", 10);
	m_export.write(id.c_str(), id.size());
	m_export.write("\n\n", 2);
	m_export2.write("\nmodule = ", 10);
	m_export2.write(id.c_str(), id.size());
	m_export2.write("\n\n", 2);
}

void
Extract::write_line(Line& _line) {
	m_export.write(_line.name.c_str(), _line.name.size());
	m_export.write("\t", 1);
	m_export.write(_line.unit.c_str(), _line.unit.size());
	m_export.write("\t", 1);
	m_export.write(_line.format.c_str(), _line.format.size());
	m_export.write("\t", 1);
	m_export.write(_line.pos.c_str(), _line.pos.size());
	m_export.write("\t", 1);
	m_export.write(_line.exp.c_str(), _line.exp.size());
	m_export.write("\n", 1);
}

void
Extract::write_line2(Line& _line) {
	static string cmd_str = "";
	if (_line.cmd != cmd_str) {
		m_export2.write(_line.cmd.c_str(), _line.cmd.size());
		m_export2.write("\n", 1);
		cmd_str = _line.cmd;
	}
}

void
Extract::parse() {
	if (!init()) return;
	string file_path = "../../import/EXPRESS.txt";
	get_dict(file_path, exp_map);
	string file_path2 = "../../import/COMMAND_hex.txt";
	get_dict(file_path2, cmd_map);
	string file_path3 = "../../import/DSTREAM_CN.txt";
	get_dict(file_path3, name_map);
	string file_path4 = "../../import/TEXT_CN.txt";
	get_dict(file_path4, text_map);
	char text[1024];
	m_import.getline(text, 1024);//过滤第一行文字
	string s_tmp = "";
	while (!m_import.eof()) {
		memset(text, 0, 1024);
		m_import.getline(text, 1024);
		string s = text;
		if (s == s_tmp) continue;
		s_tmp = s;
		Line l;
		if (!parse_line(s, l)) continue;
		write_line(l);
		write_line2(l);
	}
}
