#ifndef HTTP_ENTITIES_REQUEST_REQUEST_H
#define HTTP_ENTITIES_REQUEST_REQUEST_H

#include "request_line.h"
#include "request_header.h"
#include "tools/request_parser.h"

namespace http
{
	class Request
	{
	public:
		Request(char* request_raw);

		const RequestLine& request_line() const;
		const RequestHeader& header() const;
		const char* body_raw() const;
	protected:
		tools::RequestParser parser_;
		RequestLine request_line_;
		RequestHeader request_header_;
		const char* body_raw_;
	};
}

#endif
