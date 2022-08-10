#include "method.h"

using namespace http;

Method::Method(const char* m):
	method_name_{m},
	method_{HttpMethod::UNSUPPORTED}
{
	/* method name is case-sensitive */
	if (method_name_ == "GET")
		method_ = HttpMethod::GET;
	else if (method_name_ == "POST")
		method_ = HttpMethod::POST;
	else if (method_name_ == "PUT")
		method_ = HttpMethod::PUT;
	else if (method_name_ == "DELETE")
		method_ = HttpMethod::DELETE;
	else if (method_name_ == "LINK")
		method_ = HttpMethod::LINK;
	else if (method_name_ == "UNLINK")
		method_ = HttpMethod::UNLINK;
}

const std::string& Method::get_name() const
{
	return method_name_;
}

HttpMethod Method::get() const
{
	return method_;
}
