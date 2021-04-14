#pragma once
#include "Util.h"

class DataTable
{
private:
	std::vector<std::string>__props;
	form __dataSet;
	Util __util;
public:
	//DataTable();
	~DataTable();
	bool ReadFile(const std::string &filePath);
	void SaveFile(const std::string &filePath);
	std::vector<std::string> &GetProps();
	form &GetData();
};

