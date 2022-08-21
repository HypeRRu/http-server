#ifndef CORE_PROCESSOR_H
#define CORE_PROCESSOR_H

#include "../http-entities/request/request.h"
#include "../http-entities/response/response.h"

namespace core
{
	class Processor
	{
	public:
		static http::Response* process_request(const http::Request& request);
	};
};

#endif
