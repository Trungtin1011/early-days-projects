#include "Sach.h"

string Sach::GetISBN() { return this->ISBN; }
string Sach::GetTen() { return this->TenSach; }
string Sach::Gettg() { return this->TacGia; }
string Sach::GetNXB() { return this->NXB; }
int Sach::GetGia() { return this->GiaSach; }
int Sach::GetType() { return this->LoaiSach; }
int Sach::GetTT() { return this->TinhTrangs; }
void Sach::SetISBN(string is) { this->ISBN = is; }
void Sach::SetTen(string ten) { this->TenSach = ten; }
void Sach::SetTG(string tg) { this->TacGia = tg; }
void Sach::SetNXB(string nxb) { this->NXB = nxb; }
void Sach::SetGia(int gi) { this->GiaSach = gi; }
void Sach::SetType(int ty) { this->LoaiSach = ty; }
void Sach::SetTT(int tt) { this->TinhTrangs = tt; }
string Sach::BookType()
{
	switch (LoaiSach)
	{
	case 1: return "Sach Tieng Viet"; break;
	case 2: return "Sach Ngoai Van"; break;
	default: break;
	}
}

void Sach::XuatSach()
{
	cout << "\n*********************************************\n";
	cout << "Ten sach: " << this->TenSach << endl;
	cout << "Ma sach: " << this->ISBN << endl;
	cout << "Tac gia: " << this->TacGia << endl;
	cout << "Nha Xuat Ban: " << this->NXB << endl;
	cout << "Gia sach: " << this->GiaSach << endl;
	cout << "The loai sach: " << this->BookType();
}