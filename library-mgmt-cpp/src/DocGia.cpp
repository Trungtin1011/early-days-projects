#include "DocGia.h"

void DocGia::xuatDG()
{
	cout << "************************************\n";
	cout << "Ho va Ten: " << this->HoTen << endl;
	cout << "Ma doc gia: " << this->MaDG << endl;
	cout << "Ngay dang ky the: "; Ngay.xuat(); cout << endl;
	cout << "So dien thoai lien he: " << this->SDT << endl;
	cout << "************************************\n";
}
string DocGia::getMBD()
{
	return this->MaDG;
}
string DocGia::GetTenDG() { return this->HoTen; }
int DocGia::GetSDT() { return this->SDT; }
int DocGia::GetNgayDK() { return this->Ngay.getNgay(); }
int DocGia::GetThangDK() { return this->Ngay.getThang(); }
int DocGia::GetNamDK() { return this->Ngay.getNam(); }
int DocGia::GetTT() { return this->tinhtrang; }
void DocGia::SetMBD(string ma) { this->MaDG = ma; }
void DocGia::SetTenDG(string ten) { this->HoTen = ten; }
void DocGia::SetSDT(int sd) { this->SDT = sd; }
void DocGia::SetNgayDK(int ndk) { this->Ngay.setNgay(ndk); }
void DocGia::SetThangDK(int tdk) { this->Ngay.setThang(tdk); }
void DocGia::SetNamDK(int ydk) { this->Ngay.setNam(ydk); }
void DocGia::SetTT(int tt) { this->tinhtrang = tt; }
DocGia::~DocGia(void) {}