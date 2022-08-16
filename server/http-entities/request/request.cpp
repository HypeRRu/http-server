#include "request.h"
#include "tools/header_parser.h"
#include <iostream>

using namespace http;

Request::Request(char* request_raw):
	parser_(request_raw),
	request_line_(parser_.get_request_line_raw()),
	body_raw_(parser_.get_request_body_raw())
{
	setup_headers(parser_.get_request_headers_raw());
	/* TODO: check for errors */
}

const RequestLine& Request::request_line() const
{
	return request_line_;
}

const headers::RequestHeader& Request::request_header() const
{
	return request_header_;
}

const headers::GeneralHeader& Request::general_header() const
{
	return general_header_;
}

const headers::EntityHeader& Request::entity_header() const
{
	return entity_header_;
}

const char* Request::body_raw() const
{
	return body_raw_;
}

void Request::setup_headers(char* headers_raw)
{
	tools::HeaderParser hp(
		headers_raw,
		&general_header_,
		&request_header_,
		&entity_header_ 
	);
}

void Request::dump() const
{
	std::cout << "\tRequest Line:" << std::endl;
	std::cout << "Method: " << request_line().method().get_name() << std::endl;
	std::cout << "HttpVersion: " << request_line().version().major() << "." << request_line().version().minor() << std::endl;
	std::cout << "URI: " << request_line().uri().get() << std::endl;
	std::cout << "Resource location: " << request_line().uri().get_resource_path() << std::endl;
	std::cout << std::endl;

	std::cout << "\tGeneral Headers:" << std::endl;
	if (!general_header().get_date().size())
		std::cout << "Date: (Empty)" << std::endl;
	else
		std::cout << "Date: " << general_header().get_date() << std::endl;
	for (auto pragma_value: general_header().get_pragma_directives())
			std::cout << "prgama" << ":\t" << pragma_value << std::endl;
	std::cout << std::endl;

	std::cout << "\tRequest Headers:" << std::endl;
	if (!request_header().get().size())
	{
		std::cout << "(Empty)" << std::endl;
	}
	else
	{
		for (auto [fname, fvalue]: request_header().get())
			std::cout << fname << ":\t" << fvalue << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tEntity Headers:" << std::endl;
	if (!entity_header().get().size())
	{
		std::cout << "(Empty)" << std::endl;
	} else
	{
		for (auto [fname, fvalue]: entity_header().get())
			std::cout << fname << ":\t" << fvalue << std::endl;
	}
	std::cout << std::endl;

	std::cout << "\tBody:" << std::endl;
	if (!body_raw())
		std::cout << "(Empty)" << std::endl;
	else
		std::cout << body_raw() << std::endl;
}
