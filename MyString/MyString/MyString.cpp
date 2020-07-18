#include "MyString.h"

//constructor & destructor
MyString::MyString()
{
	strLength = 0;
	Mstr = NULL;
	strCap = 0;
}

MyString::MyString(const MyString& str)
{
	strLength = str.strLength;
	Mstr = new char(strLength + 1);
	Mystrcpy(Mstr, str.Mstr);
}

MyString::MyString(const char* arr)
{
	int l = Mystrlen(arr);
	strLength = l;
	Mstr = new char[l + 1];
	Mystrcpy(Mstr, arr);
}

MyString::MyString(char c, int n)
{
	strLength = n;
	Mstr = new char[n + 1];
	int i;
	for (i = 0; i < n; i++)
	{
		Mstr[i] = c;
	}
	Mstr[i] = '\0';
}

MyString::MyString(int len)
{
	this->strLength = len;
	Mstr = new char[len];
}

MyString::~MyString()
{
	strLength = 0;
	delete[]Mstr;
}

//My Functions
int MyString::Mystrlen(const char* arr)
{
	int i = 0;
	while (arr[i] != '\0') i++;
	return i;
}

void MyString::Mystrcpy(char*& arr1, const char* arr2)
{
	int l = Mystrlen(arr2);
	int i;
	for (i = 0; i < l; i++)
	{
		arr1[i] = arr2[i];
	}
	arr1[i] = '\0';
}

size_t MyString::_getLength(const MyString& str, size_type pos, size_t len) const {
	if (len == npos)
		len = strLength - pos;

	if (pos + len > str.strLength)
	{
		throw;
	}
	return len;
}

void MyString::Myalloc(char*& buffer, const size_t n)  const
{
	if (buffer)
		throw;
	buffer = new char[n + 1]();
}

void MyString::Mysubstr(char*& buffer, const char* other, size_type pos, size_t len) const
{

	if (other == nullptr) {
		throw;
	}
	Myalloc(buffer, len);
	for (size_type i = 0; i < len; ++i)
		buffer[i] = other[pos + i];
}

bool MyString::Myfind_compare(const char* other, size_t len, size_type pos) const 
{
	for (size_type i = 1; i < len; ++i)
		if (operator[](pos + i) != *(other + i))
			return false;
	return true;
}

size_t MyString::Myfind(const char* other, size_t len, size_type pos) const
{
	size_t temp = npos;
	if (pos == npos)
		pos = strLength - 1;
	for (; pos <= strLength - len; ++pos)
		if (operator[](pos) == *other && Myfind_compare(other, len, pos)) {
			temp = pos;
			break;
		}
	return temp;
}

size_t MyString::Myrfind(const char* other, size_t len, size_type pos) const
{
	size_t temp = npos;
	if (pos == npos || pos + len > strLength + 1)
		pos = strLength - len + 1;

	for (int i = pos; 0 <= i; --i)
		if (operator[](i) == *other && Myfind_compare(other, len, i)) {
			temp = i;
			break;
		}
	return temp;
}

//operator=
MyString& MyString::operator = (const MyString& s)
{
	this->Mstr = s.Mstr;
	this->strLength = s.strLength;
	return *this;
}

//Iterators:


//Capacity:
size_t MyString::size()
{
	return this->strLength;
}

size_t MyString::length()
{
	return this->strLength;
}

size_t MyString::max_size() const
{
	return npos - 1;
}

void MyString::resize(size_t n)
{
	for (int i = n; i < this->strLength; i++)
	{
		Mstr[i] = NULL;
	}
	this->strLength = n;
}

size_t MyString::capacity() const
{
	return strCap;
}

void MyString::clear()
{
	this->Mstr = NULL;
	this->strLength = 0;
}

bool MyString::empty() const
{
	if (this->strLength == 0) return true;
	else return false;
}

//Element access:
const char& MyString::operator [] (size_type i) const
{
	return *(Mstr + i);
}

char& MyString::operator [] (size_type i)
{
	return *(Mstr + i);
}

char& MyString::at(size_t pos)
{
	return Mstr[pos];
}

char MyString::back()
{
	return Mstr[strLength];
}

char MyString::front()
{
	return Mstr[0];
}

//Modifiers:
MyString& MyString::operator += (const char* str)
{
	char* tmp = NULL;
	Mystrcpy(tmp, this->Mstr);
	this->strLength += Mystrlen(str);
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	unsigned i = 0;
	while (tmp[i] != '\0')
	{
		this->Mstr[i] = tmp[i];
		i++;
	}

	unsigned j = i, k = 0;
	while (str[k] != '\0')
	{
		this->Mstr[j] = str[k];
		j++;
		k++;
	}
	this->Mstr[j] = '\0';

	delete[]tmp;
	return *this;
}

