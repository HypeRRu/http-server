#include "header_parser.h"
#include <cstring>
#include <cctype>

using namespace http::tools;

HeaderParser::HeaderParser(
	char* header_raw,
	headers::HttpHeader* general_header,
	headers::HttpHeader* request_header,
	headers::HttpHeader* entity_header
)
{
	/* header_raw points to first line of headers block */
	char* line = header_raw;
	char* line_end;
	/* while we have some headers */
	while (line)
	{
		/* get line end */
		line_end = strstr(line, "\r\n"); // all headers separated by CRLF
		if (line_end)
		{
			*line_end = '\0';
			line_end += 2;
		}
		if (strpbrk(line, ":"))
		{
			/* get field name */
			const char* separator = strpbrk(line, ":");
			char* field_name = new char[separator - line + 1];
			strncpy(field_name, line, separator - line);
			field_name[separator - line] = '\0';
			for (char* fname = field_name; *fname != '\0'; ++fname)
				*fname = tolower(*fname);
			/* check which header we have */
			if (is_header_general(field_name))
			{
				if (general_header)
					general_header->append_line(line);
			}
			else if (is_header_entity(field_name))
			{
				if (entity_header)
					entity_header->append_line(line);
			}
			else
			{
				if (request_header)
					request_header->append_line(line);
			}
			delete [] field_name;
		}	
		/* get new line pointer */
		line = line_end;
	}
}

bool HeaderParser::is_header_general(const char* field_name) const
{
	return (
		!strcmp(field_name, "date") ||
		!strcmp(field_name, "pragma")
	);
}

bool HeaderParser::is_header_entity(const char* field_name) const
{
	return (
		!strcmp(field_name, "allow") ||
		!strcmp(field_name, "content-encoding") ||
		!strcmp(field_name, "content-length") ||
		!strcmp(field_name, "content-type") ||
		!strcmp(field_name, "expires") ||
		!strcmp(field_name, "last-modified")
	);
}
