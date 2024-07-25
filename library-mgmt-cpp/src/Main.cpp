#define _CRT_SECURE_NO_WARNINGS

#include "DocGia.h"
#include "PhieuMuon.h"
#include "Sach.h"
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <list>
#include <sstream>
#include <iomanip>

//====================================THAO TAC PHU====================================
void textColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

int Dem_Tong_So_Sach_Hien_Co(list <Sach> L3)
{
	int Dem = 0;
	list <Sach>::iterator p = L3.begin();
	while (p != L3.end())
	{
		Dem++;
		p++;
	}
	return Dem;
}

void OutDataSach_File(list <Sach> L3)
{
	ofstream File;
	File.open("Sach.txt");
	int Dem = 1;
	int TongSoSach = Dem_Tong_So_Sach_Hien_Co(L3);
	list <Sach>::iterator p = L3.begin();
	while (p != L3.end())
	{
		File << p->GetISBN() << "," << p->GetTen() << "," << p->Gettg() << "," << p->GetNXB() << "," << p->GetGia() << "," << p->GetType();
		if (Dem < TongSoSach)
		{
			File << endl;
			Dem++;
		}
		p++;
	}
	File.close();
}

void OutDataSach_ToScreen(list <Sach> L3)
{
	list <Sach>::iterator p = L3.begin();
	while (p != L3.end())
	{
		p->XuatSach();
		p++;
	}
}

void InputData_Sach(list <Sach>& L3)
{
	string isbn = "";
	string ten = "";
	string tacgia = "";
	string nxb = "";
	int gia = 0;
	int loai = 0;
	ifstream File;
	File.open("Sach.txt");
	while (!File.eof())
	{
		getline(File, isbn, ',');
		getline(File, ten, ',');
		getline(File, tacgia, ',');
		getline(File, nxb, ',');
		File >> gia;
		File.ignore(1, ',');
		File >> loai;
		File.ignore(1, '\n');
		Sach s(isbn, ten, tacgia, nxb, gia, loai);
		L3.push_back(s);
	}
	File.close();
}

void OutDataDocGia_ToScreen(list <DocGia*> L2)
{
	list <DocGia*> ::iterator p = L2.begin();
	while (p != L2.end())
	{
		(*p)->xuatDG();
		p++;
	}
}

int SoLuongDocGia(list <DocGia*> L2)
{
	int Dem = 0;
	string madg = "";
	string hoten = "";
	int ngay = 0, thang = 0, nam = 0, sdt = 0;
	ifstream File;
	File.open("DocGia.txt");
	while (!File.eof())
	{
		Dem++;
		getline(File, madg, ',');
		getline(File, hoten, ',');
		File >> ngay;
		File.ignore(1, ',');
		File >> thang;
		File.ignore(1, ',');
		File >> nam;
		File.ignore(1, ',');
		File >> sdt;
		File.ignore(1, '\n');
	}
	File.close();
	return Dem;
}

void OutDataDocGia_File(list <DocGia*> L2)
{
	ofstream File;
	File.open("DocGia.txt");
	int Dem = 1;
	int TongSoDocGia = SoLuongDocGia(L2);
	list <DocGia*>::iterator p = L2.begin();
	while (p != L2.end())
	{
		File << (*p)->getMBD() << "," << (*p)->GetTenDG() << "," << (*p)->GetNgayDK() << "," << (*p)->GetThangDK() << "," << (*p)->GetNamDK() << "," << (*p)->GetSDT() << endl;
		if (Dem < TongSoDocGia)
		{
			File << endl;
			Dem++;
		}
		p++;
	}
	File.close();
}

void InputData_DocGia(list <DocGia*>& L2)
{
	string madg = "";
	string HoTen = "";
	int sdt = 0;
	int Ngay = 0;
	int Thang = 0;
	int Nam = 0;
	ifstream File;
	File.open("DocGia.txt");
	while (!File.eof())
	{
		getline(File, madg, ',');
		getline(File, HoTen, ',');
		File >> Ngay;
		File.ignore(1, ',');
		File >> Thang;
		File.ignore(1, ',');
		File >> Nam;
		File.ignore(1, ',');
		File >> sdt;
		File.ignore(1, '\n');
		DocGia* dg = new DocGia(madg, HoTen, Ngay, Thang, Nam, sdt);
		L2.push_back(dg);
	}
	File.close();
}

int DemTongPhieuMuon(list <PhieuMuon> L4)
{
	int nDem = 0;
	list <PhieuMuon> ::iterator p = L4.begin();
	while (p != L4.end())
	{
		nDem++;
		p++;
	}
	return nDem;
}

