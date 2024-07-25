#include "QInt.h"


//HAM KHOI TAO MAC DINH LA 0
QInt::QInt()
{
	fill(bytes, bytes + QINT_SIZE, 0);

}
//HAM HUY
QInt::~QInt()
{
	//delete[] bytes; => LOI TRAN HEAP LA DO CAI NAY	 =))))))))))))
}
//HAM MAC DUNH SO 0 KIEU QINT
QInt QInt::Zero()
{
	static QInt sZero;
	static bool zeroInit = false;
	if (!zeroInit)
	{
		fill(sZero.bytes, sZero.bytes + QINT_SIZE, 0);
		zeroInit = true;
	}
	return sZero;
}
//HAM MAC DINH SO 1 KIEU QINT
QInt QInt::One()
{
	static QInt sOne;
	static bool oneInit = false;
	if (!oneInit)
	{
		fill(sOne.bytes, sOne.bytes + QINT_SIZE, 0);
		oneInit = true;
	}
	sOne.bytes[QINT_SIZE - 1] = 1;

	return sOne;
}

//LAY GIA TRI BIT TAI MOT VI TRI 'pos'
bool QInt::GetBit(int pos) const
{
	int BytePos = 16 - 1 - pos / 8;
	int BitPos = pos % 8;
	return ((this->bytes[BytePos] >> BitPos) & 1);
}
//GAN GIA TRI 'val' VAO BIT O VI TRI 'pos'
void QInt::SetBit(int pos, bool val)
{
	int BytePos = 16 - 1 - pos / 8;
	int BitPos = pos % 8;
	if (val)
	{
		this->bytes[BytePos] = ((1 << BitPos) | this->bytes[BytePos]);
	}
	else
	{
		this->bytes[BytePos] = (~(1 << BitPos) & this->bytes[BytePos]);
	}
}
//KIEM TRA SO AM
bool QInt::CheckNeg() const
{
	return ((this->GetBit(127)) == 1); //am la 1 duong la 0
}
//DOI DAU CUA SO QINT
QInt QInt::Inverse() const
{
	if (*this == QInt::Zero()) return *this;
	QInt res = ~(*this);

	for (int i = 15; i > 0; i--)
	{
		if (res.bytes[i] < 255)
		{
			res.bytes[i] += 1;
			break;
		}
		else
			res.bytes[i] = 0;
	}
	return res;
}
//HAM NHAN DUNG CHO CHUYEN CO SO
string Mul2(string str, int add)
{
	string res = "";
	int c = add;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		int temp = str[i] - '0';
		temp = temp * 2 + c;
		res += (temp % 10 + '0');
		c = temp / 10;
	}
	if (c > 0)
		res += c + '0';
	reverse(res.begin(), res.end());

	return res;
}
//HAM CHIA DUNG CHO CHUYEN CO SO
string Div2(string str)
{
	string res = "";

	int add = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int digit = str[i] - '0';
		res += ((digit / 2 + add) + '0');
		add = ((digit % 2 == 0) ? 0 : 5);
	}

	if (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);
	return res;
}
//HAM CONG DUNG CHO OPERATOR +
QInt Cong(const QInt& a, const QInt& b)
{
	QInt res;
	bool sodu = 0;
	for (int i = 0; i < 128; i++)
	{
		int tmp = a.GetBit(i) + b.GetBit(i) + sodu;
		if (tmp == 0) // bit of a = 0, bit of b = 0
		{
			sodu = 0;
			res.SetBit(i, 0);
		}
		else if (tmp == 1) //bit of a + bit of b =1 || bit of a,b = 0 and sodu = 1
		{
			sodu = 0;
			res.SetBit(i, 1);
		}
		else if (tmp == 2) //bit of a = bit of b = 1 || sodu =1 and bit of a + bit of b = 1
		{
			sodu = 1;
			res.SetBit(i, 0);
		}
		else if (tmp == 3)//bit of a = bit of b = sodu =1
		{
			sodu = 1;
			res.SetBit(i, 1);
		}
	}
	return res;
}
//HAM CHIA DUNG CHO OPERATOR /
void QInt::divide(const QInt & divisor, QInt & div, QInt & mod) const
{
	mod = Zero();
	div = *this;
	QInt M = divisor;  //M > 0 thi A = n bit 0 va nguoc lai
	// Luu lai dau cua phep chia.
	bool isDNegative = div.CheckNeg();
	bool isMNegative = M.CheckNeg();
	if (div.GetBit(QINT_SIZE * 8 - 1) == true) // Bao dam div va M luon >= 0
	{
		QInt A;
		div = Cong(A, div.Inverse());
	}
	if (M.GetBit(QINT_SIZE * 8 - 1) == true)
	{
		QInt A;
		M = Cong(A, M.Inverse());
	}
	for (int i = 0; i < QINT_SIZE * 8; i++) // Thuc hien chia theo thuat toan trong tai lieu.
	{
		mod = mod << 1;				//DICH TRAI
		mod.SetBit(0, div.GetBit(QINT_SIZE * 8 - 1)); // Copy MSB cua Q vao LSB cua A.
		div = div << 1;
		QInt tmp = Cong(mod, M.Inverse());
		if (tmp.GetBit(QINT_SIZE * 8 - 1) == false) // tmp >= 0
		{
			mod = tmp;
			div.SetBit(0, 1);
		}
	}

	if (isDNegative)		//So du va so bi chia cung dau
		mod = mod.Inverse();
	if (isDNegative + isMNegative == 1) //Neu so bi chia va so chia trai dau thi doi dau thuong
		div = div.Inverse();
}
//HAM DICH PHAI LUAN LI
QInt QInt::ShiftRight(int nums) const
{
	QInt RESULT = *this;
	while (nums > 0)
	{
		for (int i = QINT_SIZE - 1; i > 0; i--)
		{
			bool checkbit = RESULT.bytes[i - 1] & 1; //lay bit cuoi cua byte truoc
			RESULT.bytes[i] = RESULT.bytes[i] >> 1; //Dich phai 1 bit
			if (checkbit)
			{
				RESULT.bytes[i] = ((1 << 7) | RESULT.bytes[i]);
			}
		}
		RESULT.bytes[0] = RESULT.bytes[0] >> 1;
		nums--;
	}
	return RESULT;
}
//OPERATOR SO SANH BANG
bool QInt::operator==(const QInt& Q) const
{
	for (int i = 0; i < 16; i++)
	{
		if (this->bytes[i] != Q.bytes[i])
			return false;
	}
	return true;
}

