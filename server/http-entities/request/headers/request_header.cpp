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

void RequestHeader::append(
	const std::string &field_name, 
	const std::string &field_value
)
{
	/* TODO: check for existing field-names */
	fields_.emplace(field_name, field_value);
}

bool RequestHeader::remove(const std::string& field_name)
{
	if (fields_.find(field_name) == fields_.end())
		return false;
	fields_.erase(field_name);
	return true;
}

const std::map<std::string, std::string>& RequestHeader::get() const
{
	return fields_;
}

const std::string& RequestHeader::get(const std::string& key) const
{
	return fields_.at(key);
}
