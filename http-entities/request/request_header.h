#ifndef HTTP_ENTITIES_REQUEST_REQUEST_HEADER_H
#define HTTP_ENTITIES_REQUEST_REQUEST_HEADER_H

#include <string>
#include <map>

namespace http
{
	class RequestHeader
	{
	public:
		RequestHeader(const char* request_headers_raw);
		const std::map<std::string, std::string> get() const;
	protected:
		std::map<std::string, std::string> fields_;
	};
};

#endif
