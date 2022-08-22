#ifndef HTTP_ENTITIES_COMMON_HEADERS_HTTP_HEADER_H
#define HTTP_ENTITIES_COMMON_HEADERS_HTTP_HEADER_H

#include <string>

namespace http
{
	namespace headers
	{
		enum class HeaderType
		{
			GeneralHeader,
			EntityHeader,
			RequestHeader,
			ResponseHeader,
			UnknownHeader
		};

		class HttpHeader
		{
		public:
			virtual void append_line(char* line) = 0;
			virtual void append(
				const std::string& field_name, 
				const std::string& field_value
			) = 0;
			virtual bool remove(const std::string& field_name) = 0;
			virtual ~HttpHeader() = default;
		};
	};
};

#endif