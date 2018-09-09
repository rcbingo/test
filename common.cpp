#include "common.h"

int tolower(int c){
	if (c >= 'A' && c <= 'Z')
		return c + 'a' - 'A';
	else
		return c;
}

int htoi(const char* s){
	int i;
	int n = 0;
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		i = 2;
	else
		i = 0;
	for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z');++i)
	{
		if (tolower(s[i]) > '9')
			n = 16 * n + (10 + tolower(s[i]) - 'a');
		else
			n = 16 * n + (tolower(s[i]) - '0');
	}
	return n;
}

int count(string str, string s) {
	int _count = 0;
	while (true) {
		int pos = str.find(s);
		if (pos == -1) break;
		str = str.substr(pos + 1, str.size());
		_count++;
	}
	return _count;
}

string replace(string& str, string s, string s_new) {
	while (true) {
		int pos = str.find(s);
		if (pos == -1) break;
		str = str.replace(str.begin() + pos, str.begin() + pos + s.size(), s_new);
	}
	return str;
}

string replace_once(string& str, string s, string s_new) {
	int pos = str.find(s);
	if (pos != -1)
		str = str.replace(str.begin() + pos, str.begin() + pos + s.size(), s_new);
	return str;
}

void handle_key(string& str) {
	if (str.find("a") != -1) {
		replace(str, "a", "A");
	}
	if (str.find("b") != -1) {
		replace(str, "b", "B");
	}
	if (str.find("c") != -1) {
		replace(str, "c", "C");
	}
	if (str.find("d") != -1) {
		replace(str, "d", "D");
	}
	if (str.find("e") != -1) {
		replace(str, "e", "E");
	}
	if (str.find("f") != -1) {
		replace(str, "f", "F");
	}
	if (str.find("X") != -1) {
		replace(str, "X", "x");
	}
}