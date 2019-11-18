#pragma once

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <iostream>
#include <unordered_map>
#include <algorithm>

namespace fs = boost::filesystem;

struct Date
{
	int year;
	int month;
	int day;
};

struct FinancialFile
{
	std::string name;
	std::string broker;
	std::string type;
	unsigned int account_number;
	Date date;
	std::string extension;
};

class FTPFilesAnalyzer
{
private:
	fs::path path_to_ftp;
	std::vector <FinancialFile> files;
	std::vector <std::string> directories;

	std::unordered_map<int,std::vector<FinancialFile>> account_groups;
	
	FinancialFile parce_filename(std::string filename);
	void analyze_dir(fs::path path);
	void analyze_file(fs::path path);
public:
	FTPFilesAnalyzer(fs::path path_to_ftp);

	void start_passage(fs::path path);

	void print_all_files();
	void print_account_groups_info();
};

