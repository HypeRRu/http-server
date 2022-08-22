#include "entity_header.h"
#include <cstring>
#include <cctype>

using namespace http::headers;

void EntityHeader::append_line(char* line)
{
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
	/* TODO: errors check */
	/* insert line */
	fields_.emplace(
		field_name,
		value
	);
}

void EntityHeader::append(
	const std::string &field_name, 
	const std::string &field_value
)
{
	/* TODO: errors check */
	fields_.emplace(field_name, field_value);
}

bool EntityHeader::remove(const std::string& field_name)
{
	if (fields_.find(field_name) == fields_.end())
		return false;
	fields_.erase(field_name);
	return true;
}

const std::map<std::string, std::string>& EntityHeader::get() const
{
	return fields_;
}

const std::string& EntityHeader::get(const std::string& key) const
{
	return fields_.at(key);
}