void OutDataPhieuMuon_File(list <PhieuMuon> L4, list <DocGia*> L2, list <Sach> L3)
{

	int TongPM = DemTongPhieuMuon(L4);
	int Dem = 1;
	ofstream File;
	File.open("PhieuMuon.txt");
	list <PhieuMuon> ::iterator p = L4.begin();
	while (p != L4.end())
	{
		File << p->GetMaPhieu() << "," << p->GetDocGia().getMBD() << "," << p->GetSach().GetISBN()
			<< "," << p->GetNgayMuon().getNgay() << "," << p->GetNgayMuon().getThang() << "," << p->GetNgayMuon().getNam()
			<< "," << p->GetNgayTra().getNgay() << "," << p->GetNgayTra().getThang() << "," << p->GetNgayTra().getNam() << "," << p->GetTrangThai();
		if (Dem < TongPM)
		{
			File << endl;
			Dem++;
		}
		p++;
	}
	File.close();
}

void OutDataPhieuMuon_ToScreen(list <PhieuMuon> L4)
{
	list <PhieuMuon> ::iterator p = L4.begin();
	while (p != L4.end())
	{
		p->xuatPhieu();
		p++;
	}
}

void inputData_PhieuMuon(list <PhieuMuon>& L4)
{
	int SPM = 0;
	string madg = "";
	string isbn = "";
	int NgayMuon = 0;
	int ThangMuon = 0;
	int NamMuon = 0;
	int NgayTra = 0;
	int ThangTra = 0;
	int NamTra = 0;
	int TrangThai = 0;
	ifstream File;
	File.open("PhieuMuon.txt");
	while (!File.eof())
	{
		File >> SPM;
		File.ignore(1, ',');
		getline(File, madg, ',');
		getline(File, isbn, ',');
		File >> NgayMuon;
		File.ignore(1, ',');
		File >> ThangMuon;
		File.ignore(1, ',');
		File >> NamMuon;
		File.ignore(1, ',');
		File >> NgayTra;
		File.ignore(1, ',');
		File >> ThangTra;
		File.ignore(1, ',');
		File >> NamTra;
		File.ignore(1, ',');
		File >> TrangThai;
		File.ignore(1, '\n');
		PhieuMuon pm(SPM, madg, isbn, NgayMuon, ThangMuon, NamMuon, NgayTra, ThangTra, NamTra, TrangThai);
		L4.push_back(pm);
	}
	File.close();
}

//====================================SACH====================================
bool kiemTraSach_DuTieuChuanMuon(list <Sach> L3, string is)
{
	int flag = 0;
	list <Sach> ::iterator p = L3.begin();
	while (p != L3.end())
	{
		if (is == p->GetISBN())
		{
			flag++;
		}
		p++;
	}
	if (flag == 0) return false;
	else return true;
}

void ThemSach(list <Sach>& L3)
{
	string isbn = "";
	string ten = "";
	string tacg = "";
	string nxb = "";
	int gia = 0;
	int loai = 0;
dd:
	cout << "\tNhap ma so sach: ";
	cin.ignore();
	getline(cin, isbn);
	list <Sach>::iterator p = L3.begin();
	while (p != L3.end())
	{

		if (isbn == p->GetISBN() || isbn == "")
		{
			textColor(4);
			cout << "\t\tMa so sach da ton tai hoac chua nhap ma so sach !!!\n";
			textColor(7);
			system("pause");
			goto dd;
		}
		p++;
	}
td:
	cout << "\tNhap ten sach: ";
	fflush(stdin);
	getline(cin, ten);
	if (ten == "")
	{
		textColor(4);
		cout << "\t\tKhong duoc de trong !\n";
		textColor(7);
		goto td;
	}
tg:
	cout << "\tNhap ten tac gia: ";
	fflush(stdin);
	getline(cin, tacg);
	if (tacg == "")
	{
		textColor(4);
		cout << "\t\tKhong duoc de trong !\n";
		textColor(7);
		goto tg;
	}
nxb:
	cout << "\tNhap nha xuat ban: ";
	fflush(stdin);
	getline(cin, nxb);
	if (nxb == "")
	{
		textColor(4);
		cout << "\t\tKhong duoc de trong !\n";
		textColor(7);
		goto nxb;
	}
	cout << "\tNhap gia cuon sach(VND): ";
	cin >> gia;
	do
	{
		cout << "\tNhap loai sach(1.Tieng Viet; 2.Ngoai Van): ";
		cin >> loai;
		if (loai != 1 && loai != 2) cout << "\n\tNhap sai loai sach, vui long nhap lai!!\n";
	} while (loai != 1 && loai != 2);

	Sach s(isbn, ten, tacg, nxb, gia, loai);
	L3.push_back(s);
	OutDataSach_File(L3);
	textColor(10);
	cout << "\tThem sach thanh cong !\n";
	textColor(7);
}

