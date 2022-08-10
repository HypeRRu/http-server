#ifndef HTTP_ENTITIES_REQUEST_TOOLS_REQUEST_PARSER_H
#define HTTP_ENTITIES_REQUEST_TOOLS_REQUEST_PARSER_H

#include <map>
#include <string>

namespace http
{
	namespace tools
	{
		class RequestParser
		{
		public:
			RequestParser(char* request_raw);

			char* get_request_line_raw() const;
			char* get_request_headers_raw() const;
			char* get_request_body_raw() const;
		protected:
			char* request_line_raw_;
			char* request_headers_raw_;
			char* request_body_raw_;
		};
	};
};

#endif
