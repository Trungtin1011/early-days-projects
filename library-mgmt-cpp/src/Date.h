#pragma once
#include <iostream>
#include <string>

using namespace std;
class DocGia;
class Sach;
class PhieuMuon;
class Date
{
	int Ngay;
	int Thang;
	int Nam;
public:
	friend DocGia;
	friend Sach;
	friend PhieuMuon;
	Date(int d = 0, int m = 0, int y = 0)
	{
		this->Ngay = d;
		this->Thang = m;
		this->Nam = y;
	}
	int getNgay();
	int getThang();
	int getNam();
	void setNgay(int d);
	void setThang(int m);
	void setNam(int y);
	void xuat();
	~Date(void);
};