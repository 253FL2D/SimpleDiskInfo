#ifndef _MAIN_H_
#define _MAIN_H_

#ifndef __IOSTREAM__
#define __IOSTREAM__

#include <iostream>
using namespace std;

#endif

#ifdef _WIN32
#ifndef __WINDOWS_H__
#define __WINDOWS_H__

#include <windows.h>

#endif
#endif

int ReadCSV(string* path);
void ShowThreShold();
void SetThreShold();

#endif