void XoaSach(list <Sach>& L3)
{
	cout << "\t\tNhap N de thoat! \n";
	string isbn = "";
dd:
	fflush(stdin);
	cout << "\t\tNhap ma so sach can xoa: ";
	getline(cin, isbn);
	if (isbn == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		int flag = 0;
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (isbn == p->GetISBN())
			{
				flag = 0;
				textColor(10);
				cout << "\t\t\tXoa sach thanh cong!";
				textColor(7);
				L3.erase(p);
				OutDataSach_File(L3);
				break;
			}
			else
			{
				flag = 1;
			}
			p++;
		}
		if (flag == 1)
		{
			textColor(4);
			cout << "\t\tMa so sach khong ton tai\n";
			textColor(7);
			goto dd;
		}
	}

}

void SuaSach(list <Sach>& L3)
{
	string is, ten, tg, nxb;
	int gia, loai;
	string isbn = "";
dd:
	fflush(stdin);
	cout << "\t\tNhap ma so sach can chinh sua(nhap N de thoat): ";
	getline(cin, isbn);
	if (isbn == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		int flag = 0;
		list<Sach> L = L3;
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (isbn == p->GetISBN())
			{
				flag = 0;
				int chon;
				while (true)
				{
					system("cls");
					cout << "\t\t*******************************************\n";
					cout << "\t\t  1. Sua ISBN sach			                \n";
					cout << "\t\t  2. Sua ten sach                          \n";
					cout << "\t\t  3. Sua ten tac gia	                    \n";
					cout << "\t\t  4. Sua ten NXB			                \n";
					cout << "\t\t  5. Sua gia sach				            \n";
					cout << "\t\t  6. Sua loai sach					        \n";
					cout << "\t\t  0. Thoat!                                \n";
					cout << "\t\t*******************************************\n";
				chon:
					cout << "\t\t   Nhap Lua Chon: ";
					cin >> chon;
					if (chon != 1 && chon != 2 && chon != 3 && chon != 4 && chon != 5 && chon != 6 && chon != 0)
					{
						cout << "Nhap sai, vui long nhap lai!!\n";
						system("pause");
					}
					else if (chon == 1)
					{
						cout << "\nNhap ma sach moi: ";
						cin.ignore();
						getline(cin, is);
						p->SetISBN(is);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 2)
					{
						cout << "\nNhap ten sach moi: ";
						cin.ignore(); getline(cin, ten);
						p->SetTen(ten);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 3)
					{
						cout << "\nNhap ten tac gia moi: ";
						cin.ignore(); getline(cin, tg);
						p->SetTG(tg);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 4)
					{
						cout << "\nNhap ten NXB moi: ";
						cin.ignore(); getline(cin, nxb);
						p->SetNXB(nxb);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 5)
					{
						cout << "\nNhap gia sach moi(VND): ";
						cin >> gia;
						p->SetGia(gia);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);;
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 6)
					{
						do
						{
							cout << "\nNhap loai sach moi(1.Tieng Viet; 2.Ngoai Van): ";
							cin >> loai;
							if (loai != 1 && loai != 2) cout << "\n\tNhap sai loai sach, vui long nhap lai!!\n";
						} while (loai != 1 && loai != 2);
						p->SetType(loai);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataSach_File(L3);;
						cout << "\n*SACH SAU KHI SUA*\n"; p->XuatSach();
						system("pause");
					}
					else if (chon == 0)
					{
						break;
					}
				}
				flag++;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tMa so sach khong ton tai!\n";
			textColor(7);
			goto dd;
		}
	}
}

void TimSachISBN(list <Sach> L3)
{
	int flag = 0;
	textColor(7);
	string isbn = "";
dd:
	cout << "\t\tNhap ma sach can tim(Nhap N de thoat): ";
	fflush(stdin);
	getline(cin, isbn);
	if (isbn == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (isbn == p->GetISBN())
			{
				flag = 0;
				cout << "\n\t\tTHONG TIN SACH\n";
				p->XuatSach();
				cout << "\n*********************************************\n";
				break;
			}
			else
			{
				flag = 1;
			}
			p++;
		}
		if (flag == 1)
		{
			textColor(4);
			cout << "\t\tMa sach khong ton tai !\n";
			textColor(7);
			goto dd;
		}
	}

}

