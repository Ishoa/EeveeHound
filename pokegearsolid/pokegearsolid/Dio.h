#pragma once
#include <string>
#include <fstream>
#include <stdio.h>
#include "Defines.h"

#define textWait 20000000
#define textDebug 2

using namespace std;

//char TextBuffer[100];
//static RECT textbox;

#define maxspoken 2
#define maxpics 4

class Dio
{
private:
	string name;
	string text;
	TextStruct speaker[maxspoken];
	renderInfo pics[maxpics];
	renderInfo salami;
	bool readname;
	bool readtext;
	wchar_t tempname[190];
	wchar_t temptext[190];
	ifstream infile;
public:
	Dio::Dio();
	void Dio::init(TextureStruc[]);
	void update(char[],bool&,bool&);
	void getRend(renderInfo[],int& NumSprit,TextStruct[],int& NumText);
	string getname(){return name;}
	string gettext(){return text;}
	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int)s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0); 
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}
};