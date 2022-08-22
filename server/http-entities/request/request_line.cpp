#include "request_line.h"

using namespace http;

RequestLine::RequestLine(char* request_line_raw):
	parser_(request_line_raw),
	method_(parser_.get_method_name()),
	uri_(parser_.get_resource_path()),
	version_(parser_.get_http_version_name()),
	format_(RequestFormat::FullRequest)
{
	if (version_.version_major() < 1)
		format_ = RequestFormat::SimpleRequest;
}

const Method& RequestLine::method() const
{
	return method_;
}

const Uri& RequestLine::uri() const
{
	return uri_;
}

const HttpVersion& RequestLine::version() const
{
	return version_;
}

const RequestFormat& RequestLine::format() const
{
	return format_;
}

