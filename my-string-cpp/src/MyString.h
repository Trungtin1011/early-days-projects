#pragma once
#include <iostream>
using namespace std;

using size_type = size_t;
static const size_t npos = -1;
class MyString
{
private:
	char* Mstr;
	size_t strLength;
	size_t strCap;

	size_t increaseBy = 15;
public:

	//constructor & destructor
	MyString();
	MyString(const MyString& str);
	MyString(const char* arr);
	MyString(char c, int n);
	MyString(int len);
	~MyString();

	//My Functions
	int Mystrlen(const char* arr);
	void Mystrcpy(char*& arr1, const char* arr2);	
	size_t _getLength(const MyString& str, size_type pos, size_t len) const;
	void Myalloc(char*& buffer, const size_t n)  const;
	void Mysubstr(char*& buffer, const char* other, size_type pos, size_t len) const;
	bool Myfind_compare(const char* other, size_t len, size_type pos) const;
	size_t Myfind(const char* other, size_t len, size_type pos) const;
	size_t Myrfind(const char* other, size_t len, size_type pos) const;

	//operator=
	MyString& operator = (const MyString& s);

	//Iterators:


	//Capacity:
	size_t size();
	size_t length();
	size_t max_size() const;
	void resize(size_t n);
	size_t capacity() const;
	void clear();
	bool empty() const;

	//Element access:
	const char& operator [] (size_type i) const;
	char& operator [] (size_type i);
	char& at(size_t pos);
	char back();
	char front();

	//Modifiers:
	MyString& operator += (const char* str);
	MyString& operator += (const MyString& s);
	MyString& operator += (const char c);
	MyString& append(const MyString& str);
	MyString& append(const MyString& str, size_t subpos, size_t sublen);
	MyString& append(const char* str, size_t n);
	MyString& append(const char* str);
	MyString& append(size_t n, char c);
	void push_back(char c);
	MyString& assign(const MyString& str);
	MyString& assign(const MyString& substr, size_t subpos, size_t sublen);
	MyString& assign(const char* str);
	MyString& assign(const char* str, size_t n);
	MyString& assign(size_t n, char c);
	MyString& insert(size_t pos, const MyString& str);
	MyString& erase(size_t pos, size_t len);
	MyString& replace(size_t pos, size_t len, const MyString& str);
	MyString& replace(size_t pos, size_t len, const MyString& str, size_t subpos, size_t sublen);
	MyString& replace(size_t pos, size_t len, const char* str);
	MyString& replace(size_t pos, size_t len, const char* str, size_t n);
	MyString& replace(size_t pos, size_t len, size_t n, char c);
	void swap(MyString& str);
	void pop_back();

	//String operations:
	const char* c_str() const;
	size_t copy(char* s, size_t len, size_type pos) const;
	size_t find(const MyString& other, size_type pos) const;
	size_t find(const char* s, size_type pos) const;
	size_t find(const char* s, size_type pos, size_type n) const;
	size_t find(char c, size_type pos) const;
	size_t rfind(const MyString& other, size_type pos) const;
	size_t rfind(const char* s, size_type pos) const;
	size_t rfind(const char* s, size_type pos, size_t n) const;
	size_t rfind(char c, size_type pos) const;
	MyString substr(size_type pos = 0, size_t len = npos) const;
	int compare(const MyString& str) const;

	//Non-member function overloads
	friend MyString operator + (const MyString& lhs, const MyString& rhs);
	friend MyString operator +(const MyString& lhs, const char* rhs);
	friend MyString operator + (const char* lhs, const MyString& rhs);
	friend MyString operator + (const MyString& lhs, char rhs);
	friend MyString operator + (char lhs, const MyString& rhs);
	void swap(MyString& x, MyString& y);
	friend istream& operator >> (istream& is, MyString& str);
	friend ostream& operator <<(ostream& os, const MyString& str);
	bool operator == (const MyString& s);
	bool operator != (const MyString& s);
	bool operator >= (const MyString& s);
	bool operator < (const MyString& s);
	bool operator <= (const MyString& s);
	bool operator > (const MyString& s);

};