//HAM NHAP SO QINT
void QInt::Input(string& str, int baseIn)
{
	int pos = 0;
	switch (baseIn)
	{
	case 2:
	{
		(*this) = QInt::Zero();
		for (int i = str.length() - 1; i >= 0; i--)
		{
			SetBit(pos, str[i] == '1');
			pos++;
		}
		break;
	}
	case 10:
	{
		(*this) = decToBin(str);
		break;
	}
	case 16:
	{
		(*this) = hexToBin(str);
		break;
	}
	}
}
//HAM XUAT SO QINT THEO CO SO 'baseOut'
void QInt::Output(int baseOut)
{
	string res;
	switch (baseOut)
	{
	case 2:
	{
		res = toBinStr();
		while (res[0] == '0' && res.length() > 1)
			res.erase(0, 1);
		cout << res;
		break;
	}
	case 10:
	{
		cout << binToDec(*this);
		break;
	}
	case 16:
	{
		cout << binToHex(*this);
		break;
	}
	}
}


//=========CHUYEN DOI CAC HE CO SO=========

//CHUYEN TU QINT SANG STRING
string QInt::toBinStr() const
{
	string res = "";
	for (int i = 0; i < QINT_SIZE; i++)
	{
		res += bitset<8>(this->bytes[i]).to_string();
	}
	return res;
}
//CHUYEN TU CO SO 10 SANG CO SO 2
QInt decToBin(string str)
{
	QInt res;
	bool isNegative = false;
	if (str[0] == '-')
	{
		isNegative = true;
		str.erase(0, 1);
	}

	string binStr = "";
	do
	{
		int lastD = str[str.length() - 1] - '0';
		binStr += ((lastD % 2 == 0) ? '0' : '1');
		str = Div2(str);
	} while (str != "0");

	reverse(binStr.begin(), binStr.end());
	res.Input(binStr, 2);

	if (isNegative)
		res = res.Inverse();
	return res;
}
//CHUYEN TU CO SO 2 SANG CO SO 10
string binToDec(const QInt& str)
{

	string res = "";
	if (str == QInt::Zero())
	{
		res = "0";
		return res;
	}

	QInt posSrc = str;
	if (str.CheckNeg())
	{
		posSrc = posSrc.Inverse();
	}

	string binStr = posSrc.toBinStr();
	int pos = binStr.find('1', 0) + 1;
	res = "1";
	while (pos < binStr.length())
	{
		int additive = binStr[pos] - '0';
		res = Mul2(res, additive);
		pos++;
	}
	if (str.CheckNeg())
		res = '-' + res;

	return res;
}
//CHUYEN TU CO SO 2 SANG CO SO 16
string binToHex(const QInt& str) 
{
	string res = "";
	string binStr = str.toBinStr();
	int len = binStr.length() / 4;
	int i = binStr.length() % 4;
	char current = 0, k = 0;
	if (i)
	{
		while (i--)
		{
			current = (current << 1) + (binStr[k] - '0');
			k++;
		}
		res += HEX_CHARS[current];
	}
	while (len--)
	{
		current = 0;
		for (int i = 0; i < 4; i++)
		{
			current = (current << 1) + (binStr[k] - '0');
			k++;
		}
		res += HEX_CHARS[current];
	}
	while (res[0] == '0' && res.length() > 1)
		res.erase(0, 1);

	return res;
}
//CHUYEN TU CO SO 16 SANG CO SO 2
QInt hexToBin(string str)
{
	QInt res;
	string binStr = "";
	for (int i = 0; i < str.length(); i++)
	{
		int pos = ((string)HEX_CHARS).find(str[i], 0);
		binStr += bitset<4>(pos).to_string();
	}
	res.Input(binStr, 2);

	return res;
}


