#pragma once

#include <string>

class MetaData
{
public:
	MetaData();
	MetaData(std::string title, std::string author, std::string date);

	auto get_title() const -> std::string;
	auto get_author() const -> std::string;
	auto get_date() const -> std::string;

private:
	std::string title_ = std::string();
	std::string author_ = std::string();
	std::string date_ = std::string();
};
