#ifndef HTTP_ENTITIES_RESPONSE_STATUS_H
#define HTTP_ENTITIES_RESPONSE_STATUS_H

#include <string>

namespace http
{
	class Status
	{
	public:
		Status(unsigned int code = 200, const std::string& reason = "");

		void set_code(unsigned int code);
		unsigned int get_code() const;

		void set_reason_phrase(const std::string& reason);
		const std::string& get_reason_phrase() const;
	protected:
		unsigned int status_code_;
		std::string reason_phrase_;
	};
};

#endif