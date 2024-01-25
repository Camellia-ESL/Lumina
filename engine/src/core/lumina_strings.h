#pragma once

#include <string>
#include <locale>
#include <codecvt>
#include <random>
#include <sstream>

namespace lumina
{
	// An internal tool class to work with strings in a easier way
	class lumina_strings_s
	{
	public:

		// Converts a string in a wide string (utf-8 to utf-16)
		static std::wstring str_to_wstr(const std::string& str);

		// Generate's a uuidv4 string
		static std::string generate_uuidv4();

	};
}