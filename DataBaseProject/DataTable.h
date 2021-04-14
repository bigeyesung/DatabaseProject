#pragma once
#include "Util.h"

class DataTable
{
private:
	std::vector<std::string>__props;
	form __dataSet;
	Util __util;
public:
	DataTable();
	~DataTable();
	bool ReadFile(std::string filePath);
	void SaveFile(std::string filePath);
	std::vector<std::string> &GetProps();
	form &GetData();
};

