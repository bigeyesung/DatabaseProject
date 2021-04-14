#pragma once
#include "DataTable.h"
class DataProcesser
{
private:
	std::unique_ptr<DataTable>__union;//union of two tables
	std::unique_ptr<DataTable>__inter;//intersection of two tables
	std::unique_ptr<DataTable>__diFir;//difference of first table 
	std::unique_ptr<DataTable>__diSec;//difference of second table
public:
	DataProcesser();
	~DataProcesser();
	void Analyze(DataTable &firstTable, DataTable &secondTable);
	void MergeProps(form &firDataSet, form &secDataSet, std::set<std::string> &propSet);
	std::unique_ptr<DataTable> GetUnion();
	std::unique_ptr<DataTable> GetInter();
	std::unique_ptr<DataTable> GetDiFir();
	std::unique_ptr<DataTable> GetDiSec();
};

