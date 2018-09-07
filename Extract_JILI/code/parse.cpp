#include "parse.h"

using namespace std;

Extract::~Extract() {
	if (m_file)
		m_file.close();
}

bool
Extract::load(string path) {
	m_file.open(path, ios::in);
	if (!m_file) return false;
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

void
Extract::parse() {

}
