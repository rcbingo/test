#pragma once
#include <iostream>
using namespace std;

int htoi(const char* s);
int count(string str, string s);
string replace(string& str, string s, string s_new);
string replace_once(string& str, string s, string s_new);
void handle_key(string& str);