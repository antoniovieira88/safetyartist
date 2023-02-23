#include <filesystem>
#include <fstream>
#include "../../../utils/json/include/JsonSerializer.h"

#pragma once
using namespace std;

class FileSysHandler
{
public:
	static bool createDirectories(string relativeBaseDir, vector<string> dirs);
	static bool copyFileOverwrite(string filenameSrc, string filenameDest, string relativeSrcDir, string relativeDestDir);
	static void createCSVFile(string filename, string relativeBaseDir);
	static void createCSVFile(string filename, string relativeBaseDir, vector<string> headers);
	static string createJsonFile(string filename, string relativeBaseDir);
	static bool searchForDirectory(string dir);
	static bool searchForDirectories(vector<string> dirs);

};