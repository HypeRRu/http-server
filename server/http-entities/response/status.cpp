#include "status.h"

using namespace http;

Status::Status(unsigned int code, const std::string& reason):
	status_code_{code},
	reason_phrase_{reason}
{}

void Status::set_code(unsigned int code)
{
	status_code_ = code;
}

unsigned int Status::get_code() const
{
	return status_code_;
}

void Status::set_reason_phrase(const std::string& reason)
{
	reason_phrase_ = reason;
}

const std::string& Status::get_reason_phrase() const
{
	return reason_phrase_;
}
