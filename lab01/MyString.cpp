// TODO: 12
// CS251 Data Structures
// String Implementation
// IMPORTANT: Do not use any of the functions in the string C runtime library
// Example. Do not use strcpy, strcmp, etc. Implement your own

// IMPORTANT: See the MyString.h file for a description of
// what each method needs to do.

#include <stdio.h>
#include <string.h>
#include "MyString.h"
#include <iostream>

// My own implementation of strlen
int
MyString::slength(const char *s) const
{
	int len;
	for(len = 0; s[len] != '\0'; len++);
	return len;
}

// Initialize _s. Allocate memory for _s and copy s into _s
void
MyString::initialize(const char * s)
{
	int slen = slength(s);
	_s = new char[slen + 1];
	int i;
	for(i = 0; i < slen; i++){
		_s[i] = s[i];
	}
	_s[i] = '\0';
}

// Create a MyString from a C string
MyString::MyString(const char * s)
{
	initialize(s);
}

// Create a MyString from a copy of another string
MyString::MyString(const MyString &s)
{
	initialize(s._s);	
}

// Create a MyString with an empty string
MyString::MyString()
{
	_s = new char[1];
	*_s = 0;
}

// Assignment operator. Without this operator the assignment is
// just a shallow copy that will copy the pointer _s. If the original _s
// goes away then the assigned _s will be a dangling reference.
MyString &
MyString::operator = (const MyString & other) 
{
	delete[] _s;
	initialize(other._s);
	return *this;
}

// Obtain a substring of at most n chars starting at location i
// if i is larger than the length of the string return an empty string.
MyString
MyString::substring(int i, int n)
{
	if(i > length())	return MyString();
	char * subStr = new char [n + 1];
	int j = 0;
	for(; j < n; j++)
	{
		subStr[j] = _s[i + j];
	}
	subStr[j] = '\0';
	return MyString(subStr);
}	

// Remove at most n chars starting at location i
void
MyString::remove(int i, int n)
{
	if(i > length())	return;
	int j = 0;
	for(j = 0; j < n; j++)//makes the loop run n times
	{
		for(int k = i; k < length(); k++)
		{
			_s[k] = _s[k + 1];
		}	
	}
}

// Return true if strings "this" and s are equal
bool
MyString::operator == (const MyString & s)
{
	int i = 0;
	while(this->_s[i] != '\0' && s._s[i] != '\0')
	{
		if(this->_s[i] != s._s[i])
		{
			return false;
		}
		i++;
	}
	return true;
}


// Return true if strings "this" and s are not equal
bool
MyString::operator != (const MyString &s)
{
	int i = 0;
	while(this->_s[i] != '\0' && s._s[i] != '\0')
	{
		if(this->_s[i] != s._s[i])
		{
			return true;
		}
		i++;
	}
	return false;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator <= (const MyString &s)
{
	int i = 0;
	while(this->_s[i] != '\0' && s._s[i] != '\0')
	{
		if(this->_s[i] != s._s[i])
		{
			return (this->_s[i] <= s._s[i]);
		}
		i++;
	}
	return true;
}

// Return true if string "this" and s is less or equal
bool
MyString::operator > (const MyString &s)
{
	int i = 0;;
	while(this->_s[i] != '\0' && s._s[i] != '\0')
	{
		if(this->_s[i] != s._s[i])
		{
			return (this->_s[i] > s._s[i]);
		}
		i++;
	}
	return false;
}

// Return character at position i
char
MyString::operator [] (int i)
{
	return (this->_s[i]);
}

// Return C representation of string
const char *
MyString::cStr()
{
	return _s;
}

// Get string length of this string.
int
MyString::length() const
{
	return slength(_s);
}

// Destructor. Deallocate the space used by _s
MyString::~MyString()
{
	delete[] _s;
}

// Concatanate two strings (non member method)
MyString operator + (const MyString &s1, const MyString &s2)
{
	MyString str;
	str = MyString();
	int len1 = s1.length();
	int len2 = s2.length();
	str._s = new char[len1 + len2 + 1];
	int i = 0;
	for(i = 0; i < len1; i++)
	{
		str._s[i] = s1._s[i];
	}
	for(i = 0; i <= len2; i++)
	{
		str._s[len1 + i] = s2._s[i];
	}
	return str;
}

/* Break a string into substrings of letters, e.g "A dog and a hyper-sphere"
breaks into <"A", "dog", "and", "a", "hyper", "sphere">.  The input is a string
and the output is a vector of strings. */
std::vector<MyString> words (MyString s) {
	std::vector<MyString> sub;
	const char * str = s.cStr();
	int i = 0;
	int j = 0;
	int k = 0;
	int len = s.length();
	int len1 = 0;
	while(1){
		char * str1;
		j = 0;
		len1 = 0;
		while(str[k] != ' ' && str[k] != '-' && str[k] != '\0'){
			k++;
			len1++;
		}
		k++;
		str1 = new char[len1 + 1];
		while(str[i] != ' ' && str[i] != '-' && str[i] != '\0'){
			str1[j++] = str[i++];
		}
		str1[len1] = '\0';
		i++;
		MyString mys = MyString(str1);
		sub.push_back(mys);
		delete [] str1;
		if(str[i - 1] == '\0')	break;
	}
	return sub;
}

/*
Convert a roman numberal into a number, e.g. "CLXIV" converts to 164.  The
input is a roman numeral expressed as a string whose characters are "I", "V",
"X", "L", and "C".  The output is a positive integer.
*/
unsigned int roman (MyString s) {
	int i = 0;
	const char * number = s.cStr();
	unsigned int n = 0;
	int len = s.length();
	while(number[i] != '\0'){
		switch(number[i]){
			case 'I':	{
						if(i != len - 1 && number[i + 1] == 'V'){
							n += 4;
							i += 2;
							break;
						}
						else if(i != len - 1 && number[i + 1] == 'X'){
							n += 9;
							i += 2;
							break;
						}
						else{
							n += 1;
							i++;
							break;
						}
					}
			
			case 'X':	{
						if(i != len - 1 && number[i + 1] == 'L'){
							n += 40;
							i += 2;
							break;
						}
						else if(i != len - 1 && number[i + 1] == 'C'){
							n += 90;
							i += 2;
							break;
						}
						else{
							n += 10;
							i++;
							break;
						}
					}
			
			case 'C':	{
						if(i != len - 1 && number[i + 1] == 'D'){
							n += 400;
							i += 2;
							break;
						}
						else if(i != len - 1 && number[i + 1] == 'M'){
							n += 900;
							i += 2;
							break;
						}
						else{
							n += 100;
							i++;
							break;
						}
					}
			case 'V':	{
						n += 5;
						i++;
						break;
					}
			case 'L':	{
						n += 50;
						i++;
						break;
					}
			case 'D':	{
						n += 500;
						i++;
						break;
					}
			case 'M':	{
						n += 1000;
						i++;
						break;
					}

		}
	}
	return n;
}

