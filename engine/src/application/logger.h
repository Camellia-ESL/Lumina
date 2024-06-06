#pragma once

/*
  This header contains a thread safe logger made my Camellia.

  Lumina Engine made by https://github.com/Camellia-ESL/
*/

#include "core/lumina_singleton.h"
#include "core/lumina_types.h"

#include <vector>
#include <string>
#include <mutex>
#include <thread>

// Logs a simple msg (msg can be various types not only string are supported)
#define LUMINA_LOG_INFO(msg) lumina::lumina_logger::get_singleton().log_info(msg)

// Logs a simple msg (msg can be various types not only string are supported)
#define LUMINA_LOG_WARNING(msg) lumina::lumina_logger::get_singleton().log_warning(msg)

// Logs a simple msg (msg can be various types not only string are supported)
#define LUMINA_LOG_ERROR(msg) lumina::lumina_logger::get_singleton().log_error(msg)

namespace lumina
{
	class LUMINA_SINGLETON_CLASS(lumina_logger)
	{
	public:

		enum class log_types_e
		{
			INFO_LOG,
			WARNING_LOG,
			ERROR_LOG
		};

		// The log type structure, contains every info about a log
		struct log_t
		{
			// The date of when the log was added
			std::string date;
			// The given log msg
			std::string msg;
			// The log type
			log_types_e type;
		};

		// Represent a null tag
		static constexpr l_cstr8 NULL_TAG = "";

	public:

		template<typename log_data_type>
		log_t& log(log_data_type log_data, log_types_e log_level);

		template<typename log_data_type>
		log_t& log_info(log_data_type msg) { return log(msg, log_types_e::INFO_LOG); }
		
		template<typename log_data_type>
		log_t& log_warning(log_data_type msg) { return log(msg, log_types_e::WARNING_LOG); }

		template<typename log_data_type>
		log_t& log_error(log_data_type msg) { return log(msg, log_types_e::ERROR_LOG); }

		const std::vector<log_t>& get_logs() const { return logs_; }

	private:

		std::vector<log_t> logs_;
		std::mutex log_safety_mutex_;

	};
}