MyString& MyString::operator += (const MyString& s)
{
	size_t FirstSize = s.strLength;
	char* tmp = NULL;
	Mystrcpy(tmp, this->Mstr);
	int n = this->strLength + s.strLength;
	this->strLength = n;
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	size_t i = 0;
	while (tmp[i] != '\0')
	{
		this->Mstr[i] = tmp[i];
		i++;
	}
	size_t j = i, k = 0;
	while (k < FirstSize)
	{
		this->Mstr[j] = s.Mstr[k];
		j++;
		k++;
	}

	this->Mstr[j] = '\0';

	delete[]tmp;
	return *this;

}

MyString& MyString::operator += (const char c)
{
	char* tmp = NULL;
	Mystrcpy(tmp, this->Mstr);
	this->strLength = Mystrlen(tmp) + 1;
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	size_t i = 0;
	while (tmp[i] != '\0')
	{
		this->Mstr[i] = tmp[i];
		i++;
	}
	this->Mstr[i] = c;
	this->Mstr[i + 1] = '\0';

	delete[]tmp;
	return *this;
}

MyString& MyString::append(const MyString& str)
{
	*this = *this + str;
	return *this;
}

MyString& MyString::append(const MyString& str, size_t subpos, size_t sublen)
{
	char* tmp = NULL;

	Mysubstr(tmp, str.Mstr, subpos, sublen);

	*this = *this + tmp;

	delete[] tmp;
	return *this;
}

MyString& MyString::append(const char* str, size_t n)
{
	char* tmp = NULL;
	tmp = new char[n + 1];

	for (size_t i = 0; i < n; i++)
		tmp[i] = str[i];

	tmp[n] = '\0';
	*this = *this + tmp;
	delete[] tmp;
	return *this;
}

MyString& MyString::append(const char* str)
{
	*this += str;
	return *this;
}

MyString& MyString::append(size_t n, char c)
{
	char* tmp = NULL;
	tmp = new char[n + 1];

	for (size_t i = 0; i < n; i++)
		tmp[i] = c;

	tmp[n] = '\0';

	*this = *this + tmp;
	delete[] tmp;
	return *this;
}

void MyString::push_back(char c)
{
	*this = *this + c;
}

MyString& MyString::assign(const MyString& str)
{
	return *this = MyString(str);
}

MyString& MyString::assign(const MyString& substr, size_t subpos, size_t sublen)
{

	char* tmp = NULL;
	Mysubstr(tmp, substr.Mstr, subpos, sublen);

	*this = MyString(tmp);

	delete[] tmp;
	return *this;
}

MyString& MyString::assign(const char* str)
{
	*this = MyString(str);
	return *this;
}

MyString& MyString::assign(const char* str, size_t n)
{
	char* tmp = NULL, * strcpy = NULL;
	Mystrcpy(strcpy, str);
	Mysubstr(tmp, strcpy, 0, n);

	*this = MyString();
	*this = tmp;

	delete[] tmp;
	delete[] strcpy;
	return *this;
}

MyString& MyString::assign(size_t n, char c)
{
	MyString tmp;
	tmp.append(n, c);
	*this = MyString();
	*this = tmp;
	return *this;
}

MyString& MyString::insert(size_t pos, const MyString& str)
{
	if (pos < 0 || pos > this->strLength) return *this;
	size_t   S_Of_In_Str = Mystrlen(str.Mstr);
	char* temp = NULL;

	Mystrcpy(temp, this->Mstr);

	*this = MyString();
	this->strLength = S_Of_In_Str + Mystrlen(temp);
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	size_t i = 0, j = 0;
	size_t StrSize = Mystrlen(str.Mstr);
	while (i < this->strLength)
	{
		if (i == pos)
		{
			for (size_t k = 0; k < StrSize; k++)
			{
				this->Mstr[i] = str.Mstr[k];
				i++;
			}
			continue;
		}
		else
		{
			this->Mstr[i] = temp[j];
			j++;
		}
		i++;
	}
	this->Mstr[i] = '\0';

	delete[] temp;
	return *this;
}

