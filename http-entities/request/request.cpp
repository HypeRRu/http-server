#include "request.h"

using namespace http;

Request::Request(const char* request_raw):
	parser_(request_raw),
	request_line_(parser_.get_request_line_raw()),
	request_header_(parser_.get_request_headers_raw()),
	body_raw_(parser_.get_request_body_raw())
{
	/* TODO: check for errors */
}

const RequestLine& Request::request_line() const
{
	return request_line_;
}

const RequestHeader& Request::header() const
{
	return request_header_;
}

const char* Request::body_raw() const
{
	return body_raw_;
}

