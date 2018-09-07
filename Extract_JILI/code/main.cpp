#include <iostream>
#include "parse.h"
#include<windows.h>
using namespace std;

int main() {
	string file_path = "JILIZY_FUNCFG.txt";
	Extract ex;
	map<string, string> m1;
	long begin = GetTickCount();
	ex.get_dict(file_path, m1);
	long finish = GetTickCount();
	long time = finish - begin;

	return 0;

}
