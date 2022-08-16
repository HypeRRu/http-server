#ifndef HTTP_ENTITIES_REQUEST_HEADERS_REQUEST_HEADER_H
#define HTTP_ENTITIES_REQUEST_HEADERS_REQUEST_HEADER_H

#include <string>
#include <map>
#include "../../common/headers/http_header.h"

namespace http
{
	namespace headers
	{
		class RequestHeader: public HttpHeader
		{
		public:
			const std::map<std::string, std::string>& get() const;
			const std::string& get(const std::string& key) const;
			void append_line(char* line);
		protected:
			std::map<std::string, std::string> fields_;
		};
	};	
};

#endif
