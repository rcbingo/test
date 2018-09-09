#include <iostream>
#include "parse.h"
#include<windows.h>
using namespace std;

int main() {
	string import_file = "../../import/JILIZY_FUNCFG.txt";
	string export_file = "../../export/ds.txt";
	string export_file2 = "../../export/cmd.txt";
	Extract ex(import_file, export_file, export_file2);
	long begin = GetTickCount();
	ex.parse();
	long finish = GetTickCount();
	long time = finish - begin;

	return 0;

}
