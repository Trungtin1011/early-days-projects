#pragma once
#include "Date.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <sstream>
#include <iomanip>

class Date;
class PhieuMuon;
class DocGia
{
protected:
	string MaDG;
	string HoTen;
	int SDT;
	Date Ngay;
	int tinhtrang;
public:
	friend Date;
	friend PhieuMuon;
	void xuatDG();
	string getMBD();
	string GetTenDG();
	int GetSDT();
	int GetNgayDK();
	int GetThangDK();
	int GetNamDK();
	int GetTT();
	void SetMBD(string ma);
	void SetTenDG(string ten);
	void SetSDT(int sd);
	void SetNgayDK(int ndk);
	void SetThangDK(int tdk);
	void SetNamDK(int ydk);
	void SetTT(int tt);
	DocGia(string sMaBD = "", string sHoTen = "", int nNgay = 0, int nThang = 0, int nNam = 0, int sdt = 113) :Ngay(nNgay, nThang, nNam)
	{
		this->MaDG = sMaBD;
		this->HoTen = sHoTen;
		this->SDT = sdt;
	}
	~DocGia(void);
};


