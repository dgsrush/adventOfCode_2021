#pragma once

#include<string>
#include<fstream>

namespace mhr
{

class ReadFile
{
public:
	explicit ReadFile(const char *flname);
	explicit ReadFile(const std::string &flname);
	~ReadFile();
	bool readLine(std::string &);
	void close();
	bool isOk();
	bool isEof();

private:
	std::string filename;
	std::ifstream inf;
	bool ok;
};

}
