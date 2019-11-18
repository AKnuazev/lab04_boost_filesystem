#include <iostream>
#include "../include/FTPFilesAnalyzer.h"
#define path_to_ftp "/home/anton/AKnuazev/labs/lab04_boost_filesystem/misc/ftp"
int main()
{
	FTPFilesAnalyzer analyzer(path_to_ftp);
	analyzer.start_passage(path_to_ftp);

	std::cout << std::endl;
	std::cout << "\tALL FILES" << std::endl;
	std::cout << "____________________________________" << std::endl;
	analyzer.print_all_files();
	std::cout << std::endl << std::endl;

	std::cout << "\tACCOUNT GROUPS INFO" << std::endl;
	std::cout << "_________________________________________________________________" << std::endl;
	analyzer.print_account_groups_info();
	std::cout << std::endl << std::endl;

}
