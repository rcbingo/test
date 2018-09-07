#include "stdafx.h"
#include "excel.h"
#include <fstream>
#include<algorithm>
using namespace std;

MyExcel::MyExcel(){
	if (!m_app.CreateDispatch("Excel.Application"))
	{
		AfxMessageBox("无法打开Excel应用", MB_OK | MB_ICONWARNING);
		exit(1);
	}
}

MyExcel::~MyExcel() {
	m_app.Quit();
	m_sheet.ReleaseDispatch();
	m_sheets.ReleaseDispatch();
	m_book.ReleaseDispatch();	
	m_books.ReleaseDispatch();
	m_app.ReleaseDispatch();
}

bool
MyExcel::open(CString path) {
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_books.AttachDispatch(m_app.get_Workbooks());
	LPDISPATCH lpDisp = m_books.Open(path, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional, covOptional,
		covOptional, covOptional, covOptional, covOptional, covOptional, covOptional);
	if (lpDisp == NULL) return false;
	m_book.AttachDispatch(lpDisp);
	m_sheets = m_book.get_Sheets();
	return true;
}

void
MyExcel::close() {
	COleVariant covOptional((long)DISP_E_PARAMNOTFOUND, VT_ERROR);
	m_book.Save();
	m_book.Close(covOptional, covOptional, covOptional);
	m_books.Close();
}

int
MyExcel::get_table_id(CString tab_name) {
	int sheet_num = m_sheets.get_Count();
	if (sheet_num != 14) return -1;
	for (short i = 1; i <= sheet_num; i++) {
		m_sheet = m_sheets.get_Item(COleVariant(i));
		if (tab_name == m_sheet.get_Name()) return i;
	}
	return -1;
}

bool
MyExcel::get_range(char range_id, vector<CString>& ds_vec) {
	CString pos;
	int id = 2;
	while (true)
	{
		pos.Format("%c%d", range_id, id);
		m_range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
		VARIANT val = m_range.get_Value(vtMissing);
		CString str_tmp = VariantToCString(val);
		int pos = str_tmp.Find('\.');
		if (pos >= 0 && pos < 10) {
			str_tmp = str_tmp.Left(pos);
		}
		if (str_tmp.IsEmpty()) break;
		ds_vec.push_back(str_tmp);
		id++;
	}
	return true;
}

bool
MyExcel::exist(CString name) {
	m_range = m_sheet.get_Range(COleVariant("B2"), COleVariant("B2"));
	VARIANT val = m_range.get_Value(vtMissing);
	CString str = VariantToCString(val);
	if (str.Find(name) == -1) return false;
	return true;
}

void
MyExcel::get_ds_exp(vector<CString>& ds_vec, vector<CString>& exp_vec) {
	for (int i = 0; i < ds_vec.size(); i++) {
		CString str = "SAVE[" + ds_vec[i] + "].BYTE[0] != 0x7F";
		exp_vec.push_back(str);
	}
}

bool
MyExcel::set_range(char range_id, vector<CString>& vec) {
	CString pos;
	int id = 2;
	for (int i = 0; i < vec.size(); i++) {
		pos.Format("%c%d", range_id, id);
		CRange range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
		range.put_Value2(COleVariant(vec[i]));
		range.ReleaseDispatch();
		id++;
	}
	return true;
}

bool
MyExcel::set_range2(char range_id, vector<CString>& vec, vector<CString>& vec2) {
	CString pos;	
	for (int i = 0; i < vec2.size(); i++) {
		int id = atoi(vec[i]) + 1;
		pos.Format("%c%d", range_id, id);
		CRange range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
		range.put_Value2(COleVariant(vec2[i]));
		range.ReleaseDispatch();
		id++;
	}
	return true;
}

bool
MyExcel::clr_range(char range_id, vector<CString>& vec, int id) {
	CString pos;
	CString value = "";
	for (int i = 0; i < vec.size(); i++) {
		pos.Format("%c%d", range_id, id);
		CRange range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
		range.put_Value2(COleVariant(value));
		range.ReleaseDispatch();
		id++;
	}
	return true;
}


bool
MyExcel::clr_range2(char range_id, vector<CString>& vec) {
	CString pos;
	CString value = "";
	for (int i = 0; i < vec.size(); i++) {
		int id = atoi(vec[i]) + 1;
		pos.Format("%c%d", range_id, id);
		CRange range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
		range.put_Value2(COleVariant(value));
		range.ReleaseDispatch();
		id++;
	}
	return true;
}

