#ifndef _PATH_H_
#define _PATH_H_

#include "main.h"

#include <string>
#include <vector>

enum Attribute
{
	ReallocatedSectorsCount, // 0x05
	ReallocationEventCount, // 0xC4
	CurrentPendingSectorCount, // 0xC5
	UncorrectableSectorCount, // 0xC6
};

string TCHARToString(const TCHAR* ptsz);
string GetPATH();
vector<string> READFILE(string p);
vector<string> GetDiskPATH(vector<string> disk);
vector<vector<string>> GetCSVPATH(vector<string>& disk);


#endif