//=========BITWISE OPERATOR=========

//TOAN TU GAN
QInt QInt::operator =(const QInt& Q)
{
	for (int i = 0; i < 16; i++)
	{
		this->bytes[i] = Q.bytes[i];
	}
	return *this;
}
//TOAN TU CONG
QInt QInt::operator +(const QInt& Q) const
{			
	QInt res = Zero();
	try
	{
								//ÂM là 1. Dương là 0
		bool Check1Am = this->CheckNeg();
		bool Check2Am = Q.CheckNeg();
		res = Cong(*this, Q);
		if ((Check1Am + Check2Am != 1) && (Check1Am != res.CheckNeg()))
		{ //Neu hai so cong cung dau(00 & 11) nhung ket qua lai khac dau thi:
			throw "0";
		}

		return res;
	}
	catch (const char* thr)
	{
		cout << thr;
	}
}
//TOAN TU TRU
QInt QInt::operator -(const QInt& Q) const
{
	QInt res = Zero();
	try
	{ ///1 la AM
		bool Check1 = this->CheckNeg();
		bool Check2 = (Q.CheckNeg());
		res = Cong(*this, Q.Inverse());

		if (((Check1 == 0 && Check2 == 1) || (Check1 ==1 && Check2 ==0)) && (Check1 != res.CheckNeg()))
		{ //Neu AM - DUONG = DUONG HOAC DUONG - AM = AM => throw
			throw "0";
		}
		return res;
	}
	catch ( const char* thr)
	{
		cout << thr;
	}
	
}
//TOAN TU NHAN
QInt QInt::operator *(const QInt& B) const
{
	try
	{
		if (*this == Zero() || B == Zero()) return QInt(); //NEU 1 TRONG HAI = 0 THI KET QUA = 0
		QInt Min;
		Min.SetBit(16 * 8 - 1, 1);		
		QInt Negative;
		string soam1 = "-1";
		Negative.Input(soam1, 10);			//TRUONG HOP TRAN SO DAC BIET
		if ((*this == Min && B == Negative) || (*this == Negative && B == Min))
		{
			throw "0";
		}
		QInt A;   //A = bit so lon hon
		QInt Q = B;
		bool P = false;					//Q(-1) = 0
		for (int i = 0; i < QINT_SIZE * 8; i++)
		{
			bool lsbQ = Q.GetBit(0);		//LESS SIGNFICANT BIT: BIT PHAI NHAT
			if (lsbQ == false && P == true)		//Q0 Q(-1) = 01 => A = A + *this
				A = Cong(A, *this);				
			if (lsbQ == true && P == false)		//Q0 Q(-1) = 10 => A = A - *this
			{
				QInt temp = *this;
				A = Cong(A, temp.Inverse());
			}
			P = lsbQ;
			Q = Q >> 1;										//DICH PHAI [A,Q,Q(-1)]
			Q.SetBit(QINT_SIZE * 8 - 1, A.GetBit(0));
			A = A >> 1;
		}
		if (!((Q / B) == *this))
		{
			throw "0";
		}
		return Q;
	}
	catch (const char* thr)
	{
		cout << thr;
	}
}
//TOAN TU CHIA
QInt QInt::operator /(const QInt& B) const
{
	try
	{	//TH1: So chia bang 0
		if (B == Zero())
		{
			throw "0";
		}
		//TH2: So chia bang 1 hoac so bi chia bang 0
		if (B == One() || *this == Zero())
		{
			return *this;
		}

		//TH3: Truong hop tran so duy nhat cua phep chia
		QInt min;
		min.SetBit(QINT_SIZE * 8 - 1, 1);
		QInt negOne;
		string soam1 = "-1";
		negOne.Input(soam1, 10);
		if (*this == min && B == negOne)
		{
			throw "0";
		}

		QInt div; // ket qua phep chia
		QInt mod; // so du
		this->divide(B, div, mod);

		return div;
	}
	catch (const char* thr)
	{
		cout << thr;
	}
}
//TOAN TU AND
QInt QInt::operator &(const QInt& Q) const	
{
	QInt res;
	for (int i = 0; i < 16; i++)
	{
		res.bytes[i] = this->bytes[i] & Q.bytes[i];
	}
	return res;
}
//TOAN TU OR
QInt QInt::operator |(const QInt& Q) const	
{
	QInt res;
	for (int i = 0; i < 16; i++)
	{
		res.bytes[i] = this->bytes[i] | Q.bytes[i];
	}
	return res;
}
//TOAN TU XOR
QInt QInt::operator ^(const QInt& Q) const	
{
	QInt res;
	for (int i = 0; i < 16; i++)
	{
		res.bytes[i] = this->bytes[i] ^ Q.bytes[i];
	}
	return res;
}
//TOAN TU NOT
QInt operator ~(const QInt& Q)	
{
	QInt res;
	for (int i = 0; i < 16; i++)
	{
		res.bytes[i] = Q.bytes[i] ^ 0xFF;
	}
	return res;
}


