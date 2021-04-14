#include "Util.h"

//Util::Util()
//{
//}


Util::~Util()
{
}

void Util::write_csv(std::string filename, form &dataset, std::vector<std::string> &props)
{
	std::unordered_map<std::string, std::string> title;
	std::ofstream outFile(filename);
	SetFormat(props);
	for (int ind = 0; ind < props.size(); ind++)
	{
		outFile << props[ind];
		if (ind != props.size() - 1)
			outFile << ",";
	}
	outFile << "\n";
	//int i = 0;
	for (auto& data : dataset)
	{
		for (int ind = 0; ind < props.size(); ind++)
		{
			if (data.second.find(props[ind]) != data.second.end())
			{
				//std::cout << "plan key=" << props[ind] << std::endl;
				//std::cout << "actual val=" << data.second[props[ind]] << std::endl;
				outFile << data.second[props[ind]];
			}
			else
				outFile << "NoData";

			if (ind != props.size() - 1)
				outFile << ",";
		}
		outFile << "\n";
	}
	outFile << "\n";
	outFile.close();
}

bool Util::read_csv(const std::string &filename, form &dataSet, std::vector<std::string> &props)
{
	std::unordered_map<std::string, std::string> metaData;
	std::ifstream inputFile(filename);
	std::string line, prop;
	bool init = true;
	// Make sure the file is open
	if (inputFile.is_open())
	{
		// Extract the first line(prop) in the file
		std::getline(inputFile, line);
		std::stringstream ss(line);
		while (std::getline(ss, prop, ','))
		{
			if (this->IsFormat(prop))
			{
				metaData[prop] = "NoData";
				props.push_back(prop);
			}
			else
			{
				init = false;
				break;
			}
		}
		if (init)
		{
			while (std::getline(inputFile, line) && init)
			{
				std::stringstream iss(line);
				std::string value;
				std::string drugName;
				int propInd = 0;
				while (std::getline(iss, value, ','))
				{
					if (this->IsFormat(value))
					{
						if (value == "")
							value = "NoData";
						if (propInd == 0)
						{
							drugName = value;
							dataSet[drugName] = metaData;
							dataSet[drugName][props[propInd]] = value;
						}
						else
							dataSet[drugName][props[propInd]] = value;
						propInd++;
					}
					else
					{
						init = false;
						break;
					}
				}
			}
		}

	}
	else
		init = false;

	// Close file
	inputFile.close();
	return init;
}

bool Util::IsFormat(std::string & s)
{
	for (char const &c : s) {
		if (!std::isdigit(c) && !std::isalpha(c) && c != '.')
			return false;
	}
	return true;
}

void Util::SetFormat(std::vector<std::string>& props)
{
	std::vector<std::string> orderedProps;
	orderedProps.push_back("Molecule");
	for (auto& prop : props) {
		if (prop != "Molecule")
			orderedProps.push_back(prop);
	}
	props = orderedProps;
}


std::string Util::getCurrentDir()
{
	char buff[MAX_PATH];
	GetModuleFileName(NULL, buff, MAX_PATH);
	std::string::size_type position = std::string(buff).find_last_of("\\/");
	return std::string(buff).substr(0, position);
}


