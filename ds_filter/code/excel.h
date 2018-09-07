#pragma once

#include "comm.h"

class MyExcel : public CDialogEx {
	CApplication m_app;
	CWorkbooks m_books;
	CWorkbook m_book;
	CWorksheet m_sheet;
	CWorksheets m_sheets;
	CRange m_range;
public:
	MyExcel();
	~MyExcel();
	bool open(CString path = NULL);
	void close();
	int get_table_id(CString tab_name);
	void get_ds_exp(vector<CString>& ds_vec, vector<CString>& exp_vec);
	void get_ds_enter_record_id(vector<CString>& ds_vec, vector<CString>& enter_id_vec, vector<CString>& enter_cmd_vec, vector<CString>& record_id_vec);
	bool get_range(char range_id, vector<CString>& ds_vec);
	bool set_range(char range_id, vector<CString>& vec);
	bool set_range2(char range_id, vector<CString>& vec, vector<CString>& vec2);
	bool set_ECU_INFO_sheet();
	bool clr_range(char range_id, vector<CString>& vec, int id = 2);
	bool clr_range2(char range_id, vector<CString>& vec);
	bool exist(CString name = "IDM_CDS");
	bool write_sheet();
	bool rollback_sheet();
	void get_excel_path(vector<CString>& path_vec);
	void ds_filt();
	void ds_filt_rollback();
	void write_info_id();
};
