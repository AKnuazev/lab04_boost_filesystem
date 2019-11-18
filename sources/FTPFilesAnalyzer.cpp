#include "../include/FTPFilesAnalyzer.h"

bool CompareByDate(FinancialFile file1, FinancialFile file2)
{
	if (file1.date.year < file2.date.year)
		return 1;
	if (file1.date.year > file2.date.year)
		return 0;

	if (file1.date.month < file2.date.month)
		return 1;
	if (file1.date.month > file2.date.month)
		return 0;

	if (file1.date.day < file2.date.day)
		return 1;
	if (file1.date.day > file2.date.day)
		return 0;
	
	return 0;
}

std::ostream& operator<< (std::ostream &out, const Date &date)
{
	out << date.year << "-" << date.month << "-" << date.day;

	return out;
}

FTPFilesAnalyzer::FTPFilesAnalyzer(fs::path path)
{
	this->path_to_ftp = path;
}

FinancialFile FTPFilesAnalyzer::parce_filename(std::string filename)
{
	FinancialFile file;

	file.name = filename;

	file.type = filename.substr(0, filename.find('_'));
	filename = filename.substr(filename.find('_') + 1);

	file.account_number = std::stoi(filename.substr(0, filename.find('_')));
	filename = filename.substr(filename.find('_') + 1);

	file.date.year = std::stoi(filename.substr(0,4));
	file.date.month = std::stoi(filename.substr(4, 2));
	file.date.day = std::stoi(filename.substr(6, 2));
	filename = filename.substr(8);

	if (filename[0] != '.' || filename.substr(0, 4) == ".old")
		throw std::exception();   // Ignored file with wrong syntax or ".old"

	if (filename.substr(1).find('.') != std::string::npos)
		throw std::exception();
	
	file.extension = filename;

	return file;
}

void FTPFilesAnalyzer::start_passage(fs::path path)
{
	for (fs::directory_entry dir_iter : fs::directory_iterator{ path })
	{
		fs::path current_path = fs::canonical(dir_iter);
		
		if (fs::is_regular_file(current_path))
			analyze_file(current_path);
		else if (fs::is_directory(current_path))
			analyze_dir(current_path);
	}

	if (directories.size() > 0)
		directories.pop_back();
}

void FTPFilesAnalyzer::analyze_dir(fs::path dir_path)
{
	directories.push_back(dir_path.stem().string());
	start_passage(dir_path);
}

void FTPFilesAnalyzer::analyze_file(fs::path file_path)
{
	try
	{
		FinancialFile file = parce_filename(file_path.filename().string());
		file.broker = directories[directories.size()-1];

		files.push_back(file);
		account_groups[file.account_number].push_back(file);
	}
	catch (const std::exception&){}
	
}

void FTPFilesAnalyzer::print_all_files()
{
	for (auto file : files)
		std::cout << file.broker << " " << file.name << std::endl;
}

void FTPFilesAnalyzer::print_account_groups_info()
{
	for (auto group : account_groups)
	{
		std::cout << "broker: " << group.second[0].broker << " ";
		
		std::cout << "account: ";
		for (int i = 0; i < 8 - group.first; i++)
			std::cout << '0';
		std::cout << group.first << " ";

		std::cout << "files: " << group.second.size() << " ";

		std::cout << "lastdate: " << std::max_element(group.second.begin(), group.second.end(), CompareByDate)->date << " ";
		
		std::cout << std::endl;
	}
}