void TimSachTen(list <Sach> L3)
{
	int flag = 0;
	textColor(7);
	string ten = "";
dd:
	cout << "\t\tNhap ten sach can tim(nhap N de thoat): ";
	fflush(stdin);
	getline(cin, ten);
	if (ten == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (ten == p->GetTen())
			{
				flag = 0;
				cout << "\n\t\tTHONG TIN SACH\n";
				p->XuatSach();
				cout << "\n*********************************************\n";
				break;
			}
			else
			{
				flag = 1;
			}
			p++;
		}
		if (flag == 1)
		{
			textColor(4);
			cout << "\t\tTen sach khong ton tai !\n";
			textColor(7);
			goto dd;
		}
	}

}

void TimSachTG(list <Sach> L3)
{
	int flag = 0;
	textColor(7);
	string tacgia = "";
dd:
	cout << "\t\tNhap ten tac gia sach can tim(nhap N de thoat): ";
	fflush(stdin);
	getline(cin, tacgia);
	if (tacgia == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (tacgia == p->Gettg())
			{
				flag = 0;
				cout << "\n\t\tTHONG TIN SACH\n";
				p->XuatSach();
				cout << "\n*********************************************\n";
				break;
			}
			else
			{
				flag = 1;
			}
			p++;
		}
		if (flag == 1)
		{
			textColor(4);
			cout << "\t\tTen tac gia khong ton tai !\n";
			textColor(7);
			goto dd;
		}
	}

}

void TimSachNXB(list <Sach> L3)
{
	int flag = 0;
	textColor(7);
	string nxb = "";
dd:
	cout << "\t\tNhap ten nha xuat ban cua sach can tim(nhap N de thoat): ";
	fflush(stdin);
	getline(cin, nxb);
	if (nxb == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (nxb == p->GetNXB())
			{
				cout << "\n\t\tTHONG TIN SACH\n";
				p->XuatSach();
				cout << "\n*********************************************\n";
				flag++;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tTen NXB khong ton tai !\n";
			textColor(7);
			goto dd;
		}
	}

}

void TimSachGia(list <Sach> L3)
{
	int flag = 0;
	textColor(4);

	cout << "\t\tNhap -1 de thoat!\n";
	textColor(7);
	int gia = 0;
dd:
	cout << "\t\tNhap gia sach can tim(VND): ";
	cin >> gia;
	if (gia == -1)
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		list <Sach>::iterator p = L3.begin();
		while (p != L3.end())
		{
			if (gia == p->GetGia())
			{
				cout << "\n\t\tTHONG TIN SACH\n";
				p->XuatSach();
				cout << "\n*********************************************\n";
				flag++;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tSach khong ton tai !\n";
			textColor(7);
			goto dd;
		}
	}

}

void MenuSach(list <Sach> L3)
{
	int luachon;
	InputData_Sach(L3);
	while (true)
	{
		system("cls");
		cout << "\t\t*******************************************\n";
		cout << "\t\t  1. Hien thi thong tin sach.              \n";
		cout << "\t\t  2. Them sach                             \n";
		cout << "\t\t  3. Xoa sach			                    \n";
		cout << "\t\t  4. Sua sach			                    \n";
		cout << "\t\t  5. Tim kiem sach theo ISBN               \n";
		cout << "\t\t  6. Tim kiem sach theo ten sach           \n";
		cout << "\t\t  7. Tim kiem sach theo ten tac gia        \n";
		cout << "\t\t  8. Tim kiem sach theo ten NXB            \n";
		cout << "\t\t  9. Tim kiem sach theo gia sach           \n";
		cout << "\t\t  0. Thoat!                                \n";
		cout << "\t\t*******************************************\n";
		cout << "\t\t   Nhap Lua Chon: ";
		cin >> luachon;
		if (luachon != 1 && luachon != 2 && luachon != 3 && luachon != 4 && luachon != 5 && luachon != 6 && luachon != 7 && luachon != 8 && luachon != 9 && luachon != 0)
		{
			cout << "Nhap sai, vui long nhap lai!!\n";
			system("pause");
		}
		else if (luachon == 1)
		{
			cout << "\n\t\t*THONG TIN SACH*\n";
			OutDataSach_ToScreen(L3);
			system("pause");
		}
		else if (luachon == 2)
		{
			cout << "\n\t\t*THEM SACH*\n";
			ThemSach(L3);
			system("pause");
		}
		else if (luachon == 3)
		{
			cout << "\n\t\t*XOA SACH*\n";
			XoaSach(L3);
			system("pause");
		}
		else if (luachon == 4)
		{
			cout << "\n\t\t*SUA SACH*\n";
			SuaSach(L3);
			system("pause");
		}
		else if (luachon == 5)
		{
			cout << "\n\t\t*TIM KIEM SACH THEO ISBN*\n";
			TimSachISBN(L3);
			system("pause");
		}
		else if (luachon == 6)
		{
			cout << "\n\t\t*TIM KIEM SACH THEO TEN SACH*\n";
			TimSachTen(L3);
			system("pause");
		}
		else if (luachon == 7)
		{
			cout << "\n\t\t*TIM KIEM SACH THEO TEN TAC GIA*\n";
			TimSachTG(L3);
			system("pause");
		}
		else if (luachon == 8)
		{
			cout << "\n\t\t*TIM KIEM SACH THEO TEN NXB*\n";
			TimSachNXB(L3);
			system("pause");
		}
		else if (luachon == 9)
		{
			cout << "\n\t\t*TIM KIEM SACH THEO GIA SACH*\n";
			TimSachGia(L3);
			system("pause");
		}
		else if (luachon == 0)
		{
			break;
		}
	}
	system("pause");
}