void 
MyExcel::get_ds_enter_record_id(vector<CString>& ds_vec, vector<CString>& enter_id_vec, vector<CString>& enter_cmd_vec, vector<CString>& record_id_vec) {
	CString str_tmp;
	for (int i = 0; i < ds_vec.size(); i++) {
		if(str_tmp == ds_vec[i]) continue;
		str_tmp = ds_vec[i];
		enter_cmd_vec.push_back(str_tmp);
		CString str2 = str_tmp + ",0,1";
		record_id_vec.push_back(str2);
	}
	sort(record_id_vec.begin(), record_id_vec.end());
	record_id_vec.erase(unique(record_id_vec.begin(), record_id_vec.end()), record_id_vec.end());
	sort(enter_cmd_vec.begin(), enter_cmd_vec.end());
	enter_cmd_vec.erase(unique(enter_cmd_vec.begin(), enter_cmd_vec.end()), enter_cmd_vec.end());
	int pos = 0;
	if()
	for (int i = pos; i < enter_cmd_vec.size(); i++) {
		CString str;
		str.Format("%d", i + 1);
		enter_id_vec.push_back(str);
	}
}

bool
MyExcel::write_sheet() {
	int tab_id = get_table_id("ReadCds");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	if (!exist()) return false;
	vector<CString> ds_vec, exp_vec, enter_id_vec, enter_cmd_vec, record_id_vec;
	get_range('E', ds_vec);
	get_ds_exp(ds_vec, exp_vec);
	get_ds_enter_record_id(ds_vec, enter_id_vec, enter_cmd_vec, record_id_vec);
	set_range('S', exp_vec); 
	tab_id = get_table_id("EnterSystem");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));

	set_range('A', enter_id_vec);
	set_range('B', enter_cmd_vec);
	tab_id = get_table_id("Command");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	set_range2('F', enter_cmd_vec, record_id_vec);
	return true;
}

bool
MyExcel::rollback_sheet() {
	int tab_id = get_table_id("ReadCds");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	if (!exist()) return false;
	vector<CString> ds_vec;
	get_range('E', ds_vec);
	clr_range('S', ds_vec);
	tab_id = get_table_id("EnterSystem");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	clr_range('A', ds_vec);
	clr_range('B', ds_vec);
	tab_id = get_table_id("Command");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	clr_range2('F', ds_vec);
	return true;
}

bool
MyExcel::set_ECU_INFO_sheet() {
	int tab_id = get_table_id("EcuInfo");
	m_sheet = m_sheets.get_Item(COleVariant((short)tab_id));
	if (!exist("IDM_VER")) return false;
	vector<CString> ds_vec;
	get_range('C', ds_vec);
	clr_range('A', ds_vec, 3);
	clr_range('C', ds_vec);
	clr_range('D', ds_vec);
	clr_range('E', ds_vec);
	clr_range('F', ds_vec);
	clr_range('G', ds_vec);
	clr_range('H', ds_vec);
	clr_range('I', ds_vec);
	clr_range('J', ds_vec);
	clr_range('K', ds_vec);
	CString pos = "L2";
	CString value = "READ_ECU_INFO";//可能需要修改
	CRange range = m_sheet.get_Range(COleVariant(pos), COleVariant(pos));
	range.put_Value2(COleVariant(value));
	range.ReleaseDispatch();
	return true;
}

void
MyExcel::get_excel_path(vector<CString>& path_vec) {
	CString path = "export.txt";
	ifstream file;
	char text[1024];
	file.open(path, ios::in);
	while (!file.eof()) {
		file.getline(text, 1024);
		CString str = text;
		path_vec.push_back(str);
	}
	file.close();
	path_vec.pop_back();
}

void
MyExcel::ds_filt() {
	vector<CString> path_vec;
	get_excel_path(path_vec);
	for (int i = 0; i < path_vec.size(); i++) {
		CString strFilePath = path_vec[i];
		if (strFilePath == "") continue;
		open(strFilePath);
		write_sheet();
		close();
	}
}

void
MyExcel::ds_filt_rollback() {
	vector<CString> path_vec;
	get_excel_path(path_vec);
	for (int i = 0; i < path_vec.size(); i++) {
		CString strFilePath = path_vec[i];
		if (strFilePath == "") continue;
		open(strFilePath);
		rollback_sheet();
		close();
	}
}

void
MyExcel::write_info_id() {
	vector<CString> path_vec;
	get_excel_path(path_vec);
	for (int i = 0; i < path_vec.size(); i++) {
		CString strFilePath = path_vec[i];
		if (strFilePath == "") continue;
		open(strFilePath);
		set_ECU_INFO_sheet();
		close();
	}
}
