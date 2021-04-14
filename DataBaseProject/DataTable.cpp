#include "DataTable.h"

DataTable::DataTable()
{
}

DataTable::~DataTable()
{
}

bool DataTable::ReadFile(std::string filePath)
{
	return this->__util.read_csv(filePath, this->__dataSet, this->__props);
}

void DataTable::SaveFile(std::string filePath)
{
	this->__util.write_csv(filePath, this->__dataSet, this->__props);
}

form &DataTable::GetData()
{
	//std::cout << "cur addr: " << &(this->__data) << std::endl;
	return this->__dataSet;
}

std::vector<std::string> &DataTable::GetProps()
{
	//std::cout << "cur addr :"<<&(this->__props) << std::endl;
	return this->__props;
}

