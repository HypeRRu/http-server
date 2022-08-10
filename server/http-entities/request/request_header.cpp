#include "request_header.h"
#include <cstring>

using namespace http;

RequestHeader::RequestHeader(char* request_headers_raw)
{
	/* request_headers_raw points to first line */
	char* line = request_headers_raw;
	char* line_end;
	/* while we have some headers */
	while (line)
	{
		/* get line end */
		line_end = strstr(line, "\r\n");
		if (line_end)
		{
			*line_end = '\0';
			line_end += 2;
		}
		/* insert it into map */
		append(line);
		/* get new line pointer */
		line = line_end;
	}
}

void RequestHeader::append(char *line)
{
	char* field = line;
	/* separate field and it's value */
	char* value = strpbrk(line, "=");
	if (!value)
		return;
	*(value++) = '\0';
	/* insert line */
	fields_.emplace(
		field,
		value
	);
}

const std::map<std::string, std::string> RequestHeader::get() const
{
	return fields_;
}
