#pragma once
#include <iostream>
#include <string>
#include <bitset>
#include <conio.h>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

#define QINT_SIZE 16
#define HEX_CHARS "0123456789ABCDEF" 

class QInt
{
private: 
	unsigned char bytes[QINT_SIZE];

public:
	QInt();											//HAM KHOI TAO MAC DINH LA 0
	~QInt();										//HAM HUY
	static QInt Zero();								//HAM MAC DINH SO 0 KIEU QINT											
	static QInt One();								//HAM MAC DINH SO 1 KIEU QINT

	//HAM PHU TRO
	bool GetBit(int pos) const;						//LAY GIA TRI BIT TAI MOT VI TRI
	void SetBit(int pos, bool val);					//GAN MOT GIA TRI VAO BIT O MOT VI TRI pos
	bool CheckNeg() const;							//KIEM TRA SO AM
	QInt Inverse() const;							//DOI DAU
	friend string Mul2(string str, int add);		//HAM NHAN DUNG CHO CHUYEN CO SO
	friend string Div2(string str);					//HAM CHIA DUNG CHO CHUYEN CO SO
	friend QInt Cong(const QInt &a, const QInt &b);	//HAM CONG DUNG CHO OPERATOR +
	void divide(const QInt& divisor, QInt& div, QInt& mod) const;  //HAM CHIA DUNG CHO OPERATOR /
	QInt ShiftRight(int nums) const;				//DICH PHAI LUAN LI
	bool operator==(const QInt &Q) const;			//OPERATOR SO SANH BANG


	//HAM NHAP XUAT
	void Input(string &str, int baseIn);
	void Output(int baseOut);


	//PHEP TOAN CHUYEN CO SO
	string toBinStr() const;					//QInt to BinaryString
	friend QInt decToBin(string str);			//10 -> 2
	friend string binToDec(const QInt& str);	//2 -> 10
	friend string binToHex(const QInt &str);	//2 -> 16   
	friend QInt hexToBin(string str);			//16 -> 2



	//TOAN TU =, +, -, *, /, &, |, ^, ~
	QInt operator=(const QInt &Q);		
	QInt operator +(const QInt &Q) const;	//TOAN TU CONG
	QInt operator -(const QInt &Q) const;	//TOAN TU TRU
	QInt operator *(const QInt &B) const;	//TOAN TU NHAN	
	QInt operator/(const QInt &B) const;	//TOAN TU CHIA	
	QInt operator & (const QInt &Q) const;	//AND
	QInt operator | (const QInt &Q) const;	//OR
	QInt operator ^(const QInt &Q) const;	//XOR
	friend QInt operator ~(const QInt &Q);	//NOT

	//PHEP DICH VA XOAY
	QInt operator>> (int nums) const;	//DICH PHAI SO HOC
	QInt operator<< (int nums) const;	//DICH TRAI 
	QInt rol(int nums) const;			//XOAY TRAI
	QInt ror(int nums) const;			//XOAY PHAI

};

string Process_QInt(string str, string fileout);		//XU LI CAC PHEP TOAN 
string value(QInt A, int baseOut);						// TRA VE GIA TRI THUC CUA MOT SO QINT
QInt decToBin(string str);								
string binToDec(const QInt& str);	
string binToHex(const QInt& str);	
QInt hexToBin(string str);			
void Out_File(string input, string output);				//DOC PHEP TINH TU FILE INPUT XUAT KET QUA RA FILE OUTPUT