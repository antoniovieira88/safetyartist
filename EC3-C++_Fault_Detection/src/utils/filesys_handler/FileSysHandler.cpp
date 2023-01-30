#include "include/FileSysHandler.h"

bool FileSysHandler::createDirectories(string baseDir, vector<string> dirs)
{
	bool success = true;
	for (string& dir : dirs) {
		success = filesystem::create_directories(baseDir + "/" + dir);
		if (!success) {
			break;
		}
	}

	return success;
}

bool FileSysHandler::copyFileOverwrite(string filenameSrc, string filenameDest, string relativeSrcDir, string relativeDestDir)
{
	filesystem::path fileSrcPath(relativeSrcDir + "/" + filenameSrc);
	filesystem::path fileTargetPath(relativeDestDir + "/" + filenameDest);
	filesystem::copy_file(fileSrcPath, fileTargetPath, filesystem::copy_options::overwrite_existing);
	return false;
}

void FileSysHandler::createCSVFile(string filename, string relativeBaseDir)
{
	fstream file;
	if (filename.find(".") == -1) filename = filename + ".csv";
	file.open(relativeBaseDir + "/" + filename, ios::out);
	file.close();
}

void FileSysHandler::createCSVFile(string filename, string relativeBaseDir, vector<string> headers)
{
	fstream file;
	int numberOfHeaders = headers.size();
	if (filename.find(".") == -1) filename = filename + ".csv";
	file.open(relativeBaseDir + "/" + filename, ios::out);

	for (int i = 0; i < numberOfHeaders - 1; i++) {
		file << headers[i] << ",";
	}

	file << headers[numberOfHeaders - 1] << endl;
	file.close();
}

bool FileSysHandler::searchForDirectory(string dir)
{
	return filesystem::exists(dir);
}

bool FileSysHandler::searchForDirectories(vector<string> dirs)
{
	bool dirsFound = true;
	for (string& dir : dirs) {
		dirsFound = filesystem::exists(dir);
		if (!dirsFound) {
			break;
		}
	}
	return dirsFound;
}
