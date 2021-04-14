#include "DataProcesser.h"

DataProcesser::DataProcesser()
{
	__union = std::unique_ptr<DataTable>(new DataTable);
	__inter = std::unique_ptr<DataTable>(new DataTable);
	__diFir = std::unique_ptr<DataTable>(new DataTable);
	__diSec = std::unique_ptr<DataTable>(new DataTable);
}


DataProcesser::~DataProcesser()
{
}

void DataProcesser::Analyze(DataTable &firstTable, DataTable &secondTable)
{
	//Union=intersection+diff_of_firstTable+diff_of_secondTable
	form &firDataSet = firstTable.GetData();
	form &secDataSet = secondTable.GetData();

	//get props
	std::vector<std::string> &fstProps = firstTable.GetProps();
	std::vector<std::string> &secProps = secondTable.GetProps();
	std::set<std::string> newProps(fstProps.begin(), fstProps.end());
	for (auto& x : secProps)
		newProps.insert(x);
	//merge two tables props
	this->MergeProps(firDataSet, secDataSet, newProps);
	this->MergeProps(secDataSet, firDataSet, newProps);

	for (auto& drugDict : firDataSet)
	{
		//if find it in secData-> do intersection, and remove item from secData
		if (secDataSet.find(drugDict.first) != secDataSet.end())
		{
			this->__inter->GetData()[drugDict.first] = drugDict.second;
			secDataSet.erase(drugDict.first);
		}
		//if not find in secData->diff_of_firstTable
		else
			this->__diFir->GetData()[drugDict.first] = drugDict.second;
		//all data needs to be in union
		this->__union->GetData()[drugDict.first] = drugDict.second;
	}

	//iterate secDataSet(currently it is diff_of_secondTable)
	for (auto& drugName : secDataSet)
	{
		this->__union->GetData()[drugName.first] = drugName.second;
	}
	//assign diff_of_secondTable
	this->__diSec->GetData() = secDataSet;
	std::vector<std::string> mergedProps(newProps.begin(), newProps.end());

	//assign props
	this->__inter->GetProps() = mergedProps;
	this->__union->GetProps() = mergedProps;
	this->__diFir->GetProps() = mergedProps;
	this->__diSec->GetProps() = mergedProps;
}

void DataProcesser::MergeProps(form &firDataSet, form &secDataSet, std::set<std::string> &propSet)
{
	for (auto& drugDict : firDataSet)
	{
		for (auto& prop : propSet)
		{
			//if first dataSet has no prop info-> search second dataSet and insert it to first dataset
			if (drugDict.second.find(prop) == drugDict.second.end() || drugDict.second[prop] == "NoData")
			{
				//std::cout << prop << std::endl;
				//std::cout << drugDict.first << std::endl;

				// check second dataset have the same drugName
				if (secDataSet.find(drugDict.first) != secDataSet.end())
				{
					//std::cout << secDataSet[drugDict.first][prop] << std::endl;
					drugDict.second[prop] = secDataSet[drugDict.first][prop];
				}
				else
					drugDict.second[prop] = "NoData";
			}
		}
	}
}

std::unique_ptr<DataTable> DataProcesser::GetUnion()
{
	return std::move(__union);
}

std::unique_ptr<DataTable> DataProcesser::GetInter()
{
	return std::move(__inter);
}

std::unique_ptr<DataTable> DataProcesser::GetDiFir()
{
	return std::move(__diFir);
}

std::unique_ptr<DataTable> DataProcesser::GetDiSec()
{
	return std::move(__diSec);
}


