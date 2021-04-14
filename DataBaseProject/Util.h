#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 
#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <memory>
#include <cctype>
#include <cstring>
#include <windows.h>
#include <limits.h>
using form = std::unordered_map<	std::string,
	std::unordered_map<	std::string, std::string>>;

class Util
{
public:
	//Util();
	~Util();
	void write_csv(std::string filename, form &dataset, std::vector<std::string> &props);
	void SetFormat(std::vector<std::string> &props);
	bool read_csv(const std::string &filename, form &dataSet, std::vector<std::string> &props);
	bool IsFormat(std::string &s);
	static std::string getCurrentDir();

};