//====================================DOC GIA====================================
int KiemTraDocGia(list <DocGia*> L2, string madg)
{
	int flag = 0;
	list <DocGia*>::iterator p = L2.begin();
	while (p != L2.end())
	{
		if (madg == (*p)->getMBD())
		{
			flag++;
		}
		p++;
	}
	if (flag == 0) return 0;
	else return 1;
}

void InTheThuVien(string MaDG, string HoTen, int Ngay, int Thang, int Nam, int sdt)
{
	textColor(10);
	cout << "\n\t\tDang in the thu vien vui long doi !\n";
	textColor(9);
	Sleep(300);
	cout << "\t*************************************************\n";
	Sleep(400);
	cout << "\t*     Truong Dai Hoc Khoa Hoc Tu Nhien - DHQG   *\n";
	Sleep(500);
	cout << "\t*                 THE THU VIEN                  *\n";
	Sleep(500);
	cout << "\t*************************************************\n";
	Sleep(500);
	textColor(11);
	cout << "\t* Ten : " << HoTen << "  -  Ma So: " << MaDG << "           *\n";
	Sleep(500);
	cout << "\t* So dien thoai lien he: " << sdt << "				 *\n";
	Sleep(500);
	cout << "\t* Ngay Dang Ky: " << Ngay << "/" << Thang << "/" << Nam << "                        *\n";
	Sleep(500);
	cout << "\t*************************************************\n";
	Sleep(200);
	textColor(10);
	cout << "\n\n\t\t In the thanh cong !\n";
	textColor(7);
}

void ThemDocGia(list <DocGia*>& L2)
{
	/*time_t t = time(0);
	struct tm *Now = localtime(&t);*/
	int luachon = 0;
	string madg = "";
	string HoTen = "";
	int sdt = 0;
	//int Ngay = Now->tm_mday;         //
	//int Thang = Now->tm_mon + 1;    // Ngày làm thẻ được lấy tự động
	//int Nam = Now->tm_year + 1900;  //

	int Ngay, Thang, Nam;
ma:
	cout << "\tNhap ma doc gia: ";
	cin.ignore();
	getline(cin, madg);
	list<DocGia*>::iterator p = L2.begin();
	while (p != L2.end())
	{
		if (madg == (*p)->getMBD() || madg == " ")
		{
			textColor(4);
			cout << "\tMa doc gia da ton tai hoac chua duoc nhap!!!\n";
			textColor(7);
			system("pause");
			goto ma;
		}
		p++;
	}
ts:
	cout << "\tNhap ten doc gia: ";
	fflush(stdin);
	getline(cin, HoTen);
	if (HoTen == "")
	{
		textColor(4);
		cout << "\t\tKhong duoc de trong !\n";
		textColor(7);
		goto ts;
	}
	cout << "\tNhap ngay,thang,nam lam the: ";
	cin >> Ngay >> Thang >> Nam;
	cout << "\tNhap so dien thoai cua doc gia: ";
	cin >> sdt;
	DocGia* dg = new DocGia(madg, HoTen, Ngay, Thang, Nam, sdt);
	L2.push_back(dg);
	OutDataDocGia_File(L2);
	textColor(10);
	cout << "\tThem doc gia thanh cong!\n ";
	textColor(7);
	InTheThuVien(madg, HoTen, Ngay, Thang, Nam, sdt);
	system("pause");

}

