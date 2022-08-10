#ifndef HTTP_ENTITIES_REQUEST_REQUEST_LINE_H
#define HTTP_ENTITIES_REQUEST_REQUEST_LINE_H

#include "../common/method.h"
#include "../common/uri.h"
#include "../common/http_version.h"

namespace http
{
	enum class RequestFormat
	{
		FullRequest,
		SimpleRequest
	};

	class RequestLine
	{
	public:
		RequestLine(const char* request_line_raw);
		
		const Method& method() const;
		const Uri& uri() const;
		const HttpVersion& version() const;
		const RequestFormat& format() const;
	protected:
		Method method_;
		Uri uri_;
		HttpVersion version_;
		RequestFormat format_;
	};
}

#endif