MyString& MyString::erase(size_t pos, size_t len)
{
	if (pos < 0 || pos > this->strLength - 1)
	{
		cout << "Out of range!" << endl;
		return *this;
	}

	char* Strempty = NULL;
	Mystrcpy(Strempty, this->Mstr);
	size_t i = pos, j = 0;
	for (size_t k = ((pos - 1) + len) + 1; k < this->strLength; k++)
	{
		Strempty[i] = Strempty[k];
		i++;
		j++;
	}
	Strempty[pos + j] = '\0';
	*this = MyString();
	this->strLength = Mystrlen(Strempty);
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];
	*this = Strempty;
	delete[]Strempty;
	return *this;
}

MyString& MyString::replace(size_t pos, size_t len, const MyString& str)
{

	if (pos < 0 || pos > this->strLength) return *this;

	size_t  Size_Of_Repl_Str = Mystrlen(str.Mstr);
	char* temp = NULL;
	Mystrcpy(temp, this->Mstr);

	*this = MyString();
	this->strLength = Size_Of_Repl_Str + Mystrlen(temp);
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	size_t i = 0, j = 0;
	while (i < this->strLength)
	{
		if (i == pos)
		{
			for (size_t k = 0; k < Size_Of_Repl_Str; k++)
			{
				this->Mstr[i] = str.Mstr[k];
				i++;
			}
			j = pos + len;
			continue;
		}
		else
		{
			this->Mstr[i] = temp[j];
			j++;
		}
		i++;
	}
	this->Mstr[i] = '\0';

	delete[] temp;
	return *this;
}

MyString& MyString::replace(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen)
{

	if ((pos < 0 || pos >= this->strLength) || (subpos < 0 || subpos >= str.strLength))
		return *this;

	char* SubedStr = NULL;
	Mysubstr(SubedStr, str.Mstr, subpos, sublen);
	this->replace(pos, len, SubedStr);

	delete[]SubedStr;
	return *this;
}

MyString& MyString::replace(size_t pos, size_t len, const char* str)
{

	if (pos < 0 || pos > this->strLength) return *this;

	size_t  Size_Of_Repl_Str = Mystrlen(str);
	char* temp = NULL;
	Mystrcpy(temp, this->Mstr);

	*this = MyString();
	this->strLength = Size_Of_Repl_Str + Mystrlen(temp);
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	size_t i = 0, j = 0;
	while (i < this->strLength)
	{
		if (i == pos)
		{
			for (size_t k = 0; k < Size_Of_Repl_Str; k++)
			{
				this->Mstr[i] = str[k];
				i++;
			}
			j = pos + len;
			continue;
		}
		else
		{
			this->Mstr[i] = temp[j];
			j++;
		}
		i++;
	}
	this->Mstr[i] = '\0';

	delete[] temp;
	return *this;
}

MyString& MyString::replace(size_t pos, size_t len, const char* str, size_t n)
{
	if (pos < 0 || pos > this->strLength) return *this;
	char* strcpy = NULL, * mid = NULL;
	Mystrcpy(strcpy, str);
	Mysubstr(mid, strcpy, 0, n);

	MyString lhs, rhs;
	rhs = this->substr(pos + len, pos + len);
	lhs = this->substr(0, pos);

	*this = MyString();
	*this = lhs + mid;
	*this += rhs;


	delete[] strcpy;
	delete[] mid;
	return *this;
}

MyString& MyString::replace(size_t pos, size_t len, size_t n, char c)
{
	if (pos < 0 || pos > this->strLength)	return *this;

	MyString tmp;
	tmp = *this;
	this->clear();
	size_t new_size = (tmp.strLength - len) + n;
	this->strLength = new_size;
	this->strCap = this->strLength + 16;
	this->Mstr = new char[new_size + 16];

	if (len > n || len == n)
	{
		size_t i = 0, j = 0;
		while (i < tmp.strLength)
		{
			if (i == pos)
			{
				for (size_t k = 0; k < n; k++)
				{
					this->Mstr[i] = c;
					i++;
				}
				j = pos + len;
				continue;
			}
			else
			{
				this->Mstr[i] = tmp[j];
				j++;
			}
			i++;
		}
		this->Mstr[i] = '\0';
	}
	else
	{
		char* SubedStr = NULL;
		size_t subpos = pos + len;
		Mysubstr(SubedStr, tmp.Mstr, subpos, tmp.strLength - subpos);

		size_t i = 0, j = 0;
		while (i < pos + len)
		{
			if (i == pos)
			{
				for (size_t k = 0; k < n; k++)
				{
					this->Mstr[i] = c;
					i++;
				}
				j = pos + len;
				continue;
			}
			else
			{
				this->Mstr[i] = tmp[j];
				j++;
			}
			i++;
		}
		this->Mstr[i] = '\0';
		*this += SubedStr;
		delete[]SubedStr;
	}
	return *this;
}

