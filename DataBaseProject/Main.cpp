#include "DataProcesser.h"

int main(int argc, char** argv)
{
	DataTable fstTable;
	DataTable secTable;
	if (argc == 3)
	{
		if (fstTable.ReadFile(argv[1]) && secTable.ReadFile(argv[2]))
		{
			std::unique_ptr<DataProcesser> processer(new DataProcesser);
			processer->Analyze(fstTable, secTable);
			std::unique_ptr<DataTable> unIon = processer->GetUnion();
			std::unique_ptr<DataTable> inter = processer->GetInter();
			std::unique_ptr<DataTable> diFir = processer->GetDiFir();
			std::unique_ptr<DataTable> diSec = processer->GetDiSec();
			DataProcesser* fp = processer.release();
			delete fp;
			std::string directory = Util::getCurrentDir();
			unIon->SaveFile(directory + "\\output\\union.csv");
			inter->SaveFile(directory + "\\output\\intersection.csv");
			diFir->SaveFile(directory + "\\output\\diff_of_firstTable.csv");
			diSec->SaveFile(directory + "\\output\\diff_of_secondTable.csv");
		}
		else
			std::cout << "csv files can not be opened" << std::endl;

	}
	else
		std::cout << "Please type: Project.exe, firstTable path, secondTable path" << std::endl;

	return 0;
}
