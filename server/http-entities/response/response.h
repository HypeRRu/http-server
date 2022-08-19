#ifndef HTTP_ENTITIES_RESPONSE_RESPONSE_H
#define HTTP_ENTITIES_RESPONSE_RESPONSE_H

#include <cstddef>
#include <string>
#include <map>
#include <sstream>

#include "../common/headers/http_header.h"
#include "../common/headers/general_header.h"
#include "../common/headers/entity_header.h"
#include "headers/response_header.h"
#include "../common/http_version.h"
#include "status.h"

/* TODO: Content-Type setter/getter */

namespace http
{
	class Response
	{
	public:
		Response();
		~Response();
		/* mb need a destructor */
		void set_http_version(float version);
		const HttpVersion& get_http_version() const;

		void set_status_code(unsigned int status_code);
		void set_reason_phrase(const std::string& reason_phrase);
		const Status& get_status() const;

		void add_header(
			const std::string& field_name,
			const std::string& field_value,
			headers::HeaderType htype = headers::HeaderType::UnknownHeader
		);
		bool remove_header(
			const std::string& field_name,
			headers::HeaderType htype = headers::HeaderType::UnknownHeader
		);
		const headers::HttpHeader& get_header(headers::HeaderType htype);

		void set_content_type(const std::string& type);
		const std::string& get_content_type() const;

		void set_body(char* body, size_t body_length);
		char* get_body() const;
		size_t get_body_length() const;

		const std::stringstream& get();
		void need_update();
	protected:
		/* Status Line */
		HttpVersion version_;
		Status status_;
		/* Headers */
		headers::GeneralHeader general_header_;
		headers::ResponseHeader response_header_;
		headers::EntityHeader entity_header_;
		/* Body */
		char* response_body_;
		size_t response_body_length_;
		std::string default_content_type_;
		/* String representation */
		std::stringstream raw_;
		/* Changes flag */
		bool has_chages_;
	};
};

#endif