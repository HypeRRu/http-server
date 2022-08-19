#include "response.h"
#include "../common/tools/header_type_define.h"
#include <cctype>
#include <cstring>

using namespace http;

Response::Response():
	version_{1.0},
	status_{200},
	response_body_{nullptr},
	response_body_length_{0},
	default_content_type_{"text/html"},
	has_chages_{true}	
{
	entity_header_.append("content-type", default_content_type_);
}

Response::~Response()
{
	delete [] response_body_;
}

void Response::need_update()
{
	has_chages_ = true;
}

void Response::set_http_version(float version)
{
	if (version != version_.get())
	{
		need_update();
		version_.update(version);
	}
}

const HttpVersion& Response::get_http_version() const
{
	return version_;
}

void Response::set_status_code(unsigned int status_code)
{
	if (status_code != status_.get_code())
	{
		need_update();
		status_.set_code(status_code);
	}
}

void Response::set_reason_phrase(const std::string& reason_phrase)
{
	if (reason_phrase != status_.get_reason_phrase())
	{
		need_update();
		status_.set_reason_phrase(reason_phrase);
	}	
}

const Status& Response::get_status() const
{
	return status_;
}

void Response::add_header(
	const std::string& field_name,
	const std::string& field_value,
	headers::HeaderType htype
)
{
	/* to lower case */
	std::string fname;
	fname.resize(field_name.size() + 1, '\0');
	for (size_t i = 0; i < field_name.size(); ++i)
		fname[i] = tolower(field_name[i]);
	switch (htype)
	{
		case headers::HeaderType::GeneralHeader:
			general_header_.append(fname, field_value);
			break;
		case headers::HeaderType::ResponseHeader:
			response_header_.append(fname, field_value);
			break;
		case headers::HeaderType::EntityHeader:
			entity_header_.append(fname, field_value);
			break;
		case headers::HeaderType::UnknownHeader:
			if (tools::HeaderTypeDefine::is_header_general(fname))
				general_header_.append(fname, field_value);
			else if (tools::HeaderTypeDefine::is_header_response(fname))
				response_header_.append(fname, field_value);
			else
				entity_header_.append(fname, field_value);
			break;
		default:
			/* error */
			return;
	}
	need_update();
}

bool Response::remove_header(
	const std::string& field_name,
	headers::HeaderType htype
)
{
	/* to lower case */
	std::string fname;
	fname.resize(field_name.size() + 1, '\0');
	for (size_t i = 0; i < field_name.size(); ++i)
		fname[i] = tolower(field_name[i]);
	switch (htype)
	{
		case headers::HeaderType::GeneralHeader:
			need_update();
			return general_header_.remove(fname);
		case headers::HeaderType::ResponseHeader:
			need_update();
			return response_header_.remove(fname);
		case headers::HeaderType::EntityHeader:
			need_update();
			return entity_header_.remove(fname);
		case headers::HeaderType::UnknownHeader:
			if (tools::HeaderTypeDefine::is_header_general(fname))
			{
				need_update();
				return general_header_.remove(fname);
			} else if (tools::HeaderTypeDefine::is_header_response(fname))
			{
				need_update();
				return response_header_.remove(fname);
			} else
			{
				need_update();
				return entity_header_.remove(fname);
			}
			return false;
		default:
			/* error */
			return false;
	}
}

const headers::HttpHeader& Response::get_header(headers::HeaderType htype)
{
	switch (htype)
	{
		case headers::HeaderType::GeneralHeader:
			return general_header_;
		case headers::HeaderType::ResponseHeader:
			return response_header_;
		case headers::HeaderType::EntityHeader:
			return entity_header_;
		default:
			/* error */
			return response_header_;
	}
}

void Response::set_content_type(const std::string& type)
{
	if (type != get_content_type())
	{
		need_update();
		entity_header_.remove("content-type");
		entity_header_.append("content-type", type);
	}	
}

const std::string& Response::get_content_type() const
{
	if (
		entity_header_.get().find("content-type") == 
		entity_header_.get().end()
	)
		return default_content_type_;
	return entity_header_.get().at("content-type");
}

void Response::set_body(char* body, size_t body_length)
{
	if (response_body_length_ == body_length)
	{
		size_t i = 0;
		for (i = 0; i < body_length; ++i)
			if (response_body_[i] != body[i])
				break;
		if (i == body_length)
			return;
	}

	need_update();
	delete [] response_body_;
	response_body_ = new char[body_length + 1];

	strncpy(response_body_, body, body_length);
	response_body_[body_length] = '\0';

	response_body_length_ = body_length;
}

char* Response::get_body() const
{
	return response_body_;
}

size_t Response::get_body_length() const
{
	return response_body_length_;
}

const std::stringstream& Response::get()
{
	if (!has_chages_)
		return raw_;

	/* set Content Type if needed */
	if (
		entity_header_.get().find("content-type") == 
		entity_header_.get().end()
	)
		entity_header_.append("content-type", default_content_type_);
	/* remove Content Length field from header */
	if (
		entity_header_.get().find("content-length") !=
		entity_header_.get().end()
	)
		entity_header_.remove("content-length");

	raw_.str("");
	/* if version is less than 1.0, no status line and headers provided */
	if (version_.major() >= 1)
	{
		/* Status Line */
		/* HTTP version */
		raw_ << "HTTP/" << version_.major() << "." << version_.minor() << " ";
		/* Status Code */
		raw_ << status_.get_code() << " ";
		/* Reason Phrase */
		raw_ << status_.get_reason_phrase();
		/* CRLF */
		raw_ << "\r\n";

		/* Headers */
		/* General Header */
		if (general_header_.get_date().size())
			raw_ << "date: " << general_header_.get_date() << "\r\n";
		for (const auto& pragma: general_header_.get_pragma_directives())
			raw_ << "pragma: " << pragma << "\r\n";
		/* Response Header */
		for (const auto& field: response_header_.get())
			raw_ << field.first << ": " << field.second << "\r\n";
		/* Entity Header */
		for (const auto& field: entity_header_.get())
			raw_ << field.first << ": " << field.second << "\r\n";

		/* Content Length */
		raw_ << "content-length: " << response_body_length_ << "\r\n";
		/* CRLF */
		if (response_body_length_)
			raw_ << "\r\n";
	}
	/* Body */
	if (response_body_)
		raw_ << response_body_;

	has_chages_ = false;
	return raw_;
}
