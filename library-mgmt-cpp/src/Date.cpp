#include "Date.h"

int Date::getNgay() { return Ngay; }
int Date::getThang() { return Thang; }
int Date::getNam() { return Nam; }
void Date::setNgay(int d)
{
	this->Ngay = d;
}
void Date::setThang(int m)
{
	this->Thang = m;
}
void Date::setNam(int y)
{
	this->Nam = y;
}
void Date::xuat()
{
	cout << this->Ngay << "/" << this->Thang << "/" << this->Nam;
}
Date::~Date(void) {}