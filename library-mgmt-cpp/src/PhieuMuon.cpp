#include "PhieuMuon.h"

int PhieuMuon::GetTongPhieu() { return this->TongPhieu; }
DocGia PhieuMuon::GetDocGia()
{
	return this->DG.getMBD();
}
DocGia PhieuMuon::GetDG_ten() { return this->DG.GetTenDG(); }
Sach PhieuMuon::GetSach() { return this->Book.GetISBN(); }
Date PhieuMuon::GetNgayMuon() { return this->NgayMuon; }
Date PhieuMuon::GetNgayTra() { return this->NgayTra; }
int PhieuMuon::GetMaPhieu() { return this->MaPhieu; }
int PhieuMuon::GetTrangThai() { return this->TrangThai; }
void PhieuMuon::SetTrangThai(int a) { this->TrangThai = a; }
void PhieuMuon::SetSach(Sach s) { this->Book = s; }
void PhieuMuon::SetDocGia(DocGia dg) { this->DG = dg; }
//Các hàm xử lí chuẩn ngày
int PhieuMuon::NgayPlus(int d)
{
	time_t t = time(0);
	struct tm* ta = localtime(&t);
	ta->tm_mon = ta->tm_mon + 1;
	ta->tm_year = ta->tm_year + 1900;
	if (ta->tm_mon == 1 || ta->tm_mon == 3 || ta->tm_mon == 5 || ta->tm_mon == 7 || ta->tm_mon == 8 || ta->tm_mon == 10)
	{
		int nTongNgay = 0;
		nTongNgay = ta->tm_mday + d;
		if (nTongNgay <= 31)
		{
			ta->tm_mday += d;
			return ta->tm_mday;
		}
		else
		{
			ta->tm_mday = nTongNgay - 31;
			ta->tm_mon += 1;
			return ta->tm_mday;
		}
	}
	else if (ta->tm_mon == 4 || ta->tm_mon == 6 || ta->tm_mon == 9 || ta->tm_mon == 11)
	{
		int nTongNgay = 0;
		nTongNgay = ta->tm_mday + d;
		if (nTongNgay <= 30)
		{
			ta->tm_mday += d;
			return ta->tm_mday;
		}
		else
		{
			ta->tm_mday = nTongNgay - 30;
			ta->tm_mon += 1;
			return ta->tm_mday;
		}
	}
	else if (ta->tm_mon == 12)
	{
		int nTongNgay = 0;
		int nTongThang = 0;
		nTongNgay = ta->tm_mday + d;
		if (nTongNgay <= 31)
		{
			ta->tm_mday += d;
			return ta->tm_mday;
		}
		else
		{
			ta->tm_mday = nTongNgay - 31;
			ta->tm_mon = 1;
			ta->tm_year += 1;
			return ta->tm_mday;
		}
	}

	else if (ta->tm_mon == 2)
	{
		if (KTNamNhuan() == true)
		{
			int nTongNgay = 0;
			nTongNgay = ta->tm_mday + d;
			if (nTongNgay <= 29)
			{
				ta->tm_mday += d;
				return ta->tm_mday;
			}
			else
			{
				ta->tm_mday = nTongNgay - 29;
				ta->tm_mon += 1;
				return ta->tm_mday;
			}
		}
		else
		{
			int nTongNgay = 0;
			nTongNgay = ta->tm_mday + d;
			if (nTongNgay <= 28)
			{
				ta->tm_mday += d;
				return ta->tm_mday;
			}
			else
			{
				ta->tm_mday = nTongNgay - 28;
				ta->tm_mon += 1;
				return ta->tm_mday;
			}
		}
	}
	return 0;
}