void XoaDocGia(list <DocGia*>& L2)
{
	cout << "\t\tNhap N de thoat! \n";
	string madg = "";
dg:
	fflush(stdin);
	cout << "\t\tNhap ma doc gia can xoa: ";
	getline(cin, madg);
	if (madg == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		int flag = 0;
		list <DocGia*>::iterator p = L2.begin();
		while (p != L2.end())
		{
			if (madg == (*p)->getMBD())
			{
				flag = 0;
				textColor(10);
				cout << "\t\t\tXoa doc gia thanh cong!";
				textColor(7);
				L2.erase(p);
				OutDataDocGia_File(L2);
				break;
			}
			else
			{
				flag = 1;
			}
			p++;
		}
		if (flag == 1)
		{
			textColor(4);
			cout << "\t\tMa doc gia khong ton tai\n";
			textColor(7);
			goto dg;
		}
	}

}

void SuaDocGia(list <DocGia*>& L2)
{
	string madg, ten;
	int sdt, ngay, thang, nam;
	string matim = "";
mt:
	cout << "Nhap ma so doc gia can chinh sua(nhap N de thoat): ";
	cin.ignore();
	getline(cin, matim);
	if (matim == "N")
	{
		textColor(10);
		cout << "\tBan da chon thoat! \n";
		textColor(7);
	}
	else
	{
		int flag = 0;
		list <DocGia*>::iterator p = L2.begin();
		while (p != L2.end())
		{
			if (matim == (*p)->getMBD())
			{
				flag = 0;
				int chon;
				while (true)
				{
					system("cls");
					cout << "\t\t*******************************************\n";
					cout << "\t\t  1. Sua ma doc gia		                \n";
					cout << "\t\t  2. Sua ten doc gia                       \n";
					cout << "\t\t  3. Sua ngay lam the	                    \n";
					cout << "\t\t  4. Sua thang lam the		                \n";
					cout << "\t\t  5. Sua nam lam the			            \n";
					cout << "\t\t  6. Sua so dien thoai lien he		        \n";
					cout << "\t\t  0. Thoat!                                \n";
					cout << "\t\t*******************************************\n";
				chon:
					cout << "\t\t   Nhap Lua Chon: ";
					cin >> chon;
					if (chon != 1 && chon != 2 && chon != 3 && chon != 4 && chon != 5 && chon != 6 && chon != 0)
					{
						cout << "Nhap sai, vui long nhap lai!!\n";
						system("pause");
					}
					else if (chon == 1)
					{
						cout << "\nNhap ma doc gia moi: ";
						cin.ignore();
						getline(cin, madg);
						(*p)->SetMBD(madg);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 2)
					{
						cout << "\nNhap ten doc gia moi: ";
						cin.ignore(); getline(cin, ten);
						(*p)->SetTenDG(ten);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 3)
					{
						cout << "\nNhap ngay lam the moi: ";
						cin >> ngay;
						(*p)->SetNgayDK(ngay);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 4)
					{
						cout << "\nNhap thang lam the moi: ";
						cin >> thang;
						(*p)->SetThangDK(thang);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 5)
					{
						cout << "\nNhap nam lam the moi: ";
						cin >> nam;
						(*p)->SetNamDK(nam);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 6)
					{
						cout << "\nNhap so dien thoai lien he moi: ";
						cin >> sdt;
						(*p)->SetSDT(sdt);
						textColor(10);
						cout << "\t\t\tChinh sua thanh cong!";
						textColor(7);
						OutDataDocGia_File(L2);
						cout << "\n*THONG TIN DOC GIA SAU KHI SUA*\n"; (*p)->xuatDG();
						system("pause");
					}
					else if (chon == 0)
					{
						break;
					}
				}
				flag++;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tMa so doc gia khong ton tai!\n";
			textColor(7);
			goto mt;
		}
	}
}

void TimDocGia(list <DocGia*> L2)
{
	string timkiem = "";
	int flag = 0;
dd:
	list <DocGia*>::iterator p = L2.begin();
	cout << "\tNhap ma doc gia hoac ten doc gia can tim thong tin(Nhap N de thoat): ";
	cin.ignore();
	getline(cin, timkiem);
	if (timkiem == "N")
	{
		textColor(10);
		cout << "\t\tBan da chon thoat!\n";
		textColor(7);
		return;
	}
	while (p != L2.end())
	{
		if (timkiem == (*p)->getMBD() || timkiem == (*p)->GetTenDG())
		{
			(*p)->xuatDG();
			flag++;
		}
		p++;
	}
	if (flag == 0)
	{
		textColor(4);
		cout << "\t\tDoc gia khong ton tai!\n";
		textColor(7);
		goto dd;
	}
}

void MenuDocGia(list <DocGia*> L2)
{
	InputData_DocGia(L2);
	int luachon;
	while (true)
	{
		system("cls");
		cout << "\t\t*******************************************\n";
		cout << "\t\t  1. Hien thi thong tin doc gia.           \n";
		cout << "\t\t  2. Them doc gia                          \n";
		cout << "\t\t  3. Xoa doc gia                           \n";
		cout << "\t\t  4. Sua thong tin doc gia                 \n";
		cout << "\t\t  5. Tim kiem doc gia	                    \n";
		cout << "\t\t  0. Thoat!                                \n";
		cout << "\t\t*******************************************\n";
		cout << "\t\t   Nhap Lua Chon: ";
		cin >> luachon;
		if (luachon != 1 && luachon != 2 && luachon != 3 && luachon != 4 && luachon != 5 && luachon != 0)
		{
			cout << "Nhap sai, vui long nhap lai!!\n";
			system("pause");
		}
		else if (luachon == 1)
		{
			cout << "\n\t\t*THONG TIN DOC GIA*\n";
			OutDataDocGia_ToScreen(L2);
			system("pause");
		}
		else if (luachon == 2)
		{
			cout << "\n\t\t*THEM DOC GIA*\n";
			ThemDocGia(L2);
			system("pause");
		}
		else if (luachon == 3)
		{
			cout << "\n\t\t*XOA DOC GIA*\n";
			XoaDocGia(L2);
			system("pause");
		}
		else if (luachon == 4)
		{
			cout << "\n\t\t*SUA THONG TIN DOC GIA*\n";
			SuaDocGia(L2);
			system("pause");
		}
		else if (luachon == 5)
		{
			cout << "\n\t\t*TIM KIEM DOC GIA*\n";
			TimDocGia(L2);
			system("pause");
		}
		else if (luachon == 0)
		{
			break;
		}
	}
	system("pause");
}

//====================================PHIEU MUON TRA SACH====================================
bool KTHetHanMuon(int nNgayTra, int nThangTra, int nNamTra, int nNgayHienTai, int nThangHienTai, int nNamHienTai)
{	//true la den han tra
	//false la van con han muon
	if (nNamHienTai > nNamTra)
	{
		return true;
	}
	else if (nThangHienTai > nThangTra)
	{
		return true;
	}
	else if (nThangHienTai < nThangTra)
	{
		return false;
	}
	else if (nNgayHienTai > nNgayTra)
	{
		return true;
	}
	return false;
}

void Xuat_DS_PM_HetHanMuonSach(list <PhieuMuon> L4)
{
	int NgayTra = 0;
	int ThangTra = 0;
	int NamTra = 0;
	time_t t = time(0);
	struct tm* Now = localtime(&t);
	int NgayHienTai = Now->tm_mday;
	int ThangHienTai = Now->tm_mon + 1;
	int NamHienTai = Now->tm_year + 1900;
	list <PhieuMuon> ::iterator p = L4.begin();
	while (p != L4.end())
	{
		NgayTra = p->GetNgayTra().getNgay();
		ThangTra = p->GetNgayTra().getThang();
		NamTra = p->GetNgayTra().getNam();
		if (KTHetHanMuon(NgayTra, ThangTra, NamTra, NgayHienTai, ThangHienTai, NamHienTai) == true && p->GetTrangThai() != 0)
		{
			p->XuatDGQuaHan();
		}
		p++;
	}

}

void ThemPhieuMuon(list <PhieuMuon>& L4, list <DocGia*>& L2, list <Sach>& L3)
{
	string madg = "";
	while (true)
	{
	pm:
		cout << "\t\tNhap ma doc gia can muon sach(nhap N de thoat): ";
		fflush(stdin);
		getline(cin, madg);
		if (madg == "")
		{
			textColor(4);
			cout << "Khong duoc de trong ! \n";
			textColor(7);
			system("pause");
			goto pm;
		}
		else if (madg == "N")
		{
			textColor(10);
			cout << "\t\tBan chon thoat!\n";
			textColor(7);
			return;
		}
		else if (KiemTraDocGia(L2, madg) == 0)
		{
			textColor(4);
			cout << "\t\tMa doc gia khong ton tai!\n";
			textColor(7);
			system("pause");
			goto pm;
		}
		else
		{
			break;
		}
	}
	string isbn = "";
	while (true)
	{
		cout << "\t\tNhap ma sach: ";
		fflush(stdin);
		getline(cin, isbn);
		if (isbn == "")
		{
			textColor(4);
			cout << "Khong duoc de trong ! \n";
			textColor(7);
			system("pause");
		}
		else if (kiemTraSach_DuTieuChuanMuon(L3, isbn) == true)
		{
			break;
		}
		else
		{
			textColor(4);
			cout << "\t\tMa sach khong ton tai!\n";
			textColor(7);
			system("pause");
		}
	}
	PhieuMuon pm(madg, isbn);
	L4.push_back(pm);
	OutDataPhieuMuon_File(L4, L2, L3);
	textColor(10);
	cout << "\t\tTao phieu muon thanh cong!\n";
	textColor(7);
}

void traSach_PhieuMuon(list <PhieuMuon>& L4, list <DocGia*> L2, list <Sach>& L3)
{
	int flag = 0;
	int MaPhieuMuon = 0;
	while (true)
	{
	dd:
		system("cls");
		cout << "\t\tNhap ma phieu muon can tra sach: "; cin >> MaPhieuMuon;
		list <PhieuMuon> ::iterator p = L4.begin();
		while (p != L4.end())
		{
			if (MaPhieuMuon == p->GetMaPhieu())
			{
				if (p->GetTrangThai() != 0)
				{
					flag = 1;
					p->SetTrangThai(0); // gán trạng thái 0 cho phiếu mượn đang muốn trả
					string isbn = p->GetSach().GetISBN();
					list <Sach> ::iterator q = L3.begin();
					while (q != L3.end())
					{
						if (q->GetISBN() == isbn)
						{
							q->SetTT(0); // gán tình trạng 0 cho sách đã được trả
							break;
						}
						q++;
					}
					OutDataSach_File(L3);
					OutDataPhieuMuon_File(L4, L2, L3);
					textColor(10);
					cout << "\t\tTra sach thanh cong!\n";
					textColor(7);
					break;
				}
				textColor(4);
				cout << "\t\tMa phieu muon da duoc tra!\n";
				textColor(7);
				system("pause");
				goto dd;
			}
			p++;
		}
		if (flag == 0)
		{
			textColor(4);
			cout << "\t\tMa phieu muon khong ton tai!\n";
			textColor(7);
			system("pause");
		}
		else if (flag == 1)
		{
			break;
		}
	}
}

void MenuPhieu(list <PhieuMuon> L1, list <Sach> L3, list <DocGia*>L2)
{
	inputData_PhieuMuon(L1);
	int luachon;
	while (true)
	{
		system("cls");
		cout << "\t\t******************************************\n";
		cout << "\t\t  1. Them phieu muon.                     \n";
		cout << "\t\t  2. Tra Sach.                            \n";
		cout << "\t\t  3. Xuat danh sach phieu muon            \n";
		cout << "\t\t  4. Xuat danh sach phieu het han muon    \n";
		cout << "\t\t  0. Thoat!                               \n";
		cout << "\t\t******************************************\n";
		cout << "\t\t   Nhap Lua Chon: ";
		cin >> luachon;
		if (luachon != 1 && luachon != 2 && luachon != 3 && luachon != 4 && luachon != 0)
		{
			cout << "Nhap sai, vui long nhap lai!!!\n";
			system("pause");
		}
		else if (luachon == 1)
		{
			ThemPhieuMuon(L1, L2, L3);
			system("pause");
		}
		else if (luachon == 2)
		{
			traSach_PhieuMuon(L1, L2, L3);
			system("pause");
		}
		else if (luachon == 3)
		{
			OutDataPhieuMuon_ToScreen(L1);
			system("pause");
		}
		else if (luachon == 4)
		{
			Xuat_DS_PM_HetHanMuonSach(L1);
			system("pause");
		}
		else if (luachon == 0)
		{
			break;
		}
	}
	system("pause");
}

int main()
{
	list <Sach> L3;
	list <DocGia*> L2;
	list <PhieuMuon> L1;
	int cho;
	while (true)
	{
		system("cls");
		cout << "\t\t*******************************************\n";
		cout << "\t\t  1. Thao tac voi sach.		            \n";
		cout << "\t\t  2. Thao tac voi doc gia                  \n";
		cout << "\t\t  3. Phieu muon tra sach                   \n";
		cout << "\t\t  0. Thoat!                                \n";
		cout << "\t\t*******************************************\n";
		cout << "\t\t   Nhap Lua Chon: ";
		cin >> cho;
		if (cho != 1 && cho != 2 && cho != 3 && cho != 0)
		{
			cout << "Nhap sai, vui long nhap lai!!\n";
			system("pause");
		}
		else if (cho == 1)
		{
			MenuSach(L3);
			system("pause");
		}
		else if (cho == 2)
		{
			MenuDocGia(L2);
			system("pause");
		}
		else if (cho == 3)
		{
			MenuPhieu(L1, L3, L2);
			system("pause");
		}
		else if (cho == 0)
		{
			break;
		}
	}
	system("pause");
}
