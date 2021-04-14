#include "DataTable.h"

//DataTable::DataTable()
//{
//}

DataTable::~DataTable()
{
}

bool DataTable::ReadFile(const std::string &filePath)
{
	return __util.read_csv(filePath, __dataSet, __props);
}

void DataTable::SaveFile(const std::string &filePath)
{
	__util.write_csv(filePath, __dataSet, __props);
}

form &DataTable::GetData()
{
	//std::cout << "cur addr: " << &(this->__data) << std::endl;
	return __dataSet;
}

std::vector<std::string> &DataTable::GetProps()
{
	//std::cout << "cur addr :"<<&(this->__props) << std::endl;
	return __props;
}