int PhieuMuon::ThangPlus(int m)
{
	time_t t = time(0);
	struct tm* ta = localtime(&t);
	ta->tm_mon = ta->tm_mon + 1;
	ta->tm_year = ta->tm_year + 1900;
	if (ta->tm_mon == 1 || ta->tm_mon == 3 || ta->tm_mon == 5 || ta->tm_mon == 7 || ta->tm_mon == 8 || ta->tm_mon == 10)
	{
		int nTongNgay = 0;
		nTongNgay = ta->tm_mday + m;
		if (nTongNgay <= 31)
		{
			ta->tm_mday += m;
			return ta->tm_mon;
		}
		else
		{
			ta->tm_mday = nTongNgay - 31;
			ta->tm_mon += 1;
			return ta->tm_mon;
		}
	}
	else if (ta->tm_mon == 4 || ta->tm_mon == 6 || ta->tm_mon == 9 || ta->tm_mon == 11)
	{
		int nTongNgay = 0;
		nTongNgay = ta->tm_mday + m;
		if (nTongNgay <= 30)
		{
			ta->tm_mday += m;
			return ta->tm_mon;
		}
		else
		{
			ta->tm_mday = nTongNgay - 30;
			ta->tm_mon += 1;
			return ta->tm_mon;
		}
	}
	else if (ta->tm_mon == 12)
	{
		int nTongNgay = 0;
		int nTongThang = 0;
		nTongNgay = ta->tm_mday + m;
		if (nTongNgay <= 31)
		{
			ta->tm_mday += m;
			return ta->tm_mon;
		}
		else
		{
			ta->tm_mday = nTongNgay - 31;
			ta->tm_mon = 1;
			ta->tm_year += 1;
			return ta->tm_mon;
		}
	}
	if (ta->tm_mon == 2)
	{
		if (KTNamNhuan() == true)
		{
			int nTongNgay = 0;
			nTongNgay = ta->tm_mday + m;
			if (nTongNgay <= 29)
			{
				ta->tm_mday += m;
				return ta->tm_mon;
			}
			else
			{
				ta->tm_mday = nTongNgay - 29;
				ta->tm_mon += 1;
				return ta->tm_mon;
			}
		}
		else
		{
			int nTongNgay = 0;
			nTongNgay = ta->tm_mday + m;
			if (nTongNgay <= 28)
			{
				ta->tm_mday += m;
				return ta->tm_mon;
			}
			else
			{
				ta->tm_mday = nTongNgay - 28;
				ta->tm_mon += 1;
				return ta->tm_mon;
			}
		}
	}
	return 0;
}
int PhieuMuon::NamPlus(int y)
{
	time_t t = time(0);
	struct tm* ta = localtime(&t);
	ta->tm_mon = ta->tm_mon + 1;
	ta->tm_year = ta->tm_year + 1900;
	if (ta->tm_mon == 12)
	{
		int nTongNgay = 0;
		nTongNgay = ta->tm_mday + y;
		if (nTongNgay > 31)
		{
			ta->tm_mday = nTongNgay - 31;
			ta->tm_mon = 1;
			ta->tm_year += 1;
			return ta->tm_year;
		}
	}
	return ta->tm_year;
}
bool PhieuMuon::KTNamNhuan()
{
	time_t t = time(0);
	struct tm* ta = localtime(&t);
	ta->tm_year = ta->tm_year + 1900;
	if (ta->tm_year % 400 == 0 || ta->tm_year % 4 == 0 && ta->tm_year % 100 != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
PhieuMuon::~PhieuMuon(void) {}
void PhieuMuon::xuatPhieu()
{
	cout << "\n***********************************************\n";
	cout << "<So phieu muon>:    " << this->MaPhieu << endl;
	cout << "<Ma sach>:          " << this->Book.GetISBN() << endl;
	cout << "<Ma doc gia>:       " << this->DG.getMBD() << endl;
	cout << "<Ngay muon>:        "; this->NgayMuon.xuat(); cout << endl;
	cout << "<Ngay tra>:         "; this->NgayTra.xuat(); cout << endl;
	cout << "<Tinh trang>:       " << this->TrangThai << endl;
}
void PhieuMuon::XuatDGQuaHan()
{
	cout << "************************************\n";
	cout << "Ho va Ten: " << DG.HoTen << endl;
	cout << "Ma doc gia: " << DG.MaDG << endl;
	cout << "Ngay dang ky the: "; this->DG.Ngay.xuat(); cout << endl;
	cout << "So dien thoai lien he: " << this->DG.SDT << endl;
	cout << "************************************\n";
}