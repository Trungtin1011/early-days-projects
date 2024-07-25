#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <time.h>
#include "DocGia.h"
#include "Date.h"
#include "Sach.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <sstream>
#include <iomanip>
class DocGia;
class Date;
class Sach;

class PhieuMuon
{
	DocGia DG;
	Sach Book;
	Date NgayMuon, NgayTra;
	int TongPhieu;
	int MaPhieu;
	int TrangThai;
public:
	friend Date;
	friend DocGia;
	friend Sach;
	int GetTongPhieu();
	DocGia GetDocGia();
	DocGia GetDG_ten();
	Sach GetSach();
	Date GetNgayMuon();
	Date GetNgayTra();
	int GetMaPhieu();
	int GetTrangThai();
	void SetTrangThai(int a);
	void SetSach(Sach s);
	void SetDocGia(DocGia dg);
	//Các hàm xử lí chuẩn ngày
	int NgayPlus(int d);
	int ThangPlus(int m);
	int NamPlus(int y);
	bool KTNamNhuan();
	PhieuMuon(int ma = 0, string MaDG = "", string is = "", int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0, int TrangThai = 0) : DG(MaDG), Book(is), NgayMuon(a, b, c), NgayTra(d, e, f)
	{

		this->TongPhieu++;
		this->MaPhieu = TongPhieu;
		this->TrangThai = TrangThai;
	}
	PhieuMuon(string ma = "", string is = "") : DG(ma), Book(is)
	{
		time_t t = time(0);
		struct tm* Now = localtime(&t);
		NgayMuon.setNgay(Now->tm_mday);
		NgayMuon.setThang(Now->tm_mon + 1);
		NgayMuon.setNam(Now->tm_year + 1900);

		NgayTra.setNgay(NgayPlus(7));
		NgayTra.setThang(ThangPlus(7));
		NgayTra.setNam(NamPlus(7));

		this->TongPhieu++;
		this->MaPhieu = TongPhieu;
		this->TrangThai = 1;
	}
	~PhieuMuon(void);
	void xuatPhieu();
	void XuatDGQuaHan();


};

