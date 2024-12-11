#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <algorithm>
#include <fstream>

#include "main.h"
#include "path.h"
#include "util.h"
#include "CSVReader.h"

int ReadCSV(string* path);
int y;

int THRESHOLD_0x05 = 0;
int THRESHOLD_0xC4 = 0;
int THRESHOLD_0xC5 = 0;
int THRESHOLD_0xC6 = 0;
int LIFE = 10;

int threshold[5] = { THRESHOLD_0x05 , THRESHOLD_0xC4, THRESHOLD_0xC5, THRESHOLD_0xC6, LIFE };
string s[5] = { "Threshold Value of ReallocatedSectorsCount(0x05): ",
	"Threshold Value of ReallocationEventCount(0xC4): ",
	"Threshold Value of CurrentPendingSectorCoun(0xC5): ",
	"Threshold Value of UncorrectableSectorCount(0xC6): ",
	"Threshold Value of LIFE(for SSD): " };

int main(int argc, char** argv) {
	init();
	while (TRUE) {
		y = 5;
		titleDraw();
		int menuCode = menuDraw(45, 20);
		if (menuCode == 0) {
			// Execute 1
			system("cls");
			vector<string> disk = READFILE(GetPATH());
			if (!disk.empty())
			{
				vector<string> dpath = GetDiskPATH(disk);
				vector<vector<string>> path = GetCSVPATH(dpath);

				for (int i = 0; i < path.size(); i++)
				{
					int count[5] = { 0, };
					for (int j = 0; j < path[i].size(); j++)
					{
						if (path[i][j] != "")
						{
							count[j] = ReadCSV(&path[i][j]);
							count[4] += count[j];
						}
					}
					if (path[i][0].find("SSD") != string::npos)		// SSD
					{
						if (count[4] > 10 && count[4] <= 100)
						{
							gotoxy(35, ++y);
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Good" << endl << endl;
							system("color 20");
						}
						else if (count[4] <= 10 && count[4] >= 0)
						{
							cout << endl;
							gotoxy(35, ++y);;
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Caution" << endl << endl;
							system("color E0");
						}
						else if (count[4] < threshold[4])
						{
							cout << endl;
							gotoxy(30, ++y);;
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Bad" << endl;
							cout << "			" << "Life RAW Value: " << count << "		Threshold Value: " << threshold[4] << endl << endl;
							system("color 47");
						}
						else
						{
							cout << endl;
							gotoxy(35, ++y);
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Unknown" << endl;
							cout << endl << "Please check your Disk connection and saved S.M.A.R.T. csv file(s) via CrystalDiskInfo" << endl << endl;
							system("color 80");
						}
					}
					else // HDD
					{
						if (count[4] == 0)
						{
							cout << endl;
							gotoxy(35, ++y);
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Good" << endl << endl;
							system("color 20");
						}
						else if (count[4] > 0 && (count[0] <= threshold[0] || count[1] || threshold[1] || count[2] <= threshold[2] || count[3] <= threshold[3]))
						{
							cout << endl;
							gotoxy(35, ++y);
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Caution" << endl << endl;
							system("color E0");
						}
						else if (count[0] > threshold[0] && count[1] > threshold[1] && count[2] > threshold[2] && count[3] > threshold[3])
						{
							cout << endl;
							gotoxy(35, ++y);;
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Bad" << endl << endl;
							for (int i = 0; i < 4; i++)
								cout << "			" << s[i] + "RAW Value: " << count[i] << "		Threshold Value: " << threshold[i] << endl << endl;
							system("color 47");
						}
						else
						{
							cout << endl;
							gotoxy(35, ++y);
							cout << dpath[i].substr(dpath[i].find_last_of("\\") + 1) << " Disk Status: Unknown" << endl;
							cout << endl << "Please check your Disk connection and saved S.M.A.R.T. csv file(s) via CrystalDiskInfo" << endl << endl;
							system("color 80");
						}
					}
					system("pause");
					system("cls");
					y = 5;
				}
			}
			else
			{
				gotoxy(35, y);
				cout << "Unable to find the disk information in S.M.A.R.T. directory" << endl;
				cout << "Please check whether your directory is valid or you've ever executed CrystalDiskInfo" << endl << endl;
				system("color 80");
				system("pause");
				system("cls");
			}
		}
		else if (menuCode == 1) {
			system("cls");
			ShowThreShold();
		}
		else if (menuCode == 2) {
			return FALSE;
		}
		system("color 07");
	}
	
	return 0;
}

int ReadCSV(string* path)
{
#ifdef _WIN32
	SetConsoleOutputCP(CP_UTF8);
#endif
	CSVReader reader;

	try {
		reader.ReadFile(*path);

		gotoxy(5, y++);
		cout << "Reading a file (" + *path + ")" << endl;
		return max(0, stoi(reader[reader.GetRowCount() - 1][1]));
	}
	catch (ifstream::failure& ex) {
		cout << ex.what() << endl;
		return 0;
	}
	catch (exception ex)
	{
	}
	return -1;
}

void ShowThreShold()
{
	gotoxy(0, 5);
	for (int i = 0; i < 5; i++)
		cout << s[i] << threshold[i] << endl;
	cout << endl << "Do you want to change the threshold value? (y or n)" << endl;
	string str;
	while (TRUE)
	{
		getline(cin, str);
		cout << endl;

		if (str.compare("y") == 0)
		{
			SetThreShold();
			break;
		}
		else if (str.compare("n") == 0) { break; }
		else { continue; }
	}
	system("cls");
}
void SetThreShold()
{
	int idx = 0, temp = 0;

	do
	{
		cout << "Set " + s[idx];
		cin >> temp;
		if (!cin.fail() && temp >= 0)
			threshold[idx++] = temp;
		else
			cout << "Invalid Input. Please try again";
		cout << endl;
	} while (idx < 5);
	
	threshold[4] = min(100, threshold[4]);

	cout << "Setting Completed, Press any key to return to the title" << endl;
	system("pause");
}