//DICH PHAI SO HOC
QInt QInt::operator>>(int nums) const  
{
	QInt RESULT = *this;
	bool checkbit = RESULT.GetBit(127);
	RESULT = RESULT.ShiftRight(nums);
	if (checkbit)
	{
		for (int i = 127; i > 127 - nums; i--)
			RESULT.SetBit(i, checkbit);
	}

	return RESULT;
}
//DICH TRAI
QInt QInt::operator<<(int nums) const
{
	QInt RESULT = *this;
	while (nums > 0)
	{
		for (int i = 0; i < QINT_SIZE - 1; i++)
		{
			bool checkbit = (RESULT.bytes[i + 1] >> 7) & 1; //Kiem tra bit dau cua byte sau
			RESULT.bytes[i] = RESULT.bytes[i] << 1;			//Dich trai 1 bit
			if (checkbit)
			{
				RESULT.bytes[i] = (1 | RESULT.bytes[i]);
			}
		}
		RESULT.bytes[QINT_SIZE - 1] = RESULT.bytes[QINT_SIZE - 1] << 1;
		nums--;
	}

	return RESULT;
}
//XOAY TRAI
QInt QInt::rol(int nums) const 
{
	QInt RESULT = *this;
	while (nums > 0)
	{
		bool checkbit = ((RESULT.bytes[0] >> 7) & 1);						//Luu bit dau
		RESULT = RESULT << (1);												 //Dich trai 1 bit
		if (checkbit)
			RESULT.bytes[QINT_SIZE - 1] = (1 | RESULT.bytes[QINT_SIZE - 1]); //Dat lai bit cuoi
		nums--;
	}

	return RESULT;
}
//XOAY PHAI
QInt QInt::ror(int nums) const 
{
	QInt RESULT = *this;
	while (nums > 0)
	{
		bool checkbit = (RESULT.bytes[QINT_SIZE - 1] & 1);	 //Luu bit cuoi
		RESULT = RESULT.ShiftRight(1);						 //Dich phai 1 bit
		if (checkbit)
			RESULT.bytes[0] = ((1 << 7) | RESULT.bytes[0]);  // Dat lai bit dau
		nums--;
	}
	return RESULT;
}


