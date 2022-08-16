#include "general_header.h"
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace http::headers;

GeneralHeader::GeneralHeader()
{
	date_ = new struct tm;
	memset(date_, 0, sizeof(struct tm));
}

GeneralHeader::~GeneralHeader()
{
	delete date_;
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

void GeneralHeader::set_date(const char* date)
{
	if (!strptime(date, "%a, %d %b %Y %H:%M:%S %Z", date_)) // RFC822
		if (!strptime(date, "%A, %d-%b-%y %H:%M:%S %Z", date_)) // RFC850
			if (!strptime(date, "%a %b %e %H:%M:%S %Y", date_)) // ANSI
				return;

	set_date_string();
}

void GeneralHeader::set_date(const struct tm* date_struct)
{
	memcpy(date_, date_struct, sizeof(struct tm));
	set_date_string();
}

void GeneralHeader::set_date_string()
{
	char* date_string = (char*) malloc(30 * sizeof(char));
	strftime(date_string, 30, "%a, %d %b %Y %H:%M:%S GMT", date_);
	date_string_ = date_string;
	free(date_string);
}

void GeneralHeader::add_pragma_directive(const char* pragma_directive)
{
	pragma_directives_.emplace(pragma_directive);
}

const std::tm* GeneralHeader::get_date_struct() const
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

