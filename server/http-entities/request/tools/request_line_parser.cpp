#include "request_line_parser.h"
#include <cstring>
#include <cctype>

using namespace http::tools;

RequestLineParser::RequestLineParser(char* request_line_raw):
	method_name_{nullptr},
	resource_path_{nullptr},
	http_version_name_{nullptr}
{
	if (request_line_raw)
	{
		/* method always come first */
		method_name_ = request_line_raw;
		/* get URI */
		resource_path_ = strpbrk(request_line_raw, " ");
		if (!resource_path_)
			return;
		while (isspace(*resource_path_))
			*(resource_path_++) = '\0';
		/* get Http protocol version */
		http_version_name_ = strpbrk(resource_path_, " ");
		if (!http_version_name_)
			return;
		while (isspace(*http_version_name_))
			*(http_version_name_++) = '\0';
	}
}

char* RequestLineParser::get_method_name() const
{
	return method_name_;
}

char* RequestLineParser::get_resource_path() const
{
	return resource_path_;
}

char* RequestLineParser::get_http_version_name() const
{
	return http_version_name_;
}