//TRA VE GIA TRI THUC CUA MOT SO QINT THEO CO SO
string value(QInt A, int baseOut)
{
	string res;
	switch (baseOut)
	{
	case 2:
	{
		res =A. toBinStr();
		while (res[0] == '0' && res.length() > 1)
			res.erase(0, 1);
		return res;
		break;
	}
	case 10:
	{
		return binToDec(A);
		break;
	}
	case 16:
	{
		return binToHex(A);
		break;
	}
	}
}

//XU LI CAC PHEP TOAN 
string Process_QInt(string str, string fileout)
{
	fstream fout;
	fout.open(fileout, ios_base::out);
	if (!fout.is_open())
	{
		cout << "Khong the tao file ouput hoac duong dan khong hop le" << endl;
	}
		
		int count = 1;
		int Oprtype;
		for (int i = 0; i < str.length(); i++)
		{
			if (str[i] == ' ') count++;
		}
		if (count == 3)
		{
			Oprtype = 0;
			for (int i = 0; i < str.length(); i++)
			{
				if (str[i] == '~' || str[i] == 'r')
				{
					Oprtype = 1;
					break;
				}
			}
		}
		else Oprtype = 2;
		string p1, p2, opr, OpdA, OpdB;
		stringstream ssIn;
		ssIn << str;
		ssIn >> p1;
		if (count - Oprtype == 3)
			ssIn >> p2;
		else p2 = p1;
		opr = " ";
		switch (Oprtype)
		{
		case 0: ssIn >> OpdA;
			break;
		case 1: ssIn >> opr >> OpdA;
			break;
		case 2: ssIn >> OpdA >> opr >> OpdB;
			break;
		default:
			break;
		}
		QInt A;

		
		int baseIn = atoi(p1.c_str());
		int baseOut = atoi(p2.c_str());
		A.Input(OpdA, baseIn);
		if (opr == " ")
		{
			return value(A, baseOut);
		}
		else if (opr == "~")
		{
			return value((~A), baseOut);
		}
		else if (opr == "ror")
		{
			return value((A.ror(1)), baseOut);
		}
		else if (opr == "rol")
		{
			return value((A.rol(1)), baseOut);
		}
		else if (opr == "+")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A + B), baseOut);
		}
		else if (opr == "-")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A - B), baseOut);
		}
		else if (opr == "*")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A * B), baseOut);
		}
		else if (opr == "/")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A / B), baseOut);
		}
		else if (opr == "&")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A & B), baseOut);

		}
		else if (opr == "|")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A | B), baseOut);
		}
		else if (opr == "^")
		{
			QInt B;
			B.Input(OpdB, baseIn);
			return value((A ^ B), baseOut);
		}
		else if (opr == ">>")
		{
			int B = stoi(OpdB);
			return value((A >> B), baseOut);
		}
		else if (opr == "<<")
		{
			int B = stoi(OpdB);
			return value((A << B), baseOut);
		}
}
//DOC PHEP TINH TU FILE INPUT XUAT KET QUA RA FILE OUTPUT
void Out_File(string input, string output)
{
	vector<string> T;
	ifstream fin(input);
	ofstream fout(output);
	if (!fin.is_open())
	{
		cout << "Khong tim thay file input!!!" << endl;
	}
	if (!fout.is_open())
	{
		cout << "Khong the tao file ouput!!!" << endl;
	}

	//VONG LAP DOC DU LIEU VAO
	while (!fin.eof())
	{
		string input_line;

		getline(fin, input_line); //1 bieu thuc tren 1 dong

		try
		{
			string val = "";
			val = Process_QInt(input_line, output);

			T.push_back(val);			//Luu phep tinh vua tinh vao vector T
		}
		catch (exception* e)
		{
			fout << e->what() << endl;
			cout << e->what() << endl;
			free(e);
		}

	}
	fin.close();

	int i = 0;
	while (i < T.size())
	{
		fout << T.at(i);   //Xuat tung phan tu cua vector vao file output.txt
		i++;
		if (i < T.size()) fout << endl;
	}
	fout.close();
}