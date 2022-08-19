#ifndef HTTP_ENTITIES_REQUEST_TOOLS_HEADER_PARSER_H
#define HTTP_ENTITIES_REQUEST_TOOLS_HEADER_PARSER_H

#include "../../common/headers/http_header.h"

namespace http
{
	namespace tools
	{
		class HeaderParser
		{
		public:
			HeaderParser(
				char* header_raw,
				headers::HttpHeader* general_header,
				headers::HttpHeader* request_header,
				headers::HttpHeader* entity_header = nullptr
			);
		};
	};
};

#endif