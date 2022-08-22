#ifndef HTTP_ENTITIES_REQUEST_TOOLS_REQUEST_LINE_PARSER_H
#define HTTP_ENTITIES_REQUEST_TOOLS_REQUEST_LINE_PARSER_H

#include <map>
#include <string>

namespace http
{
	namespace tools
	{
		class RequestLineParser
		{
		public:
			RequestLineParser(char* request_line_raw);

			char* get_method_name() const;
			char* get_resource_path() const;
			char* get_http_version_name() const;
		protected:
			char* method_name_;
			char* resource_path_;
			char* http_version_name_;
		};
	};
};

#endif
