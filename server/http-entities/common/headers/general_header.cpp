#include "general_header.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace http::headers;

GeneralHeader::GeneralHeader()
{
	memset(&date_, 0, sizeof(struct tm));
}

void GeneralHeader::append_line(char* line)
{
	char* separator = strpbrk(line, ":");
	if (!separator)
		return;
	*separator = '\0';
	/* field-name is case-insensitive, using lower-case */
	for (char* field_name = line; *field_name != '\0'; ++field_name)
		*field_name = tolower(*field_name);
	if (!strcmp(line, "date"))
		set_date(separator + 2);
	else if (!strcmp(line, "pragma"))
		add_pragma_directive(separator + 2);
	else
		return;
}

void GeneralHeader::append(
	const std::string& field_name, 
	const std::string& field_value
)
{
	std::string fname;
	fname.reserve(field_name.size() + 1);
	for (size_t i = 0; i < field_name.size(); ++i)
		fname = tolower(field_name[i]);

	if (fname == "date")
		set_date(field_value);
	else if (fname == "pragma")
		add_pragma_directive(field_value);
	else
		return;
}

bool GeneralHeader::remove(const std::string& field_name)
{
	std::string fname;
	fname.reserve(field_name.size() + 1);
	for (size_t i = 0; i < field_name.size(); ++i)
		fname = tolower(field_name[i]);

	if (fname == "date")
	{
		memset(&date_, 0, sizeof(struct tm));
		date_string_.clear();
		return true;
	} else if (fname == "pragma")
	{
		pragma_directives_.clear();
		return true;
	}
	return false;
}

void GeneralHeader::set_date(const char* date)
{
	if (!strptime(date, "%a, %d %b %Y %H:%M:%S %Z", &date_)) // RFC822
		if (!strptime(date, "%A, %d-%b-%y %H:%M:%S %Z", &date_)) // RFC850
			if (!strptime(date, "%a %b %e %H:%M:%S %Y", &date_)) // ANSI
				return;

	set_date_string();
}

void GeneralHeader::set_date(const std::string& date)
{
	set_date(date.c_str());
}

void GeneralHeader::set_date(const struct tm& date_struct)
{
	memcpy(&date_, &date_struct, sizeof(struct tm));
	set_date_string();
}

void GeneralHeader::set_date_string()
{
	char* date_string = (char*) malloc(31 * sizeof(char));
	date_string[30] = '\0';
	strftime(date_string, 30, "%a, %d %b %Y %H:%M:%S GMT", &date_);
	date_string_ = date_string;
	free(date_string);
}

void GeneralHeader::add_pragma_directive(const char* pragma_directive)
{
	pragma_directives_.emplace(pragma_directive);
}

void GeneralHeader::add_pragma_directive(const std::string& pragma_directive)
{
	add_pragma_directive(pragma_directive.c_str());
}

const std::tm& GeneralHeader::get_date_struct() const
{
	return date_;
}

const std::string& GeneralHeader::get_date() const
{
	return date_string_;
}

const std::set<std::string>& GeneralHeader::get_pragma_directives() const
{
	return pragma_directives_;
}

