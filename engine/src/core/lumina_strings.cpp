#include "lumina_strings.h"

namespace lumina
{
    // Random Generator Setup
    static std::random_device              rd;
    static std::mt19937                    gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

	std::wstring lumina_strings_s::str_to_wstr(const std::string& str)
	{
		return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(str);
	}

    std::string lumina_strings_s::wstr_to_str(const std::wstring& str)
    {
        return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(str);
    }
    
	std::string lumina_strings_s::generate_uuidv4()
	{
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++) {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++) {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++) {
            ss << dis(gen);
        };
        return ss.str();
	}
}