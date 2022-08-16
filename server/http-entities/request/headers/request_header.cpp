#include "request_header.h"
#include <cstring>

using namespace http::headers;

void RequestHeader::append_line(char *line)
{
	/* TODO: check for existing field-names */
	char* field_name = line;
	/* separate field and it's value */
	char* value = strpbrk(line, ":");
	if (!value)
		return;

	*value = '\0';
	value += 2;

	while (*line != '\0')
	{
		*line = tolower(*line);
		++line;
	}
	/* insert line */
	fields_.emplace(
		field_name,
		value
	);
}

const std::map<std::string, std::string>& RequestHeader::get() const
{
	return fields_;
}

const std::string& RequestHeader::get(const std::string& key) const
{
	return fields_.at(key);
}