void MyString::swap(MyString& str)
{
	MyString tmp;
	tmp = *this;
	this->clear();
	*this = str;
	str.clear();
	str = tmp;
}

void MyString::pop_back()
{
	char* tmp = NULL;
	Mystrcpy(tmp, this->Mstr);
	this->clear();
	this->strLength = Mystrlen(tmp) - 1;
	this->strCap = this->strLength + 16;
	this->Mstr = new char[this->strCap];

	for (size_t i = 0; i < this->strLength; i++)
		this->Mstr[i] = tmp[i];

	this->Mstr[this->strLength] = '\0';
	delete[] tmp;
}

//String operations:
const char* MyString::c_str() const
{
	return Mstr;
}

size_t MyString::copy(char* s, size_t len, size_type pos) const
{
	if (!s)
		throw;
	len = _getLength(*this, pos, len);
	for (size_type i = 0; i < len; ++i)
		* (s + i) = operator[](pos + i);
	return len;
}

size_t MyString::find(const MyString& other, size_type pos) const
{
	return Myfind(other.Mstr, other.strLength, pos);
}

size_t MyString::find(const char* s, size_type pos) const
{
	return Myfind(s, strlen(s), pos);
}

size_t MyString::find(const char* s, size_type pos, size_type n) const
{
	return Myfind(s, n, pos);
}

size_t MyString::find(char c, size_type pos) const
{
	return Myfind(&c, 1, pos);
}
size_t MyString::rfind(const MyString& other, size_type pos) const
{
	return Myrfind(other.Mstr, other.strLength, pos);
}

size_t MyString::rfind(const char* s, size_type pos) const
{
	return  Myrfind(s, strlen(s), pos);
}

size_t MyString::rfind(const char* s, size_type pos, size_t n) const
{
	return Myrfind(s, n, pos);
}

size_t MyString::rfind(char c, size_type pos) const
{
	return Myrfind(&c, 1, pos);
}

MyString MyString::substr(size_type pos , size_t len ) const
{
	len = _getLength(*this, pos, len);
	char* buffer = nullptr;
	Mysubstr(buffer, Mstr, pos, len);
	MyString To_Return(buffer);
	delete[]buffer;
	return To_Return;
}

int MyString::compare(const MyString& str) const
{
	if (this->Mstr == str.Mstr) return 0;
	else return 1;
}

//Non-member function overloads
MyString operator + (const MyString& lhs, const MyString& rhs)
{
	MyString temp = lhs;
	temp += rhs;
	return temp;
}

MyString operator + (const MyString& lhs, const char* rhs)
{
	MyString temp = lhs;
	temp += rhs;
	return temp;
}

MyString operator + (const char* lhs, const MyString& rhs)
{
	MyString temp = lhs;
	temp += rhs;
	return temp;
}

MyString operator + (const MyString& lhs, char rhs)
{
	MyString temp = lhs;
	temp += rhs;
	return temp;
}

MyString operator + (char lhs, const MyString& rhs)
{
	MyString temp = lhs;
	temp += rhs;
	return temp;
}

void MyString::swap(MyString& x, MyString& y)
{
	x.swap(y);
}

istream& operator >> (istream& is, MyString& str)
{
	cout << "Nhap chieu dai chuoi: ";
	is >> str.strLength;
	str.Mstr = new char[str.strLength + 1];
	is.ignore();
	is.getline(str.Mstr, str.strLength + 1);
	return is;
}

ostream& operator <<(ostream& os, const MyString& str)
{
	os << str.Mstr;
	return os;
}

bool MyString::operator == (const MyString& s)
{
	for (int i = 0; i < s.strLength; i++)
		if (this->Mstr[i] != s.Mstr[i])
			return false;
	return true;
}

bool MyString::operator != (const MyString& s)
{
	return !operator==(s);
}

bool MyString::operator >= (const MyString& s)
{
	for (int i = 0; i < s.strLength; i++)
		if (this->Mstr[i] < s.Mstr[i])
			return false;
	return true;
}

bool MyString::operator < (const MyString& s)
{
	return !operator>=(s);
}

bool MyString::operator <= (const MyString& s)
{
	for (int i = 0; i < s.strLength; i++)
		if (this->Mstr[i] > s.Mstr[i])
			return false;
	return true;
}

bool MyString::operator > (const MyString& s)
{
	return !operator<=(s);
}
