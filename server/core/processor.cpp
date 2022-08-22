#include "processor.h"
#include <fstream>
#include "tools/mime_type_define.h"
#include <sys/stat.h>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace core;

http::Response* Processor::process_request(const http::Request& request)
{
	http::Response* response = new http::Response;

	/* http version and some headers */
	response->set_http_version(request.request_line().version().get());
	response->add_header(
		"server",
		"Hyper's HTTP/1.0 server",
		http::headers::HeaderType::ResponseHeader
	);

	/* content type definition */
	std::string path = request.request_line().uri().get_resource_path();
	size_t extension_separator = path.find_last_of(".");
	std::string content_type = "application/octet-stream";
	if (extension_separator != std::string::npos)
		content_type = tools::MimeTypeDefine::mime_from_extension(
			path.substr(extension_separator + 1)
		);

	/* file stats */
	struct stat statbuf;
	int stat_result = stat(
		request.request_line().uri().get_resource_path().c_str(),
		&statbuf
	);
	if (stat_result == -1)
	{
		/* file not found */
		response->set_status_code(404);
		response->set_reason_phrase("Not found");
		return response;
	}

	switch (request.request_line().method().get())
	{
		case http::HttpMethod::GET:
		{
			response->set_status_code(200);
			response->set_reason_phrase("OK");
			/* get last modification date */
			struct tm* last_mod = gmtime(
				&statbuf.st_mtim.tv_sec
			);
			char* date_string = new char[30];
			strftime(date_string, 30, "%a, %d %b %Y %H:%M:%S GMT", last_mod);
			std::string last_mod_date = date_string;
			delete [] date_string;
			/* check for Is-Modified-Since header */
			if (
				request.entity_header().get().find("if-modified-since") !=
				request.entity_header().get().end()
			)
			{
				/* conditional GET */
				std::string cond_last_mod = request.entity_header()
					.get().at("if-modified-since");
				http::headers::GeneralHeader gh;
				gh.set_date(cond_last_mod);
				struct tm cond_last_tm = gh.get_date_struct();
				time_t cond_last_time = mktime(&cond_last_tm);
				time_t now = time(NULL);

				if (
					cond_last_time < now /* time is valid */ &&
					difftime(statbuf.st_mtim.tv_sec, cond_last_time) <= 0
				)
				{
					/* content was not modified since given date */
					response->set_status_code(304);
					response->set_reason_phrase("Not modified");
					response->add_header(
						"last-modified", 
						last_mod_date,
						http::headers::HeaderType::EntityHeader
					);
					response->set_content_type(content_type);
					return response; 
				}
			}
			std::ifstream content_stream;
			content_stream.open(
				request.request_line().uri().get_resource_path(),
				std::ios::in | std::ios::binary
			);
			if (!content_stream.is_open())
			{
				/* error while oppening file */
				response->set_status_code(500);
				response->set_reason_phrase("Error while opening file");
			}
			/* set last modification header */
			response->add_header(
				"last-modified", 
				last_mod_date,
				http::headers::HeaderType::EntityHeader
			);
			/* get content */
			response->set_content_type(content_type);
			std::stringstream buffer;
			buffer << content_stream.rdbuf();
			response->set_body(buffer.str().c_str(), buffer.str().length());
			break;
		}
		case http::HttpMethod::HEAD:
		{
			response->set_status_code(200);
			response->set_reason_phrase("OK");
			/* get last modification date */
			struct tm* last_mod = gmtime(
				&statbuf.st_mtim.tv_sec
			);
			char* date_string = new char[30];
			strftime(date_string, 30, "%a, %d %b %Y %H:%M:%S GMT", last_mod);
			std::string last_mod_date = date_string;
			delete [] date_string;
			response->set_content_type(content_type);
			/* set last modification header */
			response->add_header(
				"last-modified", 
				last_mod_date,
				http::headers::HeaderType::EntityHeader
			);
			break;
		}
		case http::HttpMethod::POST:
			/* POST method currently not implemented */
			break;
		default:
			response->set_status_code(501);
			response->set_reason_phrase("Not implemented");
			return response;
	}

	return response;
}
