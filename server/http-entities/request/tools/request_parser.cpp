#include "request_parser.h"
#include <cstring>

using namespace http::tools;

RequestParser::RequestParser(char* request_raw):
	request_line_raw_{nullptr},
	request_headers_raw_{nullptr},
	request_body_raw_{nullptr}
{
	if (request_raw)
	{
		/* request-line always come first in request */
		request_line_raw_ = request_raw;
		/* search for headers, then for request-body */
		request_headers_raw_ = strstr(request_raw, "\r\n");
		request_body_raw_ = strstr(request_raw, "\r\n\r\n");
		/* if request_body_raw_ == request_headers_raw_, no headers in request */
		if (request_body_raw_ == request_headers_raw_)
			request_headers_raw_ = nullptr;
		if (request_headers_raw_)
		{
			*request_headers_raw_ = '\0';
			request_headers_raw_ += 2; // skip CRLF bytes
		}
		if (request_body_raw_)
		{
			*request_body_raw_ = '\0';
			request_body_raw_ += 4; // skip 2CRLF bytes
		}
	}
}

char* RequestParser::get_request_line_raw() const
{
	return request_line_raw_;
}

char* RequestParser::get_request_headers_raw() const
{
	return request_headers_raw_;
}

char* RequestParser::get_request_body_raw() const
{
	return request_body_raw_;
}
