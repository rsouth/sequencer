#include "MetaData.h"

#include <utility>

MetaData::MetaData() = default;

MetaData::MetaData(std::string title, std::string author, std::string date): title_(std::move(title)),
                                                                             author_(std::move(author)),
                                                                             date_(std::move(date))
{
}

std::string MetaData::get_title() const
{
	return this->title_;
}

std::string MetaData::get_author() const
{
	return this->author_;
}

std::string MetaData::get_date() const
{
	return this->date_;
}
