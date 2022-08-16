#ifndef HTTP_ENTITIES_COMMON_HEADERS_HTTP_HEADER_H
#define HTTP_ENTITIES_COMMON_HEADERS_HTTP_HEADER_H

namespace http
{
	namespace headers
	{
		class HttpHeader
		{
		public:
			virtual void append_line(char* line) = 0;
			virtual ~HttpHeader() = default;
		};
	};
};

#endif