#ifndef HTTP_ENTITIES_REQUEST_REQUEST_H
#define HTTP_ENTITIES_REQUEST_REQUEST_H

#include "request_line.h"
#include "tools/request_parser.h"
#include "../common/headers/general_header.h"
#include "../common/headers/entity_header.h"
#include "headers/request_header.h"

namespace http
{
	class Request
	{
	public:
		Request(char* request_raw);

		const RequestLine& request_line() const;

		const headers::GeneralHeader& general_header() const;
		const headers::RequestHeader& request_header() const;
		const headers::EntityHeader&   entity_header() const;

		const char* body_raw() const;

		void dump() const;
	protected:
		void setup_headers(char* headers_raw);

		tools::RequestParser parser_;
		RequestLine request_line_;

		headers::GeneralHeader general_header_;
		headers::RequestHeader request_header_;
		headers::EntityHeader   entity_header_;

		char* body_raw_;
	};
}

#endif
