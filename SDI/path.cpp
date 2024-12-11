#define _CRT_SECURE_NO_WARNINGS

#include "path.h"

#include <io.h>
#include <ShlObj_core.h>

string GetPATH()
{
	TCHAR pf[MAX_PATH];
	SHGetSpecialFolderPath(0, pf, CSIDL_PROGRAM_FILES, FALSE);
	string p = TCHARToString(pf);
	p.append("\\CrystalDiskInfo\\Smart\\*.*");

	return p;
}

vector<string> GetDiskPATH(vector<string> disk)
{
	string p = GetPATH();
	string s;
	p = p.substr(0, p.size() - 3);

	disk.erase(disk.begin() + 0); // "."
	disk.erase(disk.begin() + 0); // ".."

	for (int i = 0; i < disk.size(); i++)
	{
		if (disk[i].compare("Exchange.ini") == 0) { disk.erase(disk.begin() + i); }
	}

	for (int i = 0; i < disk.size(); i++)
	{
		s = p;
		disk[i] = s.append(disk[i]);
	}

	return disk;
}
string TCHARToString(const TCHAR* ptsz) // https://dhkvmf88.tistory.com/56
{
	int len = wcslen((wchar_t*)ptsz);
	char* psz = new char[2 * len + 1];
	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	string s = psz;
	delete[] psz;
	return s;
}
vector<string> READFILE(string p) // https://nauco.tistory.com/5
{
	vector<string> return_;

	_finddata_t fd;
	intptr_t handle = _findfirst(p.c_str(), &fd);

	if (handle == -1L)
		return return_;

	int result = 0;
	do {
		return_.push_back(fd.name);
		result = _findnext(handle, &fd);
	} while (result != -1);

	_findclose(handle);
	return return_;
}



vector<vector<string>> GetCSVPATH(vector<string>& disk)
{
	vector<vector<string>> csvpath(disk.size(), vector<string>(4));


	for (int i = 0; i < disk.size(); i++)
	{
		if (disk[i].find("SSD") != string::npos)
		{
			csvpath[i][0] = disk[i] + "\\Life.csv";
		}
		else
		{
			csvpath[i][0] = disk[i] + "\\ReallocatedSectorsCount.csv";
			csvpath[i][1] = disk[i] + "\\ReallocationEventCount.csv";
			csvpath[i][2] = disk[i] + "\\CurrentPendingSectorCount.csv";
			csvpath[i][3] = disk[i] + "\\UncorrectableSectorCount.csv";
		}
	}

	return csvpath;
}
