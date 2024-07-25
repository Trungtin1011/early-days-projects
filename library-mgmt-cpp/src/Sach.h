#ifndef _SACH_
#define _SACH_
#include "Date.h"
class Date;
class Sach
{
private:
	string TenSach;
	string TacGia;
	string NXB;
	string ISBN;
	int GiaSach;
	int LoaiSach;
	int TinhTrangs;
public:
	friend Date;
	string GetISBN();
	string GetTen();
	string Gettg();
	string GetNXB();
	int GetGia();
	int GetType();
	int GetTT();
	void SetISBN(string is);
	void SetTen(string ten);
	void SetTG(string tg);
	void SetNXB(string nxb);
	void SetGia(int gi);
	void SetType(int ty);
	void SetTT(int tt);
	Sach()
	{
		this->TenSach = " ";
		this->TacGia = " ";
		this->NXB = " ";
		this->ISBN = " ";
		this->GiaSach = 0;
		this->LoaiSach = 0;
	}
	Sach(string is = "", string ten = "", string tg = "", string nx = "", int g = 0, int l = 0)
	{
		this->ISBN = is;
		this->TacGia = tg;
		this->TenSach = ten;
		this->NXB = nx;
		this->GiaSach = g;
		this->LoaiSach = l;
	}
	~Sach(void) {}
	string BookType();
	void XuatSach();
};

#endif _SACH_